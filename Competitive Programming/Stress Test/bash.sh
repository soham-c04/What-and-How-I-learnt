#! /bin/bash
set -e
g++ -std=c++20 -O3 code.cpp -o code
g++ -std=c++20 -O3 gen.cpp -o gen
g++ -std=c++20 -O3 brute.cpp -o brute
for((i = 1; ; ++i)); do
    ./gen $i > input_file
    ./code < input_file > myAnswer
    ./brute < input_file > correctAnswer
#    cat input_file
#echo "St: "
#    cat correctAnswer
#echo "End"
    diff -Z myAnswer correctAnswer > /dev/null || break
    echo "Passed test: "  $i
done
echo "	|"
echo "	|"
echo "	|"
echo "	|"
echo "	|"
echo "	|"
echo "	|"
echo "WA on the following test:"
cat input_file
echo "Your answer is:"
cat myAnswer
echo "Correct answer is:"
cat correctAnswer
export PATH="/mnt/c/mingw/bin:$PATH"
