from runners.python import SubmissionPy

class StickySubmission(SubmissionPy):

    def run(self, s):

      DAG = {}
      nodes = []
      order = ''
      lines = [line.split(' ') for line in s.splitlines()]
      for l in lines:
          DAG[l[-3]] = sorted(set(DAG.get(l[-3], []) + [l[1]]))
          nodes.append(l[-3])
          nodes.append(l[1])

      nodes = set(nodes)

      feasible = [n for n in nodes if n not in DAG.keys() and n not in order]
      while len(feasible) > 0:
          nxt = min(feasible)
          order += nxt

          opn_nodes = list(DAG.keys())
          for n in opn_nodes:
              if nxt in DAG[n]:
                  DAG[n].remove(nxt)
              if len(DAG[n]) == 0:
                  del DAG[n]

          feasible = [n for n in nodes if n not in DAG.keys() and n not in order]

      return order

