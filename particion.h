#ifndef PARTICIONES_H
#define PARTICIONES_H
#include "disk.h"

typedef struct discos{
    char path[100];
    char letra;
    char numero;
}discos;

typedef struct particiones{
    char id[10];
    char path[150];
    char name[50];
    int estado;
}particiones;

extern particiones ExisteParticion(char* id);

#endif // PARTICIONES_H
