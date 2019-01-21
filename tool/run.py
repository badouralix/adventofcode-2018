#!/usr/bin/env python3

# stdlib
import sys
import datetime
from collections import defaultdict
from tabulate import tabulate
from tqdm import tqdm
# project
import tool.discovery as discovery
from tool.config import CONFIG
from tool.model import Result, Submission
from tool.utils import BColor


class DifferentAnswersException(Exception):
    pass


def run(days, parts, authors, ignored_authors, languages, force, silent, all_days_parts, restricted, expand):
    problems = discovery.get_problems(days, parts, all_days_parts)
    printed_day_header = set()
    errors = []

    for problem in problems:
        if problem.day not in printed_day_header:
            printed_day_header.add(problem.day)
            print_day_header(problem)
        print_part_header(problem)

        submissions = discovery.get_submissions(problem, authors, ignored_authors, languages, force)
        inputs = discovery.get_inputs(problem)

        results_by_author = defaultdict(list)
        results_by_input = defaultdict(list)

        pbar = tqdm(total=len(inputs)*len(submissions) if not restricted else len(submissions))
        for input in inputs:
            previous = None
            for submission in submissions:
                pbar.update(1)
                # The split allows having author.lang and author.x.lang files, on the same input
                if restricted and input.author != submission.author.split('.')[0]:
                    continue
                try:
                    result = run_submission(problem, submission, input, previous)
                    results_by_author[submission.author].append(result)
                    results_by_input[input.author].append(result)
                    previous = result
                except DifferentAnswersException as e:
                    errors.append(
                        "{}ERROR: {}{}".format(BColor.RED, e, BColor.ENDC))

        for submission in submissions:
            submission.runnable.cleanup()

        pbar.close()
        if restricted:
            print_restrict_results(problem, results_by_author)
        elif expand:
            print_expanded_results(problem, results_by_input)
        else:
            print_aggregated_results(problem, results_by_author)

    for err in errors:
        print(err, file=sys.stderr)
    if errors:
        exit(1)


def run_submission(problem, submission, input, previous=None):
    start = datetime.datetime.now()
    answer = str(submission.runnable.run(input.content))
    end = datetime.datetime.now()
    msecs = (end - start).total_seconds() * 1000
    answer, msecs = duration_from_answer(answer, msecs)
    if previous is not None and answer != previous.answer:
        raise DifferentAnswersException("""different answers day:{} part:{}
input: {}
{}: {}
{}: {}""".format(
            problem.day,
            problem.part,
            input.path(),
            previous.submission.path(),
            previous.answer,
            submission.path(),
            answer))
    return Result(problem, submission, input, answer, msecs)


def print_results(results):
    results.sort(key=lambda x: x.duration)
    print(tabulate([[

        "  {color}{author}{end}  ".format(
            color=(BColor.BOLD if result.submission.author == CONFIG.user else BColor.GREEN),
            author=result.submission.author,
            end=BColor.ENDC),

        "  {color}{answer}{end}  ".format(
            color=(BColor.BOLD if result.submission.author == CONFIG.user else BColor.BLUE),
            answer=result.answer,
            end=BColor.ENDC),

        "  {color}{msecs:8.2f} ms{end}".format(
            color=BColor.BOLD,
            msecs=result.duration,
            end=BColor.ENDC),

        "  {color}{language}{end}".format(
            color=(BColor.BOLD if result.submission.author == CONFIG.user else ""),
            language=result.submission.language,
            end=BColor.ENDC,
        )
    ] for result in results]))


def print_expanded_results(problem, results_by_input):
    for input_author, submission_results in results_by_input.items():
        print("---------------------------------------------------")
        print("On input from {yellow}{author}{end}".format(
            yellow=BColor.YELLOW,
            end=BColor.ENDC,
            author=input_author))
        print("---------------------------------------------------")
        results = []
        for result in submission_results:
            results.append(result)
        print_results(results)


def print_restrict_results(problem, results_by_author):
    print("---------------------------------------------------")
    print("On own inputs")
    print("---------------------------------------------------")
    results = []
    for author, results_by_input in results_by_author.items():
        for result in results_by_input:
            results.append(result)
    print_results(results)


def print_aggregated_results(problem, results_by_author):
    print("---------------------------------------------------")
    print("Avg over all inputs")
    print("---------------------------------------------------")
    results = []
    # Loop for all authors, get all the results they produced
    for author, results_by_input in results_by_author.items():
        res_by_language = {}
        count_by_language = defaultdict(int)
        # The results can be made by different languages. Make a virtual result (storing total duration) by language
        for result in results_by_input:
            result_language = result.submission.language
            count_by_language[result_language] += 1
            # New language: make the virtual result
            if result_language not in res_by_language:
                res = Result(problem, Submission(problem, author, result_language, init_runnable=False), None, "-", 0)
                res_by_language[result_language] = res
            # The author is on his own input, get his answer (split to allow author.x.lang on input author.txt)
            if author.split('.')[0] == result.input.author:
                res_by_language[result_language].answer = result.answer
                res_by_language[result_language].input = result.input
                res_by_language[result_language].submission = result.submission
            # Add up the duration of this result
            res_by_language[result_language].duration += result.duration
        # For each language of the author, make the average and store the final result
        for lang, res in res_by_language.items():
            if count_by_language[lang] > 0:
                res.duration /= count_by_language[lang]
            results.append(res)
    print_results(results)


def print_day_header(problem):
    print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    print(BColor.RED + BColor.BOLD + "Running submissions for day %02d:" % problem.day + BColor.ENDC)


def print_part_header(problem):
    print("\n" + BColor.MAGENTA + BColor.BOLD + "* part %d:" % problem.part + BColor.ENDC)


def duration_from_answer(answer, msec):
    DURATION_HEADER_PREFIX = "_duration:"
    split = answer.split("\n")
    if len(split) < 2 or (not split[0].startswith(DURATION_HEADER_PREFIX)):
        return answer, msec
    try:
        return "\n".join(split[1:]), float(split[0][len(DURATION_HEADER_PREFIX):])
    except ValueError:
        pass
    return answer, msec
