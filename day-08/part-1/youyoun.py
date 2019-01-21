from tool.runners.python import SubmissionPy


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        seq = [int(x) for x in s.split(" ")]
        i = 0
        metadata = []
        childs = []
        sum_ = 0
        while i < len(seq) - seq[1]:
            if childs and childs[-1] == 0:
                childs.pop()
                childs[-1] -= 1
                md = metadata.pop()
                sum_ += sum(seq[i + k] for k in range(md))
                i += md
                continue
            if seq[i] > 0:
                metadata.append(seq[i + 1])
                childs.append(seq[i])
                i += 2
            else:
                sum_ += sum(seq[i + 2 + k] for k in range(seq[i + 1]))
                i += 2 + seq[i + 1]
                childs[-1] -= 1
        return sum_ + sum(seq[-seq[1]:])
