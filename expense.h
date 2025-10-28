//Header file
#ifndef EXPENSE_H
#define EXPENSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

// Expense structure
struct Expense {
    int id;
    char date[15];
    char category[20];
    float amount;
    char description[100];
};

// Linked list node
struct Node {
    struct Expense data;
    struct Node* next;
};

// Stack for undo
struct Stack {
    struct Expense arr[MAX];
    int top;
};

// BST node
struct TreeNode {
    struct Expense data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Global variables
extern struct Expense expenses[MAX];
extern int count;
extern int id_counter;
extern float limit;

extern struct Node* head;
extern struct Stack undoStack;
extern struct TreeNode* root;

// Stack functions
void initStack();
void push(struct Expense e);
struct Expense pop();
int isStackEmpty();

// Linked List functions
void addToLinkedList(struct Expense e);
void deleteFromLinkedList(int id);
void viewLinkedList();

// BST functions
struct TreeNode* insertBST(struct TreeNode* root, struct Expense e);
struct TreeNode* deleteBST(struct TreeNode* root, int id);
struct TreeNode* findMin(struct TreeNode* node);
void inorder(struct TreeNode* root);

// File functions
void saveToFile();
void loadFromFile();

// Helper functions
void getDateInput(char *date);
void getAmount(float *amount);

// Expense operations
void addExpense();
void deleteExpense();
void undoDelete();
void searchCategory();
void checkLimit();
void categorySpendingPercentage();

#endif
