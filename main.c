//------------------------------------------------------------------------------
// main.cpp - содержит главную функцию, 
// обеспечивающую простое тестирование
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> // для функций rand() и srand()
#include <time.h>   // для функции time()
#include <string.h>

#include "inrnd.c"

void errMessage1() {
    printf("incorrect command line!\n"
           "  Waited:\n"
           "     command -f infile outfile01 outfile02\n"
           "  Or:\n"
           "     command -n number outfile01 outfile02\n");
}

void errMessage2() {
    printf("incorrect qualifier value!\n"
           "  Waited:\n"
           "     command -f infile outfile01 outfile02\n"
           "  Or:\n"
           "     command -n number outfile01 outfile02\n");
}

//------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    // Массив используемый для хранения данных
    unsigned char cont[maxSize];
    // Количество элементов в массиве
    int len = 0;

    if (argc != 5) {
        errMessage1();
        return 1;
    }

    printf("Start\n");

    if (!strcmp(argv[1], "-f")) {
        FILE *ifst = fopen(argv[2], "r");
        InContainer(cont, &len, ifst);
    } else if (!strcmp(argv[1], "-n")) {
        int size = atoi(argv[2]);
        if ((size < 1) || (size > 10000)) {
            printf("incorrect numer of figures = %d. Set 0 < number <= 10000\n",
                   size);
            return 3;
        }
        InRndContainer(cont, &len, size);
    } else {
        errMessage2();
        return 2;
    }

    FILE *ofst1 = fopen(argv[3], "w");
    fprintf(ofst1, "Filled container:\n");
    OutContainer(cont, len, ofst1);
    fclose(ofst1);

    FILE *ofst2 = fopen(argv[4], "w");
    clock_t start = clock();
    ShellSort(cont, len);
    OutContainer(cont, len, ofst2);
    fclose(ofst2);

    printf("Stop\n");
    return 0;
}
