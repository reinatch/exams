#!/bin/bash

# Test compilation
echo "=== Testing POLYSET ==="
echo "Compiling reference solution..."
c++ -Wall -Wextra -Werror -std=c++98 -o reference main.cpp array_bag.cpp tree_bag.cpp searchable_array_bag.cpp searchable_tree_bag.cpp set.cpp

echo "Running reference solution with test arguments..."
./reference 1 2 3

echo ""
echo "Expected: The program should compile and run without errors."
echo "Your implementation should handle polymorphic set operations correctly."

# Clean up
rm -f reference
