#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <list>
#include <cstring>
#include "header.h"

#define TABLE_SIZE_USER 100

using namespace std;

Users *hashTable_users[TABLE_SIZE_USER];

//cálculo para definir em qual célula da tabela usuário será salvo
unsigned int hash_users(int id)
{
    int hash_value=0;

        hash_value = (3*id^2)%TABLE_SIZE_USER;

    return hash_value;
}

// inicializa tabela hash
void init_hashTable_users()
{
    for(int i=0;i<TABLE_SIZE_USER;i++){
        hashTable_users[i]=NULL;
    }
}

//imprime tabela hash
void print_table_users()
{
    cout << "  START" << endl;
    for(int i=0;i<TABLE_SIZE_USER;i++){
        if(hashTable_users[i]==NULL){
            cout << i << "  ---";

        } else{
        cout << i << " ";};
        Users *tmp = hashTable_users[i];
        while(tmp != NULL){
            cout << tmp->userID << " -> ";
            tmp = tmp->next;
        }
        printf("\n");
    }
    cout << "  END\n" << endl;
}

//insere usuário na tabela
bool hash_table_insert_users(Users *p)
{
    if(p == NULL)
        return false;

    int index = hash_users(p->userID);
    p->next = hashTable_users[index];
    hashTable_users[index] = p;
    return true;
}

//procura usuário na tabela e devolve o usuário encontrado
Users *hash_table_search_users(int number_id)
{
    int index = hash_users(number_id);
    Users *tmp = hashTable_users[index];
    while(tmp!= NULL && (tmp->userID != number_id)){
        tmp = tmp->next;
    }
    return tmp;
}
