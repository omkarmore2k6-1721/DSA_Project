#include "expense.h"

void addExpense() {
    if(count>=MAX){ 
        printf("Memory full!\n"); 
        return; 
    }

    struct Expense e;
    e.id = id_counter++;
    getDateInput(e.date);

    int catChoice;
    printf("\nSelect Category: \n1.Food \n2.Travel \n3.Shopping \n4.Entertainment \n5.Other\nEnter: ");
    scanf("%d", &catChoice);
    while(getchar()!='\n');

    switch(catChoice){
        case 1: strcpy(e.category,"Food"); break;
        case 2: strcpy(e.category,"Travel"); break;
        case 3: strcpy(e.category,"Shopping"); break;
        case 4: strcpy(e.category,"Entertainment"); break;
        case 5: strcpy(e.category,"Other"); break;
        default: strcpy(e.category,"Uncategorized");
    }

    getAmount(&e.amount);

    printf("Enter Description: ");
    fgets(e.description,sizeof(e.description),stdin);
    e.description[strcspn(e.description,"\n")]=0;

    expenses[count++]=e;
    addToLinkedList(e);
    root=insertBST(root,e);

    printf("Expense Added Successfully!\n");
    saveToFile();
}

void deleteExpense() {
    //printf("All expenses\n");
    viewLinkedList();
    int id;
    printf("Enter ID to delete: ");
    scanf("%d",&id); while(getchar()!='\n');

    int found=0;
    for(int i=0;i<count;i++){
        if(expenses[i].id==id){
            push(expenses[i]);
            deleteFromLinkedList(id);
            root=deleteBST(root,id);
            for(int j=i;j<count-1;j++) expenses[j]=expenses[j+1];
            count--;
            found=1;
            printf("Deleted! You can Undo.\n");
            saveToFile();
            break;
        }
    }
    if(!found) printf("Expense not found.\n");
}

void undoDelete() {
    if(isStackEmpty()){ 
        printf("No undo available!\n"); 
        return; 
    }
    struct Expense e = pop();
    expenses[count++]=e;
    addToLinkedList(e);
    root=insertBST(root,e);
    saveToFile();
    printf("Undo successful!\n");
}

void searchCategory() {
    int choice;
    char cat[20];

    printf("\nSelect a category to search:\n");
    printf("1. Food\n");
    printf("2. Travel\n");
    printf("3. Shopping\n");
    printf("4. Entertainment\n");
    printf("5. Other\n");
    printf("Enter your choice (1-5): ");
    scanf("%d", &choice);
    while (getchar() != '\n'); // clear input buffer

    switch (choice) {
        case 1: strcpy(cat, "Food"); break;
        case 2: strcpy(cat, "Travel"); break;
        case 3: strcpy(cat, "Shopping"); break;
        case 4: strcpy(cat, "Entertainment"); break;
        case 5: strcpy(cat, "Other"); break;
        default:
            printf("Invalid choice!\n");
            return;
    }

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(expenses[i].category, cat) == 0) {
            printf("ID:%d | %.2f | %s | %s\n",
                   expenses[i].id, expenses[i].amount, expenses[i].date, expenses[i].description);
            found = 1;
        }
    }
    if (!found)
        printf("No record found in '%s'.\n", cat);
}


void checkLimit() {
    float total=0;
    for(int i=0;i<count;i++) total+=expenses[i].amount;
    if(total>limit) printf(" Warning! Exceeded limit %.2f\n", limit);
    else printf(" Within limit. Remaining: %.2f\n", limit-total);
}

void categorySpendingPercentage() {
    if(count==0){
        printf("No expenses to analyze.\n"); 
        return; 
    }
    float total=0,food=0,travel=0,shopping=0,entertainment=0,other=0;

    for(int i=0;i<count;i++){
        total+=expenses[i].amount;
        if(strcmp(expenses[i].category,"Food")==0) 
        food+=expenses[i].amount;
        else if(strcmp(expenses[i].category,"Travel")==0) 
        travel+=expenses[i].amount;
        else if(strcmp(expenses[i].category,"Shopping")==0) 
        shopping+=expenses[i].amount;
        else if(strcmp(expenses[i].category,"Entertainment")==0) 
        entertainment+=expenses[i].amount;
        else 
        other+=expenses[i].amount;
    }
    printf("\n--- Category Spending ---\n");
    printf("Food         : %.2f%%\n",(food/total)*100);
    printf("Travel       : %.2f%%\n",(travel/total)*100);
    printf("Shopping     : %.2f%%\n",(shopping/total)*100);
    printf("Entertainment: %.2f%%\n",(entertainment/total)*100);
    printf("Other        : %.2f%%\n",(other/total)*100);
    printf("Total        : %.2f\n",total);
}
