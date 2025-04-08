/*Documentation of project 

Name :Abhinay Dameruppula

Project Title: Inverted Search

Description: An inverted index is an index data structure storing a mapping from content, such as words 
or numbers, to its locations in a database file, or in a document or a set of documents. The purpose of an 
inverted index is to allow fast full text searches, at a cost of increased processing when a document is 
added to the database. The inverted file may be the database file itself, rather than its index. It is the 
most popular data structure used in document retrieval systems, used on a large scale for example in search
engines. The purpose of this project is to implement the inverted search using Hash Algorithms.

purpose of the project: This project is efficient to search the word or terms with large datasheets by using the 
inverted index.
a) Instead of scanning entire files, an inverted index allows quick lookups of words.
b) Helps in search engines, text mining, and big data analytics.

Applications of this project :
1)search engines like google ,bing 
2) file searching in OS .
3) chat bots like chatgpt and Alexa and siri.

Date of submission :13-02-2025 

*/
#include "inverted_search.h"

int main(int argc,char* argv[])
{
    Slist * head=NULL;
    Slist* temp_head=NULL;
    hash_t arr[27];
    main_node * main_head=NULL;
    sub_node* sub_head=NULL;

    if(read_validate(argc,argv,&head)==FAILURE) //validate the file names given throught CLA and store it in a single linked list
    {
        printf(BOLDRED"ERROR : FAILED IN VALIDATION"RESET);
        return 0;
    }
    int option;
    char option1;
    int flag=0;//to prevent the user calling the create/update again 
    create_hashtable(arr); //creating the hashtable with initial index vaulue and main node address as NULL
    do
    {
        printf(YELLOW" 1️⃣  To create database✍️\n 2️⃣  To search Word in database🔍\n 3️⃣  To save database📲\n 4️⃣  To update database🔄️\n 5️⃣  To display database💻\n 6️⃣ To Exit🔚\n"RESET);
        scanf("%d",&option);
        switch(option)
        {
            case 1:
                //to create database
                if(flag==0)
                {
                    if(create_database(arr,head)==SUCCESS)
                    {
                     printf(BOLDCYAN"\nCREATED DATABASE SUCCESSFULLY👍\n"RESET);
                     flag=1;
                    }
                }
                else{
                    printf(BOLDRED"\nERROR : INFO::Files passed through CLA are already added in the database \n"RESET);
                }
                break;
            case 2:
                if(flag==1)
                {
                    char word[WORD_SIZE];
                    printf("Enter a word to search     ");
                    scanf("%s",word);
                    if(search_database(arr,word)==SUCCESS)
                        break;
                    else
                        printf(BOLDRED"ERROR : FAILED TO SEARCH WORD %s"RESET,word);
                    break; 
                }
                else
                {
                    printf(BOLDRED"ERROR : INFO::FIRST CREATE/UPDATE DATABASE👎"RESET);
                }
                break;
                
            case 3:
            if(flag==1)
            {
                char str1[F_SIZE];
                printf("Enter the file to save    ");
                scanf("%s",str1);
                 if(save_database(arr,str1)==SUCCESS)
                 {
                    printf(BOLDCYAN"\nDATABASE SAVED SUCCESSFULLY IN FILE %s👍\n"RESET,str1);
                 }
                 else
                 {
                    printf(BOLDRED"\nERROR : FAILED to SAVE the DATABASE👎\n"RESET);
                 }
            }
            else
            {
                printf(BOLDRED"ERROR  : DATABASE IS EMPTY FIRST CREATE/UPDATE DATABASE TO SAVE\n"RESET);
            }
                break;
            case 4:
                 if(flag==0)
                 {
                    char back_up[F_SIZE];
                    printf("Enter a file name to update the database     ");
                    scanf("%s",back_up);
                    if(update_database(arr,back_up,&head,&temp_head)==SUCCESS)
                    {
                        print_list(head);
                        printf(BOLDCYAN"\nDATABASE UPDATED SUCCESSFULLY WITH FILE %s 👍\n"RESET,back_up);
                        flag=1;
                    }
                    else
                    {
                        printf(BOLDRED"\nERROR : INFO::FAILED TO UPDATE DATABASE👎\n"RESET);
                    }
                    
                 }
               else
                 printf(BOLDRED"\nERROR : DATABASE ALREADY CREATED CAN'T PERFORM UPDATE DATABASE!!👎\n"RESET);
                 break;

            case 5:
                   if(display_database(arr)==SUCCESS)
                   {
                    printf(BOLDCYAN"\nDATABASE DISPLAYED SUCCESSFULLY👍\n"RESET);
                   }
                   break;
            case 6:
                exit(0);//to exit form the application
            default : 
                printf(BOLDRED"ERROR : invalid choice!!!enter correct choice👎\n"RESET);
            
        }
        printf(BOLDMAGENTA"\nDo you want to continue (y/Y) not n       "RESET);
        getchar();
        scanf(" %c",&option1);
    } while (option1=='y' || option1 =='Y');
    return 0;
}
