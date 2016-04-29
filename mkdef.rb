require 'yaml'
require 'open3'

if ARGV.size == 0
  puts("Usage: ruby mkdef.rb FULL_PATH_OF_OCI_DLL")
  exit(1)
end

file = ARGV[0]

unless File.exists?(file)
  puts("No such file: #{file}")
  exit(1)
end

ocidump_funcs = YAML.load(open(File.dirname(__FILE__) + '/ocifunc.yml'))

funcs = []
output = []
Open3.popen3("dumpbin /EXPORTS \"#{file}\"") do |i, o, e, w|
  o.each do |line|
    output << line
    funcs << $1 if line =~ /\d+\s+\h+\s+\h+\s+(\S+)/
  end
  if (!w.value.success?) || funcs.empty?
    puts(<<EOS)
Failed to get exported functions.

Output of the dumpbin command:
------------------------------
EOS
    puts(output.join)
    exit(1)
  end
end

if funcs.include?('ocidumpInit')
  puts("ERROR: The specified file is ocidump.dll or a copy of ocidump.dll: #{file}")
  exit(1)
end

unless funcs.include?('OCIEnvCreate')
  puts("ERROR: The specified file is not oci.dll: #{file}")
  exit(1)
end

open('oci-orig.def', 'w') do |f|
  f.puts("EXPORTS")
  funcs.each do |func|
    unless ocidump_funcs[func]
      f.puts("  #{func}")
    end
  end
end

open('ocidump.def', 'w') do |f|
  f.puts("EXPORTS")
  funcs.each do |func|
    if ocidump_funcs[func]
      f.puts("  #{func}")
    else
      f.puts("  #{func} = OCI-ORIG.#{func}")
    end
  end
end
puts("oci-orig.def and ocidump.def are created from #{file}.")
exit(0)
