from tool.runners.python import SubmissionPy
from collections import defaultdict


class JulesSubmission(SubmissionPy):

    def run(self, s):
        def parse(elements):
            node = Node()
            nb_of_child = int(elements[0])
            nb_of_metadatas = int(elements[1])
            elements = elements[2:]
            for j in range(nb_of_child):
                child, elements = parse(elements)
                node.add_child(child)
            for j in range(nb_of_metadatas):
                node.add_metadata(int(elements[0]))
                elements = elements[1:]
            return node, elements
                    
        class Node():
            def __init__(self):
                self.childrens = []
                self.metadatas = []
                pass

            def add_child(self, child):
                self.childrens.append(child)
            
            def add_metadata(self, metadata):
                self.metadatas.append(metadata)
            
            def sum_metadata(self):
                total = 0
                for child in self.childrens:
                    total += child.sum_metadata()
                for metadata in self.metadatas:
                    total += metadata
                return total

        elements = s.split(' ')
        nodes = []
        while len(elements) != 0:
            child, elements = parse(elements)
            nodes.append(child)
        
        total = 0
        for node in nodes:
            total += node.sum_metadata()
        return total

