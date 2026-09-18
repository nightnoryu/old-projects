from datetime import datetime
import shutil
import argparse
import os
import sys


# Prefix for all the names
PREFIX = "Screenshot"
# Format to use for date
DATE_FORMAT = "%d-%m-%y"


def get_ext(name):
    """Returns extension of the filename"""
    return name.split(".")[-1]


def parse_arguments():
    """Processes the input arguments"""
    parser = argparse.ArgumentParser(
        description="""Renames the specified file with the specified prefix,
        current date and user-defined prefix. Mostly supposed for
        screenshots.""")
    parser.add_argument("FILE",
                        help="file to rename")
    return parser.parse_args()


def main():
    """Entry point of the script"""
    # Parse the input arguments
    args = parse_arguments()
    file = os.path.realpath(args.FILE)

    # Check for errors
    if not os.path.isfile(file):
        print("The invalid file specified.")
        sys.exit(1)

    # Get the custom postfix
    postfix = input("Enter the postfix (can be blank): ").strip()

    # Generate the name: prefix + date + postfix (if not empty) + .ext
    new_name = "{}_{}{}.{}".format(
        PREFIX,
        datetime.now().strftime(DATE_FORMAT),
        ("_" + postfix) if postfix else "",
        get_ext(old_name))

    # Form a full path for the new name
    filepath, old_name = os.path.split(file)
    new_file = os.path.join(filepath, new_name)

    # Check if that file already exists
    if os.path.isfile(new_file):
        print("Error: file '{}' already exists.".format(new_file))
        print("Try adding a different postfix.")
        sys.exit(1)

    # Rename the file
    os.rename(file, new_file)
    # Log the action
    print("{} -> {}".format(old_name, new_name))


# Entry point
if __name__ == "__main__":
    main()
