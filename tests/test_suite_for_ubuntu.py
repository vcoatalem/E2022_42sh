import subprocess
import yaml
import os
from difflib import unified_diff
from termcolor import colored

path = "list-test"

def diff(ref, sh42):
    ref = ref.splitlines(keepends=True)
    sh42 = sh42.splitlines(keepends=True)

    return ''.join(unified_diff(ref, sh42, fromfile="ref", tofile="42sh"))

def test(ref, sh42):
    assert ref[0] == sh42[0], \
        f"stdout differs:\n{diff(ref[0].decode(), sh42[0].decode())}"


fname = []
for root,d_names,f_names in os.walk(path):
	for f in f_names:
		with open(os.path.join(root, f)) as stream:
			try:
				l = yaml.safe_load(stream)
				for i in range (len(l)):
					print("TEST NAME:" + l[i]['name'] + "\n")
					Command = l[i]['stdin']
					processbash = subprocess.Popen(Command.split(), stdout=subprocess.PIPE)
					outputbash, errorbash = processbash.communicate()
					returnbash = subprocess.call(Command.split())               
					print("BASH= " + outputbash.decode())
					Command42 = Command + "| ./42sh" 
					print("cmd42=" + Command42)
					process42 = subprocess.Popen(Command42.split(), stdout=subprocess.PIPE)
					output42, error42 = process42.communicate()
					print("42SH=" + output42.decode() + "\n\n")
					return42 = subprocess.call(Command42.split())
					try:
						test((outputbash, returnbash, errorbash), (output42, return42, error42))
					except AssertionError as err:
						print(f"[{colored('KO', 'red')}]", l[i]['name'])
						#print(err)
					else:
						print(f"[{colored('OK', 'green')}]", l[i]['name'])
						#print(stdout)
			except yaml.YAMLError as exc:
				print(exc)
