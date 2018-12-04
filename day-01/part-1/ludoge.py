import sys


class Submission():

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        return sum((int(line) for line in s.splitlines()))

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
