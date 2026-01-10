#!/bin/bash

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

# User solution path
USER_DIR="../../../../rendu/life"

# Check user directory
if [ ! -d "$USER_DIR" ]; then
    echo -e "${RED}❌ User directory not found: $USER_DIR${NC}"
    exit 1
fi

# Check user files
USER_C_FILES=$(find "$USER_DIR" -name "*.c")
USER_H_FILES=$(find "$USER_DIR" -name "*.h")

# if [ -z "$USER_C_FILES" ] || [ -z "$USER_H_FILES" ]; then
#     echo -e "${RED}❌ User solution not found: No .c or .h files in $USER_DIR${NC}"
#     exit 1
# fi

# Create temporary folder
TMP_DIR=$(mktemp -d)
cp "$USER_DIR"/* "$TMP_DIR"/
cp reference_life.c "$TMP_DIR"/
cp reference_life.h "$TMP_DIR"/
cd "$TMP_DIR" || exit 1

# Debug: list files in TMP_DIR



# Compile reference
gcc -Wall -Wextra -Werror -o ref_life reference_life.c 2> ref_compile_error.log
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ Reference compilation failed!${NC}"
    echo -e "${YELLOW}Compiler output:${NC}"
    cat ref_compile_error.log
    cd - >/dev/null
    rm -rf "$TMP_DIR"
    exit 1
fi

# Compile user
USER_C_FILES_ONLY=$(ls | grep '\.c$' | grep -v '^reference_life.c$')
if [ -z "$USER_C_FILES_ONLY" ]; then
    USER_C_FILES_ONLY=life.c
fi
gcc -Wall -Wextra -Werror -o user_life $USER_C_FILES_ONLY 2> compile_error.log
if [ $? -ne 0 ]; then
    echo -e "${RED}❌ User compilation failed!${NC}"
    echo -e "${YELLOW}Compiler output:${NC}"
    cat compile_error.log
    cd - >/dev/null
    rm -rf "$TMP_DIR"
    exit 1
fi

# Helper function to run a test and compare output to reference
run_test() {

    local test_name="$1"
    local input="$2"
    local rows="$3"
    local cols="$4"
    local iter="$5"
    local ref_out="ref_${test_name}.txt"
    local user_out="user_${test_name}.txt"

    echo -e "${BLUE}Running $test_name${NC}"
    echo -e "Input: '$input' | ./prog $rows $cols $iter"

    echo "$input" | ./ref_life "$rows" "$cols" "$iter" | cat -e > "$ref_out" 2>&1
    echo "$input" | ./user_life "$rows" "$cols" "$iter" | cat -e > "$user_out" 2>&1

    echo -e "${YELLOW}Reference output:${NC}"
    cat "$ref_out"
    echo -e "${YELLOW}Your output:${NC}"
    cat "$user_out"
    if diff -q "$ref_out" "$user_out" >/dev/null; then
        echo -e "${GREEN}✅ $test_name passed!${NC}"
        return 0
    else
        echo -e "${RED}❌ $test_name failed! Output differs from reference:${NC}"
        diff "$ref_out" "$user_out"
        return 1
    fi
}

# Run all tests with reference output
run_test "Test1_Basic" "sdxddssaaww" 5 5 0
run_test "Test2_Complex" "sdxssdswdxddddsxaadwxwdxwaa" 10 6 0
run_test "Test3_Vertical" "dxss" 3 3 0
run_test "Test4_Evolution1" "dxss" 3 3 1
run_test "Test5_Evolution2" "dxss" 3 3 2

# Cleanup
cd - >/dev/null
rm -rf "$TMP_DIR"
