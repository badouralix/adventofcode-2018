from tool.runners.python import SubmissionPy


class DegemerSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        deps = {}
        order = ''
        for line in s.splitlines():
            parsed = line.split(' ')
            before, after = parsed[1], parsed[-3]
            if after not in deps:
                deps[after] = set()
            if before not in deps:
                deps[before] = set()
            deps[after].add(before)

        while len(deps) > 0:
            select = None
            for let in deps:
                if len(deps[let]) == 0 and (select is None or select > let):
                    select = let
            order += select
            del deps[select]
            for let in deps:
                if select in deps[let]:
                    deps[let].remove(select)

        return order
