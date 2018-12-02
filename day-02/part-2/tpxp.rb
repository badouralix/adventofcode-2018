def run(s)
  s.each_with_index do |l1, j|
    s.slice(0,j).each do |l2|
      r1 = l1.chars.map &:ord
      r2 = l2.chars.map &:ord
      r = r1.each_with_index.map { |v, i| v - r2[i] }
      # Exactly one distinct character
      d = nil
      r.each_with_index do |v,i|
        if v != 0
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
