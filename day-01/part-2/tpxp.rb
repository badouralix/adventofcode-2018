def run(s)
  visited = Hash.new {false}
  f = 0
  vals = s.lines.map(&:to_i)
  while true do
    vals.each do |i|
      f+=i
      return f if visited[f]
      visited[f] = true
    end
  end
end

puts run(ARGV[0])
