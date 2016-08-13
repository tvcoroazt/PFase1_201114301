#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sistema.h"


void crearBloque(char* id, char* type){
    int byteInicio;
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);// struct para la hora y fec
    // strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
    MBR mbr;

    int  aux_op=0;  //auxiliar para las operacions de aputadores
    int  aux2_op=0; // auxliar para las operaciones de inodo y log bloques


    particiones parti;
    parti = ExisteParticion(id);

    part particion;
    superbloque sb;

    inodo inod;
    arbolavd avd;


    if(strcmp(parti.path,"null")==0) {
        printf("\n X- Aun no existe Particion Montada -X\n");
    }else{


        FILE* disco;
        disco = fopen(parti.path,"r");
        if(disco==NULL){
            printf("X - ERROR no existe el disco - X");
        }
        else{
            fseek(disco,0,SEEK_SET);
            fread(&mbr,sizeof(mbr),1,disco);

            printf("Size: %i  \n",particion.size);
            printf("Star: %i  \n", particion.start);

            printf("%s", parti.path);

            int n;
            n= particion.size-2*(sb.block_size)/(sb.avd_size+sb.detalle_directorio_size+sb.block_size+sb.inode_size+5)-1;


            printf("letra N: %i",n);

            sb.arbol_virtual_count = n;
            sb.detalle_directorio_count = n+particion.size;
            strftime(sb.rntime,15,"%d/%m/%y %H:%M",tlocal);
            strftime(sb.untime,15,"%d/%m/%y %H:%M",tlocal);
            sb.inodos_count=n;
            sb.magic=201114301;
            sb.avd_size=particion.start;
            sb.detalle_directorio_size=0;

            sb.ap_bitmap_avd=particion.start+particion.size;
            sb.ap_bitmap_detalle_directorio=sb.ap_bitmap_avd;

            sb.first_free_bit_avd=1;
            sb.first_free_bit_detalle_directorio=1;
            sb.first_free_bit_tabla_inodo=0;
            sb.first_free_bit_bloques=0;

            aux2_op= particion.size*0.60;
            aux2_op= aux2_op/130;



            //CREACION DEL CARPETA RAIZ /

          //  aux2_op= atoi(sb.ap_bitmap_inodo);

          //  fseek(disco,aux2_op,0);
          //  fprintf(disco,"1");
          //  aux2_op= atoi(sb.ap_bloque);//escritura al bitmap de bloques
          //  fseek(disco,aux2_op,0);
          //  fprintf(disco,"1");

            inod.count_inodo=1;
            inod.size_file=0;
            inod.count_bloques_asig=1;

            strftime(avd.avd_fecha,15,"%d/%m/%y %H:%M",tlocal);


        }

        fclose(disco);

    }



}


