#!/usr/bin/env python3

import collections
import re
import requests

# Globals

URL = 'https://cse.nd.edu/undergraduate/computer-science-curriculum/'
numberToLevel = {'2':'Sophomore', '3':'Junior', '4':'Senior'}

# Initialize a default dictionary with integer values
counts = collections.defaultdict(int)

# TODO: Make a HTTP request to URL
response = requests.get(URL)

# TODO: Access text from response object
data = response.text

# TODO: Compile regular expression to match CSE courses (ie. CSE XXXXX)
regex = re.compile(r'CSE [0-9]{5}')

# TODO: Search through data using compiled regular expression and count up all
# the courses per class year
for course in re.findall(regex, data):
	counts[numberToLevel[course[4]]] += 1

# Sort items in counts dictionary by value in reverse order and display counts
# and class year
for year, count in sorted(counts.items(), key=lambda p: p[1], reverse=True):
    print(f'{count:>7} {year}')
