# Mock Practical Exam Solutions

This folder contains correct implementations for all 6 mock practical exam problems from TIC2001 Data Structures and Algorithms.

## Problem 1: Pop Middle (problem1_pop_middle.cpp)

**Data Structure:** Deque (double-ended queue)

**Algorithm:**
- Use `deque<int>` to store queue elements
- PUSH: O(1) - add to back using `push_back()`
- POP: O(1) - remove from front using `pop_front()`
- POPMIDDLE: O(n) - access middle element at index `size/2`, rebuild deque without it

**Time Complexity:** O(Q*n) where Q is number of operations, n is queue size

---

## Problem 2: Speakers (problem2_speakers.cpp)

**Data Structure:** Ordered Set (BST)

**Algorithm:**
- Store start times in `set<long long>` (balanced BST)
- INSERT S: Check if any speech in range `(S-L, S+L)` exists using `upper_bound(S-L)`
  - Two speeches clash if their time intervals overlap
  - Speech [S, S+L-1] clashes with [T, T+L-1] if `|S-T| < L`
- REMOVE S: Use `count()` to check existence, then `erase()`

**Time Complexity:** O(Q log Q) for Q operations

**Key Insight:** Speeches clash if `S-L < T < S+L` where T is an existing start time

---

## Problem 3: Queens (problem3_queens.cpp)

**Algorithm:** Backtracking with constraint checking

**Approach:**
1. Parse board to identify pre-placed queens
2. Use backtracking to place remaining queens one row at a time
3. For each position, check safety: no attacks on same row, column, diagonal, or anti-diagonal
4. Track queen positions in `vector<int> queens` where `queens[i]` = column of queen in row i

**Time Complexity:** O(N!) worst case, but heavily pruned by constraints

**Key Insight:** A queen at (r,c) attacks positions where:
- Same row: r is constant
- Same column: c is constant
- Same diagonal: r-c is constant
- Same anti-diagonal: r+c is constant

---

## Problem 4: Instruction (problem4_instruction.cpp)

**Algorithm:** Brute force with bitmask enumeration

**Approach:**
1. Try all 2^N combinations of instructions (N ≤ 16)
2. For each combination (bitmask), apply selected instructions in order
3. Track result that minimizes `|result - K|`
4. Tie-break: choose smaller value

**Time Complexity:** O(2^N * N) = O(N * 2^N)

**Sample Trace (N=3, K=10):**
```
Instructions: +4, +3, *3
Bitmask 011 (apply +3 and *3):
  0 → +3 → 3 → *3 → 9
  Distance: |9-10| = 1 ✓ (optimal)
```

---

## Problem 5: Longest Increasing Subsequence (problem5_lis.cpp)

**Algorithm:** Dynamic Programming

**Approach:**
- `dp[i]` = length of LIS ending at index i
- `dp[i] = 1 + max(dp[j])` for all j < i where A[j] < A[i]
- Answer = `max(dp[i])`

**Time Complexity:** O(N²)

**Example:**
```
Array: [1, 4, 2, 3]
dp:    [1, 2, 2, 3]
        ↑  ↑  ↑  ↑
        1  1,4 1,2 1,2,3

LIS length = 3 (sequence: [1,2,3])
```

---

## Problem 6: XOR (problem6_xor.cpp)

**Algorithm:** Brute force subset enumeration

**Approach:**
1. Try all 2^N subsets using bitmask (N ≤ 16)
2. For each subset, calculate XOR of all elements
3. Track maximum XOR value

**Time Complexity:** O(2^N * N)

**XOR Properties:**
- Commutative: a ⊕ b = b ⊕ a
- Associative: (a ⊕ b) ⊕ c = a ⊕ (b �⊕ c)
- Identity: 0 ⊕ a = a
- Self-inverse: a ⊕ a = 0

**Example:**
```
Array: [1, 2, 3, 5]
Subset {1, 3, 5}:
  1 ⊕ 3 ⊕ 5 = 00001 ⊕ 00011 ⊕ 00101
              = 00010 ⊕ 00101
              = 00111 = 7 ✓ (maximum)
```

---

## Compilation & Testing

To compile any problem:
```bash
g++ -std=c++17 -O2 -Wall problem1_pop_middle.cpp -o problem1
```

To test:
```bash
./problem1 < input.txt
```

---

## Summary Table

| Problem | Data Structure | Algorithm | Time Complexity |
|---------|---------------|-----------|-----------------|
| 1. Pop Middle | Deque | Direct manipulation | O(Q*n) |
| 2. Speakers | BST (set) | Range query | O(Q log Q) |
| 3. Queens | Array | Backtracking | O(N!) pruned |
| 4. Instruction | - | Bitmask DP | O(N * 2^N) |
| 5. LIS | Array | DP | O(N²) |
| 6. XOR | - | Bitmask enumeration | O(N * 2^N) |

---

## Notes

- All solutions handle edge cases correctly
- Memory management is proper (no leaks)
- Input/output format matches specifications exactly
- Solutions are tested against provided sample inputs
