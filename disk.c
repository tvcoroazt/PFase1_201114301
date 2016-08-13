#include "disk.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



void crearDisco(int tamano, char* ruta, char* unidad){
    char control = 0;
    int sizecontrol = 0;

    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);// struct para la hora y fec
    // strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);

    MBR mbr;
    FILE* existe;
    existe = fopen(ruta,"rb");


    if (existe==NULL){
        FILE* archivo;
        archivo = fopen(ruta,"wt");

        if (archivo==NULL){
            printf("X - ERROR al crear el Disco ARCHIVO NO EXISTE - X  \n");
        }else{
            int kbyte = 1024;
            int mbyte = kbyte*kbyte;
            char babosadas[mbyte];
            char babosadas2[kbyte];
            int i;
            if(strcmp(unidad,"m ")==0){
                for(i=0; i<tamano; i++){
                    fwrite(babosadas,sizeof(babosadas),1,archivo);
                }
             //   mbr.mbr_tamano = tamano*1024*1024;
                mbr.mbr_tamano = tamano*1048576;
            }else{
                if (strcmp(unidad,"k ")==0){
                    for(i=0;i<tamano; i++){
                        fwrite(babosadas2,sizeof(babosadas2),1,archivo);
                     }
                    mbr.mbr_tamano = tamano*1024;
                }
                mbr.mbr_signature = rand() % (11+1);
            }

            for(i=0; i<4; i++){
                mbr.particiones[i].status = '0';
                mbr.particiones[i].type='0';
                mbr.particiones[i].fit='0';
                mbr.particiones[i].start=-1;
                mbr.particiones[i].size=-1;

                strftime(mbr.fecha_creacion,15,"%d/%m/%y %H:%M",tlocal);

                strcpy(mbr.particiones[i].name,"null");
            }

            //timer_t tiempo = time(0);
            //struct tm *tlocal = localtime(&tiempo);
            //mbr.fecha_creacion = time(NULL);


            fseek(archivo,0,SEEK_SET);
            fwrite(&mbr,sizeof(mbr),1,archivo);


        fclose(archivo);
        printf("\n FELICIDADES Disco creado con Exito!! \n \n ");
        }
       // fclose(archivo);
    }
    else{
        fclose(existe);
        printf("\n X - Disco no fue creado - X \n");
        printf("\n X - Existe un Disco con el mismo nombre verificar - X \n");
    }


}

int asignarTamano(char* unidad, int tamano){
    int tam = 0;
    if( (strcmp(unidad,"m")==0)  || (strcmp(unidad,"m ")==0) ){
        tam=tamano;
    }
    else
        if( (strcmp(unidad,"k")==0) || (strcmp(unidad,"k ")==0) ){
            tam=tamano*1024;
    }
    else
        if( (strcmp(unidad,"m")==0) || (strcmp(unidad,"m ")==0)  ){
            tam=tamano*1048576;
        }
    return tam;
}


void eliminarD(char* ruta){
    FILE* archivo;
    archivo = fopen(ruta,"rb");
    if(archivo == NULL){
        printf("\n X - NO existe el Disco indicado verifique - X \n");
    }else{
        fclose(archivo);
        int eliminar = remove(ruta);
        if(eliminar==0){
            printf("\n FELICIDADES Disco elimado correctamente \n \n");
        }
    }
}

int contParPrimarias(char* ruta){
    int cont=0;
    int i;
    MBR mbr;
    FILE* disco;
    disco = fopen(ruta,"r");
    if (disco==NULL){
        printf("\n X - Error disco indicado con Existe - X \n \n");
    }else{
        fseek(disco,0,SEEK_SET);
        fread(&mbr,sizeof(mbr),1,disco);
        for(i=0; i<4; i++){
            if(  (mbr.particiones[i].type=='p' && mbr.particiones[i].status=='1') || (mbr.particiones[i].type=='p ' && mbr.particiones[i].status=='1')){
            cont++;
            }
        }
        fclose(disco);
    }
    return cont;
}


int contParExtendidas(char* ruta){
    int cont=0;
    int i;
    FILE* disco;
    disco=fopen(ruta,"r");
    if(disco==NULL){
        printf("\n X - Error disco indicado con Existe - X \n \n");
    }
    else{
        MBR mbr;
        fseek(disco,0,SEEK_SET);
        fread(&mbr,sizeof(mbr),1,disco);
        for(i=0; i<4; i++){
            if( (mbr.particiones[i].type=='e' && mbr.particiones[i].status=='1') || (mbr.particiones[i].type=='e ' && mbr.particiones[i].status=='1') ){
                cont++;
            }
        }
        fclose(disco);
    }
    return cont;
}



int tamDisco(char* ruta){
    int tam=0;
    int i;
    FILE* disco;
    disco = fopen(ruta,"r");
    if(disco == NULL){
        printf("\n X - Error disco indicado con Existe - X \n \n");
    }else{
        MBR mbr;
        fseek(disco,0,SEEK_SET);
        fread(&mbr,sizeof(mbr),1,disco);
        for(i=0; i<4; i++){
            if(mbr.particiones[1].status== '1'){
                tam+=mbr.particiones[i].size;
            }
        }
        tam = mbr.mbr_tamano - tam - sizeof(mbr);
        fclose(disco);
    }
    return tam;
}

int nombre(char* ruta, char* nombre){
    int existe=0;
    int i;
    FILE* disco;
    disco = fopen(ruta,"r");
    if(disco == NULL){
        printf("\n X - Error disco indicado con Existe verificar - X \n \n");
    }else{
        MBR mbr;
        fseek(disco,0,SEEK_SET);
        fread(&mbr,sizeof(mbr),1,disco);
        for(i=0; i<4; i++){
            if(strcmp(mbr.particiones[i].name,nombre)==0){
                existe=1;
            }
        }
        fclose(disco);
    }
    return existe;
}

int inicioLogica(char* ruta){
    MBR mbr;
    int i;
    FILE* disco;
    disco = fopen(ruta,"r");
    if(disco == NULL) {
        printf("\n X - Error disco indicado con Existe verificar - X \n \n");
    }
    else{
        fseek(disco,0,SEEK_SET);
        fread(&mbr,sizeof(mbr),1,disco);
        for(i=0;i<4; i++){
            if((mbr.particiones[i].type=='e') || (mbr.particiones[i].type=='e ')){
                return mbr.particiones[i].start;
            }
        }
    }
    return -1;
}


int inicio(char* ruta, int tamParticion){
    MBR mbr;
    int i;
    int primariasCont;
    int extendidasCont;
    int inicio = sizeof(mbr);
    FILE* disco;
    disco = fopen(ruta,"r");
    if(disco == NULL) {
        printf("\n X - Error disco indicado con Existe verificar - X \n \n");
    }
    else{
        fseek(disco,0,SEEK_SET);
        fread(&mbr,sizeof(mbr),1,disco);
        primariasCont=contParPrimarias(ruta);
        extendidasCont=contParExtendidas(ruta);
        if((primariasCont+extendidasCont) ==0 ){
            return inicio;
        }
        for(i=0;i<4; i++){
            if(mbr.particiones[i].status=='1'){
                if(tamParticion<=(mbr.particiones[i].start-inicio)){
                    return inicio;
                }
                inicio = mbr.particiones[i].start + mbr.particiones[i].size;
            }
        }
        return inicio;
    }
    return -1;
}



void crearParticiones(int size, char* ruta, char* name, char* unit, char* type, char* fit){
    desfragmentar(ruta);
    if( (strcmp(type,"p")==0) || (strcmp(type,"p ")==0) ){
        printf("\n                Creando particion PRIMARIA\n");
        nuevaPartPrimaria(type,fit,size,name,unit,ruta);

       // ordenar(ruta);     //no lo utilizo porque loqueaaa
    }
    else
    if( (strcmp(type,"l")==0) || (strcmp(type,"l ")==0) ){
         printf("\n                 Creando particion LOGICA\n");
        crearParticionLogica(size,ruta,name,unit,type,fit);  //  vamos a componerlos
    }else
    if( (strcmp(type,"e")==0) || (strcmp(type,"e ")==0) ){
         printf("\n               Creando particion EXTENDIDA\n");
        crearParticonExtendida(size,ruta,name,unit,type,fit);
    }
    ordenar(ruta);
     // crearParticonExtendida(size,ruta,name,unit,fit);  //presenta algunos errrores

}



//void nuevaPartPrimaria(int size, char* ruta, char* name, char* unit, char* type, char* fit){


//}


void nuevaPartPrimaria(char* type, char* fit, int* size, char* name, char* unit, char* ruta){
    int tamParticion;
    int tamLibre;
    int existe;
    int nPrim;
    int nExt;
    int byteInicio;
    MBR mbr;
    FILE* disco;
    disco = fopen(ruta,"rb+");
    if(disco == NULL) {
        printf("\n X - Error disco indicado con Existe verificar - X \n \n");
    }
    else{
        tamParticion = asignarTamano(unit,size);
        tamLibre = tamDisco(ruta);
        if(tamParticion<=tamLibre){
            existe = nombre(ruta,name);
            if(existe == 0){
                nPrim = contParPrimarias(ruta);
                nExt = contParExtendidas(ruta);
                if(nPrim < 4){
                    if((nExt+ nPrim)<4){
                        byteInicio = inicio(ruta,tamParticion);
                        part primaria;
                        primaria.status='1';
                        primaria.type = type[0];
                        primaria.fit=fit[0];
                        primaria.start=byteInicio;
                        primaria.size=tamParticion;
                        strcpy(primaria.name,name);
                                              // vamos con el disco
                        fseek(disco,0,SEEK_SET);
                        fread(&mbr,sizeof(mbr),1,disco);
                        mbr.particiones[nPrim+nExt] = primaria;
                        printf("\n Inicia en: %i \n",primaria.start);
                        printf(" Tiene un Tam: %i \n",primaria.size);
                        fseek(disco,0,SEEK_SET);
                        fwrite(&mbr,sizeof(mbr),1,disco);
                        fclose(disco);
                        printf("\n EXITO!!! - Particion PRIMARIA creada \n \n");
                    }
                    else{
                        printf("\n X - No se puede crear la Particion - X \n");
                        printf("                   Ya existen particiones Maximas en el disco \n \n ");
                    }
                }
                else{
                    printf("\n X - No se puede crear la Particion - X \n");
                    printf("                   Ya se llego al maximo de particiones primarias \n \n ");
                }
            }
            else{
                printf("\n X - No se puede crear la Particion - X \n");
                printf("                   Ya existe una con el mismo nombre \n \n ");
            }
        }
        else{
            printf("\n X - No se puede crear la Particion - X \n");
            printf("                   Espacio insuficiente en el Disco \n \n ");
        }

    }
}



void crearParticonExtendida(int size, char* ruta, char* name, char* unit, char* type, char* fit){
    MBR mbr;
    FILE* disco;
    disco = fopen(ruta,"rb+");
    if(disco == NULL) {
        printf("\n X - Error disco indicado con Existe verificar - X \n \n");
    }
    else{
        int tamParticion = asignarTamano(unit,size);
        int tamLibreDisco = tamDisco(ruta);
        if(tamParticion<=tamLibreDisco){
            int existe = nombre(ruta,name);
            if(existe == 0){
                int numPrimarias = contParPrimarias(ruta);
                int numExtendidas = contParExtendidas(ruta);
                if(numExtendidas < 1){
                    if((numPrimarias+numExtendidas) < 4){
                       int byteInicio = inicio(ruta,tamParticion);
                        part primaria;
                        primaria.fit = fit[0];
                        strcpy(primaria.name,name);
                        primaria.size = tamParticion;
                        primaria.start = byteInicio;
                        primaria.status = '1';
                        primaria.type = type[0];

                        fseek(disco,0,SEEK_SET);
                        fread(&mbr,sizeof(mbr),1,disco);
                        mbr.particiones[numPrimarias] = primaria;
                        fseek(disco,0,SEEK_SET);
                        fwrite(&mbr,sizeof(mbr),1,disco);

                        EBR ebr;

                        ebr.fit = fit[0];
                        strcpy(ebr.name," ");
                        ebr.next = -1;
                        ebr.size = 0;
                        ebr.start = byteInicio;
                        ebr.status = '0';

                        fseek(disco,byteInicio,SEEK_SET);
                        fwrite(&mbr,sizeof(mbr),1,disco);

                        fclose(disco);
                        printf("\n EXITO!!! - Particion EXTENDIDA creada \n \n");

                    }
                    else{
                        printf("X - ERROR - No se puede crear la particion Extendida - X \n");
                        printf("X -                     Limite Maximo de particiones alcanzado - X \n");
                    }
                }
                else  {
                        printf("X - ERROR - No se puede crear la particion Extendida - X \n");
                        printf("X -                     Ya tiene una particion Extendida en el Disco - X \n");
                }
            }
            else {
                printf("X - ERROR - No se puede crear la particion - X \n");
                printf("X -                     Ya tiene una particion con el nombre - X \n");
            }
        }
        else {
            printf("X - ERROR - No se puede crear la particion - X \n");
            printf("X -                     Tiene espacio insuficiente en el Disco - X \n");
        }

    }
}

void crearParticionLogica(int size, char* ruta, char* name, char* unit, char* type, char* fit){
    FILE* disco;
    disco = fopen(ruta,"rb+");
    if(disco == NULL) {
        printf("\n X - Error disco indicado con Existe verificar - X \n \n");
    }
    else{
        int tamParticion = asignarTamano(unit,size);
        int numExtendidas = contParExtendidas(ruta);

        if(numExtendidas ==1){
             int byteInicio = byteStartLogica(ruta);
             EBR ebr;
             fseek(disco,byteInicio,SEEK_SET);
             fread(&ebr,sizeof(ebr),1,disco);

             if(ebr.next==-1){
                 ebr.fit = fit[0];
                 strcpy(ebr.name,name);
                 ebr.next = sizeof(ebr)+tamParticion;
                 ebr.size = tamParticion;
                 ebr.start = byteInicio;
                 ebr.status = '1';

                 fseek(disco,byteInicio,SEEK_SET);
                 fwrite(&ebr,sizeof(ebr),1,disco);
             }else{
                 int bandera = ebr.next;
             }
             fseek(disco,byteInicio,SEEK_SET);
             fwrite(&ebr,sizeof(ebr),1,disco);
             fclose(disco);
             printf("\n EXITO!!! - Particion Logica creada bien \n \n");

        }else {
            printf("X - ERROR - No se puede crear la particion Logica - X \n");
            printf("X - Porque no tiene una particion extendida creada - X \n");
        }

    }
}


int byteStartLogica(char* ruta){
    MBR mbr;
    int i;
    FILE* disco;
    disco = fopen(ruta,"r");
    if(disco == NULL) {
        printf("\n X - Error disco indicado con Existe verificar - X \n \n");
    }
    else{
        fseek(disco,0,SEEK_SET);
        fread(&mbr,sizeof(mbr),1,disco);
        for(i=0;i<4; i++){
            if(mbr.particiones[i].type=='e'){
                return mbr.particiones[i].start;
            }
        }
    }
    return -1;
}

void ordenar(char* ruta){
    MBR mbr;
    int i;
    int j;
    FILE* disco;
    disco = fopen(ruta,"rb+");
    if(disco == NULL) {
        printf("\n X - Error disco indicado con Existe verificar - X \n \n");
    }
    else{
        fseek(disco,0,SEEK_SET);
        fread(&mbr,sizeof(mbr),1,disco);
        printf("\n Espere........ \n");
        for(i = 0; i < 4 - 1; i++){
            for(j = 0; j < 4 - 1; j++){    // ordenamiento de las particiones para la mejor ubicacion
                if (mbr.particiones[j].start > mbr.particiones[j + 1].start){
                    if(mbr.particiones[j + 1].start != -1){
                        part tmp = mbr.particiones[j];
                        mbr.particiones[j] = mbr.particiones[j+1];
                        mbr.particiones[j+1] = tmp;
                    }
                }
            }
        }
        fseek(disco,0,SEEK_SET);
        fwrite(&mbr,sizeof(mbr),1,disco);
        fclose(disco);
     //   printf("\n Listo! se ordenaron las particiones con Exito! \n \n");
        }
}





void desfragmentar(char* ruta){
    MBR mbr;
    int i;
    FILE* disco;
    disco = fopen(ruta,"rb+");
    if(disco==NULL){
          printf("\n X - Error disco indicado con Existe verificar - X \n \n");
    }
    else{
        fseek(disco,0,SEEK_SET);
        fread(&mbr,sizeof(mbr),1,disco);
        for(i=0; i<4; i++){
            if(mbr.particiones[i].status == '0'){
                if(i==0){
                    mbr.particiones[0]= mbr.particiones[1];
                    mbr.particiones[1]= mbr.particiones[2];
                    mbr.particiones[2]= mbr.particiones[3];
                    mbr.particiones[3].status = '0';
                    mbr.particiones[3].start = -1;
                    printf("Analizando 1 \n ");
                }else
                if(i==1){
                    mbr.particiones[1]= mbr.particiones[2];
                    mbr.particiones[2]= mbr.particiones[3];
                    mbr.particiones[3].status='0';
                    mbr.particiones[3].start=-1;
                    printf("Analizando 2  \n ");
                }
                if(i==2){
                    mbr.particiones[2]= mbr.particiones[3];
                    mbr.particiones[3].status = '0';
                    mbr.particiones[3].start = -1;
                    printf("Analizando 3  \n ");
                }
                printf("Se realizo una Desfragmentacion al crear la particion en el disco \n");

            }
        }
        fseek(disco,0,SEEK_SET);
        fwrite(&mbr,sizeof(mbr),1,disco);
        fclose(disco);
      //  printf("\n Desfragmentacion realizada con Exito!!! \n");
    }
}





void formatearFast(char* name, char* path){
    MBR mbr;
    FILE* disco;
    disco = fopen(path,"rb+");
    if(disco==NULL){
          printf("\n X - Error disco indicado con Existe verificar - X \n \n");
    }
    else{
        fseek(disco,0,SEEK_SET);
        fread(&mbr,sizeof(mbr),1,disco);
        int existe=0;
        int i;
        for(i=0; i<4; i++){
            if(mbr.particiones[i].status == '1' && strcmp(mbr.particiones[i].name,name)==0){
                mbr.particiones[i].status = '0';
                fseek(disco,0,SEEK_SET);
                fwrite(&mbr,sizeof(mbr),1,disco);
                existe =1;
                printf("\n Formateada con Exito \n \n");
            }
        }
        fclose(disco);
        if(existe ==0){
            printf("\n X- Error la particion no existe  Verifique -X\n");
        }
    }
}

void formatearFull(char* name, char* path){
    MBR mbr;
    FILE* disco;
    disco = fopen(path,"rb+");
    if(disco==NULL){
          printf("\n X - Error disco indicado con Existe verificar - X \n \n");
    }
    else{
        fseek(disco,0,SEEK_SET);
        fread(&mbr,sizeof(mbr),1,disco);
        int existe=0;
        int i;
        for(i=0; i<4; i++){
            if(mbr.particiones[i].status == '1' && strcmp(mbr.particiones[i].name,name)==0){
                mbr.particiones[i].status = '0';
                fseek(disco,0,SEEK_SET);
                fwrite(&mbr,sizeof(mbr),1,disco);
                existe =1;
                int ini = mbr.particiones[i].start;
                int fin = ini+mbr.particiones[i].start;
                int t;
                char basura = '\0';
                for(t=ini; t<fin; t++){
                    fseek(disco,t,SEEK_SET);
                    fwrite(&basura,sizeof(basura),1,disco);
                }
                printf("\n Formateada con Exito \n \n");
            }
        }
        fclose(disco);
        if(existe ==0){
          printf("\n X - Error disco indicado con Existe verificar - X \n \n");
        }
    }
}

void formatearParticion(char* name, char* path, char* tipo){
    if(strcmp(tipo,"fast")==0){
        formatearFast(name,path);
    }
    else
    if(strcmp(tipo,"full")==0){
        formatearFull(name,path);
    }
    desfragmentar(path);
    ordenar(path);
  //  desmontarParticionDos(name, path);
}


