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
        cout << setw(10) << left << Positions;
        cout << endl;
    }

    int Id;
    string PlayerName;
    string Positions;
    vector<float> ratings;
    PlayerList *next;

};

PlayerList *hashTable[TABLE_SIZE];
vector<PlayerList> players;

unsigned int hash_(int id)
{
    int hash_value=0;

        hash_value = (3*id^2)%TABLE_SIZE;

    return hash_value;
}

void init_hashTable()
{
    for(int i=0;i<TABLE_SIZE;i++){
        hashTable[i]=NULL;

    }
}

void print_table()
{
    cout << "  START" << endl;
    for(int i=0;i<TABLE_SIZE;i++){
        if(hashTable[i]==NULL){
            cout << i << "  ---";

        } else{
        cout << i << " ";};
        PlayerList *tmp = hashTable[i];
        while(tmp != NULL){
            cout << tmp->PlayerName << " -> ";
            tmp = tmp->next;
        }
        printf("\n");
    }
    cout << "  END\n" << endl;
}

bool hash_table_insert(PlayerList *p)
{
    if(p == NULL)
        return false;

    int index = hash_(p->Id);
    p->next = hashTable[index];
    hashTable[index] = p;
    return true;


}

PlayerList *hash_table_search(int number_id)
{
    int index = hash_(number_id);
    PlayerList *tmp = hashTable[index];
    while(tmp!= NULL && (tmp->Id != number_id)){
        tmp = tmp->next;
    }
    return tmp;
}


/*void displayStudents(vector<PlayerList> &players) {

    for (auto student : players) {
        student.display();
    }
}
*/

void open_players()
{
    ifstream inputFile;
    inputFile.open("players.csv");
    string line = "";
    int counter=0;

   // vector<PlayerList> players;
    while (getline(inputFile, line)) {

        stringstream inputString(line);

        //StudentId, Last Name, playerName, Age, Phone Number, GPA
        int playerID;
        string playerName;
        string lastName;
        string tempString;


        getline(inputString, tempString, ',');
        playerID = atoi(tempString.c_str());
        getline(inputString,playerName, ',');
        getline(inputString,lastName, '\n');

        PlayerList student(playerID, playerName, lastName, NULL);
        players.push_back(student);
        line = "";
        counter++;
    }

    init_hashTable();

    for(int i=0;i<counter;i++)
    hash_table_insert(&players[i]);
    print_table();

}

void open_ratings()
{
    ifstream inputFile;
    inputFile.open("minirating.csv");
    string line = "";
    int counter=0;

   // vector<PlayerList> players;
    while (getline(inputFile, line)) {

        stringstream inputString(line);

        //StudentId, Last Name, playerName, Age, Phone Number, GPA
        int userID;
        int playerID;
        float rating;
        string tempString;

        getline(inputString, tempString, ',');
        userID = atoi(tempString.c_str());

        getline(inputString, tempString, ',');
        playerID = atoi(tempString.c_str());

        getline(inputString, tempString, '\n');
        rating = atof(tempString.c_str());


       // PlayerList student(playerID, playerName, lastName, NULL);
       hash_table_search(playerID)->ratings.push_back(rating);
      //  players.push_back(student);
        line = "";
     //   counter++;
    }

}




int main()
{

    open_players();


    string stringTest("Python");

    PlayerList *tmp1 = hash_table_search(226659);
    PlayerList *tmp2 = hash_table_search(players[2713].Id);

    if(tmp1 == NULL){
        printf("Not found!\n");
    }else
        tmp1->display();


        if(tmp2 == NULL){
        printf("Not found!\n");
    }else
        tmp2->display();

    //displayStudents(players);
}
