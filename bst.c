#include <stdlib.h>
#include <stdio.h>
#include "expense.h"

struct TreeNode* insertBST(struct TreeNode* root, struct Expense e) {
    if (!root) {
        struct TreeNode* n = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        n->data = e; n->left = n->right = NULL; return n;
    }
    if (e.amount < root->data.amount) root->left = insertBST(root->left, e);
    else root->right = insertBST(root->right, e);
    return root;
}

struct TreeNode* findMin(struct TreeNode* node) {
    while (node && node->left) node = node->left;
    return node;
}

struct TreeNode* deleteBST(struct TreeNode* root, int id) {
    if (!root) return NULL;
    if (id < root->data.id) root->left = deleteBST(root->left, id);
    else if (id > root->data.id) root->right = deleteBST(root->right, id);
    else {
        if (!root->left) { struct TreeNode* r = root->right; free(root); return r; }
        if (!root->right){ struct TreeNode* l = root->left;  free(root); return l; }
        struct TreeNode* t = findMin(root->right);
        root->data = t->data;
        root->right = deleteBST(root->right, t->data.id);
    }
    return root;
}

void inorder(struct TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    printf("ID:%d | Amount: %.2f | Category: %s | Date: %s\n",
           root->data.id, root->data.amount, root->data.category, root->data.date);
    inorder(root->right);
}
