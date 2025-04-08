#include "inverted_search.h"

main_node* create_main_node(main_node* mainnode)
{
    main_node* mnew=malloc(sizeof(main_node));
    mnew->m_link=NULL;
    if(mnew==NULL)
    {
        printf("FAILED in memory allocation");
    }
    return mnew;

}
sub_node* create_sub_node(sub_node* subnode)
{
    sub_node*snew=malloc(sizeof(sub_node));
    snew->s_link=NULL;
    if(snew==NULL)
    {
        printf("Failed in memory allocation");
    }
    return snew;
}


int create_database(hash_t *arr, Slist *shead)
{  
     main_node *mainnode=NULL;
   sub_node*subnode=NULL;
    Slist *temp = shead;
    char buffer[WORD_SIZE];

    while (temp != NULL)
    {
        FILE *fptr = fopen(temp->data, "r"); // Open the file in read mode
        if (fptr == NULL)
        {
            perror("Error opening file");
            return FAILURE;
        }

        while (fscanf(fptr, "%s", buffer) != EOF)
        {
            char ch = tolower(buffer[0]);
            int index = (isalpha(ch)) ? ch - 'a' : 26;

            if (arr[index].hlink == NULL) // If no main_node exists at this index
            {
                main_node *mnew = create_main_node(mainnode);
                sub_node *snew = create_sub_node(subnode);

                strcpy(mnew->word, buffer);
                mnew->file_count = 1;
                mnew->s_link = snew;

                strcpy(snew->f_name, temp->data);
                snew->word_count = 1;

                arr[index].hlink = mnew; // Update hash table
            }
            else // If main_nodes exist at this index
            {
                main_node *main_temp = arr[index].hlink;
                main_node *main_prev = NULL;
                int word_found = 0;

                while (main_temp != NULL)
                {
                    main_prev = main_temp;

                    if (strcmp(main_temp->word, buffer) == 0) // Word exists
                    {
                        word_found = 1;
                        sub_node *sub_temp = main_temp->s_link;
                        sub_node *sub_prev = NULL;
                        int file_found = 0;

                        while (sub_temp != NULL)
                        {
                            sub_prev = sub_temp;
                            if (strcmp(sub_temp->f_name, temp->data) == 0) // File exists
                            {
                                sub_temp->word_count++; // Increment word count
                                file_found = 1;
                                break;
                            }
                            sub_temp = sub_temp->s_link;
                        }

                        if (!file_found) // If file not found, add a new sub_node
                        {
                            sub_node *snew = create_sub_node(subnode);
                            strcpy(snew->f_name, temp->data);
                            snew->word_count = 1;
                            sub_prev->s_link = snew;
                            main_temp->file_count++; // Increment file count here
                        }

                        break;
                    }
                    main_temp = main_temp->m_link;
                }

                if (!word_found) // If word not found, create a new main_node
                {
                    main_node *mnew = create_main_node(mainnode);
                    sub_node *snew = create_sub_node(subnode);

                    strcpy(mnew->word, buffer);
                    mnew->file_count = 1;
                    mnew->s_link = snew;

                    strcpy(snew->f_name, temp->data);
                    snew->word_count = 1;

                    main_prev->m_link = mnew;
                }
            }
        }
        fclose(fptr);
        temp = temp->slink; // Move to next file
    }
    return SUCCESS;
}
