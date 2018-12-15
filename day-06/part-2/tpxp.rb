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
  size = 0
  map.size.times do |x|
    map[x].size.times do |y|
      # Find the closest point everytime
      d = pos_x.size.times.inject(0) do |s, i|
        s +=  distance([x,y], [pos_x[i], pos_y[i]])
      end
      size += 1 if d < 10000
    end
  end
  size
end


starting = Process.clock_gettime(Process::CLOCK_MONOTONIC)
answer = run(ARGV[0].lines)
elapsed = (Process.clock_gettime(Process::CLOCK_MONOTONIC) - starting) * 1000

puts "_duration:#{elapsed}\n#{answer}"
