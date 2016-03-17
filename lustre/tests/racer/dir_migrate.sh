#!/bin/bash

DIR=$1
MAX=$2

MDTCOUNT=${MDSCOUNT:-$($LFS df $DIR 2> /dev/null | grep -c MDT)}
while /bin/true ; do
	migrate_dir=$((RANDOM % MAX))
	file=$((RANDOM % MAX))
	mdt_idx=$((RANDOM % MDTCOUNT))
	mkdir -p $DIR/$migrate_dir 2> /dev/null
	$LFS mv -M$mdt_idx $DIR/$migrate_dir 2> /dev/null
	touch $DIR/$migrate_dir/$file 2> /dev/null
	$LFS getdirstripe $DIR/$migrate_dir > /dev/null 2>&1
done
