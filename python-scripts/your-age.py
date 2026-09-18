import datetime
import math

# Input user's birthday
year  = int(input('Enter your birthday year: '))
month = int(input('Enter your birthday month: '))
day   = int(input('Enter your birthday day: '))

# Initialize a birthday date object
birthday = datetime.date(year, month, day)
# Get today's date
today = datetime.date.today()

# Find time delta
delta = today - birthday

# Print information
print('\nYou have lived for this long so far:')
print('{} years'.format(math.floor(delta.days / 365)))
print('OR')
print('{} days'.format(delta.days))
print('OR')
print('{} seconds'.format(math.floor(delta.total_seconds())))
