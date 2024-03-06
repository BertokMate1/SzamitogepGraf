#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <math.h>

#define MATRIX_SIZE 3
#define M_PI 3.14159265358979323846

typedef struct {
    float data[MATRIX_SIZE][MATRIX_SIZE];
} Matrix;

void init_zero_matrix(float matrix[3][3]);

void print_matrix(const float matrix[3][3]);

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

void init_identity_matrix(Matrix* m);

void multiply_matrices(const Matrix* a, const Matrix* b, Matrix* result);

void scalar_multiply_matrix(Matrix* m, float scalar);

void transform_point(const Matrix* m, float* x, float* y);

void scale(Matrix* m, float scaleX, float scaleY);

void shift(Matrix* m, float shiftX, float shiftY);

void rotate(Matrix* m, float angle);

#endif // MATRIX_H


