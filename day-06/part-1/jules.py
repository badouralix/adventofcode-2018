from runners.python import SubmissionPy
from collections import defaultdict
import operator


class JulesSubmission(SubmissionPy):

    def run(self, s):
        def find_nearest(points, x, y):
            min_distance = 1000
            curr_nearest_point = -1
            number_having_min_distance = 0
            for point in points:
                distance = abs(x - point[0]) + abs(y - point[1])
                if distance == min_distance:
                    number_having_min_distance += 1
                if distance < min_distance:
                    min_distance = distance
                    number_having_min_distance = 1
                    curr_nearest_point = points.index(point)
            assert curr_nearest_point != -1
            return curr_nearest_point, number_having_min_distance

        def calculate_grid(offset):
            grid = defaultdict(int)
            for x in range(min_x - offset, max_x + offset):
                for y in range(min_y - offset, max_y + offset):
                    point, number_having_min_distance = find_nearest(points, x, y)
                    if number_having_min_distance == 1:
                        grid[point] += 1
            return grid
            
        points = []
        for line in s.split('\n'):
            x, y = line.split(', ')
            points.append([int(x), int(y)])
        x_list = [x[0] for x in points]
        y_list = [x[1] for x in points] 
        min_x, max_x = min(x_list), max(x_list)
        min_y, max_y = min(y_list), max(y_list)

        offset = 1
        grid = calculate_grid(offset)
        grid2 = calculate_grid(offset + 1)
        x = max_x
        y = max_y
        old_score = 0
        score = 1
        while old_score != score:
            old_score = score
            score_grid = 0
            score_grid2 = 1
            while score_grid != score_grid2:
                id_point = max(grid.items(), key=operator.itemgetter(1))[0]
                score_grid = grid[id_point]
                score_grid2 = grid2[id_point]
                del grid[id_point]
                x, y = points[id_point]
        
        return score_grid
