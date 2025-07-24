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

FILE='life.c'
ASSIGN='life/life.c'

index=0

if [ -e traceback ]
then
    rm traceback
fi

echo "=== LIFE GRADING TESTS ===" > traceback
echo "" >> traceback

cd .system/grading

echo "TEST 1: Compiling reference solution..." >> ../traceback
if ! gcc -Wall -Wextra -Werror -o source $FILE 2>>../traceback; then
    echo "FAILED: Reference compilation failed" >> ../traceback
    echo "" >> ../traceback
    echo "This means there's an issue with the reference implementation." >> ../traceback
    echo "Please report this to the maintainers." >> ../traceback
    mv ../traceback ../../traceback
    exit 1
fi
echo "PASSED: Reference compilation successful" >> ../traceback

echo "TEST 2: Running reference solution (test 1)..." >> ../traceback
echo 'sdxddssaaww' | ./source 5 5 0 | cat -e > sourcexam 2>>../traceback
if [ $? -eq 0 ]; then
    echo "PASSED: Reference solution executed successfully (test 1)" >> ../traceback
else
    echo "FAILED: Reference solution execution failed (test 1)" >> ../traceback
fi
echo "" >> ../traceback
rm source

cd ../../rendu

echo "TEST 3: Checking required files..." >> ../.system/grading/../traceback
if [ ! -f "life/life.c" ]; then
    echo "FAILED: Missing required file: life.c" >> ../.system/grading/../traceback
    echo "" >> ../.system/grading/../traceback
    echo "Make sure you have the life.c file in the life/ directory." >> ../.system/grading/../traceback
    mv ../.system/grading/../traceback ../traceback
    exit 1
fi
echo "PASSED: Required file life.c found" >> ../.system/grading/../traceback

echo "TEST 4: Compiling student solution..." >> ../.system/grading/../traceback
{
gcc -Wall -Wextra -Werror -o final $ASSIGN
}  &>../.system/grading/../traceback

if [ ! -f final ]; then
    echo "FAILED: Student compilation failed" >> ../.system/grading/../traceback
    echo "" >> ../.system/grading/../traceback
    echo "Check the compilation errors above and fix your code." >> ../.system/grading/../traceback
    mv ../.system/grading/../traceback ../traceback
    exit 1
fi
echo "PASSED: Student compilation successful" >> ../.system/grading/../traceback

echo "TEST 5: Running student solution (test 1)..." >> ../.system/grading/../traceback
{
echo 'sdxddssaaww' | ./final 5 5 0 | cat -e > finalexam
mv finalexam ../.system/grading/
rm final
}  &>../.system/grading/../traceback

cd ../.system/grading
echo "TEST 6: Comparing outputs (test 1)..." >> ../traceback
DIFF=$(diff sourcexam finalexam)
if [ "$DIFF" != "" ]
then
		index=$(($index + 1))
		echo "FAILED: Output comparison failed (test 1)" >> ../traceback
		echo "" >> ../traceback
		echo "=== EXPECTED OUTPUT (test 1) ===" >> ../traceback
		cat sourcexam >> ../traceback
		echo "" >> ../traceback
		echo "=== YOUR OUTPUT (test 1) ===" >> ../traceback
		if [ -f finalexam ]; then
			cat finalexam >> ../traceback
		else
			echo "(no output or execution failed)" >> ../traceback
		fi
		echo "" >> ../traceback
		echo "=== DIFFERENCES ===" >> ../traceback
		echo "$DIFF" >> ../traceback
else
		echo "PASSED: Output comparison successful (test 1)" >> ../traceback
fi
rm -f finalexam

# Test 2
echo "TEST 7: Running reference solution (test 2)..." >> ../traceback
gcc -Wall -Wextra -Werror -o source $FILE
echo 'dxss' | ./source 3 3 0 | cat -e > sourcexam
rm source

cd ../../rendu
echo "TEST 8: Running student solution (test 2)..." >> ../.system/grading/../traceback
{
gcc -Wall -Wextra -Werror -o final $ASSIGN
}  &>../.system/grading/../traceback
{
echo 'dxss' | ./final 3 3 0 | cat -e > finalexam
mv finalexam ../.system/grading/
rm final
}  &>../.system/grading/../traceback

cd ../.system/grading
echo "TEST 9: Comparing outputs (test 2)..." >> ../traceback
DIFF=$(diff sourcexam finalexam)
if [ "$DIFF" != "" ]
then
		index=$(($index + 1))
		echo "FAILED: Output comparison failed (test 2)" >> ../traceback
		echo "" >> ../traceback
		echo "=== EXPECTED OUTPUT (test 2) ===" >> ../traceback
		cat sourcexam >> ../traceback
		echo "" >> ../traceback
		echo "=== YOUR OUTPUT (test 2) ===" >> ../traceback
		if [ -f finalexam ]; then
			cat finalexam >> ../traceback
		else
			echo "(no output or execution failed)" >> ../traceback
		fi
		echo "" >> ../traceback
		echo "=== DIFFERENCES ===" >> ../traceback
		echo "$DIFF" >> ../traceback
else
		echo "PASSED: Output comparison successful (test 2)" >> ../traceback
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
