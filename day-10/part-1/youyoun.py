from tool.runners.python import SubmissionPy


class YouyounSubmission(SubmissionPy):

    @staticmethod
    def update_position(positions, velocities):
        for i in positions:
            positions[i] = positions[i][0] + velocities[i][0], positions[i][1] + velocities[i][1]

    @staticmethod
    def get_ascii_dictionary():
        ascii_letters = {}
        with open("day-10/alphabet.txt", "r") as f:
            while True:
                letter = f.readline().replace("\n", "")
                if letter == "":
                    break
                ascii_letter = ""
                for _ in range(10):
                    ascii_letter += f.readline()
                ascii_letters[ascii_letter] = letter
                f.readline()
        return ascii_letters

    @staticmethod
    def translate_points(positions):
        pos = positions.values()
        min_x, min_y = min([e[0] for e in pos]), min([e[1] for e in pos])
        for i in positions:
            positions[i] = positions[i][0] - min_x, positions[i][1] - min_y

    def run(self, s):
        lines = s.splitlines()
        positions = {}
        velocities = {}
        for i, line in enumerate(lines):
            x, y = int(line[10:16]), int(line[18:24])
            v_x, v_y = int(line[36:38]), int(line[40:42])
            positions[i] = x, y
            velocities[i] = v_x, v_y

        while True:
            is_close = True
            for i in range(len(positions) - 1):
                if abs(positions[i][1] - positions[i + 1][1]) > 10:
                    is_close = False
                    break
            if is_close:
                break
            YouyounSubmission.update_position(positions, velocities)

        YouyounSubmission.translate_points(positions)

        pos = positions.values()
        max_x, max_y = max([e[0] for e in pos]), max([e[1] for e in pos])

        image = []
        for i in range(max_y + 1):
            image.append([" " for _ in range(max_x + 1)])

        for i in positions:
            image[positions[i][1]][positions[i][0]] = "#"

        letters = ["" for _ in range(len(image[0]) // 7)]

        ascii_letters = YouyounSubmission.get_ascii_dictionary()

        for e in image:
            for i in range(len(image[0]) // 7):
                letters[i] += f"{''.join(e[i*8:i*8+6])}\n"

        payload = ""
        for e in letters:
            if e not in ascii_letters:
                print(e.encode())
            payload += ascii_letters[e]
        return payload
