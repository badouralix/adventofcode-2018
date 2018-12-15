def run(s)
  pos_x = Array.new (s.size)
  pos_y = Array.new (s.size)
  s.each_with_index do |line, i|
    x,y = line.split(", ").map &:to_i
    pos_x[i] = x
    pos_y[i] = y
  end

  def distance(a,b)
    (a[0] - b[0]).abs + (a[1] - b[1]).abs
  end

  map = Array.new (pos_x.max) { Array.new(pos_y.max) {0}}
  sizes = Array.new (s.size) {0}
  map.size.times do |x|
    map[x].size.times do |y|
      # Find the closest point everytime
      res, _i = pos_x.size.times.inject([0, 9999]) do |cur, j|
        challenger = distance([pos_x[j], pos_y[j]], [x,y])
        next ['.', challenger] if cur[1] == challenger
        cur[1] < challenger ? cur:[j, challenger]
      end
      map[x][y] = res
      next if res == '.'
      sizes[res]+= 1 if sizes[res] != nil
      sizes[res] = nil if [0, map.size - 1].include? x
      sizes[res] = nil if [0, map[x].size - 1].include? y
    end
  end
  sizes.compact.max
end


starting = Process.clock_gettime(Process::CLOCK_MONOTONIC)
answer = run(ARGV[0].lines)
elapsed = (Process.clock_gettime(Process::CLOCK_MONOTONIC) - starting) * 1000

puts "_duration:#{elapsed}\n#{answer}"
