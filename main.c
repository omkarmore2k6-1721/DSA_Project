#include <stdio.h>
#include "expense.h"

// Globals
struct Expense expenses[MAX];
int count = 0;
int id_counter = 1;
float limit = 10000;

struct Node* head = NULL;
struct Stack undoStack;
struct TreeNode* root = NULL;

int main() {
    int ch;
    initStack();
    loadFromFile(); // load saved expenses at start

    do {
        printf("\n=========== Expense Manager ===========\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses (Linked List)\n");
        printf("3. Delete Expense\n");
        printf("4. Undo Delete (Stack)\n");
        printf("5. Search by Category\n");
        printf("6. Check Budget Limit\n");
        printf("7. View Sorted Expenses (BST - Inorder)\n");
        printf("8. CategorySpendingPercentage\n");
        printf("9. Exit\n");
        printf("==========================================\n");
        printf("Enter choice (1-9): ");
        scanf("%d", &ch);
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
                checkLimit();
                break;
            case 7:
                printf("\nExpenses in sorted order:\n");
                inorder(root);
                break;
            case 8: categorySpendingPercentage(); break;
            case 9:
                printf("\nSaving data before exit...\n");
                saveToFile();
                printf("Data saved successfully. Exiting...\n");
                break;
            default: printf("\nInvalid choice!\n");
        }
    } while(ch != 9);

    return 0;
}
