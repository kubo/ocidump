require 'erb'
require 'yaml'

class ArgDef
  attr_reader :type
  attr_reader :name
  attr_reader :fmt
  attr_reader :fmt_arg
  attr_reader :local_var

  def initialize(arg, idx)
    @type, @fmt, *@args = arg
    @fmt_arg = @args[0] if @fmt.is_a? String
    if idx == 0
      @name = 'ret'
    else
      @name = @type.gsub(/\[\]/, '')
      /(\w+)\s*$/ =~ @name
      /\(\*(\w+)\)/ =~ @name if $1.nil?
      @name = $1
    end
    @fmt.gsub!(/[A-Z0-9_]+_FMT/) {|fmt| '%" ' + fmt + ' "'} if @fmt.is_a? String
    @args.shift if @args[0].is_a? Symbol
    @args.unshift(@name)
  end

  def to_c_code(fmt_arg)
    case @fmt
    when String
      "ocidump_log(0, \"#{@fmt}\", #{fmt_arg})"
    when :pointer_to_pointer, :array_of_pointer, :pointer_to_ocihandle
      "ocidump_%s((const void **)%s)" % [@fmt, @args.join(', ')]
    when :ocihandle
      case @args.size
      when 2
        "ocidump_ocihandle(%s, 0, 0)" % [@args.join(', ')]
      when 3
        "ocidump_ocihandle(%s, 0)" % [@args.join(', ')]
      when 4
        "ocidump_ocihandle(%s)" % [@args.join(', ')]
      end
    when :function_pointer
      "ocidump_function_pointer((void*)%s)" % [@args[0]]
    when Symbol
      "ocidump_%s(%s)" % [@fmt, @args.join(', ')]
    end
  end
end

class FuncDef
  attr_reader :name
  attr_reader :args
  attr_reader :ret
  attr_reader :before_call
  attr_reader :after_call

  attr_reader :fmt_args
  attr_reader :local_vars
  attr_reader :hide_vars
  attr_reader :cleanups
  attr_reader :logging_args
  attr_reader :logging_ret

  def initialize(key, val)
    @name = key
    @ret = ArgDef.new(val[:ret], 0)
    @args = []
    if val[:args]
      val[:args].each_with_index do |arg, idx|
        args << ArgDef.new(arg, idx + 1)
      end
    end
    @before_call = val[:before_call]
    @after_call = val[:after_call]

    @fmt_args = @args.collect {|arg| arg.fmt_arg}
    @fmt_args << @ret.fmt_arg if @ret.type != 'void'

    @local_vars = []
    @cleanups = []
    fmt_args.collect! do |fmt_arg|
      if fmt_arg.nil?
        nil
      else
        fmt_arg.gsub(/@(\w+)_BUF@/) do |match|
          var_name = "buf" + (local_vars.length + 1).to_s
          @local_vars << "char #{var_name}[OCIDUMP_#{$1}_BUF_SIZE]"
          var_name
        end.gsub(/@BUF_PTR@/) do |match|
          var_name = "buf" + (local_vars.length + 1).to_s
          @local_vars << "char *#{var_name} = NULL"
          cleanups << "free(#{var_name})"
          '&' + var_name
        end
      end
    end
    @local_vars.unshift(@ret.type + " ret") if @ret.type != 'void'

    @hide_vars = []
    @logging_args = []
    @args.each_with_index do |arg, idx|
      if arg.fmt == '\"%.*s\"'
        len, str = arg.fmt_arg.gsub(/\(.*?\)/, '').split(/\s*,\s*/)
        @hide_vars << len + ' = 6'
        @hide_vars << str + ' = (OraText*)"hidden"'
      end
      @logging_args << arg.to_c_code(@fmt_args[idx])
    end
    @logging_ret = @ret.to_c_code(@fmt_args[@args.length])
  end
end

def fix_yaml_data(data)
  case data
  when Hash
    data.each do |key, val|
      data[key] = fix_yaml_data(val)
    end
  when Array
    data.each_with_index do |val, idx|
      data[idx] = fix_yaml_data(val)
    end
  when /^:/ # a string which starts with ':'
    data[1..-1].intern # convert it to symbol.
  else
    data
  end
end

def load_yaml(filename)
  fix_yaml_data(YAML.load(open(File.dirname(__FILE__) + '/' + filename)))
end

def get_dlsym_ver
  # Guess the architecture from a compiled object file.
  open("oranumber_util.o", "r") do |f|
    return nil if f.read(4) != "\177ELF" # magic
    f.seek(18, IO::SEEK_SET)
    case f.read(2).unpack('v')[0] # architecture
    when 3 # i386
      return "GLIBC_2.0"
    when 62 # x86_64
      return "GLIBC_2.2.5"
    end
  end
  nil
rescue
  nil
end

def make_ocifunc_c
  funcs = []
  load_yaml('ocifunc.yml').each do |key, val|
    funcs << FuncDef.new(key, val)
  end
  funcs.sort! do |a, b|
    a.name <=> b.name
  end

  header_comment = <<EOS.chomp
/*
 * This file was created by #{File.basename(__FILE__)}
 * Don't edit this file manually.
 */
EOS
#'

  erb = ERB.new(open(File.dirname(__FILE__) + '/ocifunc.c.tmpl').read)
  open('ocifunc.c', 'w') do |fd|
    fd.write(erb.result(binding))
  end
  open('ocidump.map', 'w') do |fd|
    dlsym_ver = get_dlsym_ver()
    fd.write <<EOS if dlsym_ver
#{dlsym_ver} {
	dlsym;
};

EOS

    fd.write <<EOS
ocidump {
global:
EOS
    funcs.each do |func|
      fd.write <<EOS
	#{func.name};
EOS
    end

    fd.write <<EOS if dlsym_ver.nil?
	dlsym;
EOS

    fd.write <<EOS
local:
	*;
};
EOS
  end
end

class TypeDef
  attr_reader :name
  attr_reader :type
  attr_reader :datatype
  attr_reader :format
  attr_reader :values

  def initialize(key, val)
    @name = key
    @type = val[:type]
    @datatype = val[:datatype]
    @format = val[:format]
    @values = val[:values]
  end
end

def make_ocidefs_c
  typedefs = []
  htype_values = nil
  load_yaml('ocidefs.yml').each do |key, val|
    typedefs << TypeDef.new(key, val)
    htype_values = val[:values] if key == 'htype'
  end
  typedefs.sort! do |a, b|
    a.name <=> b.name
  end

  header_comment = <<EOS.chomp
/*
 * This file was created by #{File.basename(__FILE__)}
 * Don't edit this file manually.
 */
EOS
#'

  open('ocidefs.h', 'w') do |fd|
    fd.write <<EOS
/* This file was generaed by mkocifunc.rb */
#ifndef OCIDEFS_H
#define OCIDEFS_H 1

/* opaque datatypes */
EOS
    typedefs.each do |typedef|
      if typedef.type == :opaque
        fd.write <<EOS
typedef struct #{typedef.name} #{typedef.name};
EOS
      end
    end

    typedefs.each do |typedef|
      if typedef.type == :enum
        fd.write <<EOS

enum #{typedef.name} {
EOS
        typedef.values.each do |val|
          fd.write <<EOS
    #{val[1]} = #{val[0]},
EOS
        end
        fd.write <<EOS
};
typedef enum #{typedef.name} #{typedef.name};
EOS
      end
    end

    htype_values.each do |val|
        fd.write <<EOS
#define #{val[1]} #{val[0]}
EOS
    end

    typedefs.each do |typedef|
      next unless typedef.values
      if typedef.type == :enum
        arg = "enum #{typedef.name} val"
      else
        arg = "#{typedef.datatype} val"
      end
      fd.write <<EOS

int ocidump_#{typedef.name}(#{arg});
EOS
    end
    fd.write <<EOS

#endif
EOS
  end

  open('ocidefs.c', 'w') do |fd|
    fd.write <<EOS
/* This file was generaed by mkocifunc.rb */
#include <stdio.h>
#include "ocidump.h"
#include "ocidefs.h"
EOS
    typedefs.each do |typedef|
      next unless typedef.values
      if typedef.type == :enum
        arg = "enum #{typedef.name} val"
      else
        arg = "#{typedef.datatype} val"
      end
      fd.write <<EOS

int ocidump_#{typedef.name}(#{arg})
{
    const char *str = NULL;
EOS
      if typedef.format
        fd.write <<EOS
    char buf[OCIDUMP_SHORT_BUF_SIZE];
EOS
      fd.write <<EOS

    switch (val) {
EOS
      end
      typedef.values.each do |val|
        fd.write <<EOS
    case #{val[0]}: str = "#{val[1]}"; break;
EOS
      end
        fd.write <<EOS
    }
    if (str == NULL) {
EOS
      if typedef.format
        fd.write <<EOS
        sprintf(buf, "#{typedef.format}", val);
        str = buf;
EOS
      else
        fd.write <<EOS
        return -1;
EOS
      end
      fd.write <<EOS
    }
    ocidump_puts(str);
    return 0;
}
EOS
    end
  end
end

class AttrDef
  attr_reader :name
  attr_reader :value
  attr_reader :read_func
  attr_reader :write_func

  def initialize(value, name, mode, type)
    @value = value
    @name = name
    @read_func = nil
    @write_func = nil
    case mode
    when 'READ'
      read_type = type
    when 'WRITE'
      write_type = type
    when 'READ/WRITE'
      if /\// =~ type.to_s
        read_type = $`
        write_type = $'
      else
        read_type = write_type = type
      end
    else
      raise "Unknown read/write mode: #{mode}"
    end
    @read_func = type_to_func(read_type, true)
    @write_func = type_to_func(write_type, false)
  end

  private

  def type_to_func(type, is_read)
    case type
    when "ub1*"
      "ocidump_pointer_to_ub1(val)"
    when "ub1*(csfrm)"
      "ocidump_pointer_to_SQLCS(val)"
    when "ub1*(ptype)"
      "ocidump_pointer_to_OCI_PTYPE(val)"
    when "ub1*(array)"
      "ocidump_array_of_ub1(val, sizep ? *sizep : 0, status)"
    when "sb1*"
      "ocidump_pointer_to_sb1(val)"
    when "ub2*"
      "ocidump_pointer_to_ub2(val)"
    when "ub2*(sqlfncode)"
      "ocidump_pointer_to_SQLFNCODE(val)"
    when "sb2*"
      "ocidump_pointer_to_sb2(val)"
    when "ub4*"
      "ocidump_pointer_to_ub4(val)"
    when "sb4*"
      "ocidump_pointer_to_sb4(val)"
    when "ub8*"
      "ocidump_pointer_to_ub8(val)"
    when "sb8*"
      "ocidump_pointer_to_sb8(val)"
    when "word*"
      "ocidump_pointer_to_sword(val)"
    when "ub1* or sb2*"
      "ocidump_pointer_to_attr_precision(val)"
    when "boolean*"
      "ocidump_pointer_to_boolean(val)"
    when "OCIDuration*"
      "ocidump_pointer_to_OCIDuration(val)"
    when "OCITypeCode*"
      "ocidump_pointer_to_OCITypeCode(val)"
    when "OCITypeEncap*"
      "ocidump_pointer_to_OCITypeEncap(val)"
    when "OCITypeParamMode*"
      "ocidump_pointer_to_OCITypeParamMode(val)"
    when "oratext*"
      if is_read
        "ocidump_string_with_length(val, status ? 0 : (sizep ? *sizep : 0))"
      else
        "ocidump_string_with_length(val, size)"
      end
    when "oratext**"
      if is_read
        "ocidump_pointer_to_string_with_length(val, sizep, status)"
      else
        # OCI_ATTR_INITIAL_CLIENT_ROLES
        "ocidump_array_of_null_terminated_string(val, size, status)"
      end
    when "OCIServer*", "OCISession*", "OCIAuthInfo*", "OCIRaw*", "OCIRowid*", "OCIColl*"
      "ocidump_pointer(val)"
    when "OCIServer**", "OCISession**", "OCIEnv**", "void**", "OCIColl**", "OCIRef**"
      "ocidump_pointer_to_pointer(val)"
    when :function_pointer, "OCIEventCallback", "OCIFocbkStruct*"
      "ocidump_function_pointer(val)"
    when "oranumber*"
      if is_read
        "ocidump_pointer_to_raw_OCINumber(val, status ? 0 : *sizep, status)"
      else
        "ocidump_pointer_to_raw_OCINumber(val, size, 0)"
      end
    else
      "fprintf(ocidump_logfp, \"%p(unsupported:%s)\", val, \"#{type}\")"
    end
  end
end

def make_ociattr_c
  htypes = []
  load_yaml('ociattr.yml').each do |htype, attrs|
    attrdefs = []
    attrs.each do |attr|
      attrdefs << AttrDef.new(*attr)
    end
    htypes << [htype, attrdefs]
  end
  htypes.sort! do |a, b|
    a[0] <=> b[0]
  end

  open('ociattr.c', 'w') do |fd|
    fd.write <<EOS
/* This file was generaed by mkocifunc.rb */
#include <stdio.h>
#include "ocidump.h"

void ocidump_attrtype(ub4 attrtype, ub4 htype)
{
    const char *str = NULL;
    char buf[OCIDUMP_SHORT_BUF_SIZE];

    switch (htype) {
EOS
    htypes.each do |htype, attrdefs|
      fd.write <<EOS
    case #{htype}:
        switch (attrtype) {
EOS
      attrdefs.each do |attrdef|
      fd.write <<EOS
        case #{attrdef.value}: str = "#{attrdef.name}"; break;
EOS
      end
      fd.write <<EOS
        }
        break;
EOS
    end
    fd.write <<EOS
    }
    if (str == NULL) {
        sprintf(buf, "unknown(%u)", attrtype);
        str = buf;
    }
    ocidump_puts(str);
}

void ocidump_read_attrval(dvoid *val, ub4 htype, ub4 attrtype, ub4 *sizep, sword status)
{
    switch (htype) {
EOS
    htypes.each do |htype, attrdefs|
      fd.write <<EOS
    case #{htype}:
        switch (attrtype) {
EOS
      attrdefs.each do |attrdef|
      fd.write <<EOS if attrdef.read_func
        case #{attrdef.value}: #{attrdef.read_func}; return;
EOS
      end
      fd.write <<EOS
        }
        break;
EOS
    end
    fd.write <<EOS
    }
    ocidump_pointer(val);
}
EOS
    fd.write <<EOS
void ocidump_write_attrval(dvoid *val, ub4 htype, ub4 attrtype, ub4 size)
{
    sword status = 0;
    switch (htype) {
EOS
    htypes.each do |htype, attrdefs|
      fd.write <<EOS
    case #{htype}:
        switch (attrtype) {
EOS
      attrdefs.each do |attrdef|
      fd.write <<EOS if attrdef.write_func
        case #{attrdef.value}: #{attrdef.write_func}; return;
EOS
      end
      fd.write <<EOS
        }
        break;
EOS
    end
    fd.write <<EOS
    }
    ocidump_pointer(val);
}
EOS
  end
end

def check_defs
  typedefs = []
  load_yaml('ocidefs.yml').each do |key, val|
    typedefs << TypeDef.new(key, val)
  end
  typedefs.sort! do |a, b|
    a.name <=> b.name
  end
  attrdefs = []
  load_yaml('ociattr.yml').each do |htype, attrs|
    attrs.each do |attr|
      attrdefs << AttrDef.new(*attr)
    end
  end

  open('check_defs.c', 'w') do |fd|
    fd.write <<EOS
/* Verify values in ocidefs.yml */
/* This file was generaed by mkocifunc.rb */
#include <stdio.h>
#include <ociap.h>
#include <orid.h>
#include <orl.h>
#include <oro.h>
#include <ort.h>

struct {
    int expected_val;
    int actual_val;
    const char *name;
} test_values[] = {
EOS
    typedefs.each do |typedef|
      next unless typedef.values
      typedef.values.each do |val|
        val[1].split(/ or /).each do |name|
        fd.write <<EOS
    {#{val[0]}, #{name}, "#{name}"},
EOS
        end
      end
    end
    attrdefs.each do |attrdef|
      fd.write <<EOS
    {#{attrdef.value}, #{attrdef.name}, "#{attrdef.name}"},
EOS
    end
    fd.write <<EOS
};
#define NUM_TEST_VALUES (sizeof(test_values)/sizeof(test_values[0]))

int main()
{
    int n, err = 0;
    for (n = 0; n < NUM_TEST_VALUES; n++) {
        if (test_values[n].expected_val != test_values[n].actual_val) {
            err++;
            printf("%s's value is expected %d but %d\\n",
                   test_values[n].name,
                   test_values[n].expected_val,
                   test_values[n].actual_val);
        }
    }
    if (err == 0) {
        printf("all %d tests are passed.\\n", n);
    } else {
        printf("%d of %d tests are failed.\\n", err, n);
    }
    return err ? 1 : 0;
}
EOS
  end
end

if $0 == __FILE__
  if ARGV[0] == 'check_defs'
    check_defs
  else
    make_ocifunc_c
    make_ocidefs_c
    make_ociattr_c
  end
end
