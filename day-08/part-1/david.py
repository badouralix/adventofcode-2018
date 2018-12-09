from runners.python import SubmissionPy

from collections import defaultdict

class DavidSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        items = (int(x) for x in s.split(" "))

        stack = []
        result = 0
        new_node = True

        while True:
            if new_node:
                children, metadatas = next(items),next(items)
                if children == 0:
                    new_node = False
                    stack.append((0, metadatas))
                else:
                    stack.append((children-1,metadatas))
            else:
                if len(stack) == 0:
                    return result
                children,metadatas = stack.pop()
                if children == 0:
                    for _ in range(metadatas):
                        result += next(items)
                    new_node = False
                else:
                    stack.append((children-1,metadatas))
                    new_node = True
        return result
