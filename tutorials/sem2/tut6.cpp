#include <queue>
#include <set>
#include <vector>
using namespace std;

template <typename T>
struct Set {
  vector<T> v;
};

template <typename T>
bool element_of(Set<T>& s, T element) {
  for (T item : s.v) {
    if (item == element) {
      return true;
    }
  }
  return false;
}

template <typename T>
void insert(Set<T>& s, T element) {
  // make sure element is not already in the vector
  if (!element_of(s, element)) {
    s.v.push_back(element);
  }
}

template <typename T>
Set<T> intersect(Set<T>& s, Set<T>& t) {
  Set<T> new_set;
  for (T element : s.v) {
    if (element_of(t, element)) {
      insert(new_set, element);
    }
  }
  return new_set;
}

struct Airport {
  string name;
  set<Airport*> connections;
};

bool direct_connect(Airport& src, Airport& dst) {
  if (src.connections.find(&dst) != src.connections.end()) {
    return true;
  }
  return false;
}

bool indirect_connect(Airport& src, Airport& dst) {
  if (&src == &dst) {
    return true;
  }
  set<Airport*> visited;
  visited.insert(&src);
  queue<Airport*> q;
  q.push(&src);
  while (!q.empty()) {
    Airport* current = q.front();
    q.pop();

    for (Airport* next : current->connections) {
      if (next == &dst) {
        return true;
      }

      if (visited.find(next) == visited.end()) {
        visited.insert(next);
        q.push(next);
      }
    }
  }

  return false;
}
