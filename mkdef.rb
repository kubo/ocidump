require 'open3'

file = ARGV[0]

funcs = []
Open3.popen3("dumpbin /EXPORTS \"#{file}\"") do |i, o, e, w|
  o.each do |line|
    funcs << $1 if line =~ /\d+\s+\h+\s+\h+\s+(\S+)/
  end
end

open('ocidump.def', 'w') do |f|
  f.write("EXPORTS\n")
  funcs.each do |func|
    f.write(func)
    f.write("\n");
  end
end


