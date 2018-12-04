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
            data.append((int(_id), int(pw), int(ph), int(w), int(h)))

        max_w = max(pw + w for (_id, pw, ph, w, h) in data)
        max_h = max(ph + h for (_id, pw, ph, w, h) in data)

        matrix = [None] * (max_h + 1)
        for i in range(max_h + 1):
            matrix[i] = [None] * (max_w + 1)
            for j in range(max_w + 1):
                matrix[i][j] = set()

        overlapped = {}

        for (_id, pw, ph, w, h) in data:
            overlapped[_id] = False
            for i in range(ph + 1, ph + h + 1):
                for j in range(pw + 1, pw + w + 1):
                    matrix[i][j].add(_id)
                    if len(matrix[i][j]) > 1:
                        for x in matrix[i][j]:
                            overlapped[x] = True

        for k, v in overlapped.items():
            if not v:
                return k
        return -1

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
