import sys
from itertools import cycle

class Submission():

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here

        # 0 could be the answer
        frequencies = {0}
        current_freq = 0

        # Avoid parsing/casting every time we loop
        freq_changes = [int(freq_change) for freq_change in s.splitlines()]

        while True:
            for freq_change in freq_changes:
                current_freq += freq_change
                if current_freq in frequencies:
                    return current_freq
                frequencies.add(current_freq)

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
