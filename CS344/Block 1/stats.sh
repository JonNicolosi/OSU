#!/bin/bash
#Name: Jonathan Nicolosi
#Class: CS344
#Program 1
#Decription: This program calculates the mean and 
#median of both rows and column input 
#Input can be given as a file or as standard input

#stores name of temp file in TMP var
TMP=temp$$

#remove temp fileif error
trap "rm -f $TMP; exit 1" INT HUP TERM

#No arguments = the user did not specify
#rows or columns
#If the user does not specify rows or cols
#print an error message
if [ $# -eq 0 ]
	then 
	   echo "Must specify a rows or colums" >&2
	   exit 1
#If only one arg = no file
#If the user does not specify a file take input
#Store input in temp file
elif [ $# -eq 1 ]
	then
	   #if a valid option is provided [row or
	   #column] take input
	   if [[ "$1" == -r* ]] || [[ "$1" == -c* ]]
	      then
		#While there is input from the 
		#user read it into the tmp file
		while read stdInp
		do
		   echo $stdInp >> $TMP
		done
	   #if -r or -c is not specified give
	   #error
	   else
	      echo "Invalid command" >&2
	      exit 1
	   fi
#Test if file has read permissions
#If the file cannot be read print error
elif [ ! -r "$2" ]
	then
	   echo "Error opening file" >&2
	   exit 1
#Else if  there are 2 args then
#there is a file that can can be read
#Transfer contents of file to temp file
elif [ $# -eq 2 ]
	then 
	   cp $2 $TMP
#Else the user gave the wrong # of args
else
	echo "Wrong number of arguments" >&2
	exit 1
fi

#check to see if the temp file, which can contain either standard input or a file, is empty.
#if empty, delete temp file and exit.
if [ ! -s ${TMP} ]
then
	echo "File Is Empty"
	rm -f $TMP
	exit 1
fi

####################################################

#make sure r is lowercase
if [[ $1 == -r* && ${1:1:1} == r ]]
then
	
	sum=0
	count=0
	echo -e "Average Median"
	while read myLine
	do
		for i in $myLine
			do
			sum=$(($sum+$i))
			((count++))
	done
	
#each line is sorted, printed, and calculated independently. 
sorted=$(echo $myLine | tr " " "\n" | sort -n)
arr=($sorted)
echo $(((sum+$((count/2)))/count)) "     " ${arr[$(($((count/2))))]}

#reset counters
sum=0
count=0

done < "$TMP"

#######################################################

#make sure c is lowercase
elif [[ $1 == -c* && ${1:1:1} == c ]]
then
	rowCnt=0
	   declare -A colArr
	   while read line
	   do
	      colCnt=0
	     
	      #increase the row cnt for each line read
	      rowCnt=`expr $rowCnt + 1`
 
	      #get each # in the line into var x
	      for x in $line
	      do
		#add x to sum of col in array
		#sum = current sum of column
		sum=${colSum[$colCnt]}
		#add x  to sum to get updated sum
		sum=`expr $sum + $x`
		#put new sum into array
		colSum[$colCnt]=$sum

		#Add x to colArr
		colArr[$colCnt,$rowCnt]=$x

		#increase col cnt for each #(col)
		colCnt=`expr $colCnt + 1`
	      done
	   done < "$TMP"

	   #calculate average of col from colSum array
	   colCnt=0
	   for i in ${colSum[@]}
	   do
	      avg=`expr $i / $rowCnt`

	      #round if needed
	      mod=`expr $i % $rowCnt`
	      if [ `expr 2 \* $mod` -ge $rowCnt ]
	      then
		avg=`expr $avg + 1`
	      fi

	      #store avg in array
	      avgArr[$colCnt]=$avg
	      colCnt=`expr $colCnt + 1`
	   done

	   #calculate median
	   #sort cols from colArr - each row is a col
	   for ((i=0;i<colCnt;i++))
	   do
	      for ((j=1;j<=rowCnt;j++))
	      do
		lineArr[$j]=${colArr[$i,$j]}
	      done

	      #sort col
	      sorted=( $(
	         for y in "${lineArr[@]}"
	         do
		   echo "$y"
	         done | sort -n) )

	      #find middle
	      middle=`expr $rowCnt / 2`
	      med=${sorted[$middle]}

	      #store median in array
	      medArr[$i]=$med
	   done

	   #print results
	   echo "Average: "
	   for i in ${avgArr[@]}
	   do
	      printf "$i "
	   done

	   printf "\n"

	   echo "Median: "
	   for i in ${medArr[@]}
	   do
	      printf "$i "
	   done

	   printf "\n"

#else an invalid command was specified
#print an error
else
	echo "Invalid command" >&2
	rm -f $TMP
	exit 1
fi

#if completed successfully, remove temp file and exit
rm $TMP
exit 0