#include "matrix.c"

int main() {
    Matrix m;
    float x = 1.0f, y = 2.0f;

    init_identity_matrix(&m);
    printf("Unit matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%f ", m.data[i][j]);
        }
        printf("\n");
    }

    scale(&m, 2.0f, 3.0f);
    printf("\nScaled matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%f ", m.data[i][j]);
        }
        printf("\n");
    }
    
    shift(&m, 1.0f, 1.0f);
    printf("\nOffset matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%f ", m.data[i][j]);
        }
        printf("\n");
    }

    rotate(&m, 90.0f); 
    printf("\nRotated matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%f ", m.data[i][j]);
        }
        printf("\n");
    }

    transform_point(&m, &x, &y);
    printf("\nTransformed point: (%f, %f)\n", x, y);

    return 0;
}