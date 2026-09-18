import sys
import unicodedata


def print_unicode_table(word):
	'''Prints a table with unicode characters'''
	print('decimal   hex    chr  {:^40}'.format('name'))
	print('------- ------- ----- {}'.format('-' * 40))

	code = ord(' ')
	end = sys.maxunicode

	while code < end:
		c = chr(code)
		name = unicodedata.name(c, '*** unknown ***')
		if word is None or word in name.lower():
			print('{:7} {:7} {:^5} {}'.format(ord(c), hex(ord(c)), c, name.title()))
		code += 1


# Check input parameters
word = None
if len(sys.argv) > 1:
	if sys.argv[1] == '-h' or sys.argv[1] == '--help':
		print('usage: {} [word]'.format(sys.argv[0]))
		word = 0
	else:
		word = sys.argv[1].lower()

# Print the table with the presented word
if word != 0:
	print_unicode_table(word)
