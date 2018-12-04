import sys
class Submission():
    @staticmethod
    def run(input):
        return sum([
            int(n)
            for n in input.split('\n')
        ])

if __name__ == "__main__":
    print(Submission().run(sys.argv[1]))
