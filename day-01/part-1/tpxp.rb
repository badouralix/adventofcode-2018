def run(s)
  s.lines.map(&:to_i).sum
end

puts run(ARGV[0])
