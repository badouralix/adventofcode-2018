import sys


class Submission():

    def run(self, s):
        freqs = set([0])
        freq = 0
        l = s.split('\n')
        while True:
            for i in l:
                freq += int(i)
                if freq in freqs:
                    return freq
                freqs.add(freq)

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
