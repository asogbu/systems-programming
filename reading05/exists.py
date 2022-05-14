#!/usr/bin/env python3

import sys
import os

# Check if there are no arguments
if len(sys.argv) == 1:
	print('Usage: exists.py file0...')
	sys.exit(1);

# Check each command line argument
exitcode = 0;
for arg in sys.argv[1:]:
	# Check if arugment exists
	if os.path.exists(arg):
		print(str(arg) + ' exists!')
	else:
		print(str(arg) + ' does not exist!')
		exitcode = 1

sys.exit(exitcode)
