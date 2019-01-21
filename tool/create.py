#!/usr/bin/env python3

# stdlib
import os.path
import re
import sys

# project
import tool.discovery as discovery
from tool.config import CONFIG
from tool.utils import mkdirp


TEMPLATES_PATH = os.path.join("tool", "templates")


class FileNotEmptyException(Exception):
    pass


def make_dirs(day, parts):
    dirs = dict()

    # Create day directory
    day_dir = "./day-{:02d}".format(day)
    mkdirp(day_dir)

    # Create input directory
    dirs["input"] = f"{day_dir}/input"
    mkdirp(dirs["input"])

    # Create part directories
    dirs["parts"] = [f"{day_dir}/part-{part}" for part in parts]
    for part_dir in dirs["parts"]:
        mkdirp(part_dir)

    return dirs


def create_submission(author, path, language):
    # Build submission file name
    submission_file = os.path.join(path, f"{author}.{language}")

    # Extract submission template
    if language == 'py':
        # Create a dedicated class with the author name
        class_name = ''.join(x for x in f"{author} submission".title() if not x.isspace())
        submission_content = open(os.path.join(TEMPLATES_PATH, "template.py")).read().format(class_name=class_name)
    else:
        submission_content = open(os.path.join(TEMPLATES_PATH, f"template.{language}")).read()

    # Write template to submission file if it is empty
    if os.path.exists(submission_file):
        raise FileNotEmptyException(f"{submission_file} not empty")
    with open(submission_file, 'w') as f:
        f.write(submission_content)

    # Log success
    print(f"[+] created {submission_file}")

    # Create an entry in Cargo.toml if it is a Rust project
    if language == "rs":
        submission_name = f"{re.sub('[^0-9a-zA-Z]+', '-', path[2:])}-{author}"
        cargo = open(os.path.join("Cargo.toml"), "a")
        cargo.write(f"\n[[bin]]\nname = \"{submission_name}\"\npath = \"{submission_file}\"\n")
        print("[+] added submission to Cargo.toml")

    # Create a symlink to workspace if it is a Golang project
    if language == "go":
        workspace_directory = os.path.join("./workspace", os.path.normpath(path))
        workspace_submission_file = os.path.join("./workspace", os.path.normpath(submission_file))
        if not os.path.exists(workspace_submission_file):
            os.makedirs(workspace_directory, mode=0o777, exist_ok=True)
            os.symlink(os.path.realpath(submission_file), workspace_submission_file)
            # Log success
            print(f"[+] created symlink in {workspace_submission_file}")


def create_input(author, path):
    # Build input file name
    input_file = os.path.join(path, f"{author}.txt")

    # Create input file
    if os.path.exists(input_file):
        raise FileNotEmptyException(f"{input_file} not empty")
    with open(input_file, 'a') as f:
        f.close()

    # Log success
    print(f"[+] created {input_file}")


def create(day, part, author, language):
    if not day:
        latest = discovery.get_latest_problem()
        day = 1 if not latest else (latest.day + 1)

    if not author:
        author = CONFIG.user

    if not author:
        print("""please set your username using config command:
aoc config <username> <language>""", file=sys.stderr)
        exit(1)

    if not language:
        language = CONFIG.language

    # Format author name
    author = author.lower()

    # Create missing directories
    dirs = make_dirs(day, [1, 2] if not part else [part])

    # Create input file
    try:
        create_input(author, dirs["input"])
    except FileNotEmptyException:
        pass
    except Exception as e:
        print(e, file=sys.stderr)
        exit(1)

    # Create submission files
    for submission_path in dirs["parts"]:
        try:
            create_submission(author, submission_path, language)
        except FileNotEmptyException as e:
            print(e, file=sys.stderr)
            exit(1)
