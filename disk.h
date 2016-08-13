#ifndef DISK_H
#define DISK_H
#include "particion.h"


typedef struct part{
    char status;
    char type;
    char fit;
    int start;
    int size;
    char name[16];
}part;



typedef struct MBR{
    int mbr_tamano;
    char fecha_creacion[15];
    int mbr_signature;
    part particiones[4];
}MBR;


typedef struct EBR{
    char status;
    char fit;
    int start;
    int size;
    int next;
    char name[16];
}EBR;

extern void crearParticiones(int size, char* ruta, char* name, char* unit, char* type, char* fit);
extern void formatearParticion(char* name, char* path, char* tipo);
extern int tamDisco(char* ruta);
extern int byteStartLogica(char* ruta);



#endif // DISK_H
