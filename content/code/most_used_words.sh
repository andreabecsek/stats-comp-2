#!/bin/bash

for text_file in Alices_Adventures_in_Wonderland.txt Metamorphosis.txt The_Importance_of_Being_Earnest.txt The_Picture_of_Dorian_Gray.txt
do
	echo $text_file
	file_name="${text_file%.*}_count.txt"
	echo $file_name
	cat $text_file  |tr -d '[:punct:]'|tr " " "\n" | tr '[:upper:]' '[:lower:]'| sort |
	   	uniq -c|sort -n | fgrep -vwf stop_words.txt | tail -n 15 >> $file_name  

done
