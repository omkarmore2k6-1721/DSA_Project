#include <stdio.h>
#include <time.h>
#include "expense.h"

void getDateInput(char *date) {
    int choice;
    time_t t;
    struct tm tm;
    printf("\nSelect Date Option:\n1. Today\n2. Yesterday\n3. Enter manually\nEnter choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');

    if (choice == 1) {
        t = time(NULL);
        tm = *localtime(&t);
        sprintf(date, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    } else if (choice == 2) {
        t = time(NULL) - 86400;
        tm = *localtime(&t);
        sprintf(date, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    } else if (choice == 3) {
        printf("Enter Date (DD-MM-YYYY): ");
        scanf("%14s", date);
        while(getchar() != '\n');
    } else {
        t = time(NULL);
        tm = *localtime(&t);
        sprintf(date, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    }
}

void getAmount(float *amount) {
    int choice;
    do {
        printf("\nSelect Amount: 1.100 \n2.500 \n3.1000 \n4.Other\nEnter: ");
        if (scanf("%d", &choice) != 1) { 
            while(getchar() != '\n');
             continue;
         }
        while(getchar() != '\n');

        switch(choice) {
            case 1: *amount = 100; break;
            case 2: *amount = 500; break;
            case 3: *amount = 1000; break;
            case 4:
                do {
                    printf("Enter Amount: ");
                    if (scanf("%f", amount) != 1 || *amount <= 0) { 
                        while(getchar() != '\n'); continue; }
                    break;
                } while(1);
                while(getchar() != '\n');
                break;
            default: continue;
        }
        break;
    } while(1);
    *amount = ((int)(*amount * 100 + 0.5)) / 100.0;
}
