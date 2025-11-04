#include <stdio.h>
#include <string.h>
#include "auth.h"

void encryptDecrypt(char *input, char key) {
    for (int i = 0; input[i] != '\0'; i++) input[i] ^= key;
}

int loadUsers(struct User users[]) {
    FILE *fp = fopen("users.dat", "rb");
    if (!fp) return 0;
    int count = (int)fread(users, sizeof(struct User), MAX_USERS, fp);
    fclose(fp);
    return count;
}

void saveUsers(struct User users[], int count) {
    FILE *fp = fopen("users.dat", "wb");
    if (!fp) {
        printf("Error saving users!\n");
        return; 
    }
    fwrite(users, sizeof(struct User), count, fp);
    fclose(fp);
}

void registerUser(struct User users[], int *count, char key) {
    if (*count >= MAX_USERS) { 
        printf("User limit reached!\n"); 
        return; 
    }
    struct User nu;
    printf("\n--- Register New User ---\n");
    printf("Enter username: ");
    scanf("%49s", nu.username);
    printf("Enter password: ");
    scanf("%49s", nu.password);
    encryptDecrypt(nu.password, key);
    users[*count] = nu;
    (*count)++;
    saveUsers(users, *count);
    printf("User registered successfully \n");
}

int loginUser(struct User users[], int count, char key, char *loggedInUser) {
    char uname[50], pass[50];
    printf("\n--- User Login ---\n");
    printf("Username: ");
    scanf("%49s", uname);
    printf("Password: ");
    scanf("%49s", pass);
    for (int i = 0; i < count; i++) {
        char dec[50];
        strcpy(dec, users[i].password);
        encryptDecrypt(dec, key);
        if (strcmp(uname, users[i].username) == 0 && strcmp(pass, dec) == 0) {
            strcpy(loggedInUser, uname);
            printf("\nLogin successful! Welcome, %s \n", uname);
            return 1;
        }
    }
    printf("\nInvalid username or password \n");
    return 0;
}
