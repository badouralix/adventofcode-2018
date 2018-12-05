def run_p1(s)
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

def run(s)
  best = nil
  ('a'..'z').each do |c|
    r = Regexp.new "#{c}|#{c.swapcase}"
    score = run_p1 s.gsub r,""
    if best == nil or score < best
      best = score
    end
  end
  best
end

puts run(ARGV[0])
