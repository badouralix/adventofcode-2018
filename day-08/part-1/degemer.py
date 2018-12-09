from tool.runners.python import SubmissionPy


class DegemerSubmission(SubmissionPy):
    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        nodes = list(map(int, s.split(' ')))
        stack = []
        i = 0
        sum_meta = 0
        while i < len(nodes):
            if len(stack) == 0:
                children = int(nodes[i])
                metas = int(nodes[i + 1])
                i += 2
                stack.append([children, metas])
            elif stack[-1][0] == 0:
                for j in range(stack[-1][1]):
                    sum_meta += nodes[i+j]
                i += stack[-1][1]
                stack.pop()
                if len(stack) > 0:
                    stack[-1][0] -= 1
            else:
                children = int(nodes[i])
                metas = int(nodes[i + 1])
                stack.append([children, metas])
                i += 2
        return sum_meta
