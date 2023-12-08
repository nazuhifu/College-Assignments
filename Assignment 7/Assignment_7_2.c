#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

// Struct untuk stack
struct Stack {
    int items[MAX_SIZE];
    int top;
};

// Fungsi untuk cek apakah stack kosong
int kosong (struct Stack *stack) {
    return stack->top == -1;
}

// Fungsi untuk cek apakah stack penuh
int penuh(struct Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// Fungsi untuk menambah item ke stack
void push(struct Stack *stack, int nilai) {
    if(penuh(stack)) {
        printf("Stack penuh!\n");
    } else {
        stack->top++;
        stack->items[stack->top] = nilai;
    }
}

// Fungsi untuk menghapus elemen dari stack
int pop(struct Stack *stack) {
    int nilai;

    if(kosong(stack)) {
        printf("Stack kosong!\n");
        return -1;
    } else {
        nilai = stack->items[stack->top];
        stack->top--;
        return nilai;
    }
}


// Fungsi untuk mengambil item teratas tanpa dihapus
int peek(struct Stack *stack) {
    if(kosong(stack)) {
        printf("Stack kosong!\n");
        return -1;
    } else {
        return stack->items[stack->top];
    }
}

int main() {
    struct Stack myStack;
    myStack.top = -1;

    push(&myStack, 10);
    push(&myStack, 20);
    push(&myStack, 30);

    printf("Elemen teratas: %d\n", peek(&myStack));
    printf("Elemen yang dihapus: %d\n", pop(&myStack));
    printf("Elemen teratas setelah penghapusan: %d\n", peek(&myStack));

    return 0;
}
