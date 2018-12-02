puts File.readlines(ARGV[0]).map(&:to_i).reduce :+
