#include"inverted_search.h"
int save_database(hash_t* arr,char* str)
{
    if(strcmp(strstr(str,"."),".txt")!=0)
    {
        printf(BOLDRED"ERROR : Enter only .txt file to save\n"RESET);
        return FAILURE;
    }
    FILE* fptr=fopen(str,"w"); //open the file in write mode 
    if(fptr==NULL)
    {
        printf("ERROR : File not found to save\n");
        return FAILURE;
    }
    for(int i=0;i<27;i++)
    {
        main_node*main_temp=arr[i].hlink;
        if(main_temp!=NULL)
            fprintf(fptr,"#%d;",i); //to print the index value
        
        while(main_temp!=NULL)
        {
            sub_node* sub_temp=main_temp->s_link;
            fprintf(fptr,"%s;%d;",main_temp->word,main_temp->file_count);//to write word and file count
            while(sub_temp!=NULL)
            {
                fprintf(fptr,"%s;%d;",sub_temp->f_name,sub_temp->word_count);//to write the file name and word count
                sub_temp=sub_temp->s_link;
            }
            main_temp=main_temp->m_link;
            if(main_temp==NULL)
                fprintf(fptr,"#\n"); //if more than one word is present then write it in newline
            else
                fprintf(fptr,"\n"); //after writing one index data then shifting to newline
        }

    }
    return SUCCESS;
    
}