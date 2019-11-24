from argparse import ArgumentParser
from pathlib import Path
from difflib import unified_diff
from termcolor import colored

import subprocess as sp
import yaml
import time
import os

def run_42sh(args, stdin):
    return sp.run(args, capture_output=True, text=True, input=stdin)

def remove_bracket(sh):
    res = ""
    for i in range (len(sh)):
        if (sh[i] == '['):
            break;
        else:
            res = res + sh[i]
    return res
def test(binary, tests):
    start_time = time.time()
    print(tests["stdin"])
    ref = run_42sh(["bash", "--posix"], tests["stdin"])
    sh = run_42sh([binary], tests["stdin"])
   # sh.stdout = remove_bracket(sh.stdout)
    for check in tests.get("checks", ["stdout", "stderr", "returncode"]):
        if check == "stdout":
            print(tests["name"] + " execution time: %.10s" % (time.time() -
                        start_time))
            assert ref.stdout == sh.stdout, \
                f"stdout differs:\n{diff(ref.stdout, sh.stdout)}"
        elif check == "stderr":
            print(tests["name"] + " execution time: %.10s" % (time.time() -
                        start_time))
            assert ref.stderr == sh.stderr, \
                f"stderr differs:\n{diff(ref.stderr, sh.stderr)}"
        elif check == "returncode":
            print(tests["name"] + " execution time: %.10s" % (time.time() -
                        start_time))
            assert ref.returncode == sh.returncode, \
                f"Exit with {sh.returncode} , got {ref.returncode}"
        elif check == "has_stderr":
            print(tests["name"] + " execution time: %.10s" % (time.time() -
                        start_time))
            assert sh.stderr != "", "Something was expected on stderr"

def diff(ref, sh):
    ref = ref.splitlines(keepends=True)
    sh = sh.splitlines(keepends=True)

    return ''.join(unified_diff(ref, sh, fromfile="ref", tofile="42sh"))

if __name__ == "__main__":
    test_time = time.time()
    parser = ArgumentParser(description = "42sh TestSuite")
    parser.add_argument('bin', metavar='BIN')
    parser.add_argument("-l", "--list", action="store_true")
    parser.add_argument("-c", "--category", type=str)
    parser.add_argument("-t", "--timeout", type=int)
    args = parser.parse_args();
    binary = Path(args.bin).absolute()
    if args.list:
        sp.call(["ls", "list-test/"])
    else:
        success = 0
        fail = 0
        if args.category:
            with open(args.category, "r") as tests_files:
                test_case = yaml.safe_load(tests_files)
            for tests in test_case:
                try:
                    test(binary, tests)
                except AssertionError as err:
                    print(f"[{colored('KO', 'red')}]", tests["name"])
                    print(err)
                    fail = fail + 1
                else:
                    print(f"[{colored('OK', 'green')}]", tests["name"])
                    success = success + 1
        else:
            path_list = []
            for (directories, _, sub_files) in os.walk("list-test/"):
                for files in sub_files:
                    path_file = directories + '/' + files
                    path_list.append(path_file)
            for elmt in path_list:
                with open(elmt, "r") as tests_files:
                    test_case = yaml.safe_load(tests_files)
                for tests in test_case:
                    try:
                        test(binary, tests)
                    except AssertionError as err:
                        print(f"[{colored('KO', 'red')}]", tests["name"])
                        print(err)
                        fail = fail + 1
                    except TimeoutError as err:
                        print(err)
                    else:
                        print(f"[{colored('OK', 'green')}]", tests["name"])
                        success = success + 1
        print("------------ Tests Results -------------")
        print("Numbers of tests:",success + fail)
        print(f"Tests succeed: {colored(success, 'green')}")
        print(f"Tests failed: {colored(fail, 'red')}")
        print("Time to execute all tests: %.s" % (time.time() - test_time))
        print("----------------------------------------")
