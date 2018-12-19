#!/usr/bin/env python3

# stdlib
import glob
import os.path
from os import walk
from shutil import which
# project
from tool.runners import LANGUAGES, TOOL_BY_LANGUAGE, ext_by_language, language_by_ext
from tool.model import Problem, Submission, Input


_DAY_PATH_PATTERN = 'day-[0-9]*'
_PART_PATH_PATTERN = 'part-[0-9]*'
supported_languages = []


def get_supported_languages():
    global supported_languages
    if not supported_languages:
        supported_languages = [language for language in LANGUAGES if which(TOOL_BY_LANGUAGE[language]) is not None]
    return supported_languages


def get_latest_problem():
    days = get_all_days()
    if not days:
        return
    latest_day = days[-1]
    parts = get_parts_for_day(latest_day)
    if not parts:
        return
    latest_part = parts[-1]
    return Problem(latest_day, latest_part)


def get_all_problems(days=None):
    if not days:
        days = get_all_days()
    if not days:
        return []
    problems = []
    for day in days:
        for part in get_parts_for_day(day):
            problems.append(Problem(day, part))

    return problems


def get_all_days():
    return sorted(
        list(
            map(
                lambda x: int(x[-2:]),
                list(glob.glob(_DAY_PATH_PATTERN))
            )
        )
    )


def get_parts_for_day(day):
    return sorted(
        list(
            map(
                lambda x: int(x[-1]),
                list(glob.glob(os.path.join(Problem.day_to_path(day), _PART_PATH_PATTERN)))
            )
        )
    )


def get_days_for_part(part):
    return sorted(
        list(
            map(
                lambda x: int(x[4:6]),
                list(glob.glob(os.path.join(_DAY_PATH_PATTERN, "part-%d" % part)))
            )
        )
    )


def get_problems(days, parts, all_days_parts=False):
    problems = []
    if all_days_parts:
        problems = get_all_problems()
    elif days and parts:
        problems = [problem for problem in get_all_problems(days) if problem.part in parts]
    elif days:
        problems = get_all_problems(days)
    elif parts:
        latest = get_latest_problem()
        if not latest:
            return []
        problems = [
            Problem(latest.day, part)
            for part in get_parts_for_day(latest.day)
            if part in parts
        ]
    else:
        latest = get_latest_problem()
        if latest:
            problems = [
                Problem(latest.day, part)
                for part in get_parts_for_day(latest.day)
            ]
    return sorted(problems, key=lambda p: (p.day, p.part))


def get_submissions(problem, authors=None, ignored_authors=None, languages=None, force=False):
    if not languages:
        if force:
            languages = LANGUAGES
        else:
            languages = get_supported_languages()
    elif not force:
        languages = [language for language in languages if language in get_supported_languages()]

    extensions = set([ext_by_language(language) for language in languages])

    submissions = []
    for _, _, files in walk(problem.path()):
        for filename in files:
            submission, ext = os.path.splitext(filename)
            author = os.path.basename(submission)
            if (ext not in extensions) or filename.endswith('_test.go'):
                continue
            if ignored_authors and author in ignored_authors:
                continue
            if authors and author not in authors:
                continue
            submissions.append(Submission(problem, author, language_by_ext(ext)))
        break  # stop at depth 1
    return submissions


def get_inputs(problem):
    inputs_path = os.path.join(problem.day_path(), 'input')
    if not os.path.exists(inputs_path):
        return []

    inputs = []
    for input_file in glob.glob(os.path.join(inputs_path, '*.txt')):
        author = os.path.splitext(os.path.basename(input_file))[0].lower()
        with open(input_file, 'r') as content_file:
            inputs.append(Input(problem, author, content_file.read().rstrip()))
    return inputs
