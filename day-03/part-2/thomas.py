from runners.python import SubmissionPy
import numpy as np


class ThomasSubmission(SubmissionPy):
    @staticmethod
    def get_claims(lines):
        claims = []
        for line in lines.split("\n"):
            claim_id, _, border_dist, dim = line.split()
            claim_id = claim_id[1:]
            left_dist, top_dist = [int(d) for d in border_dist[:-1].split(",")]
            width, height = [int(x) for x in dim.split("x")]
            claims.append(
                (claim_id, (top_dist, top_dist + height, left_dist, left_dist + width))
            )
        return claims

    def run(self, s):
        fabric = np.zeros((1000, 1000))
        claims = self.get_claims(s)
        for _, (imin, imax, jmin, jmax) in claims:
            fabric[imin:imax, jmin:jmax] += 1
        for claim_id, (imin, imax, jmin, jmax) in claims:
            if np.count_nonzero(fabric[imin:imax, jmin:jmax] != 1) == 0:
                return claim_id
