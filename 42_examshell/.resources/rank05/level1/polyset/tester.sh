#!/bin/bash

# Color codes for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Comprehensive Test Script for polyset
echo -e "${BLUE}🔍 Running COMPREHENSIVE TESTING for polyset${NC}"
echo "=========================================="
echo ""



echo -e "${BLUE}📦 Compiling reference solution...${NC}"
# Clean up any old main.cpp/user_main.cpp
rm -f main.cpp user_main.cpp
# Copy all reference files from subject folder
cp subject/*.cpp .
cp subject/*.hpp . 2>/dev/null
cp subject/main.cpp .
# Compile only reference main.cpp and supporting files (exclude user_main.cpp)
find . -maxdepth 1 -name '*.cpp' ! -name 'user_main.cpp' > ref_sources.txt
g++ -Wall -Wextra -Werror -std=c++11 -o ref_polyset main.cpp $(grep -v '^main.cpp$' ref_sources.txt)
compile_status=$?
rm ref_sources.txt
if [ $compile_status -ne 0 ]; then
    echo -e "${RED}❌ Reference compilation failed!${NC}"
    exit 1
fi

if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Reference compilation failed!${NC}"
    exit 1
fi

echo -e "${GREEN}✅ Reference compilation successful!${NC}"
echo ""

# Check if user solution exists
USER_DIR="../../../../rendu/polyset"
USER_CPP="$USER_DIR/polyset.cpp"
USER_HPP="$USER_DIR/polyset.hpp"
if [ ! -d "$USER_DIR" ]; then
    echo -e "${RED}❌ User solution folder not found: $USER_DIR${NC}"
    exit 1
fi



# Copy and compile user solution
echo -e "${BLUE}📦 Compiling user solution...${NC}"
rm -f main.cpp user_main.cpp
cp $USER_DIR/*.cpp . 2>/dev/null
cp $USER_DIR/*.hpp . 2>/dev/null
echo "[DEBUG] Copying user main.cpp from: $USER_DIR/main.cpp"
if [ -f "$USER_DIR/main.cpp" ]; then
    cp "$USER_DIR/main.cpp" user_main.cpp
else
    echo -e "${RED}❌ main.cpp not found in $USER_DIR!${NC}"
    exit 1
fi
# Compile only user_main.cpp and supporting files (exclude main.cpp)
find . -maxdepth 1 -name '*.cpp' ! -name 'main.cpp' > user_sources.txt
g++ -Wall -Wextra -Werror -std=c++11 -o user_polyset user_main.cpp $(grep -v '^user_main.cpp$' user_sources.txt)
user_compile_status=$?
rm user_sources.txt
if [ $user_compile_status -ne 0 ]; then
    echo -e "${RED}❌ User compilation failed!${NC}"
    exit 1
fi

echo -e "${GREEN}✅ User compilation successful!${NC}"
echo ""

# Run both and capture output
echo -e "${BLUE}🚀 Running tests...${NC}"
./ref_polyset > ref_output.txt 2>&1
echo "[DEBUG] Reference output:"; cat ref_output.txt
./user_polyset > user_output.txt 2>&1
echo "[DEBUG] User output:"; cat user_output.txt

# Compare outputs
output_match=true
output_error_msg=""
if diff -q ref_output.txt user_output.txt > /dev/null; then
    echo -e "${GREEN}✅ Output matches reference!${NC}"
else
    echo -e "${RED}❌ Output does NOT match reference!${NC}"
    echo -e "${YELLOW}--- Reference Output ---${NC}"
    cat ref_output.txt
    echo -e "${YELLOW}--- Your Output ---${NC}"
    cat user_output.txt
    echo -e "${YELLOW}--- Diff ---${NC}"
    diff ref_output.txt user_output.txt
    output_match=false
    output_error_msg="Output does not match reference solution."
fi

# Run with valgrind for memory leak checking
echo -e "${BLUE}🚀 Executing valgrind analysis...${NC}"
echo "Command: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./user_polyset"
echo ""

# Capture valgrind output to analyze
valgrind_output=$(valgrind \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    -s \
    --error-exitcode=1 \
    ./user_polyset 2>&1)

exit_code=$?

# Display the full output
echo "$valgrind_output"

echo ""
echo -e "${BLUE}🏁 Valgrind analysis completed with exit code: $exit_code${NC}"
echo ""

# Parse and analyze the output
echo "======================================="
echo -e "${YELLOW}📊 DETAILED ANALYSIS RESULTS:${NC}"
echo "======================================="

# Check for memory leaks
has_leaks=false
if echo "$valgrind_output" | grep -q "definitely lost:" && echo "$valgrind_output" | grep "definitely lost:" | grep -v "0 bytes"; then
    has_leaks=true
fi
if echo "$valgrind_output" | grep -q "indirectly lost:" && echo "$valgrind_output" | grep "indirectly lost:" | grep -v "0 bytes"; then
    has_leaks=true
fi
if echo "$valgrind_output" | grep -q "possibly lost:" && echo "$valgrind_output" | grep "possibly lost:" | grep -v "0 bytes"; then
    has_leaks=true
fi

# Check for errors
has_errors=false
if echo "$valgrind_output" | grep -q "ERROR SUMMARY" && echo "$valgrind_output" | grep "ERROR SUMMARY" | grep -v "0 errors"; then
    has_errors=true
fi

# Display results with color coding
echo -n "Memory Leaks: "
if [ "$has_leaks" = true ]; then
    echo -e "${RED}DETECTED - You have memory leaks!${NC}"
else
    echo -e "${GREEN}PASSED - No memory leaks detected${NC}"
fi

echo -n "Valgrind Errors: "
if [ "$has_errors" = true ]; then
    echo -e "${RED}DETECTED - Valgrind found errors!${NC}"
else
    echo -e "${GREEN}PASSED - No valgrind errors${NC}"
fi

echo ""
echo "======================================="
echo -n "OVERALL RESULT: "
if [ "$has_leaks" = false ] && [ "$has_errors" = false ] && [ "$output_match" = true ]; then
    echo -e "${GREEN}✅ ALL TESTS PASSED!${NC}"
    echo -e "${GREEN}Your polyset implementation is clean!${NC}"
else
    echo -e "${RED}❌ ISSUES DETECTED!${NC}"
    echo -e "${YELLOW}Summary of errors:${NC}"
    if [ "$has_leaks" = true ]; then
        echo -e "${RED}  → Memory leaks detected.${NC}"
    fi
    if [ "$has_errors" = true ]; then
        echo -e "${RED}  → Valgrind errors detected.${NC}"
    fi
    if [ "$output_match" = false ]; then
        echo -e "${RED}  → Output does not match reference solution.${NC}"
    fi
fi
echo "======================================="

# Wait for user to press enter before continuing
read -rp "Press enter to continue..." dummy

# Ask user if they want to clean up files
read -rp "Do you want to clean up temporary files? (y/n): " cleanup_choice
if [ "$cleanup_choice" = "y" ] || [ "$cleanup_choice" = "Y" ]; then
    rm -f ref_polyset user_polyset user_main.cpp *.cpp *.hpp ref_output.txt user_output.txt
    echo "Temporary files cleaned up."
else
    echo "Temporary files kept."
fi