#include <stdio.h>

#include "Language.c"

void InContainer(void *c, int *len, FILE *ifst);
// Случайный ввод содержимого контейнера
void InRndContainer(void *c, int *len, int size);
// Вывод содержимого контейнера в файл
void OutContainer(void *c, int len, FILE *ofst);
// Вычисление суммы периметров всех фигур в контейнере
extern void ShellSort(void *c, int len);
//extern double CompareValue(void *l);

// Ввод содержимого контейнера из указанного файла
void InContainer(void *c, int *len, FILE *ifst) {
    void *tmp = c;
    while(!feof(ifst)) {
        if(InLanguage(tmp, ifst)) {
            tmp = tmp + sizeof(int) + 30 * sizeof(char) + sizeof(int) + sizeof(double) + sizeof(int);;
            (*len)++;
        }
    }
}

// Вывод содержимого контейнера в файл
void OutContainer(void *c, int len, FILE *ofst) {
    void *tmp = c;
    fprintf(ofst, "Container contains %d elements.\n", len);
    for(int i = 0; i < len; i++) {
        fprintf(ofst, "%d: ", i);
        OutLanguage(tmp, ofst);
        tmp = tmp + sizeof(int) + 30 * sizeof(char) + sizeof(int) + sizeof(double) + sizeof(int);;
    }
}