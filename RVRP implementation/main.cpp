#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include "funcs.cpp"
using namespace std;

float dist[401][401];
struct client
{
    string city;
    string county;
    double latitude;
    double longitude;
    long sold;
    string priority;
    int priorityi;
    int agent;
    string frequency;
};

vector<string> split(const string &str, char delimiter)
{
    vector<std::string> tokens;
    string token;
    istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{
    //input clients
    vector<client> agent[20];
    ifstream f("hackmk.csv");
    string line;
    client clients[400];
    int clientNum = 0;
    while (getline(f, line))
    { // Read each line from the file
        // Split the line into fields
        vector<string> fields = split(line, ',');
        int i = stoi(fields[0]);

        clients[i].city = fields[1];
        clients[i].latitude = std::stod(fields[3]);
        clients[i].longitude = std::stod(fields[4]);
        clients[i].sold = std::stol(fields[5]);
        clients[i].priority = fields[6];

        if(clients[i].priority == "LARGE") clients[i].priorityi = 5;
        if(clients[i].priority == "MEDIUM") clients[i].priorityi = 2;
        if(clients[i].priority == "SMALL") clients[i].priorityi = 1;

        clients[i].agent = std::stoi(fields[7]);
        clients[i].frequency = fields[8];


        agent[clients[i].agent].push_back(clients[i]);
        clientNum = i;
    }
    clientNum++;
    f.close();

    //input in distance matrix the initial position (fsega)
    ifstream("output3.txt");
    dist[0][0] = 0;
    for(int i=1; i<401; i++){
        float x; f >> x;
        dist[0][i] = x;
        dist[i][0] = x;
    }

    //input distance matrix of clients
    ifstream("output2.txt");
    for (int i = 1; i < 401; i++)
    {
        for (int j = i; j < 401; j++)
        {
            float x;
            f >> x;
            dist[i][j] = x;
            dist[j][i] = x;
        }
    }
//     int distt[5][5] = {
//     {0, 3, 2, 1, 4},
//     {3, 0, 3, 1, 5},
//     {2, 3, 0, 3, 1},
//     {1, 1, 3, 0, 12},
//     {4, 5, 1, 12, 0}};
// int weight[5] = {0, 1, 3, 5, 3};
// vector<int> temp = calculateBestPath(5,distt,weight);
// cout<<temp.size()<<endl;
// for(int i=0; i<temp.size(); i++){
//     cout<<temp[i]<<" ";
// }

    //put in the clients in their correct week
    vector<int> unorderedClients[3][4];
    for(int i=0; i<clientNum; i++){
        if(clients[i].frequency == "weekly"){
            for(int monthNum = 0; monthNum<3; monthNum++){
                for(int weekNum = 0; weekNum<4; weekNum++){
                    unorderedClients[monthNum][weekNum].push_back(i);
                }
            }
        }
        if(clients[i].frequency == "twice-a-week"){
            for(int monthNum = 0; monthNum<3; monthNum++){
                for(int weekNum = 0; weekNum<4; weekNum++){
                    unorderedClients[monthNum][weekNum].push_back(i);
                    unorderedClients[monthNum][weekNum].push_back(i);
                }
            }
        }
        if(clients[i].frequency == "bi-weekly"){
            for(int monthNum = 0; monthNum<3; monthNum++){
                for(int weekNum = 0; weekNum<4; weekNum = weekNum + 2){
                    unorderedClients[monthNum][weekNum].push_back(i);
                }
            }
        }
    }

    //loop throught the agents
    //to order its clients by date
    for (int agents = 0; agents < 20; agents++)
    {
        //first we order by months
        for(int monthNum = 0; monthNum < 3; monthNum++){
            
            //second we order by weeks
            for(int weekNum = 0; weekNum<4; weekNum++){

                //each day we have the solution vector day[i]
                vector<int> days[4];
                int nodeNum = unorderedClients[monthNum][weekNum].size() + 1;
                float tempDis[nodeNum][nodeNum]; //add the fsega node
                int tempWeight[nodeNum];

                //calculate temporary distance matrix
                tempDis[0][0] = 0;
                for(int i=0; i<nodeNum; i++){
                    tempDis[i][0] = dist[i][0];
                    tempDis[0][i] = dist[0][i];
                }
                for(int i=1; i<nodeNum; i++){
                    for(int j=i; j<nodeNum; j++){
                        tempDis[i][j] = dist[unorderedClients[monthNum][weekNum][i - 1]]
                                            [unorderedClients[monthNum][weekNum][j - 1]];
                        
                    }
                }

                //calculate temprary weight array
                tempWeight[0] = 0;
                for(int i=1; i<nodeNum; i++){
                    tempWeight[i] = 
                        clients[unorderedClients[monthNum][weekNum][i - 1]].priorityi;
                }
                days[0] = calculateBestPath(nodeNum,tempDis,tempWeight);
            }
        }
    }

    return 0;
}

/*
        set<int> hetek[4];
        for (int i : clients_of_agent[agents])
        {
            if (clients[i].frequency == "twice-a-week")
            {
                for (int j = 0; j < 4; j++)
                {
                    hetek[j].insert(i);
                }
            }
            else if (clients[i].frequency == "weekly")
            {
                for (int j = 0; j < 4; j++)
                {
                    hetek[j].insert(i);
                }
            }
            else if (clients[i].frequency == "bi-weekly")
            {
                hetek[0].insert(i);
                hetek[2].insert(i);
            }
        }
        for (int month = 0; month < 3; month++)
        {
            for (int week = 0; week < 4; week++)
            {
                vector<int> best_path;
                vector<int> path;
                set<int> visited;
                set<int> tovisit;
                int weight[50];

                tovisit = hetek[week];
                for(int i=0;i<clients_of_agent[agents].size();i++)
                {
                    if(clients[clients_of_agent[agents][i]].priority == "LARGE")
                    {
                        weight[i+1] = 5;
                    }
                    else if(clients[clients_of_agent[agents][i]].priority == "MEDIUM")
                    {
                        weight[i+1] = 2;
                    }
                    else weight[i+1] = 1;
                }
                weight[0] = 0; //fsega

                int distance[100][100];

                for (int day = 0; day < 4; day++)
                {
                    // minden napra megy a grafos fuggveny
                    // ha twice a week akkor nem erase ha bent van az utban
                    // hetek[i] ben azok akiket a heten meg kell kezelni

                    int n = tovisit.size() + 1;
                    ifstream ()
                    for(int i=0;i<n;i++)
                    {
                        distance[0][i] = 
                    }

                    for(int i=1;i<n;i++)
                    {
                        for(int j=i;j<n;j++)
                        {
                            distance[i][j] = 

                        }
                    }


                    findMaxWeightPath(0, path, 0, 0, best_path, 0, visited, tovisit.size(),
                                      weight, distance, 600);
                }
            }
        }
*/