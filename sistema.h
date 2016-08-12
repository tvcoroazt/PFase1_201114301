#ifndef SISTEMA_H
#define SISTEMA_H
#include "disk.h"

typedef struct superblok{
char cant_b[10];
char cant_ino[10];
char tama_b[6];
char firma_dd[10];
char bloques_lib[10];
char inodos_lib[10];
char fecha_mont[20];
char fecha_desmont[20];
char cant_montage[5];
char apuntador_inicio[10];
char apuntador_bloque[10];
char apuntador_bitacora[10];
char apuntador_raiz[10];
char apuntador_bloq[10];
char primer_ino_lib[10];
char primer_bit_inodo[10];
char primer_bit_bloq[10];
char cant_bita[10];

}super_b;

typedef struct superbloque{
    int arbol_virtual_count;
    int detalle_directorio_count;
    int inodos_count;
    int bloques_count;
    int free_arbol_virtual_count;
    int free_detalle_directorio_count;
    int free_bloques_count;
    int free_inodes_count;
    char rntime[15];
    char untime[15];
    int magic;
    int avd_size;
    int detalle_directorio_size;
    int inode_size;
    int block_size;
    int ap_avd;
    int ap_bitmap_avd;
    int ap_bitmap_detalle_directorio;
    int ap_table_inodo;
    int ap_bitmap_tabla_inodo;
    int ap_bloque;
    int ap_bitmap_inodo;
    int ap_log;
    int ap_copia_superbloque;
    int first_free_bit_avd;
    int first_free_bit_detalle_directorio;
    int first_free_bit_tabla_inodo;
    int first_free_bit_bloques;
}superbloque;

typedef struct arbolavd {
    char avd_fecha[40];
    char avd_name[16];
    int avd_array_subd[16];
    int avd_detalle;
    int avd_ap_avd;

}arbolavd;



typedef struct archive{
    char file_nombre[16];
    int app_inodo;
    char file_date_creation[30];
    char file_date_modification[30];

}archive;

typedef struct detalledirectorio {
    archive archivo1;
    archive archivo2;
    archive archivo3;
    archive archivo4;
    int dd_ap_detalledirectorio;

}detalledirectorio;

typedef struct inodo{
    int count_inodo;
    int size_file;
    int count_bloques_asig;
    int array_bloques[4];
    int ap_directorio;

}inodo;

typedef struct bloquedatos{
    char data[30];
 }bloquedatos;



#endif // SISTEMA_H
