# TIC2001 Data Structures & Algorithms Cheatsheet

## Files Included

1. **TIC2001_Cheatsheet.html** - HTML version (ready to print to PDF)
2. **TIC2001_Cheatsheet.tex** - LaTeX source (for local compilation)

## How to Generate PDF

### Method 1: From HTML (Easiest)
1. Open `TIC2001_Cheatsheet.html` in your web browser
2. Press `Ctrl+P` (Windows/Linux) or `Cmd+P` (Mac)
3. Select "Save as PDF" as the destination
4. Set paper size to **A4 Landscape**
5. Set margins to **Minimum** or **None**
6. Save the PDF

### Method 2: From LaTeX (Best Quality)
If you have LaTeX installed:
```bash
cd 25_26_sem1
pdflatex TIC2001_Cheatsheet.tex
```

If you don't have LaTeX, install it:
- **Ubuntu/Debian**: `sudo apt-get install texlive-latex-extra`
- **Mac**: Install MacTeX from https://www.tug.org/mactex/
- **Windows**: Install MiKTeX from https://miktex.org/

## Cheatsheet Contents

### 1. Sorting Algorithms (All Implementations)
- Bubble Sort (O(n²))
- Selection Sort (O(n²))
- Insertion Sort (O(n²))
- Merge Sort (O(n log n))
- Quick Sort (O(n log n) avg)
- Heap Sort (O(n log n))
- Counting Sort (O(n+k))
- Quick Select (O(n) avg)

### 2. Data Structures
- Linked Lists (insert, delete, reverse)
- Stack (LIFO, monotonic stack pattern)
- Queue (FIFO)
- Deque (double-ended queue)
- Priority Queue (heap operations)
- Set/Multiset (BST operations)
- Map/Multimap (key-value BST)
- Hash Table (unordered_map/unordered_set)

### 3. Recursion Patterns
- Basic template
- Factorial (linear recursion)
- Fibonacci (tree recursion + memoization)
- Power (binary recursion)
- GCD (Euclidean algorithm)
- Binary search
- Permutations (backtracking)
- Subsets (bitmask)
- N-Queens (backtracking)

### 4. Common Patterns
- Two pointers
- Sliding window
- Prefix sum
- Monotonic stack
- Binary search on answer

### 5. Complexity Analysis
- Time complexity reference
- Space complexity
- Recurrence relations

### 6. Tips & Tricks
- Fast I/O
- STL algorithms
- Custom sorting
- Bit manipulation
- Common pitfalls
- Problem-solving strategy

## Coverage

This cheatsheet covers all concepts from:
- **Lab Assignments 1-7**
- **Mock Practical Exam**
- All sorting algorithms (manual implementation without std::sort)
- Recursion techniques
- Data structure combinations

## Exam Preparation

Print this cheatsheet and use it for quick reference during:
- Practical exams (if allowed)
- Revision sessions
- Problem-solving practice

The layout is optimized for **A4 landscape** with 3 columns to maximize information density while maintaining readability.

## Tips for Printing

- Use **landscape orientation**
- Set **minimal margins** (0.3 inches)
- Print in **color** if possible (helps distinguish sections)
- Consider printing **double-sided** to save paper
- Recommended: Print on **cardstock** for durability

## License

Created for TIC2001 students - AY 2025/2026 Semester 1
