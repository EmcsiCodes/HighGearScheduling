#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <unordered_map>
#include <map>
#include <fstream>

using namespace std;

int nr_of_clients = 10;
int dist[5][5] = {
    {0, 5, 99, 93, 45, 91, 58, 56, 7, 92},
    {5, 0, 88, 3, 90, 21, 80, 55, 85, 12},
    {99, 88, 0, 46, 8, 30, 99, 68, 67, 80},
    {93, 3, 46, 0, 68, 9, 88, 16, 92, 89},
    {45, 90, 8, 68, 0, 22, 7, 86, 31, 9},
    {91, 21, 30, 9, 22, 0, 67, 13, 60, 27},
    {58, 80, 99, 88, 7, 67, 0, 41, 36, 55},
    {56, 55, 68, 16, 86, 13, 41, 0, 25, 56},
    {7, 85, 67, 92, 31, 60, 36, 25, 0, 43},
    {92, 12, 80, 89, 9, 27, 55, 56, 43, 0},
};

int main()
{

    return 0;
}