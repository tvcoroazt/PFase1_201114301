#include <string.h>
#include <stdio.h>
#include "particion.h"



discos discosMontados[20];

particiones particionesMontadas[20];
int numMontados =0;
int partiMontados =0;


void desmontarParticionDos(char* name, char* path){
    int i;
    for(i=0; i<partiMontados; i++){
        if(strcmp(particionesMontadas[i].name,name)==0 && strcmp(particionesMontadas[i].path,path)==0){
            if(particionesMontadas[i].estado ==1){
                particionesMontadas[i].estado=0;
                printf("\n Exito!!! Particion Montada \n");
            }
        }
    }
}


int verificarDisco(char* path){
    int i; int existe=0;
    for(i=0; i<numMontados; i++){
        if(strcmp(discosMontados[i].path,path)==0){
            return 1;
        }
    }
    return existe;
}

int asignarID_Disco(char* path){
        discos disk;
        disk.letra = numMontados+97;
        disk.numero = 48;
        strcpy(disk.path,path);
        if(numMontados ==0){
            FILE* disco;
            disco = fopen(path,"r");
            if(disco==NULL){
                printf("X - ERROR no existe el disco - X");
            }
            else{
                discosMontados[0] = disk;
                numMontados++;
                fclose(disco);
                return 1;
            }
        }
        else{
            if(verificarDisco(path)==0){
                FILE* disco;
                disco = fopen(path,"r");
                if(disco==NULL){
                    printf("X - ERROR no existe el disco - X");
                }
                else{
                    discosMontados[numMontados] = disk;
                    numMontados++;
                    fclose(disco);
                    return 1;
                }
            }else return 1;
        }
        return 0;
}

void asignarID_particion(char* path, char* name){
    particiones parti;

    strcpy(parti.name,name);
    strcpy(parti.path,path);
    parti.estado =1;

    int i;
    for(i=0; i<numMontados; i++){
        if(strcmp(discosMontados[i].path,path)==0){

            FILE* disco;
            disco = fopen(path,"r");
            if(disco==NULL){
                printf("X - ERROR no existe el disco - X");
            }
            else{
                int sigo = 0;

                MBR mbr;

                fseek(disco,0,SEEK_SET);
                fread(&mbr,sizeof(mbr),1,disco);

                int t;
                for(t=0; t<4; t++){
                    if(strcmp(mbr.particiones[t].name,name)==0 && mbr.particiones[t].status == '1'){
                        sigo =1;
                    }
                }

                int montada =0;
                for(t=0; t<partiMontados; t++){
                    if(strcmp(particionesMontadas[t].name,name)==0 && strcmp(particionesMontadas[t].path,path)==0 && particionesMontadas[t].estado==1){
                        montada =1;
                    }
                }


                if(sigo==1){
                    if(montada==0){
                        strcpy(parti.id,"vd");
                        parti.id[2]=discosMontados[i].letra;
                        parti.id[3]=discosMontados[i].numero+1;
                        parti.id[4] = '\0';
                        particionesMontadas[partiMontados] = parti;
                        discosMontados[i].numero++;
                        partiMontados ++;
                        printf("\nEXITO!! Particion montada \n");
                    }else printf("\n X- ALGO SALIO MAL! la particion ya esta montada -X \n");
                }else{
                    numMontados-=1;
                    printf("\n X - La particion ya Existe - X\n");
                }
                fclose(disco);
            }
        }
    }

}

void imprimirUnidades(){
    int i;
    for(i=0; i<partiMontados; i++){
        printf("%s ==> %s\n", particionesMontadas[i].name, particionesMontadas[i].id);
    }
    printf("\n\n");
    for(i=0; i<numMontados; i++){
        printf("%s ==> %c %c\n", discosMontados[i].path, discosMontados[i].letra, discosMontados[i].numero);
    }
}

void montarParticion(char* path, char* name){
    int sigo = asignarID_Disco(path);
    if(sigo == 1)asignarID_particion(path,name);
    imprimirUnidades();
}

void desmontarParticion(char* id){
    int i;
    int encontrado=0;
    for(i=0; i<partiMontados; i++){
        if(strcmp(particionesMontadas[i].id,id)==0){
            if(particionesMontadas[i].estado ==1){
                particionesMontadas[i].estado=0;
                printf("\n Exito!! - Particion desmontada \n");
                encontrado=1;
            }
        }
    }


    if(encontrado==0){
        printf("\n X - ERROR!! No Existe particion para desmontar - X \n");
    }
}

particiones ExisteParticion(char* id){
    particiones parti;
    strcpy(parti.path, "null\0");

    char cod[5];
    strcpy(cod,id);
    cod[4]='\0';

    int i;
    for(i=0; i<partiMontados; i++){

        // verificar la particon montada

        if(strcmp(particionesMontadas[i].id,cod)==0){
            if(particionesMontadas[i].estado ==1){
                strcpy(parti.id,particionesMontadas[i].id);
                strcpy(parti.name,particionesMontadas[i].name);
                parti.estado = particionesMontadas[i].estado;
                strcpy(parti.path,particionesMontadas[i].path);
                return parti;
            }
        }
    }
    return parti;
}





