from runners.python import SubmissionPy


class SilvestreSubmission(SubmissionPy):

    def parse(self, s):
        # Step H must be finished before step Z can begin.
        nodes = set()
        vertices = list()
        for line in s.splitlines():
            node1, node2 = line[5], line[-12]
            nodes.add(node1)
            nodes.add(node2)
            vertices.append((node1, node2))
        return nodes, vertices

    def run(self, s):
        nodes, vertices = self.parse(s)

        available_nodes = nodes - set(node for _, node in vertices)
        ret = []

        # browse the graph until 
        while available_nodes:
            # choose the right available node
            curr_node = min(available_nodes)
            available_nodes.remove(curr_node)
            ret += curr_node

            # add the nexts nodes if available
            next_nodes = (b for a, b in vertices if a == curr_node)
            for next_n in next_nodes:
                if not set(a for a, b in vertices if b == next_n) - set(ret):
                    available_nodes.add(next_n)


        return "".join(ret)
