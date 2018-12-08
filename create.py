#!/usr/bin/env python3

import argparse
import os.path
import re
import sys


class FileNotEmptyException(Exception):
    pass


def mkdirp(path):
    """
    Create directory if it does not exist already.

    Parameters
    ----------
    path : string
        Name of the directory to be created
    """
    if not os.path.exists(path):
        os.makedirs(path)


def make_dirs(day, parts):
    """
    Create day/part directories along with input directory.

    Parameters
    ----------
    day : int
        Day number for which a directory is created
    parts : list[int]
        List of parts for which directories is created

    Returns
    -------
    dirs : dict("input": string, "parts": list(string))
        Dictionnary containing created directories
    """
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
    """
    Create submission file from template according to the chosen language.

    Parameters
    ----------
    author : string
        Name of the author for whom the input file is created
    path : string
        Day/part directory in which the submission file is created
    language : string
        Programming language of the submission
    """
    # Build submission file name
    submission_file = os.path.join(path, f"{author}.{language}")

    # Extract submission template
    if language == 'py':
        # Create a dedicated class with the author name
        class_name = ''.join(x for x in f"{author} submission".title() if not x.isspace())
        submission_content = open(os.path.join("templates", "template.py")).read().format(class_name=class_name)
    else:
        submission_content = open(os.path.join("templates", f"template.{language}")).read()

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
    """
    Create input txt file.

    Parameters
    ----------
    author : string
        Name of the author for whom the input file is created
    path : string
        Input directory in which the input file is created
    """
    # Build input file name
    input_file = os.path.join(path, f"{author}.txt")

    # Create input file
    if os.path.exists(input_file):
        raise FileNotEmptyException(f"{input_file} not empty")
    with open(input_file, 'a') as f:
        f.close()

    # Log success
    print(f"[+] created {input_file}")


def main():
    """
    Create directories and submission files according to commamd line arguments.
    """
    # Parse command line arguments
    parser = argparse.ArgumentParser(description='Creates new empty submission')
    parser.add_argument('author', type=str, help='Name of author (github login)')
    parser.add_argument('day', type=int, help='Day of problem (between 1 and 25)')
    parser.add_argument('-p', '--part', type=int, help='Create submission for one day part only', choices=[1, 2])
    parser.add_argument('-l', '--language', help='Use specified language', default="py", choices=["c", "cpp", "go", "js", "py", "rb", "rs", "sh"])
    args = parser.parse_args()

    # Format author name
    author = args.author.lower()

    # Create missing directories
    dirs = make_dirs(args.day, [1, 2] if not args.part else [args.part])

    # Create input file
    try:
        create_input(author, dirs["input"])
    except FileNotEmptyException:
        pass
    except Exception as e:
        print(e, file=sys.stderr)
        sys.exit(1)

    # Create submission files
    for submission_path in dirs["parts"]:
        try:
            create_submission(author, submission_path, args.language)
        except FileNotEmptyException as e:
            print(e, file=sys.stderr)
            sys.exit(1)


if __name__ == '__main__':
    main()
