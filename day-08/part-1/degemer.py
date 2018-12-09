from runners.python import SubmissionPy
import sys

sys.setrecursionlimit(15000)

sum_metadata = 0
def parse(nodes, index):
    global sum_metadata
    node = {'children': [], 'metadata': []}
    node['num_children'] = nodes[index]
    node['num_metadata'] = nodes[index+1]
    index += 2
    for _ in range(node['num_children']):
        index, node = parse(nodes, index)
        node['children'].append(node)

    for i in range(node['num_metadata']):
        node['metadata'].append(nodes[index + i])
        sum_metadata += nodes[index+i]
    index += node['num_metadata']
    return index, node


class DegemerSubmission(SubmissionPy):
    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        nodes = list(map(int, s.split(' ')))
        print("NODES", len(nodes))
        parsed = parse(nodes, 0)
        global sum_metadata
        return sum_metadata
