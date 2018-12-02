def run(s)
  s.each_with_index do |l1, j|
    s.slice(0,j).each do |l2|
      # We want Exactly one distinct character
      d = nil
      l1.size.times do |i|
        if l1[i] != l2[i]
          if d != nil
            d = nil
            break
          end
          d = i
        end
      end

      if d != nil
        return l1.slice(0, d) + l1.slice(d+1, l1.size)
      end
    end
  end
end

puts run(ARGV[0].lines)
