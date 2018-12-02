def run(s)
  doubles = 0
  triples = 0

  s.lines do |l|
    prev = nil
    d = 0
    t = 0
    l.chars do |c|
      d = 1 if l.count(c) == 2
      t = 1 if l.count(c) == 3
    end
    doubles += d
    triples += t
  end
  doubles * triples
end

puts run(ARGV[0])
