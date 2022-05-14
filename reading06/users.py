#!/usr/bin/env python3

import csv

# Constants

PATH = '/etc/passwd'

# TODO: Loop through ':' delimited data in PATH and extract the fifth field
# (user description)
users = []
for record in csv.reader(open(PATH), delimiter=':'):
	users.append(record[4])

# TODO: Print user descriptions in sorted order
for user in sorted(users):
	if user:
	    print(user)
