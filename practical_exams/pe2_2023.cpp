#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

// Room struct definition
struct Room {
  map<string, Room *> exits;
};

// Your implementation goes here
string is_next(Room *src, Room *dst) {
  // Iterate using the pair<key_type, value_type> syntax
  for (pair<string, Room *> exit : src->exits) {
    string direction = exit.first;  // The key (e.g., "east", "south")
    Room *nextRoom = exit.second;   // The value (pointer to the next Room)

    // Check if this exit leads to our destination
    if (nextRoom == dst) {
      return direction;
    }
  }

  // If no exit leads to dst, return empty string
  return "";
}

// Test function
void test_is_next() {
  // Create rooms
  vector<Room> rooms(7);  // 7 rooms from 0 to 6

  // Set up connections as in the sample diagram
  rooms[0].exits["east"] = &rooms[1];
  rooms[0].exits["south"] = &rooms[4];

  rooms[1].exits["east"] = &rooms[2];
  rooms[1].exits["west"] = &rooms[0];

  // Add more connections as needed

  // Test the function
  cout << "Room 0 to Room 1: " << is_next(&rooms[0], &rooms[1]) << endl;
  cout << "Room 0 to Room 2: " << is_next(&rooms[0], &rooms[2]) << endl;
  cout << "Room 0 to Room 3: " << is_next(&rooms[0], &rooms[3]) << endl;
  cout << "Room 0 to Room 4: " << is_next(&rooms[0], &rooms[4]) << endl;
}

// Helper function for recursive path finding
vector<string> find_path_helper(Room *current, Room *dst, Room *prev,
                                set<Room *> &visited) {
  // TODO: Implement the recursive helper function
  // Hint:
  // - Check if current is the destination
  // - Try each exit (except the one back to prev)
  // - Build and return the path if found
  // Base case: Found the destination
  // Base case: Found the destination
  if (current == dst) {
    return {};  // Empty path - we're already there!
  }

  // Mark current room as visited
  visited.insert(current);

  // Try each exit from the current room
  for (auto exit : current->exits) {
    string direction = exit.first;
    Room *nextRoom = exit.second;

    // Skip rooms we've already visited to avoid cycles
    if (visited.count(nextRoom)) {
      continue;
    }

    // Recursively try to find a path from the next room
    vector<string> path = find_path_helper(nextRoom, dst, current, visited);

    // If a path was found, add the current direction to it
    if (!path.empty() || nextRoom == dst) {
      path.insert(path.begin(), direction);
      return path;
    }
  }

  // No path found from this room - remove from visited to allow other paths to
  // use it
  visited.erase(current);

  // No path found
  return {};
}

// Main function as required by the problem
vector<string> find_path(Room *src, Room *dst) {
  // TODO: Implement the main function
  // This can call the helper function to start the recursion
  // Handle the edge case where source is already destination
  if (src == dst) {
    return {};
  }

  set<Room *> visited;
  return find_path_helper(src, dst, nullptr, visited);
}

int main() {
  test_is_next();

  return 0;
}