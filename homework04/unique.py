#!/usr/bin/env python3

import os
import sys

# Functions

def usage(status=0):
    ''' Display usage message and exit with status. '''
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [flags]

    -c      Prefix lines by the number of occurences
    -d      Only print duplicate lines
    -i      Ignore differences in case when comparing, prints out full line in lowercase
    -u      Only print unique lines

By default, {progname} prints one of each type of line.''')
    sys.exit(status)

def count_frequencies(stream=sys.stdin, ignore_case=False):
    ''' Count the line frequencies from the data in the specified stream while
    ignoring case if specified. '''
    
    frequencies = {}
    for line in stream:
        line = line.rstrip()
        if ignore_case:
            line = line.lower()
        frequencies[line] = frequencies.get(line, 0) + 1
    
    return frequencies

def print_lines(frequencies, occurrences=False, duplicates=False, unique_only=False):
    ''' Display line information based on specified parameters:

    - occurrences:  if True, then prefix lines with number of occurrences
    - duplicates:   if True, then only print duplicate lines
    - unique_only:  if True, then only print unique lines
    '''
    for line, frequency in frequencies.items():
        if unique_only:
            if frequency != 1:
                continue
        elif duplicates:
            if frequency < 2:
                continue

        if occurrences:
            print(f'{frequency:>7} {line}')
        else:
            print(line)

def main():
    ''' Process command line arguments, count frequencies from standard input,
    and then print lines. '''
    
    # Default values
    occurrences = False
    duplicates = False
    unique_only = False
    ignore_case = False

    # Process command line arguments
    arguments = sys.argv[1:]
    while len(arguments) > 0:
        arg = arguments.pop(0)
        if arg == '-h':
            usage(0)
        elif arg == '-c':
            occurrences = True
        elif arg == '-d':
            duplicates = True
            unique_only = False
        elif arg == '-i':
            ignore_case = True
        elif arg == '-u':
            unique_only = True
            duplicates = False
        else:
            usage(1)

    # Count frequencies from stdin and print lines
    print_lines(count_frequencies(sys.stdin, ignore_case), occurrences, duplicates, unique_only)
        

# Main Execution

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
