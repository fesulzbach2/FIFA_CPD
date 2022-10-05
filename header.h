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

#define R 256
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
        cout<<" ";
        cout << setw(12) << left << Id;
        cout << setw(45) << left << PlayerName;
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

struct Users {
public:
    Users(
        int userid,
        Users *next
    ) {
        userID = userid;
    }

    void display() {
        cout<<" ";
        cout << setw(12) << left << userID;
        cout << endl;
    }

    int userID;
    vector<int> playerIds;
    vector<float> ratings;
    Users *next;

};


/*struct Users
{
    int userID;
    vector<int> playerIds;
    vector<float> ratings;
    Users *next;
};*/

////////////////////////////////////////////////////////// ARVORE TRIE
class Arvore_Trie
{
public:

    class Node
    {
    public:
        int val;
        Node** next = new Node*[R];
        bool isEnd;
    };
    Node* newNode()
    {
        Node* pNode= new Node;
        pNode->isEnd = false;
        for(size_t i = 0; i<R; i++)
            pNode->next[i]=NULL;
        return pNode;
    }

    Node root;

    /*
    int inTrie(string key)
    {
        Node* it = &root;

        for(size_t i = 0; i<key.length(); i++)
        {
            int index = key[i];//-'a';
            if(!it->next[index])
                return 0;
            it = it->next[index];
        }
        if(it->isEnd)
            return 1;
        else
            return 0;
    }*/

    int getVal(string key)
    {
        Node* it = &root;

        for(size_t i = 0; i<key.length(); i++)
        {
            int index = key[i];//-'a';
            if(!it->next[index])
                return NULL;
            it = it->next[index];
        }
        if(it->isEnd)
            return it->val;
        else
            return NULL;
    }

    /*
    int search(int& valor, string key)
    {
        Node* it = &root;

        for(size_t i = 0; i<key.length(); i++)
        {
            int index = key[i];//-'a';
            if(!it->next[index])
                return 1;
            it = it->next[index];
        }
        if(it->isEnd)
        {
            valor = it->val;
            return 0;
        }
        else
            return 1;
    }*/

    Node* search(string key)
    {
        Node* it = &root;

        for(size_t i = 0; i<key.length(); i++)
        {
            int index = key[i];//-'a';
            if(!it->next[index])
                return NULL;
            it = it->next[index];
        }
        return it;
    }

    int iterate(Node* it, int* ids, int& qnt, int lim)
    {
        for(int i = 0 ; i<R; i++)
        {
            if(it->next[i] != NULL)
            {
                if(it->next[i]->isEnd)
                {
                    ids[qnt] = it->next[i]->val;
                    qnt++;
                }
                if(qnt!=lim)
                {
                    qnt =  iterate(it->next[i], ids, qnt, lim);
                }
            }
            if(qnt==lim)
                break;

        }
        return qnt;
    }

    int searchPrefix(string prefix, int qnt, int* ids)
    {
        Node* it = search(prefix);
        int found = 0;
        iterate(it, ids, found, qnt);
        return found;
    }

    void insert(string key, int valor)
    {
        Node* it = &root;
        for(size_t i = 0; i<key.length(); i++)
        {
            int index = key[i];//-'.';
            if(!it->next[index])
            {
                it->next[index] = newNode();
            }
            it = it->next[index];
        }
        it->isEnd = true;
        it->val = valor;
    }

    Arvore_Trie()
    {
        this->root = *newNode();
    }
};

////////////////////////////////////////////////////////// ARVORE TRIE POINTERS
class Arvore_Trie_Ptr
{
public:

    class Node
    {
    public:
        void* val;
        Node** next = new Node*[R];
        bool isEnd;
    };
    Node* newNode()
    {
        Node* pNode= new Node;
        pNode->isEnd = false;
        for(size_t i = 0; i<R; i++)
            pNode->next[i]=NULL;
        return pNode;
    }

    Node root;

    int inTrie(string key)
    {
        Node* it = &root;

        for(size_t i = 0; i<key.length(); i++)
        {
            int index = key[i];//-'a';
            if(!it->next[index])
                return 0;
            it = it->next[index];
        }
        if(it->isEnd)
            return 1;
        else
            return 0;
    }

    void* getVal(string key)
    {
        Node* it = &root;

        for(size_t i = 0; i<key.length(); i++)
        {
            int index = key[i];//-'a';
            if(!it->next[index])
                return NULL;
            it = it->next[index];
        }
        if(it->isEnd)
            return it->val;
        else
            return NULL;
    }

    Node* search(string key)
    {
        Node* it = &root;

        for(size_t i = 0; i<key.length(); i++)
        {
            int index = key[i];//-'a';
            if(!it->next[index])
                return NULL;
            it = it->next[index];
        }
        return it;
    }

    int iterate(Node* it, void** ids, int& qnt, int lim)
    {
        for(int i = 0 ; i<R; i++)
        {
            if(it->next[i] != NULL)
            {
                if(it->next[i]->isEnd)
                {
                    ids[qnt] = it->next[i]->val;
                    qnt++;
                }
                if(qnt!=lim)
                {
                    qnt =  iterate(it->next[i], ids, qnt, lim);
                }
            }
            if(qnt==lim)
                break;

        }
        return qnt;
    }

    int searchPrefix(string prefix, int qnt, void** ids)
    {
        Node* it = search(prefix);
        int found = 0;
        iterate(it, ids, found, qnt);
        return found;
    }

    void insert(string key, void* valor)
    {
        Node* it = &root;
        for(size_t i = 0; i<key.length(); i++)
        {
            int index = key[i];//-'.';
            if(!it->next[index])
            {
                it->next[index] = newNode();
            }
            it = it->next[index];
        }
        it->isEnd = true;
        it->val = valor;
    }

    Arvore_Trie_Ptr()
    {
        this->root = *newNode();
    }
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
