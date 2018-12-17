from tool.runners.python import SubmissionPy


class YouyounSubmission(SubmissionPy):

    def value(self, parent, nodes):
        children = [e for e in nodes if e[1] == parent]
        metadata = [e[2] for e in nodes if e[0] == parent][0]
        if len(children) == 0:
            return sum(metadata)
        else:
            return sum(self.value(children[i-1][0], nodes) for i in metadata if i-1 < len(children))

    def run(self, s):
        seq = [int(x) for x in s.split(" ")]
        i = 0
        metadata = []
        childs = []
        nodes = []
        tree = [(0, None, seq[-seq[1]:])]
        j = 0
        while i < len(seq) - seq[1]:
            if childs and childs[-1] == 0:
                childs.pop()
                node = nodes.pop()
                childs[-1] -= 1
                md = metadata.pop()
                tree.append((node, nodes[-1], [seq[i + k] for k in range(md)]))
                i += md
                continue
            if seq[i] > 0:
                metadata.append(seq[i + 1])
                childs.append(seq[i])
                nodes.append(j)
                j += 1
                i += 2
            else:
                tree.append((j, nodes[-1], [seq[i + 2 + k] for k in range(seq[i + 1])]))
                j += 1
                i += 2 + seq[i + 1]
                childs[-1] -= 1
        return self.value(0, tree)

