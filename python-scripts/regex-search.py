import os
import re
import sys


# Loops through file lines
# Returns a list with matched filename, line number and the line
def findLines(file, regex):
	txtFile = open(file, 'r')

	matches = []
	line_count = 1

	for line in txtFile.readlines():
		if regex.match(line) != None:
			# remove newline symbol from the end of the line
			if line.endswith('\n'):
				matches.append('{}:{} - {}'.format(file, line_count, line[:-1]))
			else:
				matches.append('{}:{} - {}'.format(file, line_count, line))
		line_count += 1

	txtFile.close()
	return matches


# Form a regex
regex = re.compile(sys.argv[1].encode().decode('unicode_escape'))
matches = []


# Scan through all files in directory
for currentFile in os.listdir('.'):
	if currentFile.split('.')[1] == 'txt':
		matches += findLines(currentFile, regex)


# Output the matches
print('\n'.join(matches))
