def run(s)
  field = Array.new(1000) { Array.new(1000, 0) }
  overlapping = 0
  s.lines.each do |v|
    x, y, w, h = /#\d+ @ (\d+),(\d+): (\d+)x(\d+)/.match(v).captures.map &:to_i
    w.times do |dx|
      h.times do |dy|
        overlapping += 1 if field[x+dx][y+dy] == 1
        field[x+dx][y+dy] += 1
      end
    end
  end
  overlapping
end

puts run(ARGV[0])
