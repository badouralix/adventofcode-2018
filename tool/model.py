#!/usr/bin/env python3

# stdlib
import os.path
# project
from tool.runners import ext_by_language, load_submission_runnable


class Problem(object):

    @staticmethod
    def day_to_path(day):
        return "day-%02d" % day

    def __init__(self, day, part):
        self.day = day
        self.part = part

    def __repr__(self):
        return "Problem{day-%02d, part-%d}" % (self.day, self.part)

    def day_path(self):
        return Problem.day_to_path(self.day)

    def path(self):
        return os.path.join(self.day_path(), "part-%d" % self.part)


class Submission(object):
    def __init__(self, problem, author, language, content=None, init_runnable=True):
        self.problem = problem
        self.author = author
        self.language = language
        self.content = content
        self.runnable = load_submission_runnable(self.path(), language) if init_runnable else None

    def __repr__(self):
        return "Submission{%s, by %s, in %s}" % (self.problem, self.author, self.language)

    def path(self):
        return os.path.join(self.problem.path(), "%s%s" % (self.author, ext_by_language(self.language)))


class Input(object):
    def __init__(self, problem, author, content):
        self.problem = problem
        self.author = author
        self.content = content

    def __repr__(self):
        return "Input{%s, by %s, size %d}" % (self.problem, self.author, len(self.content))

    def path(self):
        return os.path.join(self.problem.day_path(), "input", self.author + ".txt")


class Result(object):
    def __init__(self, problem, submission, input, answer, duration):
        self.problem = problem
        self.submission = submission
        self.input = input
        self.answer = answer
        self.duration = duration

    def __repr__(self):
        return "Result{%s, %s, %s, %s}" % (self.problem, self.submission, self.input, self.answer)
