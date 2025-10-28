#include <stdio.h>
#include <stdlib.h>
#include "expense.h"

struct TreeNode* insertBST(struct TreeNode* root, struct Expense e) {
    if(!root) {
        struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newNode->data = e;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if(e.amount < root->data.amount) root->left = insertBST(root->left, e);
    else root->right = insertBST(root->right, e);
    return root;
}

struct TreeNode* findMin(struct TreeNode* node) {
    while(node->left) node = node->left;
    return node;
}

struct TreeNode* deleteBST(struct TreeNode* root, int id) {
    if(!root) return NULL;
    if(id < root->data.id) root->left = deleteBST(root->left, id);
    else if(id > root->data.id) root->right = deleteBST(root->right, id);
    else {
        if(!root->left) { struct TreeNode* temp = root->right; free(root); return temp; }
        else if(!root->right) { struct TreeNode* temp = root->left; free(root); return temp; }
        struct TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteBST(root->right, temp->data.id);
    }
    return root;
}

void inorder(struct TreeNode* root) {
    if(!root) return;
    inorder(root->left);
    printf("ID:%d | Amount: %.2f | Category: %s | Date: %s\n",
        root->data.id, root->data.amount, root->data.category, root->data.date);
    inorder(root->right);
}

void preorder(struct TreeNode* root) {
    if(!root) return;
    printf("ID:%d | Amount: %.2f | Category: %s | Date: %s\n",
        root->data.id, root->data.amount, root->data.category, root->data.date);
    preorder(root->left);
    preorder(root->right);
}
