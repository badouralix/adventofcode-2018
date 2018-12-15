def run(s)
  reqs = Hash.new {Array.new}
  s.each do |line|
    # Create the steps
    reqs[line[5]] = reqs[line[5]]
    reqs[line[36]] = reqs[line[36]]
    reqs[line[36]].push line[5]
  end
  free = Array.new
  reqs.each do |k,v|
    free.push k if v.size == 0
  end
  res = ""
  while free.size > 0
    free.sort!
    step = free.shift
    res += step
    reqs.each_key do |k|
      next unless reqs[k].include? step
      reqs[k].delete step
      free.push k if reqs[k].size == 0
    end
  end
  res
end


starting = Process.clock_gettime(Process::CLOCK_MONOTONIC)
answer = run(ARGV[0].lines)
elapsed = (Process.clock_gettime(Process::CLOCK_MONOTONIC) - starting) * 1000

puts "_duration:#{elapsed}\n#{answer}"
