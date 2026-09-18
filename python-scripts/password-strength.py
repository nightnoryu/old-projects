import re
import sys


def main():
	if len(sys.argv) != 2:
		print('USAGE: python {} <password>'.format(sys.argv[0]))
		sys.exit(1)

	passwordRegex = re.compile(r'''(
		^(?=.*[a-z]) # lowercase letters
		(?=.*[A-Z])  # uppercase letters
		(?=.*[0-9])  # digits
		(?=.{8,})    # 8 characters or longer
	)''', re.RegexFlag.VERBOSE)

	if passwordRegex.match(sys.argv[1]) != None:
		print('Strong password')
	else:
		print('Weak password')


if __name__ == "__main__":
		main()
