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

open('ocidump.def', 'w') do |f|
  f.puts("EXPORTS")
  funcs.each do |func|
    f.puts(func)
  end
end
puts("ocidump.def is created from #{file}.")
exit(0)
