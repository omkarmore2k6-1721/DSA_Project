#include <stdio.h>
#include <stdlib.h>
#include "expense.h"

void addToLinkedList(struct Expense e) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = e;
    newNode->next = head;
    head = newNode;
}

void deleteFromLinkedList(int id) {
    struct Node* temp = head;
    struct Node* prev = NULL;
    while (temp != NULL && temp->data.id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (!temp) return;
    if (!prev) head = head->next;
    else prev->next = temp->next;
    free(temp);
}

void viewLinkedList() {
    struct Node* temp = head;
    if (!temp) {
        printf("\nNo expenses.\n");
        return;
    }
    printf("\n------ Expense List ------\n");
    while (temp) {
        printf("ID:%d | %s | %s | %.2f | %s\n",
               temp->data.id, temp->data.date, temp->data.category,
               temp->data.amount, temp->data.description);
        temp = temp->next;
    }
}
