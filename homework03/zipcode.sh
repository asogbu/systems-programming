#!/bin/sh

# Globals

URL=https://www.zipcodestogo.com/
STATE=Indiana
CITY='.*'

# Functions

usage() {
	cat 1>&2 <<EOF
Usage: $(basename $0) [zipcode]

-c Specify the city to search for within the state
-s Specify the state to search through

If no state is specified, $STATE is assumed.
EOF
	exit $1
}

# Parse Command Line Options

while [ $# -gt 0 ]; do
    case $1 in
    -h) usage 0;;
	-c) CITY=$2; shift;;
	-s) STATE=$(echo $2 | sed -E -e 's/ /%20/g'); shift;;
     *) usage 1;;
    esac
    shift
done

# Filter Pipeline(s)

curl -s "$URL"/"$STATE"/ | grep -E -o [^/]+/../[0-9]{5} | grep "$CITY"/ | sed 's@.*/.*/@@g' | sort | uniq
