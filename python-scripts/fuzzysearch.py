import os
import sys
import re


def print_help():
    """Prints help message"""
    print("""fuzzysearch.py performs a fuzzy file search among the files in directory.
USAGE: fuzzysearch (search|rec_search|help) <query>
    search                Plain search for files in current directory
    rec_search            Search in including subdirectories
    help                  Print this help message""")

def check_argv(argv):
    """Makes sure the argv is valid"""
    if len(argv) < 1:
        print_help()
        sys.exit(1)
    elif (argv[0] == 'search' or argv[0] == 'rec_search') and len(argv) < 2:
        print_help()
        sys.exit(1)

def make_regex(query):
    """Returns a regex for search"""
    # This will make up a search regex (e.g. 'hello' will be '.*h.*e.*l.*l.*o.*')
    letters = list(query)
    regex_string = '.*' + '.*'.join(letters)
    regex = re.compile(regex_string)
    return regex

def search(query):
    """Performs fuzzy search in current directory"""
    regex = make_regex(query)

    filenames = []
    for filename in os.listdir('.'):
        if os.path.isfile(filename) and regex.match(filename):
            filenames.append(filename)

    if len(filenames) > 0:
        print('\n'.join(filenames))
    else:
        print('Nothing was found')

def recursive_search(query):
    """Performs recursive search in current directory"""
    regex = make_regex(query)

    filenames = []
    for root, dirs, files in os.walk('.'):
        for filename in files:
            if regex.match(filename):
                filenames.append(os.path.join(root, filename))

    if len(filenames) > 0:
        print('\n'.join(filenames))
    else:
        print('Nothing was found')


def main(argv):
    check_argv(argv)

    if argv[0] == 'help':
        print_help()
        sys.exit(0)
    elif argv[0] == 'search':
        search(argv[1])
    elif argv[0] == 'rec_search':
        recursive_search(argv[1])
    else:
        print('Unknown command: {}'.format(argv[0]))


if __name__ == '__main__':
    main(sys.argv[1:])
