#include <stdio.h>

#include "Functional.c"
#include "Procedure.c"
#include "Objective.c"

// Ввод параметров обобщенного языка из файла
int InLanguage(void *s, FILE *ifst) {
    char lang_type[20];
    // считываем строку вида "<lang_type> language" и обрасываем второе слово
    fscanf(ifst, "%s%*s\n", lang_type);
    if (*(lang_type) == 'p') {
        *((int*)s) = 2;
        InProcedural(s + sizeof(int), ifst);
        return 1;
    } else if (*(lang_type) == 'f') {
        *((int*)s) = 1;
        InFunctional(s + sizeof(int), ifst);
        return 1;
    } else if (*(lang_type) == 'o') {
        *((int*)s) = 3;
        ObjIn(s + sizeof(int), ifst);
        return 1;
    } else {
        printf("ERROR %s\n", lang_type);
        return 0;
    }
}

void OutLanguage(void *s, FILE *ofst) {
    int k = *((int*)s);
    if(k == 1) {
        OutFunctional(s+sizeof(int), ofst);
    } else if (k == 2) {
        OutProcedural(s+sizeof(int), ofst);
    } else if (k == 3) {
        ObjOut(s+sizeof(int), ofst);
    } else {
        fprintf(ofst, "Incorrect figure!\n");
    }
}
