#ifndef EXPENSE_H
#define EXPENSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100

struct Expense {
    int id;
    char date[15];
    char category[20];
    float amount;
    char description[100];
};

struct Node {
    struct Expense data;
    struct Node* next;
};

struct Stack {
    struct Expense arr[MAX];
    int top;
};

struct TreeNode {
    struct Expense data;
    struct TreeNode* left;
    struct TreeNode* right;
};

/* Globals (extern) */
extern struct Expense expenses[MAX];
extern int count;
extern int id_counter;
extern float limit;

extern struct Node* head;
extern struct Stack undoStack;
extern struct TreeNode* root;

/* Per-user data file (extern) */
extern char dataFile[128];

/* Stack */
void initStack();
void push(struct Expense e);
struct Expense pop();
int isStackEmpty();

/* Linked List */
void addToLinkedList(struct Expense e);
void deleteFromLinkedList(int id);
void viewLinkedList();

/* BST */
struct TreeNode* insertBST(struct TreeNode* root, struct Expense e);
struct TreeNode* deleteBST(struct TreeNode* root, int id);
struct TreeNode* findMin(struct TreeNode* node);
void inorder(struct TreeNode* root);

/* File */
void saveToFile();
void loadFromFile();

/* Helpers */
void getDateInput(char *date);
void getAmount(float *amount);

/* Expense ops */
void addExpense();
void deleteExpense();
void undoDelete();
void searchCategory();
void checkLimit();
void categorySpendingPercentage();

#endif
