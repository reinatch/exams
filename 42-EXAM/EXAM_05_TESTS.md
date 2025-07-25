# EXAM 05 - Complete Test Documentation

This document details all the tests performed by the grading system for each exercise in exam_05.

## Level 0 Exercises

### 1. POLYSET (C++ Object-Oriented Programming)

**Required Files:**
- `polyset/searchable_array_bag.hpp`
- `polyset/searchable_array_bag.cpp`
- `polyset/searchable_tree_bag.hpp`
- `polyset/searchable_tree_bag.cpp`
- `polyset/set.hpp`
- `polyset/set.cpp`

**Compilation Test:**
```bash
c++ -Wall -Wextra -Werror -std=c++98 -o final main.cpp array_bag.cpp tree_bag.cpp searchable_array_bag.cpp searchable_tree_bag.cpp set.cpp
```

**Execution Test:**
```bash
./final 1 2 3
```

**Expected Output Pattern:**
- Argument echoing: `1\n2\n3\n`
- Tree insertion messages: `create node: X`
- Tree and array bag printing
- Search results (has/doesn't have tests)
- Destruction messages: `destroying value: X`
- Set operations and extra tests

---

### 2. BIGINT (C++ Arbitrary Precision Arithmetic)

**Required Files:**
- `bigint/bigint.hpp`
- `bigint/bigint.cpp`

**Compilation Test:**
```bash
clang++ -Wall -Wextra -Werror -std=c++98 -o final main.cpp bigint/bigint.cpp
```

**Execution Test:**
```bash
./final
```

**Expected Output Pattern:**
Tests various bigint operations:
- Basic construction: `bigint a(42), b(21), c, d(1337), e(d)`
- Addition: `a + b`
- Assignment: `c += a`
- Increment: `++b, b++`
- Bit shifting: `b << 10, d <<= 4, d >>= 2`
- Comparison operators: `==, <=, >=, <, >, !=`
- String construction: `bigint f("42")`

---

### 3. VECT2 (C++ 2D Vector Class)

**Required Files:**
- `vect2/vect2.hpp`

**Compilation Test:**
```bash
clang++ -Wall -Wextra -Werror -std=c++98 -o final main.cpp
```

**Execution Test:**
```bash
./final
```

**Expected Output Pattern:**
Tests vector operations:
- Construction: `vect2 v1, v2(1,2), v3(v2), v4 = v2`
- Element access: `v1[0], v1[1]`
- Arithmetic: `+=, -=, +, -, *`
- Increment/decrement: `++, --` (pre and post)
- Comparison: `==, !=`
- Stream output: `operator<<`

---

## Level 1 Exercises

### 4. BSQ (C Algorithm - Biggest Square)

**Required Files:**
- `bsq/bsq.c`

**Compilation Test:**
```bash
gcc -Wall -Wextra -Werror -o final bsq/bsq.c
```

**Test 1 - Map1:**
```bash
./final ../system/grading/map1.txt
```

**Test 2 - Map2 (if exists):**
```bash
./final ../system/grading/map2.txt
```

**Expected Behavior:**
- Read map format: `lines empty_char obstacle_char full_char`
- Parse grid with obstacles
- Find largest possible square
- Fill square with full_char
- Print modified map
- Handle error cases: "map error"

**Map Format Example:**
```
9 . o x
...........................
....o......................
............o..............
...........................
```

---

### 5. LIFE (C Algorithm - Conway's Game of Life)

**Required Files:**
- `life/life.c`

**Compilation Test:**
```bash
gcc -Wall -Wextra -Werror -o final life/life.c
```

**Test 1:**
```bash
echo 'sdxddssaaww' | ./final 5 5 0
```

**Test 2:**
```bash
echo 'dxss' | ./final 3 3 0
```

**Expected Behavior:**
- Parse arguments: `width height iterations`
- Read movement commands from stdin:
  - `w`: move up
  - `s`: move down  
  - `a`: move left
  - `d`: move right
  - `x`: toggle pen (start/stop drawing)
- Simulate Conway's Game of Life rules:
  - Live cell with <2 neighbors dies
  - Live cell with 2-3 neighbors survives
  - Live cell with >3 neighbors dies
  - Dead cell with exactly 3 neighbors becomes alive
- Print final state: `'0'` for alive, `' '` for dead

---

## Level 2 Exercises

Currently no exercises documented for level 2.

---

## Common Test Flow

All exercises follow this pattern:

1. **TEST 1: Checking reference compilation**
   - Compiles reference implementation
   - Fails if reference has compilation errors

2. **TEST 2: Running reference solution**
   - Executes reference with test inputs
   - Captures expected output

3. **TEST 3: Checking required files**
   - Verifies all required files exist
   - Lists missing files if any

4. **TEST 4: Compiling student solution**
   - Compiles student implementation
   - Shows compilation errors if failed

5. **TEST 5: Running student solution**
   - Executes student code with same test inputs
   - Captures actual output

6. **TEST 6: Comparing outputs**
   - Uses `diff` to compare expected vs actual
   - Shows differences if any
   - Creates `passed` file if identical

## Traceback Information

When tests fail, detailed traces are saved to `traces/LEVEL-ATTEMPT_EXERCISE.trace` containing:
- Compilation errors (if any)
- Expected output
- Actual output
- Differences between outputs
- Specific test that failed

## Success Criteria

An exercise passes if:
- All required files are present
- Student code compiles without errors
- Student output exactly matches reference output
- No differences found by `diff` command
