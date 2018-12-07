def run(s)
  s.sort!
  guards = Hash.new { Array.new(60) {0} }
  sleep_start = nil
  g = nil

  s.each do |l|
    min = l[15..16].to_i
    case l[19]
    when "f"
      sleep_start = min
    when "w"
      t = min - sleep_start

      # Make sure we initialize the hash value... "Ruby is a fun language"
      guards[g] = guards[g]

      (sleep_start..min-1).each do |i|
        guards[g][i] += 1
      end
    else # "G"
      g = l[26..50].to_i
    end
  end

  most_sleeping = guards.max_by {|k,v| v.sum}
  most_sleeping[0] * most_sleeping[1].index(most_sleeping[1].max)
end

puts run(ARGV[0].lines)
