import re

import pyperclip


# Form regexes
phoneRegex = re.compile(r'''(
	(\+?\d)?\s?                     # country code
	(\d{3}\s?)                      # prefix
	(\d{2}[.\- ]?\d{2}[.\- ]?\d{2}) # number
)''', re.RegexFlag.VERBOSE)

emailRegex = re.compile(r'''(
	[a-zA-Z0-9._%+-]+ # username
	@
	[a-zA-Z0-9._]+    # domain name
	(\.[a-zA-Z]{2,4}) # top level domain
)''', re.RegexFlag.VERBOSE)


# Get the text
text = str(pyperclip.paste())

# Match regexes to the text
matches = []

for groups in phoneRegex.findall(text):
	num = ''.join(groups[1], groups[2], groups[3])
	matches.append(num)
	
for groups in emailRegex.findall(text):
	matches.append(groups[0])


# Output the matches
if len(matches) > 0:
	print('\n'.join(matches))
else:
	print('No matches found')
