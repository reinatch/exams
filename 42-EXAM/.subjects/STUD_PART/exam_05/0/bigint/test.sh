#!/bin/bash

# Test compilation
echo "=== Testing BIGINT ==="
echo "Compiling reference solution..."
clang++ -Wall -Wextra -Werror -std=c++98 -o reference main.cpp bigint.cpp

echo "Running reference solution..."
./reference

echo ""
echo "Expected: The program should compile and run without errors."
echo "Your implementation should handle big integer operations correctly."

# Clean up
rm -f reference
