def run(s)
  a = []
  s.each_char do |c|
    if c == a[-1]
      a.pop
    else
      a.push c.swapcase
    end
  end
  a.size
end

puts run(ARGV[0])
