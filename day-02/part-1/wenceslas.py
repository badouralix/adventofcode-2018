from tool.runners.python import SubmissionPy
from collections import Counter

class WenceslasSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here

        ids_twice = 0
        ids_thrice = 0

        for box_id in s.splitlines():
            counter = Counter(box_id)
            if 2 in counter.values():
                ids_twice += 1
            if 3 in counter.values():
                ids_thrice += 1
    
        return ids_twice*ids_thrice