from runners.python import SubmissionPy

class Square():

        def __init__(self, id, x, y, width, height):
            self.id = id.strip()
            self.x = int(x)
            self.y = int(y)
            self.width = int(width)
            self.height = int(height)
            self.hasAnOverlap = False

        def __str__(self):
            return(f"#{self.id} @ {self.x},{self.y}: {self.width}x{self.height}") 

        def overlap(self, square):
            for x in range(max(self.x, square.x), min(square.x + square.width, self.x + self.width)):
                for y in range(max(self.y, square.y), min(square.y + square.height, self.y + self.height)):
                    self.hasAnOverlap = True
                    square.hasAnOverlap = True

class JulesSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        totalSquare = [[0]*1000 for _ in range(1000)]
        squareList = []
        for square in s.split("\n"):
            definition = square.split(' ')
            x, y = definition[2].split(',')
            y = y[:-1] # remove trailing `:`
            width, height = definition[-1].split('x')
            squareList.append(Square(
                id=definition[0][1:],
                x=x,
                y=y,
                width=width,
                height=height))
        for i in range(len(squareList)):
            for j in range(i + 1, len(squareList)):
                squareList[i].overlap(squareList[j])
        for i in range(len(squareList)):
            if not squareList[i].hasAnOverlap:
                return squareList[i].id
        return 0
