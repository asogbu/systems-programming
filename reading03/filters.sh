#!/bin/bash

q1_answer() {
    # TODO: Complete pipeline
    echo "Read the fine manual" | tr a-z A-Z
}

q2_answer() {
    # TODO: Complete pipeline
    echo "BTW, I use Arch" | sed s/Arch/Pop/
}

q3_answer() {
    # TODO: Complete pipeline
    echo "     Yes, do as I say" | sed 's/^[ ]*//'
}

q4_answer() {
    # TODO: Complete pipeline
    curl -sL https://yld.me/raw/yWh | grep root:x | tr : '\t' | cut -f 7
}

q5_answer() {
    # TODO: Complete pipeline
    curl -sL https://yld.me/raw/yWh | egrep 4[[:digit:]]*7
}

q6_answer() {
    # TODO: Complete pipeline
    curl -sL https://yld.me/raw/yWh | sed "s_/bin/[a-z]*sh_/bin/zsh_" | grep zsh
}
