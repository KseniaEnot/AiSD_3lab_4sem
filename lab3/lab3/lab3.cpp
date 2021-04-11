#include <iostream>
#include <fstream>
#include "dualList.h"
#include "task3.h"
using namespace std;

int main()
{
    string fileNameIn = "in.txt";
    char fileNameOut[8] = "out.txt";
    task3 task;
    int size;
    task.readList(fileNameIn);
    task.Dijkstra(size);
    task.writeList(fileNameOut);
}