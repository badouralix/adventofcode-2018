from tool.runners.python import SubmissionPy

class DavidSubmission(SubmissionPy):
    def bucket_key(self, w, i):
        return w[:i] + w[i+1:]

    def run(self, s):
        words = s.split("\n")
        n = len(words[0])
        buckets = [set() for i in range(n)]
        for w in words:
            for i in range(n):
                k = self.bucket_key(w, i)
                if k in buckets[i]:
                    return k
                buckets[i].add(k)

