#include <stdio.h>
#include <string.h>
#include "expense.h"

/* No globals or main here */

void addExpense() {
    if (count >= MAX) { printf("Memory full!\n"); return; }
    struct Expense e; e.id = id_counter++;

    getDateInput(e.date);

    int catChoice;
    printf("\nSelect Category:\n1. Food\n2. Travel\n3. Shopping\n4. Entertainment\n5. Other\nEnter choice (1-5): ");
    scanf("%d", &catChoice);
    while (getchar() != '\n');
    switch (catChoice) {
        case 1: strcpy(e.category, "Food"); break;
        case 2: strcpy(e.category, "Travel"); break;
        case 3: strcpy(e.category, "Shopping"); break;
        case 4: strcpy(e.category, "Entertainment"); break;
        case 5: strcpy(e.category, "Other"); break;
        default: strcpy(e.category, "Uncategorized");
    }

    getAmount(&e.amount);

    printf("Enter Description: ");
    fgets(e.description, sizeof(e.description), stdin);
    e.description[strcspn(e.description, "\n")] = 0;

    expenses[count++] = e;
    addToLinkedList(e);
    root = insertBST(root, e);

    printf("Expense Added Successfully!\n");
    saveToFile();
}

void deleteExpense() {
    int id;
    printf("Enter ID to delete: ");
    scanf("%d", &id);
    while (getchar() != '\n');

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (expenses[i].id == id) {
            push(expenses[i]);
            deleteFromLinkedList(id);
            root = deleteBST(root, id);
            for (int j = i; j < count - 1; j++) expenses[j] = expenses[j + 1];
            count--;
            printf("Deleted! You can Undo.\n");
            saveToFile();
            found = 1;
            break;
        }
    }
    if (!found) printf("Expense not found.\n");
}

void undoDelete() {
    if (isStackEmpty()) { printf("No undo available!\n"); return; }
    struct Expense e = pop();
    expenses[count++] = e;
    addToLinkedList(e);
    root = insertBST(root, e);
    saveToFile();
    printf("Undo successful!\n");
}

void searchCategory() {
    char cat[20];
    printf("Enter category: ");
    fgets(cat, sizeof(cat), stdin);
    cat[strcspn(cat, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(expenses[i].category, cat) == 0) {
            printf("ID:%d | %.2f | %s | %s\n",
                   expenses[i].id, expenses[i].amount, expenses[i].date, expenses[i].description);
            found = 1;
        }
    }
    if (!found) printf("No record found.\n");
}

void checkLimit() {
    float total = 0;
    for (int i = 0; i < count; i++) total += expenses[i].amount;
    if (total > limit)
        printf(" Warning! You've exceeded your limit of %.2f\n", limit);
    else
        printf(" Within your limit. Remaining: %.2f\n", limit - total);
}

void categorySpendingPercentage() {
    if (count == 0) { printf("No expenses to analyze.\n"); return; }

    float total = 0, food=0, travel=0, shopping=0, entertainment=0, other=0;
    for (int i = 0; i < count; i++) {
        total += expenses[i].amount;
        if      (strcmp(expenses[i].category, "Food") == 0)          food += expenses[i].amount;
        else if (strcmp(expenses[i].category, "Travel") == 0)        travel += expenses[i].amount;
        else if (strcmp(expenses[i].category, "Shopping") == 0)      shopping += expenses[i].amount;
        else if (strcmp(expenses[i].category, "Entertainment") == 0) entertainment += expenses[i].amount;
        else                                                          other += expenses[i].amount;
    }

    printf("\n--- Category Spending Percentage ---\n");
    printf("Food         : %.2f%%\n", (food/total)*100);
    printf("Travel       : %.2f%%\n", (travel/total)*100);
    printf("Shopping     : %.2f%%\n", (shopping/total)*100);
    printf("Entertainment: %.2f%%\n", (entertainment/total)*100);
    printf("Other        : %.2f%%\n", (other/total)*100);
    printf("Total        : %.2f\n", total);
}
