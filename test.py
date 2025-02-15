import os
import subprocess
import sys
import pexpect

if not os.getenv("VIRTUAL_ENV"):
	print("Ambiente virtual não está ativado. Ativando automaticamente...")
	subprocess.call(["source", "venv/bin/activate"], shell=True)
	sys.exit(0)

GREEN = "\033[92m"
RED = "\033[91m"
MAGENTA = "\033[35m"
RESET = "\033[0m"
CYAN = "\033[96m"
YELLOW = "\033[93m"
BLUE = "\033[94m"
WHITE = "\033[97m"

tests = [
	("echo","\n"),
	("echo ola mundo","ola mundo\n"),
	("echo \"ola mundo\"","ola mundo\n"),
	("echo 'ola mundo'","ola mundo\n"),
	("echo \"'ola mundo'\"","'ola mundo'\n"),
	("echo '\"ola mundo\"'","\"ola mundo\"\n"),
	("echo -n ola mundo","ola mundo"),
	("echo -n-n-n ola mundo","-n-n-n ola mundo"),
	("echo -nnnnnnnn ola mundo","ola mundo"),
	("echo \"-n ola mundo\"","-n ola mundo\n"),
	("echo '-n ola mundo'","-n ola mundo\n"),
	("echo -n-n-n-n-n-n ola mundo","-n-n-n-n-n-n ola mundo\n"),
	("echo \"\"\"\"\"ola mundo\"\"\"\"\"","ola mundo\n"),
	("echo \"\"\"'ola mundo'\"\"\"","'ola mundo'\n"),
	("echo '''\"ola mundo\"'''","\"ola mundo\"\n"),
	("echo ''''\"ola mundo\"''''","ola mundo\n"),
	("echo \"\"\"'ola mundo'\"\"\"","'ola mundo'\n"),
	("echo \"\"\"'''ola mundo'''\"\"\"","'''ola mundo'''\n"),
]


def run_test(test_id, command, expected_output):
	minishell = pexpect.spawn("./minishell", encoding="utf-8", timeout=2)
	minishell.expect(r"👹\$ ")
	minishell.sendline(command)
	minishell.expect(r"👹\$ ")
	output = minishell.before.strip()
	output_lines = output.split("\n")
	if output_lines[0].startswith(command):
		output_lines.pop(0)
	output = "\n".join(output_lines).strip()
	minishell.sendline("exit")
	if output == expected_output.strip():
		print(f"Teste {test_id}: {command} {GREEN}[OK]{RESET}")
	else:
		print(f"Teste {test_id}: {command} {RED}[KO]{RESET}")
		print(f"{MAGENTA}Esperado:{RESET}")
		print(f"{GREEN}{expected_output}{RESET}")
		print(f"{MAGENTA}Obtido:{RESET}")
		print(f"{RED}{output}{RESET}")

def main():
	for i, (command, expected_output) in enumerate(tests, start=1):
		run_test(i, command, expected_output)
if __name__ == "__main__":
	main()
