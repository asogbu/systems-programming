#!/bin/sh

# Globals

URL="https://forecast.weather.gov/zipcity.php"
ZIPCODE=46556
FORECAST=0
TEMPUNIT=2

# Functions

usage() {
    cat 1>&2 <<EOF
Usage: $(basename $0) [zipcode]

-c    Use Celsius degrees instead of Fahrenheit for temperature
-f    Display forecast text

If zipcode is not provided, then it defaults to $ZIPCODE.
EOF
    exit $1
}

weather_information() {
    # Fetch weather information from URL based on ZIPCODE
	curl -sL "$URL?inputstring=$ZIPCODE" | grep myforecast-current | sed -E -e 's/^[^>]*>//' | sed -E -e 's/<.*//' | sed -E -e 's/&.*//'
}

temperature() {
    # Extract temperature information from weather source
    weather_information | sed -n "$1"p
}

forecast() {
    # Extract forecast information from weather source
    weather_information | sed -n 1p
}

# Parse Command Line Options

while [ $# -gt 0 ]; do
    case $1 in
        -h) usage 0;;
		-c) TEMPUNIT=3;;
		-f) FORECAST=1;;
		[0-9][0-9][0-9][0-9][0-9]) ZIPCODE=$1;;
		*) usage 1;;
    esac
    shift
done

# Display Information

if [ $FORECAST -eq 1 ]
then
	echo "Forecast:    $(forecast)"
fi

echo "Temperature: $(temperature "$TEMPUNIT") degrees"
