#!/usr/bin/env python3

import concurrent.futures
import hashlib
import os
import string
import sys

# Constants

ALPHABET = string.ascii_lowercase + string.digits

# Functions

def usage(exit_code=0):
    progname = os.path.basename(sys.argv[0])
    print(f'''Usage: {progname} [-a ALPHABET -c CORES -l LENGTH -p PATH -s HASHES]
    -a ALPHABET Alphabet to use in permutations
    -c CORES    CPU Cores to use
    -l LENGTH   Length of permutations
    -p PREFIX   Prefix for all permutations
    -s HASHES   Path of hashes file''')
    sys.exit(exit_code)

def md5sum(s):
    ''' Compute md5 digest for given string. '''
    # Use the hashlib library to produce the md5 hex digest of the given
    # string.

    return hashlib.md5(s.encode()).hexdigest()

def permutations(length, alphabet=ALPHABET):
    ''' Recursively yield all permutations of alphabet up to given length. '''
    # Use yield to create a generator function that recursively produces
    # all the permutations of the given alphabet up to the provided length.

    if length <= 0:
        yield ''
    elif length == 1:
        for character in alphabet:
            yield character
    else:
        for character in alphabet:
            for string in permutations(length - 1, alphabet):
                yield character + string

def flatten(sequence):
    ''' Flatten sequence of iterators. '''
    # Iterate through sequence and yield from each iterator in sequence.
    for seq in sequence:
        for character in seq:
            yield character

def crack(hashes, length, alphabet=ALPHABET, prefix=''):
    ''' Return all password permutations of specified length that are in hashes
    by sequentially trying all permutations. '''
    # Return list comprehension that iterates over a sequence of
    # candidate permutations and checks if the md5sum of each candidate is in
    # hashes.
    
    return [prefix + permutation for permutation in permutations(length, alphabet) if md5sum(prefix + permutation) in hashes]
    
def whack(arguments):
    ''' Call the crack function with the specified list of arguments '''
    return crack(*arguments)

def smash(hashes, length, alphabet=ALPHABET, prefix='', cores=1):
    ''' Return all password permutations of specified length that are in hashes
    by concurrently subsets of permutations concurrently.
    '''
    # TODO: Create generator expression with arguments to pass to whack and
    # then use ProcessPoolExecutor to apply whack to all items in expression.

    arguments = ((hashes, length - 1, alphabet, prefix + letter) for letter in alphabet)

    with concurrent.futures.ProcessPoolExecutor(cores) as executor:
        return flatten(executor.map(whack, arguments))

# Main Execution

def main():
    arguments   = sys.argv[1:]
    alphabet    = ALPHABET
    cores       = 1
    hashes_path = 'hashes.txt'
    length      = 1
    prefix      = ''

    # TODO: Parse command line arguments
    while len(arguments) > 0:
        arg = arguments.pop(0)
        if arg == '-h':
            usage(0)
        elif arg == '-a':
            alphabet = arguments.pop(0)
        elif arg == '-c':
            cores = int(arguments.pop(0))
        elif arg == '-l':
            length = int(arguments.pop(0))
        elif arg == '-p':
            prefix = arguments.pop(0)
        elif arg == '-s':
            hashes_path = arguments.pop(0)
        else:
            usage(1)

    # TODO: Load hashes set
    hashes = {line.rstrip() for line in open(hashes_path)}

    # TODO: Execute crack or smash function
    passwords = smash(hashes, length, alphabet, prefix, cores)

    # TODO: Print all found passwords
    for password in passwords:
        print(password)

if __name__ == '__main__':
    main()

# vim: set sts=4 sw=4 ts=8 expandtab ft=python:
