visited = Hash.new {false}
f = 0
vals = File.readlines(ARGV[0]).map(&:to_i)
while true do
  vals.each do |i|
    f+=i
    if visited[f]
      puts f
      exit
    end
    visited[f] = true
  end
end