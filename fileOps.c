#include <stdio.h>
#include "expense.h"

void saveToFile() {
    FILE *fp = fopen("expenses.txt", "w");

    if(!fp) { 
        printf("Error saving file!\n"); 
        return; 
    }

    fprintf(fp, "%-5s %-12s %-15s %-10s %-s\n", "ID", "DATE", "CATEGORY", "AMOUNT", "DESCRIPTION");// %-5s is for allocating 5 chars space.
    fprintf(fp, "---------------------------------------------------------------\n");

    struct Node* temp = head;
    while(temp) {
        fprintf(fp, "%-5d %-12s %-15s %-10.2f %-s\n",
            temp->data.id, temp->data.date, temp->data.category,
            temp->data.amount, temp->data.description);
        temp = temp->next;
    }
    fclose(fp);
}

void loadFromFile() {
    FILE *fp = fopen("expenses.txt", "r");
    if(!fp) return;

    char line[256];
    struct Expense e;

    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    while(fgets(line, sizeof(line), fp)) {
        if(sscanf(line, "%d %s %s %f %[^\n]", &e.id, e.date, e.category, &e.amount, e.description) == 5) {
            expenses[count++] = e;
            addToLinkedList(e);
            root = insertBST(root, e);
            if(e.id >= id_counter) id_counter = e.id + 1;
        }
    }
    fclose(fp);
}
