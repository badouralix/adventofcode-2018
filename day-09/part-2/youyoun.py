from tool.runners.python import SubmissionPy


class CustomStructure:
    def __init__(self):
        self.data = {}

    def __len__(self):
        return max(self.data.keys()) + 1

    def __str__(self):
        return str([self.data[index] for index in sorted(self.data.keys())])

    def insert(self, index, elt):
        if index not in self.data:
            self.data[index] = elt
        else:
            tmp = [self.data[index] for index in sorted([i for i in self.data if i >= index])]
            for i, ind in enumerate(sorted([i for i in self.data if i >= index])):
                self.data[ind + 1] = tmp[i]
            self.data[index] = elt

    def pop(self, index):
        if index not in self.data:
            raise KeyError()
        value = self.data.pop(index)
        tmp = [self.data[index] for index in sorted([i for i in self.data if i > index], reverse=True)]
        for i, ind in enumerate(sorted([i for i in self.data if i > index], reverse=True)):
            self.data[ind - 1] = tmp[i]
        del self.data[max(self.data.keys())]
        return value


class YouyounSubmission(SubmissionPy):

    def run(self, s):
        parsed = s.split(" ")
        n_players, max_points = int(parsed[0]), int(parsed[6]) * 100
        game = CustomStructure()
        game.insert(0, 0)
        scores = {i: 0 for i in range(n_players)}
        current_pos = 1
        current_player = 0
        for marble in range(1, max_points + 1):
            if marble % 10000 == 0:
                print(marble, max_points)
            if marble % 23 == 0:
                current_pos = (current_pos - 7) % len(game)
                scores[current_player] += marble + game.pop(current_pos)
            else:
                current_pos = ((current_pos + 1) % len(game)) + 1
                game.insert(current_pos, marble)

            current_player = (current_player + 1) % n_players
        return max(scores.values())
