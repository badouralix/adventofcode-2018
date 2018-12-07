from runners.python import SubmissionPy

class StickySubmission(SubmissionPy):

    def run(self, s):
        l = s.splitlines()
        d = [0]
        s = 0
        while True:
            for f in l:
              s += int(f)
              if s in d:
                  return s
              d.append(s)
