import sys


class Submission():

    def run(self, s):
        a = 0
        seen = set()
        passes = 0
        int_lines = [int(line.strip()) for line in s.splitlines() if line.strip()]
        while passes < 10000:  # avoid infinite loop just in case
            passes += 1
            for x in int_lines:
                a += x
                if a in seen:
                    return a
                seen.add(a)
        print("Error: bebert/day1/part2 never found a solution")

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
