#pragma once
#include "dualList.h"
class task3
{
private:
    int cityCount;
    dualList* adjacencyList;
    dualList* price;
    int* result;
    int resultSize;
    int from, to;
    struct City
    {
        char* name;
        size_t nameSize;
    };
    City* numberName;
public:
    
    void readList(char*);
    void readList(string);
    int* Dijkstra(int&);
    void writeList(char*);
    void writeList(string);
};