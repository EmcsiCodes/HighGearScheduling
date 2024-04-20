#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include "funcs.cpp"
using namespace std;

struct client
{
    int id;
    string city;
    string county;
    double latitude;
    double longitude;
    long sold;
    string priority;
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
    vector<int> clients_of_agent[20];
    ifstream f("hackmk.csv");
    string line;
    client clients[400];
    while (getline(f, line))
    { // Read each line from the file
        // Split the line into fields
        std::vector<std::string> fields = split(line, ',');

        // Create a Location object and assign the fields
        client location;
        location.id = std::stoi(fields[0]);
        location.city = fields[1];
        location.county = fields[2];
        location.latitude = std::stod(fields[3]);
        location.longitude = std::stod(fields[4]);
        location.sold = std::stol(fields[5]);
        location.priority = fields[6];
        location.agent = std::stoi(fields[7]);
        location.frequency = fields[8];
        clients[location.id] = location;

        clients_of_agent[location.agent].push_back(location.id);

        // Do something with the location object, like printing it
        // std::cout << "Location ID: " << location.id << std::endl;
        // std::cout << "Name: " << location.city << std::endl;
        // Print other fields...

        // You can store the location object in a vector or process it otherwise
    }
    f.close();
    ifstream("output2.txt");
    int dist[400][400];
    for (int i = 0; i < 400; i++)
    {
        for (int j = i; j < 400; j++)
        {
            float x;
            f >> x;
            dist[i][j] = x;
            dist[j][i] = x;
        }
    }

    for (int agents = 0; agents < 20; agents++)
    {
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
    }

    return 0;
}
