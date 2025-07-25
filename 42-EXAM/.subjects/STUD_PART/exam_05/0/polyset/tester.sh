# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    tester.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: exam                                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 00:00:00 by exam              #+#    #+#              #
#    Updated: 2025/01/01 00:00:00 by exam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAIN='main.cpp'
MAIN1='polyset/main.cpp'

index=0

if [ -e traceback ]
then
    rm traceback
fi

echo "=== POLYSET GRADING TESTS ===" > traceback
echo "" >> traceback

cd .system/grading

echo "TEST 1: Checking reference compilation..." >> ../traceback
# Debug: List all files in grading directory
echo "DEBUG: Files in grading directory:" >> ../traceback
ls -la >> ../traceback
echo "" >> ../traceback

# Only compile the main.cpp with necessary implementation files
# Exclude any other main files that might exist
if ! c++ -Wall -Wextra -Werror -std=c++98 -o source main.cpp \
    $(ls *.cpp | grep -v main.cpp | grep -E "(array_bag|tree_bag|searchable_.*|set)\.cpp") 2>>../traceback; then
    echo "FAILED: Reference compilation failed" >> ../traceback
    echo "Attempted to compile: main.cpp + implementation files" >> ../traceback
    echo "Available .cpp files:" >> ../traceback
    ls *.cpp >> ../traceback
    echo "" >> ../traceback
    echo "This means there's an issue with the reference implementation." >> ../traceback
    echo "Please report this to the maintainers." >> ../traceback
    mv ../traceback ../../traceback
    exit 1
fi
echo "PASSED: Reference compilation successful" >> ../traceback
echo "" >> ../traceback

echo "TEST 2: Running reference solution..." >> ../traceback
./source 1 2 3 | cat -e > sourcexam 2>>../traceback
if [ $? -eq 0 ]; then
    echo "PASSED: Reference solution executed successfully" >> ../traceback
else
    echo "FAILED: Reference solution execution failed" >> ../traceback
fi
echo "" >> ../traceback
rm source

cp main.cpp ../../rendu/polyset
cd ../../rendu

echo "TEST 3: Checking required files..." >> ../.system/grading/../traceback
missing_files=""
if [ ! -f "polyset/searchable_array_bag.hpp" ]; then missing_files="$missing_files searchable_array_bag.hpp"; fi
if [ ! -f "polyset/searchable_array_bag.cpp" ]; then missing_files="$missing_files searchable_array_bag.cpp"; fi
if [ ! -f "polyset/searchable_tree_bag.hpp" ]; then missing_files="$missing_files searchable_tree_bag.hpp"; fi
if [ ! -f "polyset/searchable_tree_bag.cpp" ]; then missing_files="$missing_files searchable_tree_bag.cpp"; fi
if [ ! -f "polyset/set.hpp" ]; then missing_files="$missing_files set.hpp"; fi
if [ ! -f "polyset/set.cpp" ]; then missing_files="$missing_files set.cpp"; fi

if [ ! -z "$missing_files" ]; then
    echo "FAILED: Missing required files:$missing_files" >> ../.system/grading/../traceback
    echo "" >> ../.system/grading/../traceback
    echo "Make sure you have all the required files as specified in the subject." >> ../.system/grading/../traceback
    mv ../.system/grading/../traceback ../traceback
    exit 1
fi
echo "PASSED: All required files present" >> ../.system/grading/../traceback
echo "" >> ../.system/grading/../traceback

echo "TEST 4: Compiling student solution..." >> ../.system/grading/../traceback
{
clang++ -Wall -Wextra -Werror -std=c++98 -o final $MAIN1 polyset/array_bag.cpp polyset/tree_bag.cpp polyset/searchable_array_bag.cpp polyset/searchable_tree_bag.cpp polyset/set.cpp
}  &>../.system/grading/../traceback

if [ ! -f final ]; then
    echo "FAILED: Student compilation failed" >> ../.system/grading/../traceback
    echo "" >> ../.system/grading/../traceback
    echo "Check the compilation errors above and fix your code." >> ../.system/grading/../traceback
    mv ../.system/grading/../traceback ../traceback
    exit 1
fi
echo "PASSED: Student compilation successful" >> ../.system/grading/../traceback
echo "" >> ../.system/grading/../traceback

rm -f polyset/main.cpp

echo "TEST 5: Running student solution..." >> ../.system/grading/../traceback
{
./final 1 2 3 | cat -e > finalexam        #TESTING
mv finalexam ../.system/grading/
rm final
}  &>../.system/grading/../traceback

cd ../.system/grading
echo "TEST 6: Comparing outputs..." >> ../traceback
DIFF=$(diff sourcexam finalexam)
if [ "$DIFF" != "" ]
then
		index=$(($index + 1))
		echo "FAILED: Output comparison failed" >> ../traceback
		echo "" >> ../traceback
		echo "=== EXPECTED OUTPUT ===" >> ../traceback
		cat sourcexam >> ../traceback
		echo "" >> ../traceback
		echo "=== YOUR OUTPUT ===" >> ../traceback
		if [ -f finalexam ]; then
			cat finalexam >> ../traceback
		else
			echo "(no output or execution failed)" >> ../traceback
		fi
		echo "" >> ../traceback
		echo "=== DIFFERENCES ===" >> ../traceback
		echo "$DIFF" >> ../traceback
else
		echo "PASSED: Output comparison successful" >> ../traceback
fi
rm -f finalexam

echo "" >> ../traceback
if [ $index -eq 0 ]
then
	echo "=== ALL TESTS PASSED ===" >> ../traceback
	touch passed
else
	echo "=== SOME TESTS FAILED ===" >> ../traceback
	echo "Review the failed tests above and fix your implementation." >> ../traceback
fi

{
mv ../traceback ../../traceback
}	&>/dev/null
rm sourcexam
