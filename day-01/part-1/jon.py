import sys


class Submission():

    def run(self, s):
        return eval(s.replace("\n", ""))

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
