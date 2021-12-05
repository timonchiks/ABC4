#include <stdio.h>

int CompareValue(void *pVoid);

// Ввод параметров прямоугольника из файла
void InFunctional(void *f, FILE *ifst) {
    char typing_type[20];
    fscanf(ifst, "name: %s\n""date: %i\n""popularity: %lf\n""type: %s\n",
           f, f + 32 * sizeof(char), f + 32 * sizeof(char) + sizeof(int), typing_type);
    int *ptr = (int *) (f + 32 * sizeof(char) + sizeof(int) + sizeof(double));
    if (*typing_type == 'D') {
        *ptr = 1;
    } else if (*typing_type == 'S') {
        *ptr = 2;
    } else {
        printf("ERROR%s\n", typing_type);
    }
}

void OutFunctional(void *f, FILE *ofst) {
    char *typing_type;
    int *typing = (int *) (f + 32 * sizeof(char) + sizeof(int) + sizeof(double));
    if (*typing == 1) {
        typing_type = "1";
    } else if (*typing == 2) {
        typing_type = "2";
    }
    fprintf(ofst,
            "functional:\n name: %s\n creation_date: %i\n popularity: %lf\n typing_type: %s\n compare_value: %lf\n",
            (char *) f, *(int *) (f + 32 * sizeof(char)), *(double *) (f + 32 * sizeof(char) + sizeof(int)),
            typing_type, CompareValue(f));
}