#include <stdio.h>

int CompareValue(void *pVoid);

void ObjIn(void *o, FILE *ifst) {
    char inheritance_type[20];
    fscanf(ifst, "name: %s\n creation_date: %i\n popularity: %lf\n nheritance_type: %s\n",
           o, o + 32 * sizeof(char), o + 32 * sizeof(char) + sizeof(int), inheritance_type);
    int *ptr = (int *) (o + 32 * sizeof(char) + sizeof(int) + sizeof(double));
    if (*inheritance_type == 'I') {
        *ptr = 1;
    } else if (*inheritance_type == 'S') {
        *ptr = 2;
    } else if (*inheritance_type == 'M') {
        *ptr = 3;
    } else {
        printf("ERROR %s\n", inheritance_type);
    }
}

void ObjOut(void *o, FILE *ofst) {
    char *inheritance_type;
    int *inheritance = (int *) (o + 32 * sizeof(char) + sizeof(int) + sizeof(double));
    if (*inheritance == 1) {
        inheritance_type = "INTERFACE";
    } else if (*inheritance == 2) {
        inheritance_type = "SINGLE";
    } else if (*inheritance == 3) {
        inheritance_type = "MULTIPLE";
    }
    fprintf(ofst,
            "object_oriented language:\n name: %s\n creation_date: %i\n popularity: %lf\n inheritance_type: %s\n compare_value: %d\n",
            (char *) o, *(int *) (o + 32 * sizeof(char)), *(double *) (o + 32 * sizeof(char) + sizeof(int)),
            inheritance_type, CompareValue(o));
}
