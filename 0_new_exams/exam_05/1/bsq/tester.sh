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

FILE='bsq.c'
ASSIGN='bsq/bsq.c'

index=0

if [ -e traceback ]
then
    rm traceback
fi

echo "=== BSQ GRADING TESTS ===" > traceback
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

echo "TEST 2: Running reference solution with map1..." >> ../traceback
./source map1.txt | cat -e > sourcexam 2>>../traceback
if [ $? -eq 0 ]; then
    echo "PASSED: Reference solution executed successfully" >> ../traceback
else
    echo "FAILED: Reference solution execution failed" >> ../traceback
fi
echo "" >> ../traceback
rm source

cd ../../rendu

echo "TEST 3: Checking required files..." >> ../.system/grading/../traceback
if [ ! -f "bsq/bsq.c" ]; then
    echo "FAILED: Missing required file: bsq.c" >> ../.system/grading/../traceback
    echo "" >> ../.system/grading/../traceback
    echo "Make sure you have the bsq.c file in the bsq/ directory." >> ../.system/grading/../traceback
    mv ../.system/grading/../traceback ../traceback
    exit 1
fi
echo "PASSED: Required file bsq.c found" >> ../.system/grading/../traceback

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

echo "TEST 5: Running student solution with map1..." >> ../.system/grading/../traceback
{
./final ../.system/grading/map1.txt | cat -e > finalexam
mv finalexam ../.system/grading/
rm final
}  &>../.system/grading/../traceback

cd ../.system/grading
echo "TEST 6: Comparing outputs for map1..." >> ../traceback
DIFF=$(diff sourcexam finalexam)
if [ "$DIFF" != "" ]
then
		index=$(($index + 1))
		echo "FAILED: Output comparison failed for map1" >> ../traceback
		echo "" >> ../traceback
		echo "=== EXPECTED OUTPUT (map1) ===" >> ../traceback
		cat sourcexam >> ../traceback
		echo "" >> ../traceback
		echo "=== YOUR OUTPUT (map1) ===" >> ../traceback
		if [ -f finalexam ]; then
			cat finalexam >> ../traceback
		else
			echo "(no output or execution failed)" >> ../traceback
		fi
		echo "" >> ../traceback
		echo "=== DIFFERENCES ===" >> ../traceback
		echo "$DIFF" >> ../traceback
else
		echo "PASSED: Output comparison successful for map1" >> ../traceback
fi
rm -f finalexam

# Test 2 with different map if it exists
if [ -f map2.txt ]; then
    echo "TEST 7: Running reference solution with map2..." >> ../traceback
    gcc -Wall -Wextra -Werror -o source $FILE
    ./source map2.txt | cat -e > sourcexam
    rm source
    
    cd ../../rendu
    echo "TEST 8: Running student solution with map2..." >> ../.system/grading/../traceback
    {
    gcc -Wall -Wextra -Werror -o final $ASSIGN
    }  &>../.system/grading/../traceback
    {
    ./final ../.system/grading/map2.txt | cat -e > finalexam
    mv finalexam ../.system/grading/
    rm final
    }  &>../.system/grading/../traceback
    
    cd ../.system/grading
    echo "TEST 9: Comparing outputs for map2..." >> ../traceback
    DIFF=$(diff sourcexam finalexam)
    if [ "$DIFF" != "" ]
    then
            index=$(($index + 1))
            echo "FAILED: Output comparison failed for map2" >> ../traceback
            echo "" >> ../traceback
            echo "=== EXPECTED OUTPUT (map2) ===" >> ../traceback
            cat sourcexam >> ../traceback
            echo "" >> ../traceback
            echo "=== YOUR OUTPUT (map2) ===" >> ../traceback
            if [ -f finalexam ]; then
                cat finalexam >> ../traceback
            else
                echo "(no output or execution failed)" >> ../traceback
            fi
            echo "" >> ../traceback
            echo "=== DIFFERENCES ===" >> ../traceback
            echo "$DIFF" >> ../traceback
    else
            echo "PASSED: Output comparison successful for map2" >> ../traceback
    fi
    rm -f finalexam
fi

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
