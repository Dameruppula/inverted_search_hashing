#include "inverted_search.h"
int search_database(hash_t* arr,char* word)
{
    char ch=tolower(word[0]);
    int index=ch-'a';

    if(index<0 || index>26) //to check the if index is not valid
    {
        printf(BOLDRED"ERROR : Failed to search!! invalid index found\n"RESET);
        return FAILURE;
    }
    main_node*main_temp=arr[index].hlink;
    while(main_temp!=NULL)
    {
        sub_node*sub_temp=main_temp->s_link;
        if(strcmp(word,main_temp->word)==0)
        {
            if(sub_temp->s_link==NULL)//if only one word is present in each index
            {
                printf(BOLDMAGENTA"Word [%s] is present in file [%s] with file count [%d] and word count [%d] time(s)"RESET,word,sub_temp->f_name,main_temp->file_count,sub_temp->word_count);
                break;
            }
            if(main_temp->file_count>=2) //if more than one word and more than one files present
            {
                printf(BOLDMAGENTA"word [%s] is present in [%d] files\n"RESET,word,main_temp->file_count);
                while(sub_temp!=NULL)
                {
                    printf(BOLDMAGENTA"[%d] occurances in %s\n"RESET,sub_temp->word_count,sub_temp->f_name);
                    sub_temp=sub_temp->s_link;
                }
                printf("\n");
                return SUCCESS;
            }
        }
        main_temp=main_temp->m_link;
    }
    if(main_temp==NULL) 
    {
        printf(BOLDRED"INFO : Word %s is not found in database\n"RESET,word);
        return FAILURE;
    }
    return SUCCESS;

  
}