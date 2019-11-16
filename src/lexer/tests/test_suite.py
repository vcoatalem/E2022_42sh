from argparse import ArgumentParser
from pathlib import Path
from difflib import unified_diff
from termcolor import colored

import subprocess as sp
import yaml
 

def run_42sh(args, stdin):
    return sp.run(args, capture_output=True, text=True, input=stdin)

def test(binary, tests):
    ref = run_42sh(["bash", "--posix"], tests["stdin"])
    student = run_42sh([binary], tests["stdin"])
    for check in tests.get("checks", ["stdout", "stderr", "returncode"]):
        if check == "stdout":
            assert ref.stdout == student.stdout, \
                f"stdout differs:\n{diff(ref.stdout, student.stdout)}"
        elif check == "stderr":
            assert ref.stderr == student.stderr, \
                f"stderr differs:\n{diff(ref.stderr, student.stderr)}"
        elif check == "returncode":
            assert ref.returncode == student.returncode, \
                f"Exit with {student.returncode} , got {ref.returncode}"
        elif check == "has_stderr":
            assert student.stderr != "", "Something was expected on stderr"

def diff(ref, student):
    ref = ref.splitlines(keepends=True)
    student = student.splitlines(keepends=True)

    return ''.join(unified_diff(ref, student, fromfile="ref", tofile="student"))

if __name__ == "__main__":
    parser = ArgumentParser(description = "42sh TestSuite")
    parser.add_argument('bin', metavar='BIN')
    args = parser.parse_args();

    binary = Path(args.bin).absolute()

    with open("tests.yml", "r") as tests_files:
        test_case = yaml.safe_load(tests_files)

    for tests in test_case:
        try:
            test(binary, tests)
        except AssertionError as err:
            print(f"[{colored('KO', 'red')}]", tests["name"])
            print(err)
        else:
            print(f"[{colored('OK', 'green')}]", tests["name"])
