#! /bin/bash
set -e
g++ code.cpp -o code
g++ gen.cpp -o gen
g++ brute.cpp -o brute
g++ checker.cpp -o checker
for(( i=0;; i++ ))
do
    ./gen $i > input_file
    ./code < input_file > myAnswer
    ./brute < input_file > correctAnswer
    ./checker > checker_log
    read res < checker_log
    if [ $res == "-1" ]
       then 
          break
    fi
    echo "Passed test: "  $i
done
echo "  |"
echo "  |"
echo "  |"
echo "  |"
echo "  |"
echo "  |"
echo "  |"
cat checker_log
