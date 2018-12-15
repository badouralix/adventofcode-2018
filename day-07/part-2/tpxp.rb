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

  # The time is incremented by 1 tick at the beginning, tasks start at t=0
  time = -1
  processed = 0
  while processed < reqs.size
    # Make on simulation turn
    time += 1
    remaining = remaining.map {|i| i-1}
    remaining.each_with_index do |t, i|
      next if t > 0
      # Else, give him another task!
      step = tasks[i]
      reqs.each_key do |k|
        next unless reqs[k].include? step
        reqs[k].delete step
        free.push k if reqs[k].size == 0
      end unless step == nil
      free.sort!
      step = free.shift
      if step != nil
        tasks[i] = step
        remaining[i] = step.ord - 4 # -64 + 60
        processed += 1
      end
    end
  end
  time += remaining.max
  time
end

starting = Process.clock_gettime(Process::CLOCK_MONOTONIC)
answer = run(ARGV[0].lines)
elapsed = (Process.clock_gettime(Process::CLOCK_MONOTONIC) - starting) * 1000

puts "_duration:#{elapsed}\n#{answer}"
