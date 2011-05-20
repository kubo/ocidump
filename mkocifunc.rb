require 'erb'
require 'yaml'

class ArgDef
  attr_reader :type
  attr_reader :name
  attr_reader :fmt
  attr_reader :fmt_arg

  def initialize(arg)
    @type, @fmt, @fmt_arg = arg
    @name = @type.gsub(/\[\]/, '')
    /(\w+)\s*$/ =~ @name
    /\(\*(\w+)\)/ =~ @name if $1.nil?
    @name = $1
  end
end

class FuncDef
  attr_reader :name
  attr_reader :args
  attr_reader :ret
  attr_reader :before_call
  attr_reader :after_call

  def initialize(key, val)
    @name = key
    @ret = ArgDef.new(val[:ret])
    @args = val[:args].collect do |arg|
      ArgDef.new(arg)
    end
    @before_call = val[:before_call]
    @after_call = val[:after_call]
  end
end

def make_ocifunc_c
  funcs = []
  YAML.load(open(File.dirname(__FILE__) + '/ocifunc.yml')).each do |key, val|
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
  YAML.load(open(File.dirname(__FILE__) + '/ocidefs.yml')).each do |key, val|
    typedefs << TypeDef.new(key, val)
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

    typedefs.each do |typedef|
      next unless typedef.values
      if typedef.type == :enum
        arg = "enum #{typedef.name} val"
      else
        arg = "#{typedef.datatype} val"
      end
      arg += ", char *buf" if typedef.format
      fd.write <<EOS

const char *ocidump_#{typedef.name}2name(#{arg});
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
EOS
    typedefs.each do |typedef|
      next unless typedef.values
      if typedef.type == :enum
        arg = "enum #{typedef.name} val"
      else
        arg = "#{typedef.datatype} val"
      end
      arg += ", char *buf" if typedef.format
      fd.write <<EOS

const char *ocidump_#{typedef.name}2name(#{arg})
{
    switch (val) {
EOS
      typedef.values.each do |val|
        fd.write <<EOS
    case #{val[0]}: return "#{val[1]}";
EOS
      end
      if typedef.format
        fd.write <<EOS
    }
    sprintf(buf, "#{typedef.format}", val);
    return buf;
}
EOS
      else
        fd.write <<EOS
    }
    return NULL;
}
EOS
      end
    end
  end
end

def check_defs
  typedefs = []
  YAML.load(open(File.dirname(__FILE__) + '/ocidefs.yml')).each do |key, val|
    typedefs << TypeDef.new(key, val)
  end
  typedefs.sort! do |a, b|
    a.name <=> b.name
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
  end
end
