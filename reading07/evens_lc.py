#!/usr/bin/env python3

import sys

print(' '.join(
    # TODO: One-line expression with list comprehension
	[number for number in [number.strip() for number in sys.stdin] if int(number) % 2 == 0]
))
