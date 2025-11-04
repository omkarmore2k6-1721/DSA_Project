#include <stdio.h>
#include <string.h>
#include "expense.h"
#include "auth.h"

/* Globals defined once here */
struct Expense expenses[MAX];
int count = 0;
int id_counter = 1;
float limit = 10000;
struct Node* head = NULL;
struct Stack undoStack;
struct TreeNode* root = NULL;
char dataFile[128] = "expenses.txt";

/* Optional helpers */
#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#include <sys/stat.h>
#define MKDIR(path) mkdir(path, 0755)
#endif

static void sanitize(char *s) {
    for (char *p = s; *p; ++p)
        if (!((*p>='0'&&*p<='9')||(*p>='A'&&*p<='Z')||(*p>='a'&&*p<='z')||*p=='_'))
            *p = '_';
}

static void runExpenseMenu(void);

int main(void) {
    // Auth flow
    struct User users[MAX_USERS];
    int userCount = loadUsers(users);
    char key = 0x5A;
    char loggedInUser[50] = "";

    while (1) {
        int choice;
        printf("\n1) Register\n2) Login\n3) Exit\nChoose: ");
        if (scanf("%d", &choice) != 1) return 0;
        while (getchar() != '\n');

        if (choice == 1) {
            registerUser(users, &userCount, key);
        } else if (choice == 2) {
            if (loginUser(users, userCount, key, loggedInUser)) break;
        } else if (choice == 3) {
            return 0;
        } else {
            printf("Invalid choice.\n");
        }
    }

    // Per-user data file
    MKDIR("data");
    sanitize(loggedInUser);
    snprintf(dataFile, sizeof(dataFile), "data/expenses_%s.txt", loggedInUser);

    // Data structures
    initStack();
    head = NULL; 
    root = NULL; 
    count = 0; 
    id_counter = 1;
    loadFromFile();

    // Menu
    runExpenseMenu();

    // Save
    printf("\nSaving data before exit...\n");
    saveToFile();
    printf("Data saved successfully. Exiting...\n");
    return 0;
}

static void runExpenseMenu(void) {
    int ch;
    do {
        printf("\n=========== Expense Manager ===========\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses \n");
        printf("3. Delete Expense\n");
        printf("4. Undo Delete )\n");
        printf("5. Search by Category\n");
        printf("6. Check Budget Limit\n");
        printf("7. View Sorted Expenses \n");
        printf("8. CategorySpendingPercentage\n");
        printf("9. Exit\n");
        printf("==========================================\n");
        printf("Enter choice (1-9): ");
        if (scanf("%d", &ch) != 1) return;
        while(getchar() != '\n');

        switch(ch) {
            case 1: addExpense(); break;
            case 2: viewLinkedList(); break;
            case 3: deleteExpense(); break;
            case 4: undoDelete(); break;
            case 5: searchCategory(); break;
            case 6:
                printf("Enter your monthly budget limit: ");
                scanf("%f", &limit);
                while(getchar() != '\n');
                checkLimit();
                break;
            case 7:
                printf("\nExpenses in sorted order:\n");
                inorder(root);
                break;
            case 8: categorySpendingPercentage(); break;
            case 9: break;
            default: printf("\nInvalid choice!\n");
        }
    } while(ch != 9);
}
