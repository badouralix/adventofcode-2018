def run(s)
  s.lines.map(&:to_i).reduce :+
end

puts run(ARGV[0])
