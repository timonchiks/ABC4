#include <stdio.h>

int CompareValue(void *pVoid);


void InProcedural(void *p, FILE *ifst) {
    fscanf(ifst, "name: %s\n creation_date: %i\n popularity: %lf\n has_adt: %i\n",
           p, p + 32 * sizeof(char), p + 32 * sizeof(char) + sizeof(int),
           p + 32 * sizeof(char) + sizeof(int) + sizeof(double));
}


void OutProcedural(void *p, FILE *ofst) {
    fprintf(ofst, "procedural language:\n name: %s\n creation_date: %i\n popularity: %lf\n has_adt: %i\n compare_value: %lf\n",
            ((char *) p), *(int *) (p + 32 * sizeof(char)), *(double *) (p + 32 * sizeof(char) + sizeof(int)),
            *(int *) (p + 32 * sizeof(char) + sizeof(int) + sizeof(double)), CompareValue(p));
}