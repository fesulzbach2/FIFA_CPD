#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <list>
#include <cstring>
#include "header.h"

using namespace std;

// realiza o quicksort no vetor de jogadores utilizando a nota média como critério, de maneira decrescente
void quickSort(vector<PlayerList> &set, float start, float end) {
   float pivotPoint;
   if (start < end) {
       //get the pivot pofloat
       pivotPoint = partition(set, start, end);
       //sort first sublist
       quickSort(set, start, pivotPoint - 1);
       //sort second sublist
       quickSort(set, pivotPoint + 1, end);
   }
}
//particionamento (parte da quicksort)
float partition(vector<PlayerList> &set, float start, float end) {
    float pivotValue, pivotIndex, mid;

    mid = (start + end) / 2;
    swapInt(set[start].Id, set[mid].Id);
    swapString(set[start].PlayerName, set[mid].PlayerName);
    swapString(set[start].Positions, set[mid].Positions);
    swapDouble(set[start].average, set[mid].average);
    swapInt(set[start].Asize, set[mid].Asize);

    pivotIndex = start;
    pivotValue = (set[start].average / set[start].Asize);

    for(float scan = start + 1; scan <= end; scan++) {
        if ((set[scan].average / set[scan].Asize) > pivotValue) {
            pivotIndex++;
            swapInt(set[pivotIndex].Id, set[scan].Id);
            swapString(set[pivotIndex].PlayerName, set[scan].PlayerName);
            swapString(set[pivotIndex].Positions, set[scan].Positions);
            swapDouble(set[pivotIndex].average, set[scan].average);
            swapInt(set[pivotIndex].Asize, set[scan].Asize);
        }
    }

    swapInt(set[start].Id, set[pivotIndex].Id);
    swapString(set[start].PlayerName, set[pivotIndex].PlayerName);
    swapString(set[start].Positions, set[pivotIndex].Positions);
    swapDouble(set[start].average, set[pivotIndex].average);
    swapInt(set[start].Asize, set[pivotIndex].Asize);

    return pivotIndex;
}

//troca os valores inteiros da struct
void swapInt(int &value1, int &value2) {
    int temp = value1;
    value1 = value2;
    value2 = temp;
}
//troca strings da struct
void swapString(string &value1, string &value2) {
    string temp = value1;
    value1 = value2;
    value2 = temp;
}
//troca valores double da struct
void swapDouble(float &value1, float &value2) {
    float temp = value1;
    value1 = value2;
    value2 = temp;
}
