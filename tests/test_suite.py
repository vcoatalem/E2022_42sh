from argparse import ArgumentParser
from pathlib import Path
from difflib import unified_diff

import difflib

import subprocess as sp
import yaml
import time
import os

GREEN =  '\033[32m'
WHITE = '\033[37m'
global html



def run_42sh(args, stdin):
#    stdin = stdin + ';'
    print(stdin)
    return sp.run(args, capture_output=True, text=True, input=stdin)

def remove_bracket(sh):
    res = ""
    for i in range (len(sh)):
        if (sh[i] == '['):
            break;
        else:
            res = res + sh[i]
    return res

def put_in_file_sh(out):
    new_file = open("shout.txt", "a")
    new_file.write(out.stdout)
    new_file.write("\n")
    new_file.close()

def put_in_file_ref(out):
    new_file = open("refout.txt", "a")
    new_file.write(out.stdout)
    new_file.write("\n")
    new_file.close()

def test(binary, tests):
    start_time = time.time()
    ref = run_42sh(["bash", "--posix"], tests["stdin"])
    sh = run_42sh([binary], tests["stdin"])
    put_in_file_sh(sh)
    put_in_file_ref(ref)
   # sh.stdout = remove_bracket(sh.stdout)
    print(tests["name"] + " execution time: %.10s" % (time.time() -
                        start_time))
    print(sh.stdout)
    for check in tests.get("checks", ["stdout", "stderr", "returncode"]):
        
        if check == "stdout":
            assert ref.stdout == sh.stdout, \
                f"stdout differs:\n{diff(ref.stdout, sh.stdout)}"
        elif check == "stderr":
            assert ref.stderr == sh.stderr, \
                f"stderr differs:\n{diff(ref.stderr, sh.stderr)}"
        elif check == "returncode":
            assert ref.returncode == sh.returncode, \
                f"Exit with {sh.returncode} , got {ref.returncode}"
        elif check == "has_stderr":
            assert sh.stderr != "", "Something was expected on stderr"

def diff(ref, sh):
    ref = ref.splitlines(keepends=True)
    sh = sh.splitlines(keepends=True)
    differ = difflib.HtmlDiff( tabsize=4, wrapcolumn=40 )
    html = differ.make_file( ref, sh, context=False )
    outfile = open( 'test.html', 'w' )
    outfile.write(html)
    outfile.close() 

    return ''.join(unified_diff(ref, sh, fromfile="ref", tofile="42sh"))

if __name__ == "__main__":
    test_time = time.time()
    open("refout.txt", "w").close()
    open("shout.txt", "w").close()
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
                    print(f"\033[31m[KO]", tests["name"], "\033[m")
                    print(err)
                    fail = fail + 1
                else:
                    print(f"\033[32m[OK]", tests["name"], "\033[m")
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
                        print(f"\033[31m[KO]", tests["name"], "\033[m\n")
                        print(err)
                        fail = fail + 1
                    except TimeoutError as err:
                        print(err)
                    else:
                        print(f"\033[32m[OK]", tests["name"], "\033[m\n")
                        success = success + 1
        print("------------ Tests Results -------------")
        print("Numbers of tests:",success + fail)
        print(f"Tests succeed" , success)
        print(f"Tests failed" , fail)
        print("Time to execute all tests: %.10s" % (time.time() - test_time))
        print("----------------------------------------")
