#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int maxTime = 9;
int bestWeight = 0;
vector<int> bestPath;

// Function to generate all possible paths under distance k using backtracking
void generatePaths(int node, vector<int>& path,int totalTime, 
int totalWeight,int n,int dist[][5],int weight[],int lastweight) {

    path.push_back(node);

    if (totalTime < maxTime) {
        for (int i = 0; i < n; ++i) {
            if(i != node) {
                bool found = false;
                for(int k=0; k<path.size(); k++){
                    if(path[k] == i) found = true;
                }
                if(!found)generatePaths(i, path, totalTime + dist[node][i], 
                                        totalWeight + weight[i], n, dist, weight, weight[i]);
                else generatePaths(i, path, totalTime + dist[node][i], 
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

vector<int> calculateBestPath(int n,int dist[][5],int weight[]){
    vector<int> path;
    generatePaths(0,path,0,0,n,dist,weight,0);
    return bestPath;
}