#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Union-Find (Disjoint Set Union) data structure
class UnionFind {
 private:
  vector<int> parent;
  vector<int> rank;

 public:
  UnionFind(int n) {
    parent.resize(n + 1);
    rank.resize(n + 1, 0);
    for (int i = 0; i <= n; i++) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);  // Path compression
    }
    return parent[x];
  }

  bool unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
      return false;  // Already in same set (would create cycle)
    }

    // Union by rank
    if (rank[rootX] < rank[rootY]) {
      parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
      parent[rootY] = rootX;
    } else {
      parent[rootY] = rootX;
      rank[rootX]++;
    }

    return true;
  }
};

void solution() {
  int V, E;
  cin >> V >> E;

  // Store edges as (weight, u, v)
  vector<tuple<int, int, int>> edges;

  for (int i = 0; i < E; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back({w, u, v});
  }

  // Sort edges by weight in DESCENDING order (maximum first)
  sort(edges.begin(), edges.end(), greater<tuple<int, int, int>>());

  // Kruskal's algorithm with Union-Find
  UnionFind uf(V);
  long long totalWeight = 0;
  int edgesUsed = 0;

  for (auto& edge : edges) {
    int w = get<0>(edge);
    int u = get<1>(edge);
    int v = get<2>(edge);

    // Try to add this edge
    if (uf.unite(u, v)) {
      totalWeight += w;
      edgesUsed++;

      // A spanning tree has exactly V-1 edges
      if (edgesUsed == V - 1) {
        break;
      }
    }
  }

  // Check if we have a spanning tree
  if (edgesUsed == V - 1) {
    cout << totalWeight << endl;
  } else {
    // Graph is not connected
    cout << -1 << endl;
  }
}

int main() {
  solution();
  return 0;
}

/**
 * # Maximum Spanning Tree - Solution Explanation

## Problem

Find a tree that connects all vertices with the **maximum** total edge weight.

## Key Insight

Maximum Spanning Tree (MaxST) is the opposite of Minimum Spanning Tree (MST):
- **MST**: Connect all vertices with minimum total weight
- **MaxST**: Connect all vertices with maximum total weight

**Solution:** Use Kruskal's algorithm, but sort edges in **descending order**
(largest weight first)!

## Algorithm: Modified Kruskal's Algorithm

### Standard Kruskal's (for MST):
1. Sort edges by weight (ascending)
2. Add smallest edges that don't create cycles

### Modified Kruskal's (for MaxST):
1. Sort edges by weight (**descending**)
2. Add **largest** edges that don't create cycles

## Example Walkthrough

**Input:**
```
4 4
1 3 2
1 4 6
2 4 7
3 4 1
```

**Graph:**
```
    1
   /|\
  2 | 6
 /  |  \
3   |   4
 \  |  /
  1 | 7
   \|/
    2
```

### Step 1: List All Edges
```
Edge 1-3: weight 2
Edge 1-4: weight 6
Edge 2-4: weight 7
Edge 3-4: weight 1
```

### Step 2: Sort by Weight (Descending)
```
1. Edge 2-4: weight 7  ← largest
2. Edge 1-4: weight 6
3. Edge 1-3: weight 2
4. Edge 3-4: weight 1  ← smallest
```

### Step 3: Kruskal's Algorithm with Union-Find

**Initial State:**
```
Union-Find: {1}, {2}, {3}, {4}
Total Weight: 0
Edges Used: 0
```

**Process Edge 2-4 (weight 7):**
- Find(2) = 2, Find(4) = 4 → different sets
- Unite(2, 4) → SUCCESS
- Add to tree
```
Union-Find: {1}, {2, 4}, {3}
Total Weight: 7
Edges Used: 1
Tree so far: 2---7---4
```

**Process Edge 1-4 (weight 6):**
- Find(1) = 1, Find(4) = 2 (representative of {2, 4})
- Different sets → Unite(1, 4)
```
Union-Find: {1, 2, 4}, {3}
Total Weight: 7 + 6 = 13
Edges Used: 2
Tree so far:
    1
    |
    6
    |
    4---7---2
```

**Process Edge 1-3 (weight 2):**
- Find(1) = 1 (representative of {1, 2, 4})
- Find(3) = 3
- Different sets → Unite(1, 3)
```
Union-Find: {1, 2, 3, 4}
Total Weight: 13 + 2 = 15
Edges Used: 3
Tree:
    1---2---3
    |
    6
    |
    4---7---2
```

**Stop:** We have V-1 = 3 edges (spanning tree complete)

**Process Edge 3-4 (weight 1):** SKIPPED (not needed)

### Final Result

**Maximum Spanning Tree:**
```
Edges: 2-4 (7), 1-4 (6), 1-3 (2)
Total Weight: 7 + 6 + 2 = 15
```

**Output:** `15` ✓

## Union-Find Data Structure

The key to efficient cycle detection!

### Operations:

**1. Find(x) - Find the representative of x's set**
```cpp
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}
```
- Path compression: Make all nodes point directly to root
- Time complexity: O(α(n)) ≈ O(1) amortized

**2. Unite(x, y) - Merge the sets containing x and y**
```cpp
bool unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) {
        return false; // Already in same set (cycle!)
    }

    // Union by rank
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }

    return true;
}
```
- Union by rank: Attach smaller tree under larger tree
- Keeps tree shallow for faster finds

### Why Union-Find?

**Problem:** How do we know if adding an edge creates a cycle?

**Answer:** If both vertices are already in the same connected component!

```
Example:
If 1 and 3 are connected: {1, 2, 3}
And we try to add edge 1-3:
  Find(1) = 1, Find(3) = 1 → SAME → Would create cycle!
```

## Code Walkthrough

### 1. Reading Input and Storing Edges
```cpp
vector<tuple<int, int, int>> edges;
for (int i = 0; i < E; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edges.push_back({w, u, v}); // Store as (weight, u, v)
}
```
Store weight first so sorting is easy!

### 2. Sort by Weight (Descending)
```cpp
sort(edges.begin(), edges.end(), greater<tuple<int, int, int>>());
```
`greater<>` sorts in descending order (largest first)

### 3. Kruskal's Algorithm
```cpp
UnionFind uf(V);
long long totalWeight = 0;
int edgesUsed = 0;

for (auto& edge : edges) {
    int w = get<0>(edge);
    int u = get<1>(edge);
    int v = get<2>(edge);

    if (uf.unite(u, v)) { // If doesn't create cycle
        totalWeight += w;
        edgesUsed++;

        if (edgesUsed == V - 1) break; // Done!
    }
}
```

### 4. Check if Graph is Connected
```cpp
if (edgesUsed == V - 1) {
    cout << totalWeight << endl;
} else {
    cout << -1 << endl; // Not connected
}
```
A spanning tree has exactly V-1 edges!

## Time Complexity Analysis

1. **Reading input:** O(E)
2. **Sorting edges:** O(E log E)
3. **Kruskal's loop:**
   - Iterate through E edges: O(E)
   - Each unite/find operation: O(α(V)) ≈ O(1)
   - Total: O(E × α(V)) ≈ O(E)

**Overall: O(E log E)**

Since E ≤ V² in any graph, E log E ≤ E log(V²) = 2E log V = O(E log V)

And since the problem states O((V + E) log(V + E)), and typically E ≥ V-1 for
connected graphs:
**O(E log E) = O((V + E) log(V + E))** ✓

## Space Complexity

- Union-Find structure: O(V)
- Edge storage: O(E)
- **Total: O(V + E)**

## Comparison: MaxST vs MST

```
┌────────────────────────┬─────────────┬─────────────┐
│      Operation         │     MST     │    MaxST    │
├────────────────────────┼─────────────┼─────────────┤
│ Sort order             │ Ascending   │ Descending  │
│ Goal                   │ Minimize    │ Maximize    │
│ Select edges           │ Smallest    │ Largest     │
│ Algorithm              │ Kruskal     │ Kruskal     │
│ Cycle detection        │ Union-Find  │ Union-Find  │
│ Time complexity        │ O(E log E)  │ O(E log E)  │
└────────────────────────┴─────────────┴─────────────┘
```

**The algorithms are nearly identical!**

## Alternative Approach: Negate Weights

```cpp
// Convert MaxST to MST by negating weights
for (auto& edge : edges) {
    get<0>(edge) = -get<0>(edge);
}

// Run standard MST algorithm (ascending sort)
sort(edges.begin(), edges.end());

// ... Kruskal's ...

// Negate the result
totalWeight = -totalWeight;
```

Both approaches work, but descending sort is clearer!

## Why NOT Other Algorithms?

**Prim's Algorithm:**
- ✅ Also works for MaxST (use max-heap instead of min-heap)
- ✅ Same time complexity: O(E log V)
- ❌ More complex to implement than Kruskal's

**DFS/BFS:**
- ❌ Don't consider weights
- ❌ Just find connectivity, not optimal tree

**Dijkstra:**
- ❌ For shortest paths, not spanning trees
- ❌ Wrong problem type

## Edge Cases Handled

1. **Disconnected graph:**
   ```
   3 1
   1 2 5
   ```
   Output: `-1` ✓ (can't connect all vertices)

2. **Single vertex:**
   ```
   1 0
   ```
   Output: `-1` ✓ (need 0 edges, but also can't connect nothing)

3. **Complete graph:**
   - Correctly picks V-1 largest edges

4. **Multiple edges with same weight:**
   - Algorithm still works (order doesn't matter)

## Spanning Tree Properties

A tree with V vertices has:
- ✅ Exactly V-1 edges
- ✅ Connected (path between any two vertices)
- ✅ Acyclic (no cycles)

If we have < V-1 edges after processing all edges → graph is disconnected!

## Visual Example

**Graph:**
```
    (2)
1 -------- 3
|          |
|(6)      (1)
|          |
4 -------- 2
    (7)
```

**Maximum Spanning Tree (weight = 15):**
```
    (2)
1 -------- 3
|
|(6)
|
4 -------- 2
    (7)
```
Edges selected: 7, 6, 2 (total = 15)
Edge rejected: 1 (would create cycle)

**Minimum Spanning Tree (weight = 10):**
```
    (2)
1 -------- 3
           |
          (1)
           |
4 -------- 2
    (7)
```
Edges selected: 1, 2, 7 (total = 10)

# MST vs MaxST - Visual Comparison

## The Same Graph, Two Different Trees

### Input Graph
```
    1
   /|\
  2 6 \
 /  |  \
3   |   4
 \  |  /
  1 | 7
   \|/
    2

Edges:
• 1-3: weight 2
• 1-4: weight 6
• 2-4: weight 7
• 3-4: weight 1
```

---

## Minimum Spanning Tree (MST)

### Goal: Minimize total weight

### Kruskal's Steps (Ascending Order):

```
Step 1: Sort edges ascending
┌──────┬────────┐
│ Edge │ Weight │
├──────┼────────┤
│ 3-4  │   1    │ ← smallest
│ 1-3  │   2    │
│ 1-4  │   6    │
│ 2-4  │   7    │ ← largest
└──────┴────────┘

Step 2: Add edge 3-4 (weight 1)
    1       2

    3───1───4

Step 3: Add edge 1-3 (weight 2)
    1───2───3
            │
            1
            │
            4       2

Step 4: Add edge 2-4 (weight 7)
    1───2───3
            │
            1
            │
            4───7───2

Done! (3 edges for 4 vertices)

Step 5: Skip edge 1-4 (would create cycle)
```

### MST Result:
```
    1───2───3
            │
            1
            │
            4───7───2

Edges: {3-4, 1-3, 2-4}
Total: 1 + 2 + 7 = 10
```

---

## Maximum Spanning Tree (MaxST)

### Goal: Maximize total weight

### Kruskal's Steps (Descending Order):

```
Step 1: Sort edges descending
┌──────┬────────┐
│ Edge │ Weight │
├──────┼────────┤
│ 2-4  │   7    │ ← largest
│ 1-4  │   6    │
│ 1-3  │   2    │
│ 3-4  │   1    │ ← smallest
└──────┴────────┘

Step 2: Add edge 2-4 (weight 7)
    1       3

            4───7───2

Step 3: Add edge 1-4 (weight 6)
    1───6───4───7───2

            3

Step 4: Add edge 1-3 (weight 2)
    1───2───3
    │
    6
    │
    4───7───2

Done! (3 edges for 4 vertices)

Step 5: Skip edge 3-4 (would create cycle)
```

### MaxST Result:
```
    1───2───3
    │
    6
    │
    4───7───2

Edges: {2-4, 1-4, 1-3}
Total: 7 + 6 + 2 = 15
```

---

## Side-by-Side Comparison

```
┌─────────────────────────┬─────────────────────────┐
│    Minimum (MST)        │    Maximum (MaxST)      │
│    Total = 10           │    Total = 15           │
├─────────────────────────┼─────────────────────────┤
│                         │                         │
│   1───2───3             │   1───2───3             │
│           │             │   │                     │
│           1             │   6                     │
│           │             │   │                     │
│           4───7───2     │   4───7───2             │
│                         │                         │
│ Uses: smallest edges    │ Uses: largest edges     │
│ Avoids: 6 (expensive)   │ Avoids: 1 (cheap)       │
└─────────────────────────┴─────────────────────────┘
```

---

## Algorithm Differences

```
┌──────────────────┬────────────────┬────────────────┐
│    Feature       │      MST       │     MaxST      │
├──────────────────┼────────────────┼────────────────┤
│ Sort Order       │ Ascending ↑    │ Descending ↓   │
│ Pick Strategy    │ Smallest first │ Largest first  │
│ Result           │ Minimize cost  │ Maximize cost  │
│ Code Change      │ sort(edges)    │ sort(greater)  │
│ Time Complexity  │ O(E log E)     │ O(E log E)     │
│ Union-Find       │ Same           │ Same           │
└──────────────────┴────────────────┴────────────────┘
```

---

## Union-Find Execution Trace

### For MaxST (descending order):

```
Initial: {1} {2} {3} {4}

Process 2-4 (w=7):
  Find(2)=2, Find(4)=4 → Different sets
  Unite → {1} {2,4} {3}
  ✓ Add edge 2-4

Process 1-4 (w=6):
  Find(1)=1, Find(4)=2 → Different sets
  Unite → {1,2,4} {3}
  ✓ Add edge 1-4

Process 1-3 (w=2):
  Find(1)=1, Find(3)=3 → Different sets
  Unite → {1,2,3,4}
  ✓ Add edge 1-3

Process 3-4 (w=1):
  Find(3)=1, Find(4)=1 → SAME set!
  ✗ Skip (would create cycle)
```

---

## When to Use Each?

### Use MST when:
- Minimizing cost (roads, cables, pipes)
- Building cheapest network
- Reducing expenses

**Examples:**
- Connecting cities with minimum cable length
- Power grid with minimum cost
- Water pipeline network

### Use MaxST when:
- Maximizing value (profit, capacity)
- Selecting best connections
- Optimization problems

**Examples:**
- Selecting highest-profit routes
- Maximum capacity network
- Best quality connections

---

## Real-World Analogy

### Building a Road Network

**MST Scenario:**
```
You have $10M budget to connect 4 cities.
Goal: Connect all cities with minimum cost.

Roads:
• A-B: $7M  (expensive, avoid if possible)
• A-C: $6M  (expensive, avoid if possible)
• B-C: $2M  (cheap, use!)
• C-D: $1M  (cheapest, use!)

MST picks: C-D, B-C, A-C = $9M ✓
(or C-D, B-C, A-B = $10M)
```

**MaxST Scenario:**
```
You built 4 roads. Budget cuts force removal of 1.
Goal: Keep roads with maximum total quality score.

Roads:
• A-B: quality 7  (best, keep!)
• A-C: quality 6  (great, keep!)
• B-C: quality 2  (okay)
• C-D: quality 1  (worst, remove!)

MaxST picks: A-B, A-C, B-C = quality 15 ✓
(Remove C-D with quality 1)
```

---

## Common Pitfalls

### ❌ Wrong: Using MST algorithm for MaxST
```cpp
sort(edges.begin(), edges.end()); // Ascending!
// This gives MINIMUM, not MAXIMUM!
```

### ✓ Correct: Sort descending
```cpp
sort(edges.begin(), edges.end(), greater<>());
// Now we get MAXIMUM!
```

### ❌ Wrong: Forgetting cycle check
```cpp
// Adding all large edges without checking
for (auto& edge : edges) {
    totalWeight += get<0>(edge); // WRONG!
}
// This includes cycles!
```

### ✓ Correct: Use Union-Find
```cpp
if (uf.unite(u, v)) { // Only if no cycle
    totalWeight += w;
}
```

---

## Summary

Both MST and MaxST:
- Use Kruskal's algorithm
- Use Union-Find for cycle detection
- Have O(E log E) time complexity
- Build a tree with V-1 edges

**The ONLY difference:**
```cpp
// MST
sort(edges.begin(), edges.end());

// MaxST
sort(edges.begin(), edges.end(), greater<>());
```

One line of code changes everything! 🎯
 */