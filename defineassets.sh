#!/bin/bash

DEFASSETS=""
NL=$'\n'

for file in ./assets/*.txt 
do
  filename=$(basename "${file%.*}")
  DEFASSETS+="#define $filename \"\\$NL"
  DEFASSETS+="$(cat $file | sed -z 's/\\/\\\\/g' | sed -z 's/"/\\"/g' | sed -z 's/\n/\\n\\\n/g')"
  DEFASSETS+="$NL\"$NL"
done


echo "$DEFASSETS" > ./include/assets.h
