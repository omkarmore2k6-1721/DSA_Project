#ifndef AUTH_H
#define AUTH_H

#define MAX_USERS 100

struct User {
    char username[50];
    char password[50]; // XOR-obfuscated
};

void encryptDecrypt(char *input, char key);
int  loadUsers(struct User users[]);
void saveUsers(struct User users[], int count);
void registerUser(struct User users[], int *count, char key);
int  loginUser(struct User users[], int count, char key, char *loggedInUser);

#endif
