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
Arvore_Trie A_nomes;
Arvore_Trie_Ptr A_tags;


bool inVec(int& obj, vector<int>* vec)
{
    for(int i : *vec)
    {
        if(i == obj)
            return 1;
    }
    return 0;
}

// abre o arquivo com os jogadores e salva todos eles em um vetor, que depois será inserido em uma tabela hash organizando os jogadores devidamente
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

        A_nomes.insert(playerName, playerID);

        PlayerList player(playerID, playerName, positions, NULL);
        players.push_back(player);
     //   players2.push_back(player);
        line = "";
        counter++;
    }

    init_hashTable_players();

    for(int i=0;i<counter;i++)
    hash_table_insert_players(&players[i]);
}

//abre o arquivo com as tags e associa elas aos jogadores correspondentes utilizando a tabela hash e uma arvore trie
void open_tags()
{
    ifstream inputFile;
    inputFile.open("tags.csv");
    string line = "";
    int counter=0;
    int* ids;
    vector<int>* vec;

    getline(inputFile, line);
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

        if(!A_tags.inTrie(tag))
        {
            vector<int>* ids = new vector<int>;
            ids->push_back(playerID);

            A_tags.insert(tag, ids);
            hash_table_search_players(playerID)->tags.push_back(tag);
        }
        else if(!inVec(playerID, (vec = (vector<int>*)A_tags.getVal(tag))))
        {
            vec->push_back(playerID);
            hash_table_search_players(playerID)->tags.push_back(tag);
        }
        line = "";
    }
}

// abre o arquivo das avaliações, lê as avaliações, associa ao jogadores correspondentes e soma a nota à uma variavél que posteriormente será usada para se obter as médias
void open_ratings()
{
    int i=0;
    init_hashTable_users();
    ifstream inputFile;
    inputFile.open("minirating.csv");
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


        hash_table_search_players(playerID)->average = hash_table_search_players(playerID)->average + rating;
        hash_table_search_players(playerID)->Asize++;

       /* if(counter==0)
            counter=0;
        else{

            if(hash_table_search_users(userID)==NULL){

                Users user(userID,NULL);
                users.push_back(user);
                users[i].playerIds.push_back(playerID);
                users[i].ratings.push_back(rating);
                hash_table_insert_users(&users[i]);
                i++;}

            else{
            hash_table_search_users(userID)->playerIds.push_back(playerID);
            hash_table_search_users(userID)->ratings.push_back(rating);
            }*/


        line = "";
    }
   // counter=1;
}


// Dado um número de jogadores e uma posição, busca na lista de jogadores e devolve os que se encaixam nos critérios
void search_position(int total, string position)
{
    int j=0,i=0,ok=0;

    while(j<total){
            if(i>18944){break;}
        if (players2[i].Positions.find(position) != string::npos){
            if(players2[i].Asize>=1){ // no lugar do 1 deveria ser 1000, só está assim pra poder funcionar com o "minirating"
                players2[i].display();
                j++;
                ok++;
            }
            i++;
        } else
        i++;
    }
    if(ok==0){
            cout<<" NENHUM JOGADOR ENCONTRADO"<<endl;
        }
}
//============================================================================
//Search Name(Quantidade, Prefixo)
//Entradas:
//  Quantidade(int): Número de jogadores quedevem ser achados com o prefixo.
//
//  Prefixo: Prefixo do nome dos jogadores a serem achados.
//
//Saidas
//  int: Quantidade de jogadores efetivamente encontrados.
//
//============================================================================
int search_name(int total, string prefix)
{
    int found = 0;
    int* ids = new int[total];
    PlayerList* Player;
    if(!(found = A_nomes.searchPrefix(prefix, total, ids)))
    {
        cout<<" NENHUM JOGADOR ENCONTRADO"<<endl;
        return 1;
    }
    for(int i = 0; i< found; i++)
    {
        Player = hash_table_search_players(ids[i]);
        Player->display();
    }
    return found;
}

//============================================================================
//Search Tag(Tags)
//Entradas:
//  Tags: Tags dos jogadores a serem achados.
//
//Saidas
//  int: Quantidade de jogadores efetivamente encontrados.
//
//============================================================================
int search_tag(vector<string> tags)
{
    int found = 0;
    PlayerList* Player;
    vector<vector<int>*> ids_list;
    vector<int>* ids;
    for(string tag : tags)
    {
        if((ids = (vector<int>*)A_tags.getVal(tag)))
        {
            ids_list.push_back(ids);
        }
        else{
            cout<<" NENHUM JOGADOR ENCONTRADO"<<endl;
            return 1;}
    }

    for(int id : *ids_list.at(0))
    {
        bool flag = true;
        for(int i = 1; i<ids_list.size(); i++)
        {
            if(!inVec(id, ids_list[i]))
            {
                flag = false;
            }
        }
        if(flag)
        {
            Player = hash_table_search_players(id);
            Player->display();
        }
    }
    return found;
}

void menu()
{

    string gk;
    int num;
    string name,tag;
    string vg;
    vector<string> tags;//= {"Manchester United", "Dribbler"};

    int n=0;

    while(n!=5){

        cout<<endl;
        cout<< " 1: PESQUISA POR USUARIO" << endl;
        cout<< " 2: PESQUISA POR NOME" << endl;
        cout<< " 3: PESQUISA POR POSICAO" << endl;
        cout<< " 4: PESQUISA POR TAGS" << endl;
        cout<< " 5: SAIR" << endl<<endl;
        cout<< " INSIRA SUA OPCAO: ";
        cin>> n;

        switch(n)
        {
            case(2):
                cout<<endl;
                cout<<" INSIRA O NOME A SER PESQUISADO (ENTRE ASPAS): ";
                cin>>quoted(name);
                cout<<endl;
                search_name(19000,name);
                break;
            case(3):
                cout<<" INSIRA O NUMERO DE JOGADORES: ";
                cin>>num;
                cout<<" INSIRA A POSICAO A SER PESQUISADA: ";
                cin>>gk;
                cout<<endl;
                search_position(num,gk);
                break;
            case(4):
                cout<<endl;
                cout<<" INSIRA AS TAGS DESEJADAS ENTRE ASPAS (DIGITE '*' PARA SIMBOLIZAR FIM DAS TAGS): ";

               while (tag != "*"){
                    cin>>quoted(tag);
                    if(tag=="*"){
                        tag=" ";
                        break;}
                    else
                    tags.push_back(tag);}

                cout<<endl;
                search_tag(tags);
                tags.clear();
                break;
            case(5):
                break;
        }

    }

}

int main()
{
    A_nomes = Arvore_Trie();
    A_tags = Arvore_Trie_Ptr();
    open_players();
    open_ratings();
    open_tags();

    for (auto players : players)
        players2.push_back(players);
    quickSort(players2, 0, players2.size());

    menu();

}


