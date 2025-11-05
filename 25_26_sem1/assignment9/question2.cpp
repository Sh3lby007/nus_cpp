#include <iostream>
#include <vector>

using namespace std;

void dfs(int node,
         vector<vector<int>>& adj,
         vector<bool>& visited,
         vector<int>& component) {
  visited[node] = true;
  component.push_back(node);

  for (int neighbor : adj[node]) {
    if (!visited[neighbor]) {
      dfs(neighbor, adj, visited, component);
    }
  }
}

int solution() {
  int N, M;
  cin >> N >> M;

  // Build adjacency list (1-indexed)
  vector<vector<int>> adj(N + 1);

  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  // Find connected components
  vector<bool> visited(N + 1, false);
  vector<int> componentSize(N + 1, 0);

  for (int i = 1; i <= N; i++) {
    if (!visited[i]) {
      vector<int> component;
      dfs(i, adj, visited, component);

      // All nodes in this component have the same size
      int size = component.size();
      for (int node : component) {
        componentSize[node] = size;
      }
    }
  }

  // Output the result
  for (int i = 1; i <= N; i++) {
    cout << componentSize[i];
    if (i < N)
      cout << " ";
  }
  cout << endl;

  return 0;
}

int main() {
  solution();
  return 0;
}
/**
 * # Cat Lunches Problem - Solution Explanation

## Problem Understanding

**Question:** For each cat, if they host the lunch, how many cats can attend
using only the M remaining bus routes?

**Key Insight:** This is a **Connected Components** problem!
- Cats that can reach each other form a connected component
- If cat X hosts, all cats in X's connected component can attend
- Each cat in the same component has the same answer

## Why This Works

Think of the graph structure:
```
Cats = Vertices
Bus Routes = Edges (undirected)
```

If cat A can reach cat B through bus routes, and cat B can reach cat C, then:
- When A hosts: B and C can attend
- When B hosts: A and C can attend
- When C hosts: A and B can attend

They're all in the same connected component with size 3!

## Example Walkthrough

Input:
```
10 7
1 8
7 2
7 8
3 4
1 7
6 4
10 5
```

### Step 1: Build the Graph

Adjacency List:
```
1: [8, 7]
2: [7]
3: [4]
4: [3, 6]
5: [10]
6: [4]
7: [2, 8, 1]
8: [1, 7]
9: []
10: [5]
```

### Step 2: Find Connected Components Using DFS

**Component 1:** Start from cat 1
- Visit 1 → 8 → 7 → 2
- Component: {1, 2, 7, 8}
- Size: 4

**Component 2:** Start from cat 3 (not visited yet)
- Visit 3 → 4 → 6
- Component: {3, 4, 6}
- Size: 3

**Component 3:** Start from cat 5
- Visit 5 → 10
- Component: {5, 10}
- Size: 2

**Component 4:** Start from cat 9
- Visit 9 (isolated)
- Component: {9}
- Size: 1

### Step 3: Assign Sizes

For each cat, assign the size of their component:
```
Cat 1: Component size = 4
Cat 2: Component size = 4
Cat 3: Component size = 3
Cat 4: Component size = 3
Cat 5: Component size = 2
Cat 6: Component size = 3
Cat 7: Component size = 4
Cat 8: Component size = 4
Cat 9: Component size = 1
Cat 10: Component size = 2
```

**Output:** `4 4 3 3 2 3 4 4 1 2` ✓

## Visual Representation

```
Component 1 (size 4):
    1 --- 8
    |     |
    7 --- +
    |
    2

Component 2 (size 3):
    3 --- 4 --- 6

Component 3 (size 2):
    5 --- 10

Component 4 (size 1):
    9 (isolated)
```

## Algorithm Details

### Time Complexity: O(N + M)
- Building adjacency list: O(M) - process each edge once
- DFS traversal: O(N + M) - visit each vertex once, explore each edge once
- Assigning sizes: O(N) - process each vertex once
- **Total: O(N + M)** ✓ Meets the requirement!

### Space Complexity: O(N + M)
- Adjacency list: O(N + M)
- Visited array: O(N)
- Component size array: O(N)

### Why DFS?
- Simple and efficient for finding connected components
- Could also use BFS (same complexity)
- Union-Find would also work but is overkill here

## Code Structure

```cpp
1. Read N and M
2. Build adjacency list from M edges
3. For each unvisited vertex:
   - Run DFS to find all vertices in the component
   - Store the component size for all vertices in that component
4. Output the component size for each vertex
```

## Why NOT Dijkstra or MST?

**Dijkstra (SSSP):**
- ❌ We don't need shortest paths
- ❌ We don't have weights (or weights don't matter)
- ❌ We just need to know: "Can I reach this vertex?" (reachability)

**MST (Kruskal/Prim):**
- ❌ We don't need a spanning tree
- ❌ We're not minimizing anything
- ❌ We just need connected components

**DFS/BFS (Graph Traversal):**
- ✅ Perfect for finding connected components
- ✅ O(N + M) time complexity
- ✅ Simple and efficient

## Key Takeaway

When you see:
- "How many vertices can reach each other?"
- "Which vertices are connected?"
- "Find groups of connected vertices"

Think: **Connected Components using DFS or BFS**

NOT shortest path (Dijkstra) or spanning tree (MST)!
 */