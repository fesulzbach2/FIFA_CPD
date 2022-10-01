#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <list>
#include <cstring>
#include "header.h"

#define TABLE_SIZE 20000

using namespace std;

PlayerList *hashTable_players[TABLE_SIZE];


unsigned int hash_players(int id)
{
    int hash_value=0;

        hash_value = (3*id^2)%TABLE_SIZE;

    return hash_value;
}

void init_hashTable_players()
{
    for(int i=0;i<TABLE_SIZE;i++){
        hashTable_players[i]=NULL;

    }
}

void print_table_players()
{
    cout << "  START" << endl;
    for(int i=0;i<TABLE_SIZE;i++){
        if(hashTable_players[i]==NULL){
            cout << i << "  ---";

        } else{
        cout << i << " ";};
        PlayerList *tmp = hashTable_players[i];
        while(tmp != NULL){
            cout << tmp->PlayerName << " -> ";
            tmp = tmp->next;
        }
        printf("\n");
    }
    cout << "  END\n" << endl;
}

bool hash_table_insert_players(PlayerList *p)
{
    if(p == NULL)
        return false;

    int index = hash_players(p->Id);
    p->next = hashTable_players[index];
    hashTable_players[index] = p;
    return true;
}

PlayerList *hash_table_search_players(int number_id)
{
    int index = hash_players(number_id);
    PlayerList *tmp = hashTable_players[index];
    while(tmp!= NULL && (tmp->Id != number_id)){
        tmp = tmp->next;
    }
    return tmp;
}


