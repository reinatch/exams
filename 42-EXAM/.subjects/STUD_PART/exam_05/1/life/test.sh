#!/bin/bash

# Test compilation and execution
echo "=== Testing LIFE ==="
echo "Compiling reference solution..."
gcc -Wall -Wextra -Werror -o reference life.c

echo "Running reference solution (test 1)..."
echo "Input: 'sdxddssaaww' | ./reference 5 5 0"
echo 'sdxddssaaww' | ./reference 5 5 0

echo ""
echo "Running reference solution (test 2)..."
echo "Input: 'dxss' | ./reference 3 3 0"
echo 'dxss' | ./reference 3 3 0

echo ""
echo "Expected: Conway's Game of Life simulation."
echo "Arguments: width height generations"
echo "Input: string representing initial state (d=dead, others=alive)"
echo "Output: final state after specified generations"

# Clean up
rm -f reference
