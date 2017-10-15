#include "proj.h"

void read_data(char *file_name, int key) {				//function to read data from text file
        char decrypt_str[100];						//string to decrypt
        FILE *fp;							//declare file 

        fp = fopen(file_name, "r");					//open file 

        if (fp == NULL) {
                printf ("File not found.");
                return;
        }

        fseek(fp, 45, SEEK_SET);					//skips certain amount of spaces


        while (fgets(decrypt_str, 100, fp) != NULL) {			//traverses file
                int size;
                char name[20];
                char *q = decrypt_str;

                while (*q != '\n') {					//traverses string 
                        *q = *q^key;					//decodes
                        q++;
                }

                sscanf(decrypt_str, "%s%d", name, &size);
                insert(name, size);					//sends to insert function
        }

        fclose(fp);
        return;
}

void save_data(char *file_name, int key) {				//function to save data to text file
        FILE *fp;							//declare file 
        NODE *p;
        int i;

        fp = fopen(file_name, "w");					//open file to write

        if (fp == NULL) {
                printf ("File not found\n");
                return;
        }

        fprintf (fp, "Name:\t\tSize:\n-------------------------------\n");

        for (i = 0; i < 4; i++) {					//prints encrypted info to file
                p = heads[i];
                while (p != NULL) {
                        char encrypt_str[30];
                        char *q = encrypt_str;

                        sprintf(encrypt_str, "%s\t%d\n", p->name, p->size);

                        while (*q != '\0') {				//encrypts file with key
                                *q = *q^key;
                                q++;
                        }
                        fprintf(fp, "%s\n", encrypt_str);
                        p = p->next;
                }
        }

        fclose (fp);							//closes file
        return;
}

void free_nodes() {							//function to free nodes
        NODE *p;
        int i;

        for (i = 0; i < 4; i++) {
                p = heads[i];
                recursive_free(p);					//passes p to recursive_free
        }
}

void recursive_free(NODE *p) {						//function to recursively free nodes
        if (p == NULL) {
                return;
        }

        recursive_free(p->next);
        free(p);
        return;
}

void *auto_save(void *arg) {						//function to auto-save data
        char *binary = (char *) arg;

        FILE *outfp;
        NODE *p;
        int i;

        while(1) {
                pthread_mutex_lock (&mutex);				//lock
                outfp = fopen(binary, "wb");

                if (outfp == NULL) {
                        printf ("File not found\n");
                }

                for (i = 0; i < 4; i++) {				//saves data to binary file
                        p = heads[i];
                        while (p != NULL) {
                                fwrite(p, sizeof(NODE), 1, outfp);
                                p = p->next;
                        }
                }

                fclose(outfp);
                pthread_mutex_unlock(&mutex);				//unlock
                sleep(5);						//repeats every 5 seconds
        }
}

void read_auto_saved(char *binary) {					//function to read auto-save binary file
        pthread_mutex_lock(&mutex);					//lock
        FILE *infp;
        NODE save_temp;

        infp = fopen(binary, "rb");

        if (infp == NULL) {
                printf ("File not found\n");
                return;
        }

        printf("\nCurrent Reservations:\n");
        printf("\n---------------------------------\nName\t\tGroup Size\n");

        while (fread(&save_temp, sizeof(NODE), 1, infp)!= 0) {		//reads info and prints data
                printf("%s\t\t%d\n", save_temp.name, save_temp.size);
        }

        fclose (infp);
        pthread_mutex_unlock(&mutex);					//unlock
        return;
}


