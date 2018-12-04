import sys


class Submission():

    def run(self, s):

        l = [x.strip() for x in s.splitlines()]

        for i in range(len(l)):
            for j in range(i+1, len(l)):
                if hamming(l[i], l[j]) == 1:
                    return comstr(l[i], l[j])

def hamming(a, b):
    return sum(1 for k in range(len(a)) if a[k] != b[k])

def comstr(a, b):
    return "".join(a[k] for k in range(len(a)) if a[k] == b[k])

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
