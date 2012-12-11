#!/bin/bash

for TESTCASE in `ls ./bin/*Test`
do
	echo -e "\033[1;30mRunning test: \033[0;36m${TESTCASE}\033[0m"
	${TESTCASE}
done
