#include "inverted_search.h"

int read_validate(int argc,char* argv[],Slist **head)
{
    if(argc<=1)
    {
        printf(BOLDRED"ERROR :  pass atleast 1 filename.txt to perform the operations\n"RESET);
        return FAILURE;
    }
    for(int i=1;i<argc;i++)
    {   
        if(strcmp(strstr(argv[i],"."),".txt")!=0)
        {
            printf(BOLDRED"ERROR : The file is not .txt %s not adding to list\n"RESET,argv[i]);
        }
        else if(strcmp(strstr(argv[i],"."),".txt")==0)
        {
            FILE* fp1=fopen(argv[i],"r");
            if(fp1==NULL)
            {
                printf(BOLDRED"ERROR : FIle %s is not present not adding to list\n"RESET,argv[i]);
            }
            else if(fp1!=NULL)
            {
                fseek(fp1,0,SEEK_END);
                long  k=ftell(fp1);
                if(k==0)
                {
                    printf(BOLDRED"ERROR : FILE %s is empty so not adding to list\n"RESET,argv[i]);
                }
                else if(k!=0)
                {
                    if(duplicate_check((*head),argv[i])==FAILURE)
                    {
                        printf(BOLDRED"ERROR : Duplicate file %s found not adding in to list\n"RESET,argv[i]);
                    }
                    else
                    {
                        if(insert_last(head,argv[i])==SUCCESS)
                        {
                            printf(GREEN"Added file %s is Successful\n"RESET,argv[i]);
                        }
                        else{
                            printf(BOLDRED"ERROR : FAILED to add file %s\n"RESET,argv[i]);
                        }
                    }
                    
                }

            }
        }
    }
    print_list(*head);
    return SUCCESS;
    
}
int duplicate_check(Slist*head ,char *argv)
{
    if(head==NULL)
    {
        return SUCCESS;
    }
    else{
        Slist* temp=head;
        while(temp!=NULL)
        {
            if(strcmp(temp->data,argv)==0)
            {
                return FAILURE;
            }
            temp=temp->slink;
        }
        return SUCCESS;
    }
}

int insert_last(Slist** head,char* argv)
{
    Slist* new=malloc(sizeof(Slist));
    strcpy(new->data,argv);
    new->slink=NULL;
    if(new==NULL)
    {
        printf("FAILED in allocating memory in Sinlge linked list");
        return FAILURE;
    }
    if((*head)==NULL)
    {
        *head=new;
        return SUCCESS;
    }
    Slist* temp=*head;
    while(temp->slink!=NULL)
    {
        temp=temp->slink;
    }
    temp->slink=new;
    return SUCCESS;

}
void print_list(Slist * head)
{
    if(head==NULL)
    {
        return ;
    }
    printf(GREEN"Successfully added files are "RESET);
    while(head!=NULL)
    {
        printf(BOLDBLUE" %s  "RESET,head->data);
        head=head->slink;
    }
    printf("\n");
}
void create_hashtable(hash_t* arr)
{
    for(int i=0;i<27;i++)
    {
        arr[i].index=i; //initially index values are 0,1,2,3,....
        arr[i].hlink=NULL;//each main_node as NULL
    }
}