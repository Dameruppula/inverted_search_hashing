#include "inverted_search.h"



int update_database(hash_t* arr, char* back_up, Slist** head, Slist** temp_head) {

    FILE* fptr = fopen(back_up, "r");

    if (fptr == NULL) {
        printf(BOLDRED "INFO::FILE NOT FOUND\n" RESET);
        return FAILURE;
    }
    if (strcmp(strstr(back_up, "."), ".txt") != 0) {
        printf(BOLDRED "INFO:: ERROR The FILE extension is not '.txt'\n" RESET);
        fclose(fptr);
        return FAILURE;
    }

    // Validate start and end markers
    rewind(fptr);
    char ch1, ch2;
    fseek(fptr, 0, SEEK_SET);
    fscanf(fptr, "%c", &ch1);
    fseek(fptr, -2, SEEK_END);
    fscanf(fptr, "%c", &ch2);
    rewind(fptr);

    if (!(ch1 == '#' && ch2 == '#')) {
        printf(BOLDRED "The saved file was not stored/saved properly\n" RESET);
        fclose(fptr);
        return FAILURE;
    }

    int index1, word_count1, file_count1;
    char word1[WORD_SIZE];
    char f_name1[F_SIZE];

    while (1) {
        if (fscanf(fptr, "#%d;%[^;];%d;", &index1, word1, &file_count1) == 3) {
            // reading with index if present 
        } 
        else if (fscanf(fptr, "%[^;];%d;", word1, &file_count1) == 2) {
        

            // to check first character is a valid letter
            // if (isalpha(word1[0])) {
            //     index1 = tolower(word1[0]) - 'a';
            // } else {
            //     index1 = 26; // for non-alphabetic words
            // }
        } 
        else {
            break; // End of file or invalid format
        }

        // Check if word already exists
        main_node* main_temp = arr[index1].hlink;
        main_node* existing_main_node = NULL;

        while (main_temp != NULL) {
            if (strcmp(main_temp->word, word1) == 0) {
                existing_main_node = main_temp;
                break;
            }
            main_temp = main_temp->m_link;
        }

        // Create new main node only if word doesn't exist
        main_node* mnew;
        if (existing_main_node == NULL) {
            mnew = create_main_node(NULL);
           
            strcpy(mnew->word, word1);
            mnew->file_count = file_count1;
            mnew->s_link = NULL;
            mnew->m_link = NULL;

            if (arr[index1].hlink == NULL) {
                arr[index1].hlink = mnew;
            } else {
                main_node* temp = arr[index1].hlink;
                while (temp->m_link != NULL) {
                    temp = temp->m_link;
                }
                temp->m_link = mnew;
            }
        } else {
            mnew = existing_main_node;
        }

        // Handle sub-node creation
        sub_node* sub_prev = NULL;
        for (int j = 0; j < file_count1; j++) {
            if (j == file_count1 - 1)
                fscanf(fptr, "%[^;];%d;#\n", f_name1, &word_count1);
            else
                fscanf(fptr, "%[^;];%d;", f_name1, &word_count1);

            // Check if sub-node already exists
            sub_node* sub_temp = mnew->s_link;
            int found = 0;
            while (sub_temp != NULL) {
                if (strcmp(sub_temp->f_name, f_name1) == 0) {
                    sub_temp->word_count += word_count1;  // Increment count if already present
                    found = 1;
                    break;
                }
                sub_temp = sub_temp->s_link;
            }

            if (!found) {  // Only create a new sub-node if it doesn't exist
                sub_node* snew = create_sub_node(NULL);
        
                snew->word_count = word_count1;
                strcpy(snew->f_name, f_name1);
                snew->s_link = NULL;

                if (sub_prev == NULL)
                    mnew->s_link = snew;
                else
                    sub_prev->s_link = snew;

                sub_prev = snew;
                insert_last(temp_head, f_name1);
            }
        }
    }

    fclose(fptr);

    remove_duplicate_fnames(head, *temp_head);
    if (*head != NULL)
        printf(GREEN "After removing, the new added files are\n" RESET);
    else
        printf("No new files to update\n");

    create_database(arr, *head);
    return SUCCESS;
}


//program for removing the existing files form list1 and adding new files to it after update.

void remove_duplicate_fnames(Slist** new_head1, Slist* saved_head) {
    Slist* temp = *new_head1;
    Slist* prev = NULL;

    while (temp != NULL) {
        Slist* s_temp = saved_head;
        int duplicate = 0;  // Reset duplicate flag for each node in new_head1

        // Check if temp->data exists in saved_head (list2)
        while (s_temp != NULL) {
            if (strcmp(temp->data, s_temp->data) == 0) {
                duplicate = 1;  // Mark as duplicate
                break;
            }
            s_temp = s_temp->slink;
        }

        if (duplicate) {
            // Remove the duplicate node from list1
            Slist* to_delete = temp;
            if (prev == NULL) {  
                // Deleting head node
                *new_head1 = temp->slink;
                temp = *new_head1;
            } else {
                prev->slink = temp->slink;
                temp = prev->slink;
            }
            free(to_delete);
        } else {
            // Move forward only if no deletion occurs
            prev = temp;
            temp = temp->slink;
        }
    }
}


