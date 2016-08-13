#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "comandos.h" // header


typedef struct comandos{
    char valor[200];
}comandos;

typedef struct dato{
    char valorDato[200];
}dato;






char com1[100];
char com2[100];
char com3[100];
char com4[100];
char com5[100];
char com6[100];



char par1[20];
char par2[20];
char par3[20];
char par4[20];
char par5[20];
char par6[20];

char pathrep[50];

char *fgets(char *s, int n, FILE *stream);

void bienvenida(){
    printf("----------------- BIENVENIDO A ADMINISTRADOR DE DISCOS -------------- \n \n");

}



int ContadorCaracteres(char *cad){
     int i=0;
     while (cad[i]!='\0'){
           i++;
     }
     return(i);
}

void minusculas(char *s)
{
    while(*s!='\0')
    {
        if(*s>='A' && *s<='Z')
            *s+=(char)32;
        s++;
    }
}

int cantComandos(char* cad){
    int i = 0;
    int cant =0;
    bool comillas = false;

    while(cad[i]!='\0'){

       if(comillas == false){
            if(cad[i]== ' '){
                if(cad[i+1] != ' ') cant++;
            }else
            if(cad[i]== '"'){
                comillas = true;
               // printf("HAY COMILLAS 1 \n");
            }
        }else{
            if(cad[i]=='"'){
                comillas =false;
              }
        }

        i++;
    }
//    printf("\nse recibieron %i paratemtros \n", cant);
    return cant;
}


void imprimirComandos(char* cad){
    int i=0;

    int i1 =0;
    int i2 =0;
    int i3 =0;
    int i4=0;
    int i5=0;
    int i6=0;

    bool si;
    si =false;
    int indicador= 0;

    bool comillas = false;

    //recorre la cadena y obtine los valores de los parametros
      while(cad[i]!='\0'){
          if(comillas == false){
            if( (cad[i]==':' && cad[i+1]==':') || (cad[i]==':' && cad[i+1]==':' && cad[i+2]=='"') ){

                  indicador++;
                  i++;
                  si=true;

                  if(cad[i]== '"') comillas =true;
              }else
              if(cad[i]==' '){
                  si = false;
              }
          }else{
              if(cad[i]== '"') comillas =false;
          }


          if(si){
              if(indicador ==1){
                  com1[i1] = cad[i+1];
                  i1++;
                  com1[i1] = '\0';
              }else
              if(indicador == 2){
                  com2[i2] = cad[i+1];
                  i2++;
                  com2[i2] = '\0';
              }else
              if(indicador ==3){
                  com3[i3] = cad[i+1];
                  i3++;
                  com3[i3] = '\0';
              }else
              if(indicador ==4){
                  com4[i4] = cad[i+1];
                  i4++;
                  com4[i4] = '\0';
              }else
              if(indicador ==5){
                  com5[i5] = cad[i+1];
                  i5++;
                  com5[i5] = '\0';
              }else
              if(indicador ==6){
                  com6[i6] = cad[i+1];
                  i6++;
                  com6[i6] = '\0';
              }
          }

          i++;
      }

      printf("  CAD3-> -%s,%s,%s,%s,%s,%s-\n",com1,com2,com3,com4,com5,com6);
}


void imprimirComandos2(char* cad){
    int i=0;
    int i1 =0;
    int i2 =0;
    int i3 =0;
    int i4=0;
    int i5=0;
    int i6=0;
    bool si;
    int indicador= 0;
    si=false;

//    char cad[100];
//    int k;
//    int j;
//    while(cadComillas[k] != '\0')
//    {
//        if ( cadComillas[k] != '"' )
//        {
//            cad[j]=cadComillas[k];
//            j++;
//        }
//        k++;
//    }
//    cad[j]='\0';

    //   printf(cad);

    bool comillas = false;

    //recorre la cadena y obtine los valores
      while(cad[i]!='\0'){

//          if(comillas == false){

//              if(cad[i]==':'){
//                  indicador++;
//                  i++;
//                  si=true;
//                  if(cad[i]== '"') {
//                      comillas = true;
//                     // printf("tiene comillas");
//                  }
//              }else
//              if(cad[i]==' '){
//                  si = false;
//              }
//          }else{
//              if(cad[i]== '"') {
//                  comillas = true;
//              }
//          }

if (comillas == false){



          if( (cad[i]==':' && cad[i+1]==':') || (cad[i]==':' && cad[i+1]==':' && cad[i+2]=='"') ){
              indicador++;
              i++;
              si=true;
               if(cad[i]== '"') comillas =true;
          }else
              if(cad[i]==' '){
                  si = false;
          }
}      else{
    if(cad[i]== '"') comillas =false;
}


          if(si){
              if(indicador ==1){
                  com1[i1] = cad[i+1];
                  i1++;
                  com1[i1] = '\0';
              }else
              if(indicador == 2){
                  com2[i2] = cad[i+1];
                  i2++;
                  com2[i2] = '\0';
              }else
              if(indicador ==3){
                  com3[i3] = cad[i+1];
                  i3++;
                  com3[i3] = '\0';
              }else
              if(indicador ==4){
                  com4[i4] = cad[i+1];
                  i4++;
                  com4[i4] = '\0';
              }else
              if(indicador ==5){
                  com5[i5] = cad[i+1];
                  i5++;
                  com5[i5] = '\0';
              }else
              if(indicador ==6){
                  com6[i6] = cad[i+1];
                  i6++;
                  com6[i6] = '\0';
              }
          }

          i++;
      }

      printf("  CAD1-> %s,%s,%s,%s,%s,%s-\n",com1,com2, com3, com4, com5, com6);
}


void imprimir(char* cad){
    int i=0;
    int i1 =0;
    int i2 =0;
    int i3 =0;
    int i4 =0;
    int i5=0;
    int i6=0;

    bool si=false;
    int indicador= 0;

    bool comillas = false;

    //recorre la cadena y obtienen los nombres de los parametros
    while(cad[i]!='\0'){

        if(comillas == false){
            if(cad[i]==' '){
                if(cad[i+1] != ' '){
                    indicador++;
                    i++;
                    si=true;
                }
            }else
            if(cad[i]==':' && cad[i+1]==':'){
                si = false;
                if(cad[i+2]=='"') {
                    comillas = true;
                }
            }
        }else{
            if(cad[i+2]=='"'){
                comillas =false;
            }
        }

        if(si){
            if(indicador ==1){
                par1[i1] = cad[i];
                i1++;
                par1[i1] = '\0';
            }else
            if(indicador == 2){
                par2[i2] = cad[i];
                i2++;
                par2[i2] = '\0';
            }else
            if(indicador ==3){
                par3[i3] = cad[i];
                i3++;
                par3[i3] = '\0';
            }else
            if(indicador ==4){
                par4[i4] = cad[i];
                i4++;
                par4[i4] = '\0';
            }else
            if(indicador ==5){
                par5[i5] = cad[i];
                i5++;
                par5[i5] = '\0';
            }else
            if(indicador ==6){
                par6[i6] = cad[i];
                i6++;
                par6[i6] = '\0';
            }

        }

        i++;
    }

    printf("  CAD2 -> %s,%s,%s,%s,%s,%s-\n",par1,par2,par3,par4,par5,par6);

}

char *trim(char *s)
{
  char *start = s;

  /* Nos comemos los espacios al inicio */
  while(*start && isspace(*start))
    ++start;

  char *i = start;
  char *end = start;

  /* Nos comemos los espacios al final */
  while(*i)
  {
    if( !isspace(*(i++)) )
      end = i;
  }

  /* Escribimos el terminados */
  *end = 0;

  return start;
}


void comandosLista(char* cadena){

    char cad[500];
    strcpy(cad,cadena);
    minusculas(cad);

    //en este metodo trabajo todo con la cadena de entrada
    imprimir(cad);
    imprimirComandos(cad);

    char comando[15];

    int j;
    for(j=0; j<14; j++){
        if(cad[j]== ' '){
            break;
        }else{
            comando[j] = cad[j];
            comando[j+1] = '\0';
        }
    }

 //   printf("\nComando ingresado = %s\n",comando);

    comandos valores[6];
    comandos parametros[6];

    strcpy(valores[0].valor,com1);
    strcpy(valores[1].valor,com2);
    strcpy(valores[2].valor,com3);
    strcpy(valores[3].valor,com4);
    strcpy(valores[4].valor,com5);
    strcpy(valores[5].valor,com6);


    strcpy(parametros[0].valor,par1);
    strcpy(parametros[1].valor,par2);
    strcpy(parametros[2].valor,par3);
    strcpy(parametros[3].valor,par4);
    strcpy(parametros[4].valor,par5);
    strcpy(parametros[5].valor,par6);

    int numParemetros = cantComandos(cad);

    //---------------------------------------------------------------------------------  MKDISK
    if(strcmp(comando,"mkdisk")==0){
        char size[15]= "null\0";
        char unit[2]= "m\0";
        char path[100]= "null\0";
        char name[15]= "null\0";

        char rutacomp[100]="null\0";
         char rutacomp2[100]="null\0";
        int i;
        for(i=0; i<numParemetros; i++){
            if(strcmp(parametros[i].valor,"-size")==0){
                strcpy(size,valores[i].valor);
            }else
            if(strcmp(parametros[i].valor,"+unit")==0){
                strcpy(unit,valores[i].valor);
            }else
            if(strcmp(parametros[i].valor,"-path")==0){
                strcpy(path,valores[i].valor);


                int cont;
                int iz;
                for(iz=0; path[iz]!=' '; iz++) {

                rutacomp2[iz]=path[iz];
                cont++;
                }
               // strcpy(rutacomp2,' ');



            }else
                if(strcmp(parametros[i].valor,"-name")==0){
                    strcpy(name,valores[i].valor);
           }
        }

        if(strcmp(size,"null")==0 || strcmp(path,"null")==0 || strcmp(name,"null")==0){
            printf("X- Error en el comando MKDISK verifique -X \n");
        }else {

//           printf(path);

            printf("\nSe esta creando -%s- de tamaño (%s)(%s) en -%s- \n",name,size,unit,path);
            printf("espere....... \n");



//            int ia;
//            int jb;
//            while(path[ia] != '\0')
//            {
//                if (path[ia] != ' ')
//                {
//                    rutacomp[jb]=path[ia];
//                    jb++;
//                }
//                ia++;
//            }


            strcat(rutacomp2,name);
            printf("Ruta: -%s- \n",rutacomp2);
            crearDisco(atoi(size),rutacomp2,unit);                         // ------- va a a crear discos

        }
    }else

    // --------------------------------------------------------------------------------- RMDISK
    if(strcmp(comando,"rmdisk")==0){
        char ent[5];


        if(strcmp(parametros[0].valor,"-path")==0){
         //   printf("\n Borrar disco(%s)\n",valores[0].valor);

            printf("\n Realmente desea eliminar el disco -%s- , [S/N]: ", valores[0].valor);
            scanf("%s", ent);

            if (ent[0]=='s'){
             eliminarD (valores[0].valor);
            }
            else{
             printf("NO se elimino el disco \n");
            }

           // eliminarD (valores[0].valor);                  //      -----  va a eliminar discos
        }
        else{
            printf("X-Error en el comando RMDISK-X- Verifique y vuelva a intentar \n");
        }
    }else



    //---------------------------------------------------------------------------------- FDISK
    if(strcmp(comando,"fdisk")==0){
        char size[15]="null\0";
        char unit[2]="k\0";
        char path[100]="null\0";
        char type[2]="p\0";
        char fit[3] = "wf\0";   // ---------------> aca venia a ser el WF que esl el peor ajuste por defecto
        char delete_[5]="null";
        char name[30]="null";
        char add[15]= "null";
        int i;

        char path2[100]="null\0";
        for(i=0; i<numParemetros; i++){
            if(strcmp(parametros[i].valor,"-size")==0){
                strcpy(size,valores[i].valor);
            }else
            if(strcmp(parametros[i].valor,"+unit")==0){
                strcpy(unit,valores[i].valor);
            }else
            if(strcmp(parametros[i].valor,"-path")==0){
                strcpy(path,valores[i].valor);


                int iz;
                for(iz=0; path[iz]!=' '; iz++) {
                path2[iz]=path[iz];
                }
                printf("path de mkfs -%s- \n",path2);

            }else
            if(strcmp(parametros[i].valor,"+type")==0){
                strcpy(type,valores[i].valor);
            }else
            if(strcmp(parametros[i].valor,"+fit")==0){
                strcpy(fit,valores[i].valor);
            }else
            if(strcmp(parametros[i].valor,"+delete")==0){
                strcpy(delete_,valores[i].valor);
            }else
            if(strcmp(parametros[i].valor,"-name")==0){
                strcpy(name,valores[i].valor);
            }else
            if(strcmp(parametros[i].valor,"+add")==0){
                strcpy(add,valores[i].valor);
            }
        }

        if(strcmp(delete_,"null")==0 && strcmp(add,"null")==0){
            if(strcmp(size,"null")==0 || strcmp(name,"null")==0 || strcmp(path,"null")==0){
                printf("\n X - Error en el comando FDISK verifique - X \n");
            }else{
                printf("Crear Particion (%s,%s,%s,%s,%s,%s) \n",size,unit,path2,type,fit,name);    //  va acrear
                crearParticiones(atoi(size),path2,name,unit,type,fit);
            }
        }else
        if(strcmp(delete_,"null")==0){
            printf("- Agregar Espacio(%s,%s,%s,%s) \n",add,unit,path2,name);
            formatearParticion(name,path2,delete_);
        }else
        if(strcmp(add,"null")==0){
            printf("- Formatear Particion (%s,%s,%s) \n",delete_,path2,name);
           formatearParticion(name,path2,delete_);
        }

    }else



    //-------------------------------------------------------------------------------------------- MOUNT
    if(strcmp(comando,"mount")==0){
        char name[30]= "null\0";
        char path[100]="null\0";
        int i;
        for(i=0; i<numParemetros; i++){
            if(strcmp(parametros[i].valor,"-name")==0){
                strcpy(name,valores[i].valor);
            }else
            if(strcmp(parametros[i].valor,"-path")==0){
                strcpy(path,valores[i].valor);
            }
        }

        if(strcmp(path,"null")==0 || strcmp(name,"null")==0){
           printf("\n X - Error en el comando MOUNT verifique - X \n");
        }else{
             montarParticion(path, name);
             printf("Se monto la particion con Exito!!  \n");
        }
    }else

    //----------------------------------------------------------------------------------------- UNMOUNT
    if(strcmp(comando,"unmount")==0){
        char id[150]= "null\0";
        int i;
        for(i=0; i<numParemetros; i++){
            if(strcmp(parametros[i].valor,"-id")==0){
                strcpy(id,valores[i].valor);
            }
        }
        if(strcmp(id,"null")==0){
            printf("\n X - Error en el comando UNMOUNT verifique - X \n");
        }else{
            printf("Id Recibido = %s\n ",id);
            printf("Desmontando Unidad \n");
            desmontarParticion(id);
        }
    }else

        //---------------------------------------------------------------------------------  MKFS
        if(strcmp(comando,"mkfs")==0){
            char id[10]="null\0";
            char type[7]= "full\0";

            char add[10]="null\0";
            char unit[4]="k\0";
            char fs[5]="2fs\0"; // EXT2 O EXT3 valores 2FS O 3FS


            int i;
            for(i=0; i<numParemetros; i++){
                if(strcmp(parametros[i].valor,"-id")==0){
                    strcpy(id,valores[i].valor);
                }else
                    if(strcmp(parametros[i].valor,"+type")==0){
                        strcpy(type,valores[i].valor);
                }else
                    if(strcmp(parametros[i].valor,"+add")==0){
                        strcpy(add,valores[i].valor);
                }else
                    if(strcmp(parametros[i].valor,"+unit")==0){
                        strcpy(unit,valores[i].valor);
                }else
                    if(strcmp(parametros[i].valor,"+fs")==0){
                        strcpy(fs,valores[i].valor);
                }

            }

            if(strcmp(id,"null")==0 ){
                printf("\n X - Error en el comando MKFS verifique - X  \n");
            }else {
                printf("\n Comando de formateo de la particion (%s)(%s) \n",id,type);
                printf("espere formateando....... \n \n");

                crearBloque(id,type);



            }
        }else

        //---------------------------------------------------------------------------------  MKFILE
        if(strcmp(comando,"mkfile")==0){
            char id[10]="null\0";
            char p[20]="null\0";
            char size[15]= "null\0";
            char cont[2]= "null\0";
            char path[100]= "null\0";
            int i;
            for(i=0; i<numParemetros; i++){
                if(strcmp(parametros[i].valor,"-size")==0){
                    strcpy(size,valores[i].valor);
                }else
                if(strcmp(parametros[i].valor,"-cont")==0){
                    strcpy(cont,valores[i].valor);
                }else
                if(strcmp(parametros[i].valor,"-path")==0){
                    strcpy(path,valores[i].valor);
                }else
                    if(strcmp(parametros[i].valor,"-id")==0){
                        strcpy(id,valores[i].valor);
                    }else
                        if(strcmp(parametros[i].valor,"-p")==0){
                            strcpy(p,valores[i].valor);
                        }
            }

            if(strcmp(id,"null")==0 || strcmp(path,"null")==0){
                printf("\n X - Error en el comando verifique - X - MKFILE - X \n");
            }else {
                printf("\n Comando que permite crear archivos (%s)(%s)(%s)(%s)(%s) \n",id,path,p,size,cont);
                printf("espere....... \n \n");
               // crearDisco(atoi(size),path,unit);                         // ------- va a a crear discos
            }
        }else



            //---------------------------------------------------------------------------------  CAT
            if(strcmp(comando,"cat")==0){
                char id[10]="null\0";
                char path[100]= "null\0";
                int i;
                for(i=0; i<numParemetros; i++){
                    if(strcmp(parametros[i].valor,"-path")==0){
                        strcpy(path,valores[i].valor);
                    }else
                        if(strcmp(parametros[i].valor,"-id")==0){
                            strcpy(id,valores[i].valor);
                        }

                }

                if(strcmp(id,"null")==0 || strcmp(path,"null")==0){
                    printf("\n X - Error en el comando verifique - X - CAT - X \n");
                }else {
                    printf("\n Comando que muestra el contenido (%s)(%s) \n",id,path);
                    printf("espere....... \n \n");

                }
            }else

                //---------------------------------------------------------------------------- REM
                if(strcmp(comando,"rem")==0){
                    char id[10]="null\0";
                    char path[100]= "null\0";
                    int i;
                    for(i=0; i<numParemetros; i++){
                        if(strcmp(parametros[i].valor,"-path")==0){
                            strcpy(path,valores[i].valor);
                        }else
                            if(strcmp(parametros[i].valor,"-id")==0){
                                strcpy(id,valores[i].valor);
                            }

                    }

                    if(strcmp(id,"null")==0 || strcmp(path,"null")==0){
                        printf("\n X - Error en el comando verifique - X - REM - X \n");
                    }else {
                        printf("\n Comando elimina archivo o carpeta (%s)(%s) \n",id,path);
                        printf("espere....... \n \n");

                    }
                }else



    //----------------------------------------------------------------------------------------- EXEC
    if(strcmp(comando,"exec")==0){


        if(strcmp(parametros[0].valor,"-path")==0){

            char ruta[100];
            strcpy(ruta,valores[0].valor);
            FILE* script = fopen(ruta,"r");
            if(script == NULL){
                printf("\n X - NO EXISTE - X \n");
            }
            else{
                char line[100];
                while (fgets(line, 99, script) != NULL)
                {
                   if(line[0] !='#'){
                       if(strcmp(line,"\n") !=0){
                           int t;
                           int index = ContadorCaracteres(line);
                           char linea[index];
                           line[index-1]='\0';
                        //   printf("%s\n",line);

                           for(t=0; t<index; t++){
                               if(line[t]=='#'){
                                   linea[t] = '\0';
                                   break;
                               }
                               linea[t] = line[t];
                           }
                           printf("__________________________________________________\n");
                           printf("\n%s\n",linea);
                           comandosLista(linea);
                           printf("___________________________________________________\n");
                       }
                   }
                }
            }
        }
        else{
            printf("\n X - Error en el comando - X - Verifique y vuelva a intentar \n");
        }


    }else


    //--------------------------------------------------------------------------------------------- REP
    if(strcmp(comando,"rep")==0){
        char id[5]= "null\0";
        char name[32]= "null\0";
        char path[150]= "null\0";
        int i;
        for(i=0; i<numParemetros; i++){
            if(strcmp(parametros[i].valor,"-name")==0){
                strcpy(name,valores[i].valor);
            }
            if(strcmp(parametros[i].valor,"-id")==0){
                strcpy(id,valores[i].valor);
            }
            if(strcmp(parametros[i].valor,"-path")==0){
                strcpy(path,valores[i].valor);
            }
        }


        if(strcmp(id,"null")==0 || strcmp(path,"null")==0 || strcmp(name,"null")==0){
             printf("\n X - Error en el comando verifique - X REP - X \n");
        }else{
            if(strcmp(name,"mbr")==0){
                 printf("\n CREANDO REPORTE MBR \n");
                 reporteMbr(path,id);

              //   pathrep = path;
                 printf("Directorio %s",path);
            }
            else
             if(strcmp(name,"disk")==0){
                 printf("\n CREANDO REPORTE DE DISCO  \n");
                 reporteDisco(path,id);

                // pathrep = path;
                 printf("Directorio %s",path);

             }
            else{
                printf("El Comando /-name/ unicamente acepta los siguiente: mbr | disk \n");
            }

        }
    }else


    //---------------------------------------------------------------- EXIT
    if(strcmp(comando,"exit")==0){
        exit(0);
    }
/*
    //-------------------------------------------------------------- COMENTARIO

    if(strcmp(comando,"#")==0){
       printf("Comentario \n");
    }

    if(strcmp(comando,"#Validaciones")==0){
       printf("Comentario \n");
    }

    if(strcmp(comando,"#Crear")==0){
       printf("Comentario \n");
    }

    if(strcmp(comando,"#Elimina")==0){
       printf("Comentario \n");
    }
*/
    // --------------------------------------------------------------- INCORRECTO
    else{
        printf("\n X -x Comando \"%s\" Incorrecto x -X \n",comando);
    }
}


void ingresarComando(){

    char texto[300];
    printf("Escriba su comando: \n ");
    scanf(" %99[^\n]", texto);
    //    printf("%s\n",entrada);


      //  ordenarParametros(entrada);  // ayuda a complementar los parametros y la lectura de los mismos
          comandosLista(texto);


        printf(" -------------------------------------------- \n");
        ingresarComando();
}
