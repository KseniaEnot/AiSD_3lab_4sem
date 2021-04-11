#include "task3.h"
#include "Iterator.h"
#include <fstream>

using namespace std;

int* task3::Dijkstra(int& _resultSize) {
    int* distance = new int[cityCount];
    int* fromWhere = new int[cityCount];
    bool* visited = new bool[cityCount];
    for (size_t i = 0; i < cityCount; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    Iterator* priceIter = price[from].create_iterator(0);
    Iterator* adjacIter = adjacencyList[from].create_iterator(0);
    int bufCity,bufPrice;

    while (priceIter->has_next())
    {
        bufCity = adjacIter->next();
        bufPrice = priceIter->next();
        distance[bufCity] = bufPrice;
        fromWhere[bufCity] = from;
    }
    distance[from] = 0;
    visited[from] = true;
    fromWhere[from] = from;
    int min,index=0;
    
    for (size_t i = 0; i < cityCount; i++)
    {
        min = INT_MAX;
        for (size_t j = 0; j < cityCount; j++)
        {
            if ((visited[j]==false)&&(distance[j]<min))
            {
                min = distance[j];
                index = j;
            }
        }
        visited[index] = true;
        priceIter = price[index].create_iterator(0);
        adjacIter = adjacencyList[index].create_iterator(0);
        while (priceIter->has_next())
        {
            bufCity = adjacIter->next();
            bufPrice = priceIter->next();
            if ((visited[bufCity]==false)&&(distance[index]!=INT_MAX)&&((distance[index]+bufPrice)<distance[bufCity]))
            {
                distance[bufCity] = distance[index] + bufPrice;
                fromWhere[bufCity] = index;
            }
        }
    }
    if (distance[to] == INT_MAX)
        throw out_of_range("Result not found");
    else {
        int count = 2;
        index = to;
        while (fromWhere[index]!=from)
        {
            count++;
            index = fromWhere[index];
        }
        _resultSize = count;
        result = new int[_resultSize];
        result[_resultSize - 1] = to;
        result[0] = from;
        int i = _resultSize -2;
        index = to;
        while (fromWhere[index] != from)
        {
            result[i]= fromWhere[index];
            i--;
            index = fromWhere[index];
        }
        resultSize = _resultSize;
        return result;
    }
}

void task3::readList(char* fileName) {
    fstream file;
    file.open(fileName, ios::in);
    int countStr;
    file >> cityCount >> countStr;
    if (file.eof() || cityCount == 0) throw out_of_range("Graph is empty");
    adjacencyList = new dualList[cityCount];
    price = new dualList[cityCount];
    numberName = new City[cityCount];
    char* str;
    int indexStr = 0;
    int indexCity = 0;
    int found1 = -1;
    int found2 = -1;
    int bufPrice;

    for (size_t i = 0; (i < countStr) && (!file.eof()); i++) {
        indexStr = 0;
        str = new char[100];
        file >> str[indexStr];
        while (str[indexStr] != ';') //first city
        {
            indexStr++;
            file >> str[indexStr];
        }
        found1 = -1;
        for (size_t i = 0; (i < indexCity) && (found1 == -1); i++) //find city
        {
            if (indexStr == numberName[i].nameSize)  //check size
            {
                for (size_t j = 0; j < numberName[i].nameSize; j++)  //check name
                    if (str[j] == numberName[i].name[j])
                        found1 = i;
                    else {
                        found1 = -1;
                        break;
                    }
            }
        }
        if (found1 == -1)
        {
            numberName[indexCity].nameSize = indexStr;
            numberName[indexCity].name = new char[indexStr];
            for (size_t i = 0; i < indexStr; i++)
                numberName[indexCity].name[i] = str[i];
            found1 = indexCity;
            indexCity++;
        }
        delete str;
        str = new char[100];

        indexStr = 0;
        file >> str[indexStr];
        while (str[indexStr] != ';') //second city
        {
            indexStr++;
            file >> str[indexStr];
        }
        found2 = -1;
        for (size_t i = 0; (i < indexCity) && (found2 == -1); i++) //find city
        {
            if (indexStr == numberName[i].nameSize)  //check size
            {
                for (size_t j = 0; j < numberName[i].nameSize; j++)  //check name
                    if (str[j] == numberName[i].name[j])
                        found2 = i;
                    else {
                        found2 = -1;
                        break;
                    }
            }
        }
        if (found2 == -1)
        {
            numberName[indexCity].nameSize = indexStr;
            numberName[indexCity].name = new char[indexStr];
            for (size_t i = 0; i < indexStr; i++)
                numberName[indexCity].name[i] = str[i];
            found2 = indexCity;
            indexCity++;
        }
        delete str;
        str = new char[100];

        indexStr = 0;
        file >> str[indexStr];
        while (str[indexStr] != ';') //first price
        {
            indexStr++;
            file >> str[indexStr];
        }
        if (str[0] == 'N')
        {
        }
        else {
            bufPrice = 0;
            for (size_t i = 0; i < indexStr; i++)
            {
                switch (str[i]) //convert to int
                {
                case '0':bufPrice *= 10; break;
                case '1':bufPrice = bufPrice * 10 + 1; break;
                case '2':bufPrice = bufPrice * 10 + 2; break;
                case '3':bufPrice = bufPrice * 10 + 3; break;
                case '4':bufPrice = bufPrice * 10 + 4; break;
                case '5':bufPrice = bufPrice * 10 + 5; break;
                case '6':bufPrice = bufPrice * 10 + 6; break;
                case '7':bufPrice = bufPrice * 10 + 7; break;
                case '8':bufPrice = bufPrice * 10 + 8; break;
                case '9':bufPrice = bufPrice * 10 + 9; break;
                default:
                    break;
                }
            }
            adjacencyList[found1].push_back(found2);
            price[found1].push_back(bufPrice);
        }
        delete str;
        str = new char[100];

        indexStr = 0;
        file >> str[indexStr];
        while (str[indexStr] != ';') //second price
        {
            indexStr++;
            file >> str[indexStr];
        }
        if (str[0] == 'N')
        {
        }
        else {
            bufPrice = 0;
            for (size_t i = 0; i < indexStr; i++)
            {
                switch (str[i]) //convert to int
                {
                case '0':bufPrice *= 10; break;
                case '1':bufPrice = bufPrice * 10 + 1; break;
                case '2':bufPrice = bufPrice * 10 + 2; break;
                case '3':bufPrice = bufPrice * 10 + 3; break;
                case '4':bufPrice = bufPrice * 10 + 4; break;
                case '5':bufPrice = bufPrice * 10 + 5; break;
                case '6':bufPrice = bufPrice * 10 + 6; break;
                case '7':bufPrice = bufPrice * 10 + 7; break;
                case '8':bufPrice = bufPrice * 10 + 8; break;
                case '9':bufPrice = bufPrice * 10 + 9; break;
                default:
                    break;
                }
            }
            adjacencyList[found2].push_back(found1);
            price[found2].push_back(bufPrice);
        }
        delete str;
    }
    indexStr = 0;
    str = new char[100];
    file >> str[indexStr];
    while (str[indexStr] != ';') //first city
    {
        indexStr++;
        file >> str[indexStr];
    }
    found1 = -1;
    for (size_t i = 0; (i < indexCity) && (found1 == -1); i++) //find city
    {
        if (indexStr == numberName[i].nameSize)  //check size
        {
            for (size_t j = 0; j < numberName[i].nameSize; j++)  //check name
                if (str[j] == numberName[i].name[j])
                    found1 = i;
                else {
                    found1 = -1;
                    break;
                }
        }
    }
    if (found1 == -1)
        throw out_of_range("Missing value");
    delete str;
    str = new char[100];

    indexStr = 0;
    file >> str[indexStr];
    while (str[indexStr] != ';') //second city
    {
        indexStr++;
        file >> str[indexStr];
    }
    found2 = -1;
    for (size_t i = 0; (i < indexCity) && (found2 == -1); i++) //find city
    {
        if (indexStr == numberName[i].nameSize)  //check size
        {
            for (size_t j = 0; j < numberName[i].nameSize; j++)  //check name
                if (str[j] == numberName[i].name[j])
                    found2 = i;
                else {
                    found2 = -1;
                    break;
                }
        }
    }
    if (found2 == -1)
        throw out_of_range("Missing value");
    this->from = found1;
    this->to = found2;
    this->result = NULL;
    file.close();
}

void task3::readList(string fileName) {
    fstream file;
    file.open(fileName, ios::in);
    int countStr;
    file >> cityCount >> countStr;
    if (file.eof() || cityCount == 0) throw out_of_range("Graph is empty");
    adjacencyList = new dualList[cityCount];
    price = new dualList[cityCount];
    numberName = new City[cityCount];
    char* str;
    int indexStr = 0;
    int indexCity = 0;
    int found1 = -1;
    int found2 = -1;
    int bufPrice;

    for (size_t i = 0; (i < countStr) && (!file.eof()); i++) {
        indexStr = 0;
        str = new char[100];
        file >> str[indexStr];
        while (str[indexStr] != ';') //first city
        {
            indexStr++;
            file >> str[indexStr];
        }
        found1 = -1;
        for (size_t i = 0; (i < indexCity) && (found1 == -1); i++) //find city
        {
            if (indexStr == numberName[i].nameSize)  //check size
            {
                for (size_t j = 0; j < numberName[i].nameSize; j++)  //check name
                    if (str[j] == numberName[i].name[j])
                        found1 = i;
                    else {
                        found1 = -1;
                        break;
                    }
            }
        }
        if (found1 == -1)
        {
            numberName[indexCity].nameSize = indexStr;
            numberName[indexCity].name = new char[indexStr];
            for (size_t i = 0; i < indexStr; i++)
                numberName[indexCity].name[i] = str[i];
            found1 = indexCity;
            indexCity++;
        }
        delete str;
        str = new char[100];

        indexStr = 0;
        file >> str[indexStr];
        while (str[indexStr] != ';') //second city
        {
            indexStr++;
            file >> str[indexStr];
        }
        found2 = -1;
        for (size_t i = 0; (i < indexCity) && (found2 == -1); i++) //find city
        {
            if (indexStr == numberName[i].nameSize)  //check size
            {
                for (size_t j = 0; j < numberName[i].nameSize; j++)  //check name
                    if (str[j] == numberName[i].name[j])
                        found2 = i;
                    else {
                        found2 = -1;
                        break;
                    }
            }
        }
        if (found2 == -1)
        {
            numberName[indexCity].nameSize = indexStr;
            numberName[indexCity].name = new char[indexStr];
            for (size_t i = 0; i < indexStr; i++)
                numberName[indexCity].name[i] = str[i];
            found2 = indexCity;
            indexCity++;
        }
        delete str;
        str = new char[100];

        indexStr = 0;
        file >> str[indexStr];
        while (str[indexStr] != ';') //first price
        {
            indexStr++;
            file >> str[indexStr];
        }
        if (str[0] == 'N')
        {
        }
        else {
            bufPrice = 0;
            for (size_t i = 0; i < indexStr; i++)
            {
                switch (str[i]) //convert to int
                {
                case '0':bufPrice *= 10; break;
                case '1':bufPrice = bufPrice * 10 + 1; break;
                case '2':bufPrice = bufPrice * 10 + 2; break;
                case '3':bufPrice = bufPrice * 10 + 3; break;
                case '4':bufPrice = bufPrice * 10 + 4; break;
                case '5':bufPrice = bufPrice * 10 + 5; break;
                case '6':bufPrice = bufPrice * 10 + 6; break;
                case '7':bufPrice = bufPrice * 10 + 7; break;
                case '8':bufPrice = bufPrice * 10 + 8; break;
                case '9':bufPrice = bufPrice * 10 + 9; break;
                default:
                    break;
                }
            }
            adjacencyList[found1].push_back(found2);
            price[found1].push_back(bufPrice);
        }
        delete str;
        str = new char[100];

        indexStr = 0;
        file >> str[indexStr];
        while (str[indexStr] != ';') //second price
        {
            indexStr++;
            file >> str[indexStr];
        }
        if (str[0] == 'N')
        {
        }
        else {
            bufPrice = 0;
            for (size_t i = 0; i < indexStr; i++)
            {
                switch (str[i]) //convert to int
                {
                case '0':bufPrice *= 10; break;
                case '1':bufPrice = bufPrice * 10 + 1; break;
                case '2':bufPrice = bufPrice * 10 + 2; break;
                case '3':bufPrice = bufPrice * 10 + 3; break;
                case '4':bufPrice = bufPrice * 10 + 4; break;
                case '5':bufPrice = bufPrice * 10 + 5; break;
                case '6':bufPrice = bufPrice * 10 + 6; break;
                case '7':bufPrice = bufPrice * 10 + 7; break;
                case '8':bufPrice = bufPrice * 10 + 8; break;
                case '9':bufPrice = bufPrice * 10 + 9; break;
                default:
                    break;
                }
            }
            adjacencyList[found2].push_back(found1);
            price[found2].push_back(bufPrice);
        }
        delete str;
    }
    indexStr = 0;
    str = new char[100];
    file >> str[indexStr];
    while (str[indexStr] != ';') //first city
    {
        indexStr++;
        file >> str[indexStr];
    }
    found1 = -1;
    for (size_t i = 0; (i < indexCity) && (found1 == -1); i++) //find city
    {
        if (indexStr == numberName[i].nameSize)  //check size
        {
            for (size_t j = 0; j < numberName[i].nameSize; j++)  //check name
                if (str[j] == numberName[i].name[j])
                    found1 = i;
                else {
                    found1 = -1;
                    break;
                }
        }
    }
    if (found1 == -1)
        throw out_of_range("Missing value");
    delete str;
    str = new char[100];

    indexStr = 0;
    file >> str[indexStr];
    while (str[indexStr] != ';') //second city
    {
        indexStr++;
        file >> str[indexStr];
    }
    found2 = -1;
    for (size_t i = 0; (i < indexCity) && (found2 == -1); i++) //find city
    {
        if (indexStr == numberName[i].nameSize)  //check size
        {
            for (size_t j = 0; j < numberName[i].nameSize; j++)  //check name
                if (str[j] == numberName[i].name[j])
                    found2 = i;
                else {
                    found2 = -1;
                    break;
                }
        }
    }
    if (found2 == -1)
        throw out_of_range("Missing value");
    this->from = found1;
    this->to = found2;
    this->result = NULL;
    file.close();
}

void task3::writeList(char* fileName) {
    if (result != NULL) {
        fstream file;
        file.open(fileName, ios::out);
        for (size_t i = 0; i < resultSize; i++)
        {
            for (size_t j = 0; j < numberName[result[i]].nameSize; j++)
            {
                file << numberName[result[i]].name[j];
            }
            file << endl;
        }
        file.close();
    }
}
void task3::writeList(string fileName) {
    if (result != NULL) {
        fstream file;
        file.open(fileName, ios::out);
        for (size_t i = 0; i < resultSize; i++)
        {
            for (size_t j = 0; j < numberName[result[i]].nameSize; j++)
            {
                file << numberName[result[i]].name[j];
            }
            file << endl;
        }
        file.close();
    }
}