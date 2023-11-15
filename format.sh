#!/bin/bash

FILES=$(find . -name "*.c" -o -name "*.h")

for file in $FILES
do
    betty-style "$file"
    betty-doc "$file"
    indent -kr -i8 "$file"
done

