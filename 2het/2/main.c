#include "stack.c"

int main() {
    MatrixStack stack;
    initStack(&stack);

    // Először néhány példa transzformációs mátrixot hozzáadunk a veremhez
    Matrix identity = { .matrix = {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    push_matrix(&stack, identity);

    Matrix translate = { .matrix = {
        {1, 0, 0, 2},
        {0, 1, 0, 3},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    push_matrix(&stack, translate);

    Matrix rotate = { .matrix = {
        {0, 1, 0, 0},
        {-1, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
    }};
    push_matrix(&stack, rotate);

    // Kiírjuk a verem tartalmát
    print_stack(stack);

    // Most visszavonjuk az utolsó két műveletet
    printf("Undo operations:\n");
    Matrix removed1 = pop_matrix(&stack);
    printf("Deleted Matrix 1:\n");
    print_matrix(removed1);

    Matrix removed2 = pop_matrix(&stack);
    printf("Deleted Matrix 2:\n");
    print_matrix(removed2);

    // Kiírjuk a maradék mátrixot a veremben
    printf("Remaining matrixes in the stack:\n");
    print_stack(stack);

    return 0;
}