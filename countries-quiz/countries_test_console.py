import sys
import random

from countries_scanner import CountriesScanner


DELIMITER = ':'
FILENAME = 'countries.txt'


def print_result(amount, wrong_answers, wrong_countries):
    if wrong_answers > 0:
        print('\nYou have made %d %s out of %d countries.'
                % (wrong_answers, 'mistake' if amount == 1 else 'mistakes', amount))

        print('Wrong countries:')
        for country, capital in wrong_countries.items():
            print('%s - %s' % (country, capital))
    else:
        print('\nZero mistakes. Nice.')


# Initialize a scanner object
countries_scanner = CountriesScanner(FILENAME, DELIMITER)
# Get the dictionary
countries_dict = countries_scanner.get_countries_dict()


# Suffle the countries
keys = list(countries_dict.keys())
random.shuffle(keys)

wrong_answers = 0
wrong_countries = {}
print('The countries will be printed on the screen. You need to write a capital of this country. There will be %d countries.' % len(countries_dict))

# Test cycle
for country in keys:
    capital = countries_dict[country]
    answer = input('%s - ' % country)
    if answer == capital:
        print('Yeah. Good.')
    else:
        print('The right answer is %s.' % capital)
        wrong_countries[country] = capital
        wrong_answers += 1
    # So the countries won't repeat
    del countries_dict[country]
print_result(countries_scanner.lines, wrong_answers, wrong_countries)

# for country, capital in countries_dict.items():
#     answer = input('%s - ' % country)
#     if answer == capital:
#         print('Yeah. Good.')
#     else:
#         print('The right answer is %s.' % capital)
#         wrong_countries[country] = capital
#         wrong_answers += 1
# print_result(lines, wrong_answers, wrong_countries)