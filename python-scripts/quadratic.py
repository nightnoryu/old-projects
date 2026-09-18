import cmath
import math
import sys


def get_float(msg, allow_zero=True):
	'''Returns a float number'''
	x = None
	while x is None:
		try:
			x = float(input(msg))
			# Check the number
			if not allow_zero and abs(x) < sys.float_info.epsilon:
				print('The number is too small or zero.')
				x = None
		except ValueError as err:
			# Print an input error
			print(err)
	return x


# Input the values
print('ax\N{superscript two} + bx + c = 0')
a = get_float('Enter a: ', False)
b = get_float('Enter b: ')
c = get_float('Enter c: ')


# Calculate the results
x1 = None
x2 = None
discriminant = (b ** 2) - (4 * a * c)

if discriminant == 0:
	x1 = -(b / (2 * a))
else:
	if discriminant > 0:
		root = math.sqrt(discriminant)
	else:
		root = cmath.sqrt(discriminant)
	x1 = (-b - root) / (2 * a)
	x2 = (-b + root) / (2 * a)


# Print the results
equation = ('\n{}x\N{superscript two} + {}x + {} = 0\n'
		  'x = {}'.format(a, b, c, x1))
if x2 is not None:
	equation += '\nx = {}'.format(x2)

print(equation)
