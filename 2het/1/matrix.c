#include "matrix.h"

void init_identity_matrix(Matrix* m) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            m->data[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

void multiply_matrices(const Matrix* a, const Matrix* b, Matrix* result) {
    Matrix tempResult;
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            tempResult.data[i][j] = 0.0f;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                tempResult.data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result->data[i][j] = tempResult.data[i][j];
        }
    }
}

void scalar_multiply_matrix(Matrix* m, float scalar) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            m->data[i][j] *= scalar;
        }
    }
}


void transform_point(const Matrix* m, float* x, float* y) {
    float tempX = *x * m->data[0][0] + *y * m->data[0][1] + m->data[0][2];
    float tempY = *x * m->data[1][0] + *y * m->data[1][1] + m->data[1][2];
    *x = tempX;
    *y = tempY;
}

void scale(Matrix* m, float scaleX, float scaleY) {
    Matrix scaleMatrix;
    init_identity_matrix(&scaleMatrix);
    scaleMatrix.data[0][0] = scaleX;
    scaleMatrix.data[1][1] = scaleY;
    Matrix temp;
    multiply_matrices(&scaleMatrix, m, &temp);
    *m = temp;
}

void shift(Matrix* m, float shiftX, float shiftY) {
    Matrix shiftMatrix;
    init_identity_matrix(&shiftMatrix);
    shiftMatrix.data[0][2] = shiftX;
    shiftMatrix.data[1][2] = shiftY;
    multiply_matrices(&shiftMatrix, m, m);
}

void rotate(Matrix* m, float angle) {
    Matrix rotateMatrix;
    init_identity_matrix(&rotateMatrix);
    float rad = angle * M_PI / 180.0f;
    rotateMatrix.data[0][0] = cos(rad);
    rotateMatrix.data[0][1] = -sin(rad);
    rotateMatrix.data[1][0] = sin(rad);
    rotateMatrix.data[1][1] = cos(rad);
    multiply_matrices(&rotateMatrix, m, m);
}