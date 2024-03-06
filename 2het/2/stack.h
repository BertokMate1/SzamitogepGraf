#ifndef STACK_H
#define STACK_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    float matrix[4][4];
} Matrix;

typedef struct {
    Matrix data[MAX_SIZE];
    int top;
} MatrixStack;

void initStack(MatrixStack *stack);

void push_matrix(MatrixStack *stack, Matrix item);

Matrix pop_matrix(MatrixStack *stack);

void print_matrix(Matrix matrix);

void print_stack(MatrixStack stack);


#endif //STACK_H