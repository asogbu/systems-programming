#!/usr/bin/env python3

import requests

# Constants

URL = 'http://catalog.cse.nd.edu:9097/query.json'

# TODO: Make a HTTP request to URL
response = requests.get(URL)

# TODO: Access json representation from response object
data = response.json()

# TODO: Display all machine names with type "wq_factory"
for machine in data:
	if machine['type'] == 'wq_factory':
		print(machine['name'])
