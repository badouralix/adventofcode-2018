import subprocess

from .wrapper import SubmissionWrapper

class SubmissionBash(SubmissionWrapper):

    def __init__(self, file):
        self.executable = file

    def language(self):
        return 'sh'

    def exec(self, input):
        return subprocess.check_output(f"./{self.executable} <<< '{input}'", shell=True).decode()
