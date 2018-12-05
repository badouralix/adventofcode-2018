from runners.python import SubmissionPy
import string


class DegemerSubmission(SubmissionPy):

    def run(self, ss):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        mini = None
        for cc in string.ascii_lowercase:
            stack = []
            s = ss.replace(cc, "")
            s = s.replace(cc.upper(), "")

            for c in s:
                if len(stack) == 0:
                    stack.append(c)
                elif stack[-1].lower() == c.lower() and stack[-1] != c:
                    stack.pop()
                else:
                    stack.append(c)

            if mini is None or mini > len(stack):
                mini = len(stack)
        return mini
