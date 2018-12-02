from runners.python import SubmissionPy


class WenceslasSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        serial_numbers = s.splitlines()

        for id, sn1 in enumerate(serial_numbers):
            for sn2 in serial_numbers[id+1:]:
                diff_indexes = []
                # All inputs have the same length
                for i in range(len(sn1)):
                    if sn1[i] != sn2[i]:
                        diff_indexes.append(i)
                    if len(diff_indexes) > 1:
                        break
                else:
                    if len(diff_indexes) == 1:
                        return sn1[:diff_indexes[0]] + sn1[diff_indexes[0]+1:]
