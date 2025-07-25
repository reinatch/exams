#!/bin/bash

# Test compilation and execution
echo "=== Testing BSQ ==="
echo "Compiling reference solution..."
gcc -Wall -Wextra -Werror -o reference bsq.c

echo "Running reference solution with map1..."
./reference map1.txt

echo ""
echo "Running reference solution with map2 (if available)..."
if [ -f map2.txt ]; then
    ./reference map2.txt
else
    echo "map2.txt not found, skipping second test"
fi

echo ""
echo "Expected: The program should find and display the biggest square in the map."
echo "Input format: First line contains map dimensions and characters."
echo "Following lines contain the map with obstacles and empty spaces."

# Clean up
rm -f reference
