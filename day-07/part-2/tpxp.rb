def run(s)
  reqs = Hash.new {Array.new}
  s.each do |line|
    # Create the steps
    reqs[line[5]] = reqs[line[5]]
    reqs[line[36]] = reqs[line[36]]
    reqs[line[36]].push line[5]
  end
  free = Array.new
  tasks = Array.new (5)
  remaining = Array.new (5) {0}
  reqs.each do |k,v|
    free.push k if v.size == 0
  end

  time = 0
  processed = 0
  while processed < reqs.size
    # Make on simulation turn
    interval = remaining.reject {|v| v <= 0 }.min || 0
    time += interval
    remaining = remaining.map {|i| i-interval}
    # Free tasks that can now be completed
    remaining.each_with_index do |t, i|
      next if t > 0
      step = tasks[i]
      reqs.each_key do |k|
        next unless reqs[k].include? step
        reqs[k].delete step
        free.push k if reqs[k].size == 0
      end unless step == nil
    end
    free.sort!
    # Give tasks to idle workers now
    remaining.each_with_index do |t, i|
      next if t > 0
      step = free.shift
      if step != nil
        tasks[i] = step
        remaining[i] = step.ord - 4 # -64 + 60
        processed += 1
      end
    end
  end
  time + remaining.max
end

starting = Process.clock_gettime(Process::CLOCK_MONOTONIC)
answer = run(ARGV[0].lines)
elapsed = (Process.clock_gettime(Process::CLOCK_MONOTONIC) - starting) * 1000

puts "_duration:#{elapsed}\n#{answer}"
