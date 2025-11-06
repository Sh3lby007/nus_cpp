# Uncle Tan's Leaderboard System - Complete Explanation

## Problem Overview

A leaderboard system that manages player scores with the ability to:
- Add/update player scores dynamically
- Query top k players
- Query individual player scores
- Create checkpoints (SNAP)
- Undo to previous checkpoints (UNDO)

---

## Core Challenge: Dual Data Structure Synchronization

The key insight is that you need **TWO synchronized data structures** to efficiently support all operations:

```
┌─────────────────────────────────────────────────────────────┐
│                    LEADERBOARD SYSTEM                        │
├─────────────────────────────────────────────────────────────┤
│                                                               │
│  scores (map)                 leaderboard (set)              │
│  ┌──────────────────┐        ┌──────────────────────────┐   │
│  │ id    → score    │        │ (score, id) sorted by:   │   │
│  ├──────────────────┤        │ 1. score (descending)    │   │
│  │ alice → 10       │        │ 2. id (ascending)        │   │
│  │ bob   → 5        │        ├──────────────────────────┤   │
│  │ carl  → -3       │        │ (10, "alice")  ← best    │   │
│  └──────────────────┘        │ (5, "bob")               │   │
│         ▲                     │ (-3, "carl")   ← worst   │   │
│         │                     └──────────────────────────┘   │
│    O(log n) lookup                      ▲                    │
│    for SCORE                    O(k) for TOP k               │
│                                                               │
└─────────────────────────────────────────────────────────────┘
```

---

## Data Structures in Detail

### 1. Custom Comparator: LeaderboardComp

```cpp
struct LeaderboardComp {
  bool operator()(const pair<int, string>& a,
                  const pair<int, string>& b) const {
    if (a.first != b.first) {
      return a.first > b.first;  // Higher score comes first (DESCENDING)
    }
    return a.second < b.second;  // Alphabetically smaller id (ASCENDING)
  }
};
```

**Why Custom Comparator?**

Default comparison on `pair<int, string>`:
```
(5, "bob") < (10, "alice")  ← ascending order
```

We need:
```
(10, "alice") < (5, "bob")  ← descending by score, ascending by id
```

**Comparator Truth Table:**

```
Entry A          Entry B          Result    Reason
─────────────────────────────────────────────────────────
(100, "alice")   (100, "bob")     true      Same score, "alice" < "bob" lexicographically
(100, "alice")   (100, "alice")   false     Identical entries
(100, "bob")     (50, "zoe")      true      100 > 50 (higher score comes first)
(50, "zoe")      (100, "bob")     false     50 < 100
```

### 2. Scores Map

```cpp
map<string, int> scores;  // player_id → current_score
```

**Purpose:** O(log n) score lookup for SCORE operations

**Content:**
```
scores["alice"] = 10
scores["bob"] = 5
scores["carl"] = -3
```

### 3. Leaderboard Set

```cpp
set<pair<int, string>, LeaderboardComp> leaderboard;
```

**Purpose:** Maintain sorted ranking for TOP k operations

**Content:** Automatically sorted by comparator
```
leaderboard = {
  (10, "alice"),    ← rank 1 (highest score)
  (5, "bob"),       ← rank 2
  (-3, "carl")      ← rank 3 (lowest score)
}
```

### 4. Checkpoints Stack

```cpp
stack<Snapshot> checkpoints;

struct Snapshot {
  map<string, int> scores;
  set<pair<int, string>, LeaderboardComp> leaderboard;
};
```

**Purpose:** Save complete state for UNDO operations

**Visualization:**
```
checkpoints stack (LIFO)
┌─────────────────────────────────────────┐
│ Top (most recent checkpoint)            │
│ ┌─────────────────────────────────────┐ │
│ │ Snapshot 2 (after step 4, before 5) │ │
│ │ scores: {alice: 10, bob: 5}          │ │
│ │ leaderboard: {(10,alice), (5,bob)}   │ │
│ └─────────────────────────────────────┘ │
│ ┌─────────────────────────────────────┐ │
│ │ Snapshot 1                          │ │
│ │ (bottom of stack)                   │ │
│ └─────────────────────────────────────┘ │
└─────────────────────────────────────────┘
```

---

## Operation Details

### ADD: Update Score

**The Challenge:** Updating a set element requires removal and reinsertion

```cpp
// Before: ADD bob 20
scores["bob"] = 5
leaderboard contains (5, "bob")

// Step 1: Remove old entry
leaderboard.erase({5, "bob"});

// Step 2: Update score
scores["bob"] += 20;  // scores["bob"] = 25

// Step 3: Insert new entry
leaderboard.insert({25, "bob"});

// After:
scores["bob"] = 25
leaderboard contains (25, "bob")
```

**Why Three Steps?**

❌ **Wrong approach:**
```cpp
// Can't modify in-place - corrupts set ordering
leaderboard.find({scores["bob"], "bob"})->first += 20;
```

✅ **Correct approach:**
```cpp
// Remove old, update, re-insert
leaderboard.erase({scores["bob"], "bob"});
scores["bob"] += delta;
leaderboard.insert({scores["bob"], "bob"});
```

**Complexity:** O(log n)

---

### SNAP: Create Checkpoint

```cpp
Snapshot snap;
snap.scores = scores;           // Deep copy of entire scores map
snap.leaderboard = leaderboard; // Deep copy of entire leaderboard set
checkpoints.push(snap);         // Push to stack
```

**Visualization:**
```
Before SNAP:
┌──────────────────┐      ┌──────────────────┐
│ scores           │      │ leaderboard      │
├──────────────────┤      ├──────────────────┤
│ alice → 10       │      │ (10, "alice")    │
│ bob → 5          │      │ (5, "bob")       │
│ carl → -3        │      │ (-3, "carl")     │
└──────────────────┘      └──────────────────┘

SNAP operation takes snapshot
        ↓
checkpoints = [
  Snapshot {
    scores: {alice: 10, bob: 5, carl: -3},
    leaderboard: {(10, alice), (5, bob), (-3, carl)}
  }
]
```

**Complexity:** O(n) time and space

---

### TOP k: Query Top Players

```cpp
int count = 0;
bool first = true;
for (auto& entry : leaderboard) {  // Iterates in sorted order
  if (count >= k) break;           // Stop after k players
  if (!first) cout << " ";
  cout << entry.second;            // Print player id
  first = false;
  count++;
}
cout << endl;
```

**Why This Works:**

Set iteration follows the comparator order automatically:
```
leaderboard iteration order:
(10, "alice")  ← Printed first (count=0)
(5, "bob")     ← Printed second (count=1)
(-3, "carl")   ← Stop if k=2

Output: "alice bob"
```

**Complexity:** O(k)

---

### SCORE: Query Single Player

```cpp
if (scores.count(id)) {
  cout << scores[id] << endl;
} else {
  cout << 0 << endl;  // Unseen players have score 0
}
```

**Key Point:** Querying does NOT create the player. Only ADD does.

```
SCORE unknown_player → 0
(unknown_player not added to scores)

ADD alice 10
SCORE alice → 10
```

**Complexity:** O(log n)

---

### UNDO: Restore to Checkpoint

```cpp
if (checkpoints.empty()) {
  cout << "EMPTY" << endl;  // No checkpoint available
} else {
  Snapshot snap = checkpoints.top();
  checkpoints.pop();
  scores = snap.scores;           // Restore scores
  leaderboard = snap.leaderboard; // Restore leaderboard
}
```

**Visualization:**
```
Before UNDO:
┌────────────────────────┐
│ Current State:         │
│ alice: 25, bob: 25     │
│ carl: -3               │
└────────────────────────┘
        checkpoint: [] (empty)

UNDO with empty checkpoint
        ↓
Output: "EMPTY"
State unchanged


After SNAP (Step 4):
┌────────────────────────┐
│ Current State:         │
│ alice: 10, bob: 5      │
└────────────────────────┘
        ↓ checkpoints stack
┌────────────────────────┐
│ Snapshot {             │
│   alice: 10, bob: 5    │
│ }                      │
└────────────────────────┘

After ADD bob 20, ADD carl -3:
┌────────────────────────┐
│ Current State:         │
│ alice: 10, bob: 25     │
│ carl: -3               │
└────────────────────────┘
        ↓ checkpoints stack (unchanged)
┌────────────────────────┐
│ Snapshot {             │
│   alice: 10, bob: 5    │
│ }                      │
└────────────────────────┘

UNDO restores:
        ↓
┌────────────────────────┐
│ Current State:         │
│ alice: 10, bob: 5      │
│ carl: (removed)        │
└────────────────────────┘
```

**Complexity:** O(n)

---

## Complete Example Walkthrough

### Input
```
12
ADD alice 10
ADD bob 5
TOP 2
SNAP
ADD bob 20
ADD carl -3
TOP 3
UNDO
TOP 3
SCORE carl
UNDO
UNDO
```

### Step-by-Step Execution

#### Step 1: `ADD alice 10`
```
scores["alice"] not found, so:
  scores["alice"] = 0 + 10 = 10
  leaderboard.insert({10, "alice"})

State:
  scores: {alice: 10}
  leaderboard: {(10, "alice")}
  checkpoints: []
Output: (none)
```

#### Step 2: `ADD bob 5`
```
scores["bob"] not found, so:
  scores["bob"] = 0 + 5 = 5
  leaderboard.insert({5, "bob"})

State:
  scores: {alice: 10, bob: 5}
  leaderboard: {(10, "alice"), (5, "bob")}
  checkpoints: []
Output: (none)
```

#### Step 3: `TOP 2`
```
Iterate leaderboard, print first 2 entries:
  entry[0] = (10, "alice") → print "alice"
  entry[1] = (5, "bob") → print "bob"

State: (unchanged)
Output: alice bob
```

#### Step 4: `SNAP`
```
Create checkpoint of current state:
  snap.scores = {alice: 10, bob: 5}
  snap.leaderboard = {(10, "alice"), (5, "bob")}
  checkpoints.push(snap)

State:
  scores: {alice: 10, bob: 5}
  leaderboard: {(10, "alice"), (5, "bob")}
  checkpoints: [snap1]
Output: (none)
```

#### Step 5: `ADD bob 20`
```
scores["bob"] = 5 (found):
  leaderboard.erase({5, "bob"})     ← Remove old entry
  scores["bob"] = 5 + 20 = 25       ← Update
  leaderboard.insert({25, "bob"})   ← Insert new entry

Set reorders automatically:
  (25, "bob") now comes before (10, "alice")

State:
  scores: {alice: 10, bob: 25}
  leaderboard: {(25, "bob"), (10, "alice")}
  checkpoints: [snap1]
Output: (none)
```

#### Step 6: `ADD carl -3`
```
scores["carl"] not found, so:
  scores["carl"] = 0 + (-3) = -3
  leaderboard.insert({-3, "carl"})

State:
  scores: {alice: 10, bob: 25, carl: -3}
  leaderboard: {(25, "bob"), (10, "alice"), (-3, "carl")}
  checkpoints: [snap1]
Output: (none)
```

#### Step 7: `TOP 3`
```
Iterate leaderboard in order, print all 3:
  (25, "bob") → "bob"
  (10, "alice") → "alice"
  (-3, "carl") → "carl"

State: (unchanged)
Output: bob alice carl
```

#### Step 8: `UNDO`
```
checkpoints.empty() = false:
  snap = checkpoints.top() = snap1
  checkpoints.pop()
  scores = snap.scores = {alice: 10, bob: 5}
  leaderboard = snap.leaderboard = {(10, "alice"), (5, "bob")}

State:
  scores: {alice: 10, bob: 5}
  leaderboard: {(10, "alice"), (5, "bob")}
  checkpoints: []
  carl is removed
Output: (none)
```

#### Step 9: `TOP 3`
```
Iterate leaderboard, print all entries (only 2 exist):
  (10, "alice") → "alice"
  (5, "bob") → "bob"

State: (unchanged)
Output: alice bob
```

#### Step 10: `SCORE carl`
```
scores.count("carl") = 0 (not found):
  Output: 0

State: (unchanged)
Output: 0
```

#### Step 11: `UNDO`
```
checkpoints.empty() = true:
  Output: "EMPTY"
  State unchanged

State: (no change)
Output: EMPTY
```

#### Step 12: `UNDO`
```
checkpoints.empty() = true:
  Output: "EMPTY"
  State unchanged

State: (no change)
Output: EMPTY
```

### Complete Output
```
alice bob
bob alice carl
alice bob
0
EMPTY
EMPTY
```

---

## Visual Timeline

```
Timeline of state changes:

Step 1-2:
┌─────────────────────────┐
│ alice: 10, bob: 5       │
│ Ranking: [alice, bob]   │
│ Checkpoints: []         │
└─────────────────────────┘

Step 3:
┌─────────────────────────┐     Output: alice bob
│ alice: 10, bob: 5       │
│ Ranking: [alice, bob]   │
│ Checkpoints: []         │
└─────────────────────────┘

Step 4 (SNAP):
┌─────────────────────────┐
│ alice: 10, bob: 5       │
│ Ranking: [alice, bob]   │
│ Checkpoints: [snap1]    │◄─ Checkpoint created
└─────────────────────────┘

Step 5-6 (Changes):
┌─────────────────────────┐
│ alice: 10, bob: 25      │
│ carl: -3                │
│ Ranking: [bob, alice]   │
│ Checkpoints: [snap1]    │◄─ Checkpoint unchanged
└─────────────────────────┘

Step 7:
Output: bob alice carl

Step 8 (UNDO):
┌─────────────────────────┐
│ alice: 10, bob: 5       │ ◄─ Restored from snap1
│ Ranking: [alice, bob]   │
│ Checkpoints: []         │◄─ Snapshot popped
└─────────────────────────┘

Step 9:
Output: alice bob

Step 10:
Output: 0

Steps 11-12:
Checkpoints empty → Output: EMPTY (twice)
```

---

## Complexity Analysis

| Operation | Time | Space | Notes |
|-----------|------|-------|-------|
| ADD | O(log n) | O(1) | Erase + Update + Insert on set |
| SNAP | O(n) | O(n) | Copy entire state to stack |
| UNDO | O(n) | O(1) | Copy from stack back to structures |
| TOP k | O(k) | O(1) | Iterate sorted set, take first k |
| SCORE | O(log n) | O(1) | Map lookup with count() |

**Overall:**
- Best case: Q SCORE operations → O(Q log n)
- Worst case: Alternating SNAP/UNDO → O(Q²) or O(Q·n)

---

## Key Design Decisions

### 1. Why Two Data Structures?

```
Option A: Only scores map
  ADD: O(log n) ✓
  SCORE: O(log n) ✓
  TOP k: O(n log n) ✗ Need to sort every time

Option B: Only leaderboard set
  ADD: O(log n) ✓
  SCORE: O(n) ✗ Linear search
  TOP k: O(k) ✓

Option C: Both (chosen)
  ADD: O(log n) ✓
  SCORE: O(log n) ✓
  TOP k: O(k) ✓
```

### 2. Why Custom Comparator?

Need descending score + ascending id for tie-breaking:
```
Default: (5, "bob") < (10, "alice")  ← ascending scores
Need: (10, "alice") < (5, "bob")     ← descending scores
```

Custom comparator reverses the score comparison direction.

### 3. Why Stack for Checkpoints?

```
SNAP → Push (O(1))
UNDO → Pop (O(1))
Multiple nested SNAPs → Stack LIFO semantics perfect fit
```

### 4. Why Deep Copy on SNAP/UNDO?

Simple and correct. Alternative approaches:
- **Copy-on-write:** Complex, needs reference counting
- **Diff-based:** Complex, need to track changes
- **Deep copy:** Simple, works correctly for nested checkpoints

---

## Common Pitfalls

### ❌ Pitfall 1: Modifying Set Elements In-Place
```cpp
// WRONG - corrupts set ordering
auto it = leaderboard.find({5, "bob"});
it->first = 10;  // Violates set's sorted property

// CORRECT
leaderboard.erase({5, "bob"});
leaderboard.insert({10, "bob"});
```

### ❌ Pitfall 2: Forgetting Score Default is 0
```cpp
// User might expect SCORE unknown_player to fail
SCORE alice → 10  (alice exists)
SCORE zoe → 0     (zoe doesn't exist, returns 0)
```

### ❌ Pitfall 3: Not Tracking Checkpoint Stack Depth
```cpp
SNAP, SNAP, UNDO, UNDO, UNDO
          ↑ Last UNDO finds empty stack → "EMPTY"
```

### ❌ Pitfall 4: Ignoring Comparator Order in TOP k
```cpp
// Leaderboard iteration depends on comparator
for (auto entry : leaderboard) {
  // Entry comes in (score desc, id asc) order
  // NOT sorted by id, NOT reverse score order
}
```

---

## Summary

The Uncle Tan Leaderboard system is complex because it requires:

1. **Dual data structures** (scores map + leaderboard set) for efficient operations
2. **Custom comparator** to handle descending score + ascending id tie-breaking
3. **Careful synchronization** between map and set during ADD
4. **Stack-based checkpointing** for SNAP/UNDO functionality
5. **Deep copying** of entire state for each checkpoint

The design trades some space complexity for clean, correct semantics and O(log n) per operation (except SNAP/UNDO which are O(n)).
