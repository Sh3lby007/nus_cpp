#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

void solution() {
  int V, E;
  cin >> V >> E;

  vector<vector<pair<int, int>>> adj(V + 1);

  for (int i = 0; i < E; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  vector<long long> dist(V + 1, LLONG_MAX);
  priority_queue<pair<long long, int>, vector<pair<long long, int>>,
                 greater<pair<long long, int>>>
      pq;

  dist[1] = 0;
  pq.push({0, 1});

  while (!pq.empty()) {
    long long d = pq.top().first;
    int u = pq.top().second;
    pq.pop();

    if (d > dist[u]) {
      continue;
    }

    for (auto& edge : adj[u]) {
      int v = edge.first;
      int weight = edge.second;
      long long newDist = dist[u] + weight;

      if (newDist < dist[v]) {
        dist[v] = newDist;
        pq.push({newDist, v});
      }
    }
  }

  for (int i = 2; i <= V; i++) {
    if (dist[i] == LLONG_MAX) {
      cout << -1 << endl;
    } else {
      cout << dist[i] << endl;
    }
  }
}

int main() {
  solution();
  return 0;
}

/**
 * # SSSP (Single Source Shortest Path) - Solution Explanation

## Problem

Find the shortest path from vertex 1 to every other vertex in an undirected
weighted graph.

## Algorithm: Dijkstra's Algorithm

**Why Dijkstra?**
- Works perfectly for graphs with non-negative edge weights (all weights ≥ 1)
- Time complexity: O((V + E) log V) with priority queue
- Optimal for this problem

## How Dijkstra Works

**Core Idea:** Greedily explore vertices in order of their distance from the
source.

**Steps:**
1. Initialize distance to source (vertex 1) as 0, all others as infinity
2. Use a min-heap (priority queue) to always process the closest unprocessed
vertex
3. For each vertex, relax all its neighbors (update their distances if we found
a shorter path)
4. Repeat until all reachable vertices are processed

## Example Walkthrough

**Input:**
```
4 4
1 3 2
1 4 6
2 4 7
3 4 1
```

**Graph visualization:**
```
    1
   /|\
  2 | 6
 /  |  \
3   |   4
 \  |  /
  1 | 7
   \|/
    (2-4-7)
```

Actually:
```
1 ---2--- 3
|         |
6         1
|         |
4 ---7--- 2
```

### Step-by-Step Execution

**Initial State:**
```
dist[1] = 0
dist[2] = ∞
dist[3] = ∞
dist[4] = ∞

PQ: [(0, 1)]
```

**Iteration 1:** Process vertex 1 (distance 0)
- Edge 1→3 (weight 2): dist[3] = min(∞, 0+2) = 2
- Edge 1→4 (weight 6): dist[4] = min(∞, 0+6) = 6

```
dist[1] = 0
dist[2] = ∞
dist[3] = 2  ← updated
dist[4] = 6  ← updated

PQ: [(2, 3), (6, 4)]
```

**Iteration 2:** Process vertex 3 (distance 2)
- Edge 3→1 (weight 2): dist[1] = min(0, 2+2) = 0 (no improvement)
- Edge 3→4 (weight 1): dist[4] = min(6, 2+1) = 3 ← better!

```
dist[1] = 0
dist[2] = ∞
dist[3] = 2
dist[4] = 3  ← updated

PQ: [(3, 4), (6, 4)]  // Note: (6, 4) is now stale
```

**Iteration 3:** Process vertex 4 (distance 3)
- Edge 4→1 (weight 6): dist[1] = min(0, 3+6) = 0 (no improvement)
- Edge 4→2 (weight 7): dist[2] = min(∞, 3+7) = 10 ← updated!
- Edge 4→3 (weight 1): dist[3] = min(2, 3+1) = 2 (no improvement)

```
dist[1] = 0
dist[2] = 10  ← updated
dist[3] = 2
dist[4] = 3

PQ: [(6, 4), (10, 2)]
```

**Iteration 4:** Process vertex 4 again (distance 6 - STALE)
- Skip because 6 > dist[4] = 3

**Iteration 5:** Process vertex 2 (distance 10)
- Edge 2→4 (weight 7): dist[4] = min(3, 10+7) = 3 (no improvement)

**Final distances:**
```
From vertex 1 to:
  vertex 2: 10 (path: 1→3→4→2)
  vertex 3: 2  (path: 1→3)
  vertex 4: 3  (path: 1→3→4)
```

**Output:**
```
10
2
3
```
✓ Matches expected output!

## Code Explanation

### Key Data Structures

1. **Adjacency List:**
   ```cpp
   vector<vector<pair<int, int>>> adj(V + 1);
   // adj[u] = [(v1, w1), (v2, w2), ...]
   ```

2. **Distance Array:**
   ```cpp
   vector<long long> dist(V + 1, LLONG_MAX);
   // dist[i] = shortest distance from vertex 1 to vertex i
   ```

3. **Priority Queue (Min-Heap):**
   ```cpp
   priority_queue<pair<long long, int>,
                  vector<pair<long long, int>>,
                  greater<pair<long long, int>>> pq;
   // Stores (distance, vertex) pairs
   // Always gives us the vertex with minimum distance
   ```

### Critical Implementation Details

**1. Why use `long long` for distances?**
```cpp
vector<long long> dist(V + 1, LLONG_MAX);
```
- With V, E ≤ 10^5 and weights ≤ 1000
- Worst case path length: (V-1) × max_weight = 10^5 × 1000 = 10^8
- This fits in `long long` but might overflow `int` in edge cases

**2. Why check `if (d > dist[u])`?**
```cpp
if (d > dist[u]) {
    continue; // Skip stale entries
}
```
- Priority queue may contain multiple entries for the same vertex
- Only process the one with the current best distance
- Older entries become "stale" after we find better paths

**3. Relaxation step:**
```cpp
long long newDist = dist[u] + weight;
if (newDist < dist[v]) {
    dist[v] = newDist;
    pq.push({newDist, v});
}
```
- This is the core of Dijkstra
- "Can I reach v through u faster than the current best path?"

**4. Handling unreachable vertices:**
```cpp
if (dist[i] == LLONG_MAX) {
    cout << -1 << endl;
}
```
- If a vertex is never reached, its distance stays at infinity
- Output -1 as required

## Time Complexity Analysis

**Operations:**
1. Building adjacency list: O(E)
2. Dijkstra's main loop:
   - Each vertex is extracted from PQ once: O(V log V)
   - Each edge is relaxed at most once: O(E log V)
   - Total: O((V + E) log V)

**Overall: O((V + E) log V)**

Since V ≤ E in most connected graphs, this simplifies to:
**O(E log V)** or equivalently **O((V + E) log(V + E))** ✓

## Space Complexity

- Adjacency list: O(V + E)
- Distance array: O(V)
- Priority queue: O(V) in the worst case
- **Total: O(V + E)**

## Why NOT Other Algorithms?

**BFS (Breadth-First Search):**
- ❌ Only works for unweighted graphs or equal weights
- ❌ Cannot handle different edge weights

**Bellman-Ford:**
- ✅ Works but slower: O(VE)
- ✅ Handles negative weights (not needed here)
- ❌ Overkill and inefficient for this problem

**DFS (Depth-First Search):**
- ❌ Doesn't guarantee shortest paths
- ❌ Explores paths in wrong order

**Floyd-Warshall:**
- ✅ Finds all-pairs shortest paths
- ❌ O(V³) - way too slow
- ❌ Overkill when we only need single-source

## Common Pitfalls to Avoid

1. **Forgetting to add edges in both directions** (undirected graph)
2. **Using `int` instead of `long long`** (potential overflow)
3. **Not skipping stale priority queue entries** (wrong answers)
4. **Initializing distance array with 0 instead of infinity**
5. **Forgetting to handle unreachable vertices** (should output -1)

## Testing Edge Cases

**Disconnected graph:**
```
3 1
1 2 5
```
Output: `5 -1` (vertex 3 is unreachable)

**Single vertex:**
```
1 0
```
Output: (none - only 1 vertex)

**Direct edge is shortest:**
```
3 2
1 2 10
1 3 5
```
Output: `10 5`



# Dijkstra's Algorithm - Visual Step-by-Step Guide

## Example Graph

```
    2
   / \
  2   6
 /     \
1       4
 \     /
  2   1
   \ /
    3
    |
    7
    |
    2
```

Edges:
- 1-3: weight 2
- 1-4: weight 6
- 2-4: weight 7
- 3-4: weight 1

## Dijkstra Execution Trace

### Initial State
```
┌─────┬──────────┬────────┐
│ Vtx │ Distance │ Status │
├─────┼──────────┼────────┤
│  1  │    0     │ START  │
│  2  │    ∞     │        │
│  3  │    ∞     │        │
│  4  │    ∞     │        │
└─────┴──────────┴────────┘

Priority Queue: [(0, 1)]
```

### Step 1: Process vertex 1
```
Current: vertex 1, distance 0

Exploring neighbors:
  • 1 → 3 (weight 2): 0 + 2 = 2 < ∞ → UPDATE dist[3] = 2
  • 1 → 4 (weight 6): 0 + 6 = 6 < ∞ → UPDATE dist[4] = 6

┌─────┬──────────┬────────┐
│ Vtx │ Distance │ Status │
├─────┼──────────┼────────┤
│  1  │    0     │ ✓ DONE │
│  2  │    ∞     │        │
│  3  │    2     │ ← NEW  │
│  4  │    6     │ ← NEW  │
└─────┴──────────┴────────┘

Priority Queue: [(2, 3), (6, 4)]
```

### Step 2: Process vertex 3
```
Current: vertex 3, distance 2

Exploring neighbors:
  • 3 → 1 (weight 2): 2 + 2 = 4 > 0 → NO UPDATE
  • 3 → 4 (weight 1): 2 + 1 = 3 < 6 → UPDATE dist[4] = 3

┌─────┬──────────┬────────┐
│ Vtx │ Distance │ Status │
├─────┼──────────┼────────┤
│  1  │    0     │ ✓ DONE │
│  2  │    ∞     │        │
│  3  │    2     │ ✓ DONE │
│  4  │    3     │ ← BETTER│
└─────┴──────────┴────────┘

Priority Queue: [(3, 4), (6, 4) ← stale]
```

### Step 3: Process vertex 4
```
Current: vertex 4, distance 3

Exploring neighbors:
  • 4 → 1 (weight 6): 3 + 6 = 9 > 0 → NO UPDATE
  • 4 → 2 (weight 7): 3 + 7 = 10 < ∞ → UPDATE dist[2] = 10
  • 4 → 3 (weight 1): 3 + 1 = 4 > 2 → NO UPDATE

┌─────┬──────────┬────────┐
│ Vtx │ Distance │ Status │
├─────┼──────────┼────────┤
│  1  │    0     │ ✓ DONE │
│  2  │   10     │ ← NEW  │
│  3  │    2     │ ✓ DONE │
│  4  │    3     │ ✓ DONE │
└─────┴──────────┴────────┘

Priority Queue: [(6, 4) ← stale, (10, 2)]
```

### Step 4: Skip stale entry (6, 4)
```
Current: vertex 4, distance 6 (from PQ)

Check: 6 > dist[4] = 3 → SKIP (stale entry)

Priority Queue: [(10, 2)]
```

### Step 5: Process vertex 2
```
Current: vertex 2, distance 10

Exploring neighbors:
  • 2 → 4 (weight 7): 10 + 7 = 17 > 3 → NO UPDATE

┌─────┬──────────┬────────┐
│ Vtx │ Distance │ Status │
├─────┼──────────┼────────┤
│  1  │    0     │ ✓ DONE │
│  2  │   10     │ ✓ DONE │
│  3  │    2     │ ✓ DONE │
│  4  │    3     │ ✓ DONE │
└─────┴──────────┴────────┘

Priority Queue: []
```

### Final Result

```
Shortest paths from vertex 1:
  To vertex 2: 10 (path: 1→3→4→2)
  To vertex 3: 2  (path: 1→3)
  To vertex 4: 3  (path: 1→3→4)
```

## Key Observations

1. **Greedy Choice**: Always process the vertex with minimum distance
2. **Relaxation**: Update distances when we find shorter paths
3. **Stale Entries**: Priority queue may have old entries - skip them
4. **One Pass**: Each vertex is processed exactly once (when popped from PQ)
5. **Optimal Substructure**: Shortest path to v through u uses shortest path to
u

## Comparison with Other Algorithms

```
┌────────────────┬──────────────┬─────────────┬──────────────┐
│   Algorithm    │ Time         │ Neg Weights │ Use Case     │
├────────────────┼──────────────┼─────────────┼──────────────┤
│ BFS            │ O(V + E)     │ NO          │ Unweighted   │
│ Dijkstra       │ O(E log V)   │ NO          │ Non-neg ✓    │
│ Bellman-Ford   │ O(VE)        │ YES         │ Neg weights  │
│ Floyd-Warshall │ O(V³)        │ YES         │ All-pairs    │
└────────────────┴──────────────┴─────────────┴──────────────┘
```

For this problem: **Dijkstra is optimal!**
 */