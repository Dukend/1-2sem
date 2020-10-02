#!/usr/bin/env bash
# (9) удлинение имен файлов до указанной длины заданными знаком/знаками

case $# in
   2) 	count=$1;
		argument="$2";
		Dir="./";;
   3) 	count=$1;
		argument="$2";
		Dir=$3;;
   *) echo "
   	(9) удлинение имен файлов до указанной длины заданными знаком/знаками
	$0 [count] [word] [Dir]
	Пример: $0 7 qw ./ww => ./ww/testqwq.txt, ./ww/11qwqwq.c
	";
	exit 1;;
esac

for i in $( find $Dir -type f ); do
	ii=$(basename $i)
	name=${ii%.*}
	ext=${ii##*.}
	if [ $ext = $name ]
	then 
		ext=" "
	else 
		ext=".$ext"
	fi
	if((${#name} < $count));then
		while (( ${#name} != $count)); do
			name="$name$argument"
			name=$(cut -c 1-$count < <(echo "$name"))
		done
	 	
	fi
	mv "$Dir/$ii" "$Dir/$name$ext"
done
