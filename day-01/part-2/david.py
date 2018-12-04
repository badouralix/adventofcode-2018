import sys

class Submission():

    def run(self, s):
        seen = set()
        x = 0
        while True:
            for line in s.split("\n"):
                n = int(line[1:])
                x += (n if line[0] == "+" else -n)
                if x in seen:
                    return x
                seen.add(x)

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
