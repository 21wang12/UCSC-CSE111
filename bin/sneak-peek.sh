#!/bin/sh
# $Id: sneak-peek.sh,v 1.2 2021-02-26 00:10:19-08 - - $
cat $0
cat $* | tr A-Z a-z | tr -c a-z '\n' | sort | uniq | fmt -60
