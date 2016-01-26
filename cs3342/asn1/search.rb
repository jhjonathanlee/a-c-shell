if ARGV.length != 3
  put "Usage: ruby search.rb string src dest"
end

str = ARGV[0]
src = ARGV[1]
dest = ARGV[2]

arr = []

File.foreach(src) do |line|
  if line.include? str
    arr << line
  end
end

#arr.each { |x| puts x }

File.new(dest)
File.open(dest, "w") do |f|
  arr.each { |x| f.write(x) }
  f.close
end

print File.read(dest)
