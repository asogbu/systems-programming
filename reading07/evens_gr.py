#!/usr/bin/env python3

import sys

def evens(stream):
    # TODO: Implementation that uses yield statement
	for number in sys.stdin:
		number = number.strip()
		if int(number) % 2 == 0:
			yield number

print(' '.join(evens(sys.stdin)))
