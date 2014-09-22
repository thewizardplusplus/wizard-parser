#!/usr/bin/env bash

result=`./main "$1" 2>&1`
if [[ $? == 0 ]]
then
	xmllint --format <(echo $result)
else
	echo $result
fi
