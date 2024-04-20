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
    int id;
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
    ifstream f("test.csv");
    string line;
    client clients[400];
    int clientNum = 0;
    int agentNum = 1;
    while (getline(f, line))
    { // Read each line from the file
        // Split the line into fields
        vector<string> fields = split(line, ',');
        int i = stoi(fields[0]);
        clients[i].id = i;
        clients[i].city = fields[1];
        clients[i].latitude = std::stod(fields[3]);
        clients[i].longitude = std::stod(fields[4]);
        clients[i].sold = std::stol(fields[5]);
        clients[i].priority = fields[6];

        if(clients[i].priority == "LARGE") clients[i].priorityi = 5;
        else if(clients[i].priority == "MEDIUM") clients[i].priorityi = 2;
        else if(clients[i].priority == "SMALL") clients[i].priorityi = 1;
        else clients[i].priorityi = 0;

        int ii = std::stoi(fields[7]);
        clients[i].agent = ii;
        clients[i].frequency = fields[8];
        agent[ii].push_back(clients[i]);
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
    //
    

    //
//     float distt[401][401];
// int weight[5] = {0, 1, 3, 5, 3};
// distt[0][0]=0;
// distt[0][1] = distt[1][0] = 3;
// distt[0][2] = dist[2][0] = 2;
// distt[0][3] = distt[3][0] = 1;
// distt[0][4] = distt[4][0] = 4;
// distt[1][1] = 0;
// distt[1][2] = distt[2][1] = 3;
// distt[1][3] = dist[3][1] = 1;
// distt[1][4] = distt[4][1] = 5;
// distt[2][2] = 0;
// distt[2][3] = distt[3][2] = 3;
// distt[2][4] = distt[4][2] = 1;
// distt[3][3] = 0;
// distt[3][4] = distt[4][3] = 12;
// set<int> cantGo;
// vector<int> temp = calculateBestPath(5,distt,weight,cantGo);
// cout<<temp.size()<<endl;
// for(int i=0; i<temp.size(); i++){
//     cout<<temp[i]<<" ";
// }
    //float distt[401][401];
int weight[5] = {0, 1, 2, 5, 2};
dist[0][0]=0;
dist[0][1] = dist[1][0] = 5;
dist[0][2] = dist[2][0] = 5;
dist[0][3] = dist[3][0] = 1;
dist[0][4] = dist[4][0] = 4;
dist[1][1] = 0;
dist[1][2] = dist[2][1] = 3;
dist[1][3] = dist[3][1] = 1;
dist[1][4] = dist[4][1] = 5;
dist[2][2] = 0;
dist[2][3] = dist[3][2] = 3;
dist[2][4] = dist[4][2] = 1;
dist[3][3] = 0;
dist[3][4] = dist[4][3] = 12;
set<int> cantGo;
vector<int> temp = calculateBestPath(5,dist,weight,cantGo);
cout<<temp.size()<<endl;
for(int i=0; i<temp.size(); i++){
    cout<<temp[i]<<" ";
}

//iterate through the agents
    for(int agenti = 0; agenti < agentNum; agenti++){

        //put in the clients in their correct week
        vector<int> unorderedClients[3][4];
        for(client currClient : agent[agenti]){
            if(currClient.frequency == "weekly"){
                for(int monthNum = 0; monthNum<3; monthNum++){
                    for(int weekNum = 0; weekNum<4; weekNum++){
                        unorderedClients[monthNum][weekNum].push_back(currClient.id);
                    }
                }
            }
            if(currClient.frequency == "twice-a-week"){
                for(int monthNum = 0; monthNum<3; monthNum++){
                    for(int weekNum = 0; weekNum<4; weekNum++){
                        unorderedClients[monthNum][weekNum].push_back(currClient.id);
                        unorderedClients[monthNum][weekNum].push_back(currClient.id);
                    }
                }
            }
            if(currClient.frequency == "bi-weekly"){
                for(int monthNum = 0; monthNum<3; monthNum++){
                    for(int weekNum = 0; weekNum<4; weekNum = weekNum + 2){
                        //ezt leellenorizni
                        unorderedClients[monthNum][weekNum].push_back(currClient.id);
                    }
                }
            }
        }
        for(int i=0; i<4; i++){
            cout<<"week "<<i<<": ";
            for(int j : unorderedClients[0][i]){
                cout<<j<<" ";
            }
            cout<<endl;
        }
        //first we order by months
        for(int monthNum = 0; monthNum < 3; monthNum++){
            
            //second we order by weeks
            for(int weekNum = 0; weekNum<4; weekNum++){

                //each day we have the solution vector day[i]
                vector<int> days[4];
                int nodeNum = unorderedClients[monthNum][weekNum].size(); //+1
                float tempDis[401][401]; //add the fsega node
                int tempWeight[nodeNum];

                //calculate temporary distance matrix
                tempDis[0][0] = 0;
                for(int i=0; i<nodeNum; i++){
                    tempDis[i][0] = dist[i][0];
                    tempDis[0][i] = dist[0][i];
                }
                for(int i=1; i<nodeNum; i++){
                    for(int j=i; j<nodeNum; j++){
                        tempDis[j][i] = tempDis[i][j] = dist[unorderedClients[monthNum][weekNum][i - 1]]
                                            [unorderedClients[monthNum][weekNum][j - 1]];
                    }
                }
            //     cout<<nodeNum<<endl;
            //    for(int i=0; i<nodeNum; i++){
                
            //         for(int j=0; j<nodeNum; j++){
            //             cout<<dist[i][j]<<" ";
            //         }
            //         cout<<endl;
            //     }
            //     cout<<endl;
            //     for(int i=0; i<nodeNum; i++){
                
            //         for(int j=0; j<nodeNum; j++){
            //             cout<<tempDis[i][j]<<" ";
            //         }
            //         cout<<endl;
            //     }

                //calculate temprary weight array
                tempWeight[0] = 0;
                for(int i=0; i<nodeNum; i++){
                    tempWeight[i] = 
                        clients[unorderedClients[monthNum][weekNum][i]].priorityi;//i - 1
                }

// for(int i=0; i<nodeNum; i++) cout<<tempWeight[i]<<" ";
// cout<<endl;

                set<int> cantGo;
                cout<<"week:"<<weekNum<<endl;
                days[0] = calculateBestPath(nodeNum,tempDis,tempWeight,cantGo);
                cout<<0<<endl;
                                for(int i=0; i<4; i++){
                    cout<<i+1<<": ";
                    for(int j=0; j<days[i].size(); j++){
                        cout<<days[i][j]<<" ";
                    }
                    cout<<endl;
                } 
                cout<<endl;
                for(int i=0; i<days[0].size(); i++) if(days[0][i]!=0) cantGo.insert(days[0][i]);
                days[1] = calculateBestPath(nodeNum,tempDis,tempWeight,cantGo);
                                cout<<1<<endl;
                                for(int i=0; i<4; i++){
                    cout<<i+1<<": ";
                    for(int j=0; j<days[i].size(); j++){
                        cout<<days[i][j]<<" ";
                    }
                    cout<<endl;
                } 
                cout<<endl;
                for(int i=0; i<days[1].size(); i++) if(days[1][i]!=0) cantGo.insert(days[1][i]);
                days[2] = calculateBestPath(nodeNum,tempDis,tempWeight,cantGo);
                                cout<<2<<endl;
                                for(int i=0; i<4; i++){
                    cout<<i+1<<": ";
                    for(int j=0; j<days[i].size(); j++){
                        cout<<days[i][j]<<" ";
                    }
                    cout<<endl;
                } 
                cout<<endl;
                for(int i=0; i<days[2].size(); i++) if(days[2][i]!=0) cantGo.insert(days[2][i]);
                days[3] = calculateBestPath(nodeNum,tempDis,tempWeight,cantGo);
                                cout<<3<<endl;
                                for(int i=0; i<4; i++){
                    cout<<i+1<<": ";
                    for(int j=0; j<days[i].size(); j++){
                        cout<<days[i][j]<<" ";
                    }
                    cout<<endl;
                } 
                cout<<endl;
                for(int i=0; i<days[3].size(); i++) if(days[3][i]!=0) cantGo.insert(days[3][i]);

                  cout<<4<<endl;
                                for(int i=0; i<4; i++){
                    cout<<i+1<<": ";
                    for(int j=0; j<days[i].size(); j++){
                        cout<<days[i][j]<<" ";
                    }
                    cout<<endl;
                } 
                cout<<endl;
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
                vector<int> tovisit; // az a vector amibol kitorlom ha egyik napon megvizteli
                int weight[50];      // hetek[week] hez kotheto prioritasok

                for (int i : hetek[week]) // hetek[week] = azon a heten kiket kell megkezelni
                {
                    tovisit.push_back(i);
                }

                int distance[100][100];
                set<int> twiceaweek;
                for (int day = 0; day < 4; day++)
                {
                    // minden napra megy a grafos fuggveny
                    // ha twice a week akkor nem erase ha bent van az utban
                    // hetek[i] ben azok akiket a heten meg kell kezelni
                    cout<<day<<endl;
                    for(int i:tovisit)
                    {
                        cout<<i<<" ";
                    }
                    cout<<endl;
                    for (int i = 0; i < tovisit.size(); i++)
                    {
                        if (clients[tovisit[i]].priority == "LARGE")
                        {
                            weight[i + 1] = 5;
                        }
                        else if (clients[tovisit[i]].priority == "MEDIUM")
                        {
                            weight[i + 1] = 2;
                        }
                        else
                            weight[i + 1] = 1;
                    }
                    weight[0] = 0; // fsega

                    int n = tovisit.size() + 1;
                    ifstream g("output3.txt");
                    for (int i = 0; i < n; i++)
                    {
                        g >> distance[0][i];
                        distance[i][0] = distance[0][i];
                    } // distances from fsega in row 0
                    // tovisit vector contains ids of clients to visit today
                    for (int i = 1; i < n; i++)
                    {
                        for (int j = i; j < n; j++)
                        {
                            distance[i][j] = dist[tovisit[i]][tovisit[j]];
                            distance[j][i] = dist[tovisit[i]][tovisit[j]];
                        }
                    }

                    findMaxWeightPath(0, path, 0, 0, best_path, 0, visited, tovisit.size(),
                                      weight, distance, 600);

                    for (int i : twiceaweek)
                    {
                        for (auto it = tovisit.begin(); it != tovisit.end();)
                        {
                            if (*it == i)
                            {
                                it = tovisit.erase(it); // erase() returns the iterator to the next valid position
                            }
                            else
                            {
                                ++it; // Move to the next element
                            }
                        }
                    }

                    for (int i : best_path)
                    {
                        if (clients[i].frequency == "twice-a-week")
                        {
                            twiceaweek.insert(i);
                        }
                        else
                        {
                            for (auto it = tovisit.begin(); it != tovisit.end();)
                            {
                                if (*it == i)
                                {
                                    it = tovisit.erase(it); // erase() returns the iterator to the next valid position
                                }
                                else
                                {
                                    ++it; // Move to the next element
                                }
                            }
                        }
                    }
                }
            }
        }
*/