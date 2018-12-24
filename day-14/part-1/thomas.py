from tool.runners.python import SubmissionPy


class ThomasSubmission(SubmissionPy):
    def run(self, s):
        nb_recipes = int(s)
        recipes = [3, 7]
        elves = [0, 1]
        while len(recipes) < nb_recipes + 10:
            new = recipes[elves[0]] + recipes[elves[1]]
            recipes += [int(c) for c in str(new)]
            elves = [
                (elves[0] + 1 + recipes[elves[0]]) % len(recipes),
                (elves[1] + 1 + recipes[elves[1]]) % len(recipes),
            ]
            # if len(recipes) <= 26:
            #     print(recipes, elves)
        return "".join(str(n) for n in recipes[nb_recipes : nb_recipes + 10])
