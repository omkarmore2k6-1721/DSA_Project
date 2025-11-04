#include "expense.h"

void initStack() { undoStack.top = -1; }

void push(struct Expense e) {
    if (undoStack.top < MAX - 1) undoStack.arr[++undoStack.top] = e;
}

struct Expense pop() {
    if (undoStack.top >= 0) return undoStack.arr[undoStack.top--];
    struct Expense empty = (struct Expense){0};
    return empty;
}

int isStackEmpty() { return undoStack.top == -1; }
