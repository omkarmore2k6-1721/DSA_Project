#include <stdio.h>
#include "expense.h"

void saveToFile() {
    FILE *fp = fopen(dataFile, "w");
    if (!fp) { printf("Error saving file!\n"); return; }

    fprintf(fp, "%-5s %-12s %-15s %-10s %-s\n",
            "ID", "DATE", "CATEGORY", "AMOUNT", "DESCRIPTION");
    fprintf(fp, "---------------------------------------------------------------\n");

    struct Node* t = head;
    while (t) {
        fprintf(fp, "%-5d %-12s %-15s %-10.2f %-s\n",
                t->data.id, t->data.date, t->data.category,
                t->data.amount, t->data.description);
        t = t->next;
    }
    fclose(fp);
}

void loadFromFile() {
    FILE *fp = fopen(dataFile, "r");
    if (!fp) return;

    char line[256];
    struct Expense e;

    fgets(line, sizeof(line), fp);
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%d %14s %19s %f %[^\n]",
                   &e.id, e.date, e.category, &e.amount, e.description) == 5) {
            expenses[count++] = e;
            addToLinkedList(e);
            root = insertBST(root, e);
            if (e.id >= id_counter) id_counter = e.id + 1;
        }
    }
    fclose(fp);
}
