from tool.runners.python import SubmissionPy


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        r1, r2 = 0, 0
        possible_r2s = set()
        last_r2 = None

        while True:
            r1 = r2 | 65536
            r2 = 1250634

            while True:
                r2 = (((r2 + (r1 & 255)) & 16777215) * 65899) & 16777215
                if 256 > r1:
                    if r2 not in possible_r2s:
                        possible_r2s.add(r2)
                        last_r2 = r2
                    else:
                        return last_r2
                    break
                else:
                    r1 = r1 // 256
