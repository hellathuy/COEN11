#include "proj.h"

int main(int argc, char*argv[]) {							//main function
        char name [20];
        int size;
        int option;
        int key = atoi(argv[3]);							//key

        if (argc == 1) {								//return if file name is not declared
                printf("The file name is missing!\n");
                return (-1);
        }

        else {
                read_data(argv[1], key);						//read data from text file
        }

        pthread_t thread;								//pthread
        pthread_mutex_init (&mutex, NULL);
        pthread_create (&thread, NULL, auto_save, (void *) argv[2]);

        while (1) {									//forever loop to continuously repeat program
                printf("What do you want to do?\n");
                printf(" [1] Add a name to the list.\n");
                printf(" [2] Remove a name from the list.\n");
                printf(" [3] Show the list of names.\n");
                printf(" [4] Count how many characters there are in the names.\n");
                printf(" [5] Print out names backwards.\n");
                printf(" [6] Print the auto-saved binary file.\n");
                printf(" [7] Quit the program.\n\n");

                scanf ("%d", &option);							//receive input from user

                switch (option) {							//switch function to switch between functions
                        case 1:
                                printf ("What is the guest's name? ");
                                scanf ("%s", name);
                                printf ("\nHow many people are in the party? ");
                                scanf ("%d", &size);
                                insert(name, size);					//calls insert function
                                break;
                        case 2:
                                cancel();						//calls delete function
                                break;
                        case 3:
                                list();							//calls list function
                                break;
                        case 4:
                                char_count();						//calls character count function
                                break;
                        case 5:
                                name_backwards();					//call function to display name backwards
                                break;
                        case 6:
                                read_auto_saved(argv[2]);				//read data from auto save text file
                                break;
                        default:							//quits program and saves program to text file
                                save_data(argv[1], key);
                                free_nodes();
                                return 0;
                }
        }
}

