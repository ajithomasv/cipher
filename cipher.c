//  Date Created  :-  20130221
//  Description   :-  This C program encryptes and decryptes a password using private key

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//--- Function to Decrypt the password ----------------------------------------------/

char *Decrypt(char *password) {
        int i, j, ascii, new_ascii, key;
        char *new_password = (char *)malloc(100);
        j = 1;
        i = -1;
        while( *password != '\0' ){
                key = *password;
                ascii = *++password;
                if ( j == 1 )
                        new_ascii = key ^ ascii;
                else
                        new_ascii = ascii ^ key;
                j = j * -1;
                new_password[++i] = new_ascii;
                *password++;
        }
        new_password[++i] = 0;
        return(new_password);
}
//-----------------------------------------------------------------------------------/



//--- Function to Encrypt the password ----------------------------------------------/

void Encrypt(char *password, int sec) {
                int array[255] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

        int i, ascii, new_ascii, key;
        i = 1;
        while ( *password != '\0' ) {
                ascii = *password;

                key = key = (rand() % 100) + 21 + sec;
                new_ascii = ascii ^ key;

                while ( new_ascii == ascii || array[new_ascii] == 0 || array[key] == 0 ) {
                        key = (rand() % 100) + 21 + sec;
                        new_ascii = ascii ^ key;
                }

                if ( i = 1 )
                        printf("%c%c", key, new_ascii);
                else
                        printf("%c%c", new_ascii, key);

                i = i * -1;

                *password++;
        }
}
//-----------------------------------------------------------------------------------/



//--- Main Function -----------------------------------------------------------------/

int main(int argc, char *argv[]) {
        //---check no of arguments
        if ( argc != 4 ) {
                printf("Usage   : %s -E|D <password> <PRIVATE KEY file>\n", argv[0]);
                exit (1);
        }

        //---declrations
        int s, key;
        int len1, len2;
        time_t timer;
        struct tm* tm_info;
        char ss[3];
        char *PRIVATE_KEY = (char *)malloc(100);
        char *PRIVATE_KEY_len = (char *)malloc(100);
        char *DecryptedPassword = (char *)malloc(120);
        char *excessChar = (char *)malloc(120);
        FILE *keyFile;

        //---open and read private key file
        keyFile = fopen(argv[3], "r");
        if ( keyFile == NULL ) {
                printf("ERROR : Private key file [%s] is not readable or does not exist or permission denied.\n", argv[3]);
                exit (2);
        }
        fscanf(keyFile, "%s", PRIVATE_KEY);

        //---check private key length
        if ( strlen(PRIVATE_KEY) > 8 ) {
                printf("ERROR : Private key length is more than 8.\n");
                exit (2);
        }

        //---Start Encryption
        if ( strcmp(argv[1], "-E" ) == 0 ) {
                //---check password length
                if ( strlen(argv[2]) > 30 ) {
                        printf("ERROR : Password length is more than 30.\n");
                        exit (2);
                }
                time(&timer);
                tm_info = localtime(&timer);
                strftime(ss, 3, "%S", tm_info);
                s=atoi(ss);
                PRIVATE_KEY_len[0] = strlen(PRIVATE_KEY) + 48;
                PRIVATE_KEY_len[1] = 0;

                int i = -1;
                int j = 0;
                int len = (strlen(argv[2]) + strlen(PRIVATE_KEY) + 1);

                while ( len < 49 ) {
                        excessChar[++i] = j + 48;
                        j++;
                        if ( j > 9 ) j = 0;
                        len++;
                }

                excessChar[++i] = '|';
                excessChar[++i] = 0;
                Encrypt(excessChar, s);
                Encrypt(PRIVATE_KEY_len, s);
                Encrypt(PRIVATE_KEY, s);
                Encrypt(argv[2], s);
        }
        //---End of Encryption

        //---Start Decryption
        else if ( strcmp(argv[1], "-D" ) == 0 ) {
                if ( strlen(argv[2]) % 2 != 0 ) {
                        printf("ERROR : Invalid encrypted data.\n");
                        exit (3);
                }

                strcpy(DecryptedPassword, Decrypt(argv[2]));
                len1 = strlen(PRIVATE_KEY);

                while(*DecryptedPassword++ != '|');

                len2 = *DecryptedPassword - 48;
                *++DecryptedPassword;

                if ( len1 == len2 && strncmp(DecryptedPassword, PRIVATE_KEY, len1) == 0 ) {
                        DecryptedPassword += (len1 - 1);
                        while( *++DecryptedPassword != 0 ) printf("%c", *DecryptedPassword);
                }
                else {
                        printf("ERROR : Invalid PRIVATE KEY.\n");
                        exit (4);
                }
        }
        //---End of Decryption

        else {
                printf("Invalid option; Usage   : %s -E|D <password>\n", argv[0]);
                exit (2);
        }

        printf("\n");
        return 0;
}


// EOF
//____________________________________________________________________________________//
