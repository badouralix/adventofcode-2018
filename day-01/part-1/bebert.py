import sys


class Submission():

    def run(self, s):
        a = 0
        for line in s.splitlines():
            x = int(line.strip())
            a += x

        return a

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
