require 'erb'
require 'yaml'

class ArgDef
  attr_reader :type
  attr_reader :name
  attr_reader :fmt
  attr_reader :fmt_arg

  def initialize(arg)
    @type, @fmt, @fmt_arg = arg
    /(\w+)\s*$/ =~ @type
    /\(\*(\w+)\)/ =~ @type if $1.nil?
    @name = $1
  end
end

class FuncDef
  attr_reader :name
  attr_reader :args
  attr_reader :ret

  def initialize(key, val)
    @name = key
    @ret = ArgDef.new(val[:ret])
    @args = val[:args].collect do |arg|
      ArgDef.new(arg)
    end
  end
end

def mkstub
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

if $0 == __FILE__
  mkstub
end
