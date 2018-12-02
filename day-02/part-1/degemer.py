from runners.python import SubmissionPy


class DegemerSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        twos, threes = 0, 0
        for code in s.splitlines():
            letters = {}
            for let in code:
                letters[let] = letters.get(let, 0) + 1
            two, three = False, False
            for let, val in letters.items():
                if not two and val == 2:
                    two = True
                    twos += 1
                if not three and val == 3:
                    three = True
                    threes += 1
                if two and three:
                    break
        return twos * threes
