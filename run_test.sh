#!/bin/bash

prog="$1"
[ -e $prog ] || {
  echo "file $prog not exists" 1>&2
  exit 1
}

for file in t???.dat ; do
  echo $file
  cat $file | $prog > ${file}.out
  diff -q -b ${file}.ans ${file}.out

done

