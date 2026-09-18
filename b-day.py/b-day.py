#!/usr/bin/env python3

from datetime import date
from math import floor
from textwrap import dedent
import argparse
import os
import re

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Globals
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

# The main birthday storage file
BDAY_FILE=os.path.join(os.path.dirname(os.path.realpath(__file__)),
                       "bday_list.txt")

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Classes
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class CustomArgumentParser(argparse.ArgumentParser):
    """Override ArgumentParser's help message"""
    def format_help(self):
        help_text = dedent(f"""\
        B-day.py is a simple birthday manager.

        Usage: {self.prog} [OPTIONS] MODE [MODE_OPTIONS]

        MODE:
          Either 'show' or 'add', for displaying and adding the dates respectively

        Options:
          -h,  --help      show help

        'show' mode options:
          -d,  --days   display dates within the specified amount of days

        For more information visit:
        https://github.com/m3tro1d/b-day.py
        """)
        return help_text

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Functions
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def positive_int(string):
    """Converts the string to a positive integer"""
    try:
        value = int(string)
        if value <= 0:
            raise ValueError
    except ValueError:
        error = f"Invalid value: {string}"
        raise argparse.ArgumentTypeError(error)
    return value


def file_record(name, date):
    """Add a birthday record to the file"""
    with open(BDAY_FILE, "a") as f:
        f.write(f"{name} : {date}\n")


def file_get_records():
    """Returns all records from the file in a tuple"""
    # Regex for our dates
    record_regex = re.compile(r"([\w\s]+) : (\d{4}-\d{2}-\d{2})\n")
    contents = ""
    try:
        # Read the file
        with open(BDAY_FILE, "r") as f:
            contents = f.read()
    except FileNotFoundError:
        # Print an alert
        print("The birthday file does nott exist!")
        print("Try adding a date with 'b-day.py add'.")
        return tuple()
    else:
        return record_regex.findall(contents)


def show_dates(days=None):
    """Prints all records within the specified amount of days"""
    for record in file_get_records():
        today = date.today()
        # Get the info
        name = record[0]
        bday = date.fromisoformat(record[1])
        # Calculate age
        age = floor((today - bday).days / 365)
        # If 'days' wasn't specified, show all of the dates
        if not days:
            # Print the info
            print(f"{name} : {bday} : {age} years")
        # If 'days' is specified, show only records within the range
        else:
            # Get the next birthday date
            next_bday = bday.replace(year=today.year)
            # If it already happened, take the next year
            if next_bday.month < today.month:
                next_bday = next_bday.replace(year=today.year + 1)
            # Find the delta & print if it's less or equal
            delta = next_bday - today
            if delta.days <= days:
                print(f"{name} : {bday} : {age} years : {delta.days}"
                      " days until the next bday")


def add_date():
    """Prompts for info & adds a new date to the file"""
    # Input the needed information
    name = input("Name: ")
    bday_str = input("Birthday date (YYYY-MM-DD): ")
    bday = date.fromisoformat(bday_str)
    # Write the new date to file
    file_record(name, bday)
    print("All set!")

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Main script
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~

def main():
    """Main script"""
    # Parse the input arguments
    parser = CustomArgumentParser(usage="%(prog)s [OPTIONS] MODE [MODE_OPTIONS]")
    subparsers = parser.add_subparsers(help="available commands")

    # Show dates command
    parser_show = subparsers.add_parser("show")
    parser_show.add_argument("-d", "--days", type=positive_int, default=None)
    parser_show.set_defaults(func=lambda args: show_dates(args.days))

    # Add date command
    parser_add = subparsers.add_parser("add")
    parser_add.set_defaults(func=lambda args: add_date())

    args = parser.parse_args()
    args.func(args)


# Entry point
if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\nUser interrupt", file=sys.stderr)
        sys.exit(1)
