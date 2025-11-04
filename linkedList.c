#include <stdio.h>
#include <stdlib.h>
#include "expense.h"

void addToLinkedList(struct Expense e) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->data = e; 
    n->next = head; 
    head = n;
}

void deleteFromLinkedList(int id) {
    struct Node* t = head; struct Node* p = NULL;
    while (t && t->data.id != id) { 
        p = t; 
        t = t->next; 
    }
    if (!t) return;
    if (!p) head = head->next; 
    else p->next = t->next;
    free(t);
}

void viewLinkedList() {
    struct Node* t = head;
    if (!t) { 
        printf("\nNo expenses.\n"); 
        return;
     }
    printf("\n------ Expense List ------\n");
    while (t) {
        printf("ID:%d | %s | %s | %.2f | %s\n",
               t->data.id, t->data.date, t->data.category,
               t->data.amount, t->data.description);
        t = t->next;
    }
}
