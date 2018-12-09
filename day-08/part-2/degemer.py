from runners.python import SubmissionPy


class DegemerSubmission(SubmissionPy):
    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        nodes = list(map(int, s.split(' ')))
        stack = []
        i = 0
        while i < len(nodes):
            if len(stack) == 0:
                children = int(nodes[i])
                metas = int(nodes[i + 1])
                i += 2
                stack.append([children, metas, children, []])
            elif stack[-1][0] == 0:
                val = 0
                if stack[-1][2] == 0:
                    for j in range(stack[-1][1]):
                        val += nodes[i+j]
                else:
                    for j in range(stack[-1][1]):
                        index = nodes[i+j] - 1
                        if index >= len(stack[-1][3]):
                            continue
                        val += stack[-1][3][index]
                i += stack[-1][1]
                stack.pop()
                if len(stack) > 0:
                    stack[-1][0] -= 1
                    stack[-1][3].append(val)
                else:
                    return val
            else:
                children = int(nodes[i])
                metas = int(nodes[i + 1])
                stack.append([children, metas, children, []])
                i += 2
