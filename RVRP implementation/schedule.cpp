#include <iostream>
#include <vector>
#include <set>
using namespace std;

// Global variables (as per your provided code)
int nr_of_clients = 5;
int time_g = 9;
int dist[5][5] = {
    {0, 3, 2, 1, 4},
    {3, 0, 3, 1, 5},
    {2, 3, 0, 3, 1},
    {1, 1, 3, 0, 12},
    {4, 5, 1, 12, 0}};
int weight[5] = {0, 1, 3, 5, 3}; // Adjusted the size to match the number of clients
// Function to find the maximum weight path
void findMaxWeightPath(int node, vector<int>& path, int currentWeight, int currentTime, vector<int>& bestPath, int& maxWeight, set<int>& visited) {
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
                findMaxWeightPath(nextNode, path, currentWeight, nextTime, bestPath, maxWeight, visited);
            }
        }
    }

    // Backtrack: remove the current node from the path and mark it as unvisited
    path.pop_back();
    visited.erase(node);
}

int main() {
    vector<int> path, bestPath;
    set<int> visited;
    int maxWeight = 0;

    // Try each node as a starting point
    for (int startNode = 0; startNode < nr_of_clients; ++startNode) {
        findMaxWeightPath(startNode, path, 0, 0, bestPath, maxWeight, visited);
    }

    // Output the best path and its weight
    cout << "Best path with maximum weight sum within time limit:" << endl;
    for (int node : bestPath) {
        cout << node << " ";
    }
    cout << "\nMaximum weight sum: " << maxWeight << endl;

    return 0;
}
