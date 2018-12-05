from runners.python import SubmissionPy

import re


class MathieuSubmission(SubmissionPy):

    def run(self, s):
        # :param s: input in string format
        # :return: solution flag
        # Your code goes here
        almighty_regex = r'Aa|Zz|Ee|Rr|Tt|Yy|Uu|Ii|Oo|Pp|Qq|Ss|Dd|Ff|Gg|Hh|Jj|Kk|Ll|Mm|Ww|Xx|Cc|Vv|Bb|Nn|aA|zZ|eE|rR|tT|yY|uU|iI|oO|pP|qQ|sS|dD|fF|gG|hH|jJ|kK|lL|mM|wW|xX|cC|vV|bB|nN'
        cur_size = len(s)

        s = re.sub(almighty_regex, '', s)

        while len(s) != cur_size:
            cur_size = len(s)
            s = re.sub(almighty_regex, '', s)

        return (len(s))

