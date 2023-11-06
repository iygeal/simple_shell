#!/bin/bash

#Read the value from the file and store it in the variable pid_max
pid_max=$(cat /proc/sys/kernel/pid_max)

#print the value
echo "The maximum value of a process ID can be is: $pid_max"