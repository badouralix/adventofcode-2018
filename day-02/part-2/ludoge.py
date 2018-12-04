import sys


class Submission():

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        s_list = s.splitlines()
        for i in range(len(s_list)):
            for j in range(i+1, len(s_list)):
                m = self.match(s_list[i], s_list[j])
                if m is not None:
                    return m
        pass

    def match(self, a, b):
        k = -1
        for i in range(len(a)):
            if a[i] != b[i]:
                if k == -1:
                    k = i
                else:
                    return None
        return a[:k]+a[k+1:]

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
