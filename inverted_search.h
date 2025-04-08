#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H
#include "colors.h"

#define F_SIZE 50
#define WORD_SIZE 100
#define SUCCESS 0
#define FAILURE -1

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
//for sub node 
typedef struct subnode
{
    int word_count;
    char f_name[F_SIZE];
    struct subnode* s_link;     
    
}sub_node;

//for main node
typedef struct main_node
{
    int file_count;
    char word[WORD_SIZE];
    struct main_node* m_link;
    sub_node* s_link;

}main_node;

//single linked list
typedef struct single
{
    char data[15];
    struct single* slink;
}Slist;


typedef struct hashnode
{
    int index;
    struct main_node *hlink;
}hash_t;

int read_validate(int argc,char* argv[],Slist** head);
void create_hashtable(hash_t* arr);
main_node* create_main_node(main_node* mainnode);
sub_node* create_sub_node(sub_node* subnode);
int display_database(hash_t* arr);
int search_database(hash_t* arr,char* word);
int save_database(hash_t* arr,char* str);
int update_database(hash_t* arr,char* back_up,Slist** head,Slist** temp_head);
void remove_duplicate_fnames(Slist** new_head1,Slist* saved_head);
int duplicate_check(Slist*head ,char *argv);
int insert_last(Slist** head,char* argv);
void print_list(Slist* head);
int create_database(hash_t *arr,Slist* shead);
#endif 