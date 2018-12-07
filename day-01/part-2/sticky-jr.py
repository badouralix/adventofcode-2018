from runners.python import SubmissionPy

class StickySubmission(SubmissionPy):

    def run(self, s):
        l = {int(f) for f in s.splitlines()}
        d = {0}
        s = 0
        for i in range(100000):
            for f in l:
              s += f
              if s in d:
                  return s
              d.append(s)
