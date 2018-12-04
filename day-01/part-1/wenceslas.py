import sys


class Submission():

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here

        res_freq = 0

        for freq_change in s.splitlines():
            res_freq += int(freq_change)

        return res_freq

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
