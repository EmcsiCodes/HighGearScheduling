#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include "funcs.cpp"
using namespace std;

ifstream in_data("input.csv");
ofstream out_data("output.csv");
#define inf 100000
float dist[401][401];
float tempDis[401][401]; //add the fsega node
int tempWeight[401];
int mainDate = 5;
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

void createOutput(client currClient,int date){
    out_data << currClient.id << "," << currClient.city << "," << currClient.county << ","
    << currClient.latitude << "," << currClient.longitude << "," << currClient.sold << ","
    << currClient.priority << "," << currClient.agent << "," << currClient.frequency << ","
    << date <<endl;
}

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
    string line;
    client clients[401];
    int clientNum = 0;
    int agentNum = 20;
    getline(in_data,line); //first is initial position
    while (getline(in_data, line))
    { 
        // Read each line from the file
        // Split the line into fields
        vector<string> fields = split(line, ',');
        int i = stoi(fields[0]);
        clients[i].id = i;
        clients[i].city = fields[1];
        clients[i].county = fields[2];
        clients[i].latitude = std::stod(fields[3]);
        clients[i].longitude = std::stod(fields[4]);
        clients[i].sold = std::stol(fields[5]);
        clients[i].priority = fields[6];

        if(clients[i].priority == "LARGE") clients[i].priorityi = 5;
        else if(clients[i].priority == "MEDIUM") clients[i].priorityi = 2;
        else clients[i].priorityi = 1;

        int ii = std::stoi(fields[7]);
        clients[i].agent = ii;
        clients[i].frequency = fields[8];
        agent[ii].push_back(clients[i]);
        clientNum = i;
    }
    clientNum++;
    in_data.close();

    //input in distance matrix the initial position (fsega)
    ifstream in_matrix("distanceMatrix.txt");
    for(int i=0; i<clientNum+1; i++){
        for(int j=i; j<clientNum+1; j++){
            float x; in_matrix>>x;
            dist[i][j] = dist[j][i] = x;
        }
    }
    in_matrix.close();   

    for(int agenti = 0; agenti < agentNum; agenti++){
        if(agenti == 9) agenti ++;
        if(agenti == 18) agenti ++;

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
                    }
                }
            }
            if(currClient.frequency == "bi-weekly"){
                for(int monthNum = 0; monthNum<3; monthNum++){
                    for(int weekNum = 0; weekNum<4; weekNum = weekNum + 2){
                        unorderedClients[monthNum][weekNum].push_back(currClient.id);
                    }
                }
            }
        }

        for(int monthNum = 0; monthNum < 3; monthNum++){
            
            //second we order by weeks
            for(int weekNum = 0; weekNum<4; weekNum++){

                //each day we have the solution vector day[i]
                vector<int> days[4];
                int nodeNum = unorderedClients[monthNum][weekNum].size() + 1;

                //calculate temporary distance matrix          
                tempDis[0][0] = 0;
                for(int i=1; i<nodeNum; i++){
                    tempDis[i][0] = tempDis[0][i] = dist[0][unorderedClients[monthNum][weekNum][i-1]];
                }
                for(int i=1; i<nodeNum; i++){
                    for(int j=i; j<nodeNum; j++){
                        tempDis[i][j] = tempDis[j][i] = dist[unorderedClients[monthNum][weekNum][i-1]]
                                                            [unorderedClients[monthNum][weekNum][j-1]];
                    }
                }                     
                    
                //calculate temprary weight array
                tempWeight[0] = 0;
                for(int i=1; i<nodeNum; i++){
                    tempWeight[i] = 
                        clients[unorderedClients[monthNum][weekNum][i - 1]].priorityi;
                }  

                //iterate throuht the 4 days.
                set<int> cantGo;          
                for(int dayNum = 0; dayNum < 4; dayNum++){
                    days[dayNum] = calculateBestPath(nodeNum,tempDis,tempWeight,cantGo);
                    for(int i=0; i<days[dayNum].size(); i++) {
                        if(days[dayNum][i]!=0) cantGo.insert(days[dayNum][i]);
                        days[dayNum][i] = unorderedClients[monthNum][weekNum][days[dayNum][i]];
                    }
                    int date = 5 + dayNum + weekNum * 7 + monthNum * 4 * 7;
                    set<int> currClients;
                    for(int k : days[dayNum]){
                        if(k < 0 || k > 20) break;
                        currClients.insert(k);                     
                    }
                    for(auto k : currClients){
                        createOutput(clients[k],date);
                    }
                }
            }
        }
    }
    return 0;
}
