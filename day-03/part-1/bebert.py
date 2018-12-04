import sys


class Submission():

    def run(self, s):
        data = []
        for line in s.splitlines():
            i, x = line.split(" @ ")
            _id = i.strip("#")
            p, s = x.split(": ")
            pw, ph = p.split(",")
            w, h = s.split("x")
            data.append((int(pw), int(ph), int(w), int(h)))

        max_w = max(pw + w for (pw, ph, w, h) in data)
        max_h = max(ph + h for (pw, ph, w, h) in data)

        matrix = [None] * (max_h + 1)
        for i in range(max_h + 1):
            matrix[i] = [0] * (max_w + 1)

        for (pw, ph, w, h) in data:
            for i in range(ph + 1, ph + h + 1):
                for j in range(pw + 1, pw + w + 1):
                    matrix[i][j] += 1

        return sum(1 if x >= 2 else 0 for line in matrix for x in line)

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
