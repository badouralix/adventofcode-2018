from runners.python import SubmissionPy


class DegemerSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        words = list(s.splitlines())
        for i, word in enumerate(words):
            for word2 in words[i+1:]:
                unmatch = 0
                chars = []
                for i in range(len(word)):
                    if word[i] != word2[i]:
                        unmatch += 1
                    else:
                        chars.append(word[i])
                    if unmatch > 1:
                        break
                if unmatch == 1:
                    return ''.join(chars)
