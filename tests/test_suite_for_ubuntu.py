import subprocess
import yaml
import os
path = "list-test"

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
					print("BASH= " + outputbash.decode())
					Command42 = Command + " | ./42sh "
					#print("cmd42=" + Command42)
					process42 = subprocess.Popen(Command42.split(), stdout=subprocess.PIPE)
					output42, error42 = process42.communicate()
					print("42SH=" + output42.decode() + "\n\n")
			except yaml.YAMLError as exc:
				print(exc)