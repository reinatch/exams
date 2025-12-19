#!/bin/bash

# Test compilation
echo "=== Testing VECT2 ==="
echo "Compiling reference solution..."
clang++ -Wall -Wextra -Werror -std=c++98 -o reference main.cpp vect2.hpp

echo "Running reference solution..."
./reference

echo ""
echo "Expected: The program should compile and run without errors."
echo "Your vect2.hpp should implement a 2D vector class correctly."

# Clean up
rm -f reference
