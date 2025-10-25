#include <iostream>
#include <map>
using namespace std;

int main() {
  long long n, m;
  cin >> n >> m;

  // multimap: key = candies per packet (y), value = number of packets (x)
  // We want to prioritize packets with MORE candies, so we'll iterate in
  // reverse
  multimap<long long, long long> packets;

  for (long long i = 0; i < n; i++) {
    long long x, y;
    cin >> x >> y;
    packets.insert({y, x});
  }

  long long totalCandies = 0;
  long long packetsTaken = 0;

  // Iterate from highest candies per packet to lowest
  // multimap is sorted in ascending order, so we use reverse iterator
  for (auto it = packets.rbegin(); it != packets.rend() && packetsTaken < m;
       ++it) {
    long long candiesPerPacket = it->first;
    long long availablePackets = it->second;

    // Take as many packets as possible from this neighbor
    long long packetsToTake = min(availablePackets, m - packetsTaken);

    totalCandies += packetsToTake * candiesPerPacket;
    packetsTaken += packetsToTake;
  }

  cout << totalCandies << endl;

  return 0;
}