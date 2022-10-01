#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <list>
#include <cstring>

#define TABLE_SIZE 20000
using namespace std;

////////////////////////////////////////////////////////// ESTRUTURAS

struct PlayerList {
public:
    PlayerList(
        int id,
        string playerName,
        string positions,
        PlayerList *next

    ) {
        Id = id;
        PlayerName = playerName;
        Positions = positions;
    }

    void display() {
        cout << setw(10) << left << Id;
        cout << setw(40) << left << PlayerName;
        cout << setw(25) << left << Positions;
        cout << setw(15) << left << average/Asize << " ";
        cout << setw(25) << left << Asize;
        cout << endl;
    }

    int Id;
    string PlayerName;
    string Positions;
    float average=0;
    int Asize=0;
    vector<string> tags;
    PlayerList *next;

};

struct Avaliations
{
    int playerID;
    float rating;
};

struct Users
{
    int userID;
    vector<Avaliations> avaliation;
    Users *next;
};

////////////////////////////////////////////////////////// HASHTABLE PLAYERS

unsigned int hash_players(int id);
void init_hashTable_players();
void print_table_players();
bool hash_table_insert_players(PlayerList *p);
PlayerList *hash_table_search_players(int number_id);

////////////////////////////////////////////////////////// HASHTABLE USERS

unsigned int hash_users(int id);
void init_hashTable_users();
void print_table_users();
bool hash_table_insert_users(Users *p);
Users *hash_table_search_users(int number_id);

////////////////////////////////////////////////////////// QUICKSORT

void quickSort(vector<PlayerList> &set, float start, float end);
float partition(vector<PlayerList> &set, float start, float end);
void swapInt(int &value1, int &value2);
void swapString(string &value1, string &value2);
void swapDouble(float &value1, float &value2);

////////////////////////////////////////////////////////// SEARCHES

void search_position(int total, string position);

#endif // HEADER_H_INCLUDED
