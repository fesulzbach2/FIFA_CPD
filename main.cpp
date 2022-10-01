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

void open_tags()
{
    ifstream inputFile;
    inputFile.open("tags.csv");
    string line = "";
    int counter=0;

    while (getline(inputFile, line)) {

        stringstream inputString(line);

        int userID;
        int playerID;
        string tag;
        string tempString;

        getline(inputString, tempString, ',');
        userID = atoi(tempString.c_str());
        getline(inputString, tempString, ',');
        playerID = atoi(tempString.c_str());
        getline(inputString,tag, '\n');


        hash_table_search_players(playerID)->tags.push_back(tag);

        line = "";
    }
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


void search_position(int total, string position)
{
    int j=0,i=0;

    while(j<total){
        if (players2[i].Positions.find(position) != string::npos){
            if(players2[i].Asize>=1){ // no lugar do 1 deveria ser 1000, só está assim pra poder funcionar com o "minirating"
                players2[i].display();
                j++;
            }
            i++;
        } else
        i++;

    }

}



int main()
{

    open_players();
    open_ratings();
    open_tags();

    for (auto players : players)
        players2.push_back(players);

    quickSort(players2, 0, players2.size());

    string gk = "ST";
    int num=10;

    search_position(num,gk);



   /* for(int i=0;i<20;i++){
        cout << "\n" << players[i].PlayerName << "\n" <<endl;
        for(int j=0;j<players[i].tags.size();j++)
            cout << players[i].tags[j] << ", ";}*/





   // print_table_players();

}
