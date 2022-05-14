#!/usr/bin/env python3

import sys

print(' '.join(
    # TODO: One-line expression with map, filter, lambda
	filter(lambda x: int(x) % 2 == 0, map(lambda x: x.strip(), sys.stdin))
))
