#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <unordered_map>
#include <map>
#include <fstream>
#include <queue>
#include <set>

using namespace std;
typedef struct Node{
    int id;
    int weight;
    int ctime;
    set<int> currStack;
}Node;

int nr_of_clients = 5;
int time_g = 9;
int dist[5][5] = {
    {0,3,2,1,4},
    {3,0,3,1,5},
    {2,3,0,3,1},
    {1,1,3,0,5},
    {4,5,1,5,0}
};
int weight[10] = {0,1,3,5,3};

void bfs(){
    Node graph[5];
    for(int i=0; i<nr_of_clients; i++){
        graph[i] = {i,0,0,{i}};
    }
    queue<Node> q;
    q.push(graph[0]);
    while(!q.empty()){
        Node curr = q.front();
        q.pop();
        for(int i=0; i<nr_of_clients; i++){
            //cout<<curr.id<<" "<<graph[i].id<<" "<<dist[graph[i].id][curr.id]<<"+"
            //<<curr.ctime<<endl;
            if(curr.currStack.find(graph[i].id) == curr.currStack.end()
            && curr.weight + weight[graph[i].id] > graph[i].weight
            && dist[graph[i].id][curr.id] + curr.ctime <= time_g){
                graph[i].currStack = curr.currStack;
                graph[i].currStack.insert(graph[i].id);
                graph[i].ctime = curr.ctime + dist[graph[i].id][curr.id];
                graph[i].weight = curr.weight + weight[graph[i].id];
                q.push(graph[i]);
            }
        }
    }
    for(int i=0; i<nr_of_clients; i++){
        cout<<graph[i].id<<": time="<<graph[i].ctime<<",  weight="<<graph[i].weight<<endl;
        cout<<"Stack: {";
        for(auto k:graph[i].currStack){
            cout<<k<<", ";
        }
        cout<<"}"<<endl<<endl;
    }
}

int main()
{
    bfs();
    return 0;
}