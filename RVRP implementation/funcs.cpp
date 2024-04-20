#include <vector>
#include <set>
using namespace std;

void findMaxWeightPath(int node, vector<int>& path, int currentWeight, 
int currentTime, vector<int>& bestPath, int maxWeight, 
set<int>& visited, int nr_of_clients, int weight[], int dist[][100], int time_g) {
    // Mark the current node as visited
    visited.insert(node);

    // Add the current node to the path
    path.push_back(node);
    currentWeight += weight[node];

    // If the current path is better, update the best path and max weight
    if (currentWeight > maxWeight && currentTime <= time_g) {
        maxWeight = currentWeight;
        bestPath = path;
    }

    // Explore all adjacent nodes
    for (int nextNode = 0; nextNode < nr_of_clients; ++nextNode) {
        if (visited.find(nextNode) == visited.end()) { // Check if the node is not already visited
            int nextTime = currentTime + dist[node][nextNode];
            if (nextTime <= time_g) {
                findMaxWeightPath(nextNode, path, currentWeight, nextTime, bestPath,
                 maxWeight, visited, nr_of_clients, weight, dist, time_g);
            }
        }
    }

    // Backtrack: remove the current node from the path and mark it as unvisited
    path.pop_back();
    visited.erase(node);
}