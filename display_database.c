#include "inverted_search.h"

int display_database(hash_t* arr)
{   
    printf(BOLDYELLOW"\n------------------- INVERTED INDEX DATABASE ----------------------------\n"RESET);
    printf(BOLDMAGENTA"%-10s %-20s %-15s %-15s %-15s\n"RESET, "INDEX", "WORD", "FILE COUNT", "WORD COUNT", "FILE NAME");
    printf(BOLDYELLOW"--------------------------------------------------------------------------\n"RESET);

    for (int i = 0; i < 27; i++)
    {   
        if (arr[i].hlink != NULL)
        {    
            main_node* main_temp = arr[i].hlink;
            int first_main = 1; // Flag to print index only once.
            while (main_temp != NULL)
            {   
              
                if (first_main)
                {
                    printf(WHITE"%-10d "RESET, i);
                    first_main = 0;
                }
                else
                {
                    printf("%-10s ", ""); // Empty space for same words in the same index
                }

                // to Print the word and its file count
                printf(GREEN"%-20s %-15d "RESET, main_temp->word, main_temp->file_count);

                sub_node* sub_temp = main_temp->s_link;
                int first_sub = 1; // Flag update to 1
                while (sub_temp != NULL)
                {   
                    if (!first_sub)  
                    {
                        // to print the correct format sub-node rows correctly
                        printf("\n%-10s %-20s %-15s ", "", "", "");
                    }

                    // Print word count and file name
                    printf(GREEN"%-15d %-15s"RESET, sub_temp->word_count, sub_temp->f_name);
                    
                    first_sub = 0;
                    sub_temp = sub_temp->s_link;
                }

                printf("\n"); // Move to the next main node
                main_temp = main_temp->m_link;
            }
        }
    }
    
    printf(BOLDYELLOW"--------------------------------------------------------------------------\n"RESET);
    return SUCCESS;
}
