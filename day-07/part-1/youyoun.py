from tool.runners.python import SubmissionPy


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        payload = ""
        links = {}
        requirements = {}
        required_after = set({})  # Used to get the first nodes
        for e in s.splitlines():
            b = e.split(" ")
            required_after.add(b[7])
            if b[1] in links:
                links[b[1]].append(b[7])
            else:
                links[b[1]] = [b[7]]
            if b[7] in requirements:
                requirements[b[7]].add(b[1])
            else:
                requirements[b[7]] = {b[1]}
        required_first = [x for x in links if x not in required_after]
        added = set({})
        while required_first:
            required_first = sorted(required_first, key=lambda x: ord(x) + (x in requirements) * 1000)
            next_ = required_first.pop(0)
            payload += next_
            added.add(next_)
            if next_ in links:
                next_requirements = links.pop(next_)
                required_first += [x for x in next_requirements if x not in added and x not in required_first]
                to_delete = set({})
                for e in requirements:
                    if next_ in requirements[e]:
                        requirements[e].remove(next_)
                        if len(requirements[e]) == 0:
                            to_delete.add(e)
                for e in to_delete:
                    requirements.pop(e)
        return payload
