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


vector<PlayerList> players;
vector<PlayerList> players2;
vector<Users> users;


void open_players()
{
    ifstream inputFile;
    inputFile.open("players.csv");
    string line = "";
    int counter=0;

    while (getline(inputFile, line)) {

        stringstream inputString(line);

        int playerID;
        string playerName;
        string positions;
        string tempString;

        getline(inputString, tempString, ',');
        playerID = atoi(tempString.c_str());
        getline(inputString,playerName, ',');
        getline(inputString,positions, '\n');

        PlayerList player(playerID, playerName, positions, NULL);
        players.push_back(player);
        players2.push_back(player);
        line = "";
        counter++;
    }

    init_hashTable_players();

    for(int i=0;i<counter;i++)
    hash_table_insert_players(&players[i]);
}

void open_ratings()
{
    int i=0;
    init_hashTable_users();
    ifstream inputFile;
    inputFile.open("rating.csv");
    string line = "";
    int counter=0;

    while (getline(inputFile, line)) {

        stringstream inputString(line);

        int userID;
        int playerID;
        float rating=0;
        string tempString;

        getline(inputString, tempString, ',');
        userID = atoi(tempString.c_str());

        getline(inputString, tempString, ',');
        playerID = atoi(tempString.c_str());

        getline(inputString, tempString, '\n');
        rating = atof(tempString.c_str());


     /*   Avaliations avaliation; avaliation.playerID = playerID;
                                avaliation.rating = rating;


       // if(hash_table_search_users(userID)==NULL){


            Users user;
            user.userID = userID;
            user.avaliation.push_back(avaliation);

            users.push_back(user);
            hash_table_insert_users(&users[i]);
            i++;

       // } //else
           // hash_table_search_users(userID)->avaliation.push_back(avaliation);*/


        hash_table_search_players(playerID)->average = hash_table_search_players(playerID)->average + rating;
        hash_table_search_players(playerID)->Asize++;

        line = "";
     //   counter++;
    }

}




int main()
{

    open_players();
    open_ratings();

    for (auto players : players)
        players2.push_back(players);

    quickSort(players2, 0, players2.size());

   /* string gk;
    int num;

    cout<< "INSIRA O NUM DE JOGADORES: ";
    cin>>num;

    cout<< "INSIRA A POSICAO: ";
    cin.ignore(1);
    //cin>>gk;
    getline(cin, gk, '\'');
   // cout<< "sua string eh:" << gk;

    int j=0;

    for (int i=0;j<num;i++){
        if (players2[i].Positions.find(gk) != string::npos){
            players2[i].display();
            j++;
        }
    }*/



   // print_table_players();
   // print_table_users();


       //for (auto players : players)
     //  for(int i=0;i<18944;i++)
          //  players2[i].display();


    //displayStudents(players);
}
