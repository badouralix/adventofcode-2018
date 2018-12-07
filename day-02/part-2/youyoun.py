from tool.runners.python import SubmissionPy


class YouyounSubmission(SubmissionPy):

    def compare_strings(self, str1, str2):
        c = 0
        pos = 0
        for i in range(len(str1)):
            if str1[i] != str2[i]:
                if c == 0:
                    c = 1
                    pos = i
                else:
                    return False, None
        return True, pos

    def run(self, s):
        strs = s.splitlines()
        for i in range(len(strs)):
            for j in range(i+1, len(strs)):
                is_close, pos = self.compare_strings(strs[i], strs[j])
                if is_close:
                    return strs[i][:pos] + strs[i][pos + 1:]
        return
