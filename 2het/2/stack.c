#include "stack.h"

void initStack(MatrixStack *stack) {
    stack->top = -1;
}

void push_matrix(MatrixStack *stack, Matrix item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("The stack is full!\n");
        return;
    }
    stack->data[++stack->top] = item;
}

Matrix pop_matrix(MatrixStack *stack) {
    if (stack->top == -1) {
        printf("The stack is empty!\n");
        exit(EXIT_FAILURE);
    }
    return stack->data[stack->top--];
}

void print_matrix(Matrix matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%.2f\t", matrix.matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_stack(MatrixStack stack) {
    printf("Content of the stack:\n");
    for (int i = 0; i <= stack.top; ++i) {
        printf("Matrix %d:\n", i + 1);
        print_matrix(stack.data[i]);
    }
}
