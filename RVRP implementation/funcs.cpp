#include <iostream>
#include <vector>
#include <set>
using namespace std;

<<<<<<< HEAD
void findMaxWeightPath(int node, vector<int>& path, int currentWeight, 
int currentTime, vector<int>& bestPath, int maxWeight, 
set<int>& visited, int nr_of_clients, int weight[], int dist[][100], int time_g) {
    // Mark the current node as visited
    visited.insert(node);
=======
const int maxTime = 9;
int bestWeight = 0;
vector<int> bestPath;

// Function to generate all possible paths under distance k using backtracking
void generatePaths(int node, vector<int>& path,int totalDistance, 
int totalWeight,int n,float dist[][401],int weight[],int lastweight) {
>>>>>>> 31ea769c505c7d7e3510ef09d9c24c66652fa159

    path.push_back(node);

    if (totalDistance < maxTime) {
        for (int i = 0; i < n; ++i) {
            if(i != node) {
                bool found = false;
                for(int k=0; k<path.size(); k++){
                    if(path[k] == i) found = true;
                }
                if(!found)generatePaths(i, path, totalDistance + dist[node][i], 
                                        totalWeight + weight[i], n, dist, weight, weight[i]);
                else generatePaths(i, path, totalDistance + dist[node][i], 
                                        totalWeight, n, dist, weight, 0);
            }
        }
    } else {
        totalWeight -= lastweight;
        if(totalWeight > bestWeight){
            bestWeight = totalWeight;
            bestPath = path;
        }
    }
    path.pop_back();
}

vector<int> calculateBestPath(int n,float dist[][401],int weight[]){
    vector<int> path;
    generatePaths(0,path,0,0,n,dist,weight,0);
    return bestPath;
}