def run(s)
  field = Array.new(1000) { Array.new(1000, -1) }
  overlapping = Array.new(s.size) {false}
  s.each_with_index do |v,i|
    x, y, w, h = /#\d+ @ (\d+),(\d+): (\d+)x(\d+)/.match(v).captures.map &:to_i
    w.times do |dx|
      h.times do |dy|
        if field[x+dx][y+dy] != -1
          overlapping[i] = true
          overlapping[field[x+dx][y+dy]] = true
        end
        field[x+dx][y+dy] = i
      end
    end
  end
  overlapping.index(false) + 1
end

puts run(ARGV[0].lines)
