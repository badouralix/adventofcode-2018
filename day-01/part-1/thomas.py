import sys

class Submission():

    def run(self, s):
        return sum([int(i) for i in s.split('\n')])

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
