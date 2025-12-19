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
MAIN1='vect2/main.cpp'

index=0

if [ -e traceback ]
then
    rm traceback
fi

echo "=== VECT2 GRADING TESTS ===" > traceback
echo "" >> traceback

cd .system/grading

echo "TEST 1: Compiling reference solution..." >> ../traceback
clang++ -Wall -Wextra -Werror -std=c++98 -o source $MAIN 2>>../traceback
if [ $? -eq 0 ]; then
    echo "PASSED: Reference compilation successful" >> ../traceback
else
    echo "FAILED: Reference compilation failed" >> ../traceback
    mv ../traceback ../../traceback
    exit 1
fi

echo "TEST 2: Running reference solution..." >> ../traceback
./source | cat -e > sourcexam 2>>../traceback
if [ $? -eq 0 ]; then
    echo "PASSED: Reference solution executed successfully" >> ../traceback
else
    echo "FAILED: Reference solution execution failed" >> ../traceback
fi
echo "" >> ../traceback
rm source

cp main.cpp ../../rendu/vect2
cd ../../rendu

echo "TEST 3: Checking required files..." >> ../.system/grading/../traceback
if [ ! -f "vect2/vect2.hpp" ]; then
    echo "FAILED: Missing required file: vect2.hpp" >> ../.system/grading/../traceback
    echo "Make sure you have the vect2.hpp file in the vect2/ directory." >> ../.system/grading/../traceback
    mv ../.system/grading/../traceback ../traceback
    exit 1
fi
echo "PASSED: Required file vect2.hpp found" >> ../.system/grading/../traceback

echo "TEST 4: Compiling student solution..." >> ../.system/grading/../traceback
{
clang++ -Wall -Wextra -Werror -std=c++98 -o final $MAIN1
}  &>../.system/grading/../traceback

if [ ! -f final ]; then
    echo "FAILED: Student compilation failed" >> ../.system/grading/../traceback
    echo "Check the compilation errors above and fix your code." >> ../.system/grading/../traceback
    mv ../.system/grading/../traceback ../traceback
    exit 1
fi
echo "PASSED: Student compilation successful" >> ../.system/grading/../traceback

rm -f vect2/main.cpp

echo "TEST 5: Running student solution..." >> ../.system/grading/../traceback
{
./final | cat -e > finalexam
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
fi

{
mv ../traceback ../../traceback
}	&>/dev/null
rm sourcexam
