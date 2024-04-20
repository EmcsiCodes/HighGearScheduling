#include <iostream>
#include <vector>
#include <set>
using namespace std;

const int maxTime = 9;

// Function to generate all possible paths under distance k using backtracking
void generatePaths(int node, vector<int>& path,int totalDistance, 
int totalWeight,int n,float dist[][401],int weight[],int lastweight,set<int> cantGo,
int &bestWeight,vector<int> &bestPath) {

    path.push_back(node);

    if (totalDistance < maxTime) {
        for (int i = 0; i < n; ++i) {
            if(i != node && cantGo.find(i) == cantGo.end()) {
                bool found = false;
                for(int k=0; k<path.size(); k++){
                    if(path[k] == i) found = true;
                }
                if(!found)generatePaths(i, path, totalDistance + dist[node][i], 
                                        totalWeight + weight[i], n, dist, weight, 
                                        weight[i], cantGo, bestWeight, bestPath);
                else generatePaths(i, path, totalDistance + dist[node][i], 
                                        totalWeight, n, dist, weight, 0, cantGo,
                                        bestWeight, bestPath);
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

vector<int> calculateBestPath(int n,float dist[][401],int weight[],set<int> cantGo){
    vector<int> path;
    int bestWeight = 0;
    vector<int> bestPath;
    cout<<"in, set size="<<cantGo.size()<<endl;
    generatePaths(0,path,0,0,n,dist,weight,0,cantGo,bestWeight,bestPath);
    return bestPath;
}