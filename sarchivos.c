#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



 struct MBR {

char inicioP[20];
char tipo_sis[20];
char tipo_p[10];
char parti_act[2];
char tamanio[20];
 } datos;

 struct nomUnidad{
char nombre[50];
char tamanio[7];
}datauni;

struct superblok{
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

struct inodo{
char id_inodo[10];
char tamanio[10];
char num_bloq[10];
char fecha_mod[15];
char fecha_acceso[20];
char fecha_creacion[15];
char bloq_D1[10];
char bloq_D2[10];
char bloq_D3[10];
char bloq_D4[10];
char bloq_i1[10];
}bloq_inodo,aux_bloq_ind;

struct bloq_ext3{
char datos[67];
}bloq_dato;

struct archivo{
char nombre[10];
char inodo[10];
char usado[2];
}bloq_arch;

struct bitacora{
char opercion[20];
char tipo[5];
char direccion[120];
char fecha[20];
char contenido[835];
}bloq_bita;

struct estados{
char  unidad1;
char  unidad2;
char  direccion[100];
FILE  *disco1;
FILE  *disco2;
    }estado;




/************** FUNCIONES PARA  EXT3 ****************************/
  void limpiarsuperb(){
      int a;
      for(a=0; a<10;a++){
 super_b.cant_b[a]=0;
 super_b.cant_ino[a]=0;
 if(a < 6){
 super_b.tama_b[a]=0;
}
 super_b.firma_dd[a]=0;
 super_b.bloques_lib[a]=0;
 super_b.inodos_lib[a]=0;
 super_b.fecha_mont[a]=0;
 super_b.fecha_desmont[a]=0;
 if(a < 5){
 super_b.cant_montage[a]=0;
  }
 super_b.apuntador_inicio[a]=0;
 super_b.apuntador_bloque[a]=0;
 super_b.apuntador_bitacora[a]=0;
 super_b.apuntador_raiz[a]=0;
 super_b.apuntador_bloq[a]=0;
 super_b.primer_ino_lib[a]=0;
 super_b.primer_bit_inodo[a]=0;
 super_b.primer_bit_bloq[a]=0;
 super_b.cant_bita[a]=0;

          }


      }

  void limpiarinodo(){
  int a;
  for(a=0; a< 20;a++){

   if(a < 15){
  bloq_inodo.fecha_mod[a]=0;
  bloq_inodo.fecha_creacion[a]=0;
  }
    bloq_inodo.fecha_acceso[a]=0;

  if(a < 10){
  bloq_inodo.id_inodo[a]=0;
  bloq_inodo.tamanio[a]=0;
  bloq_inodo.num_bloq[a]=0;
   bloq_inodo.bloq_D1[a]=0;
   bloq_inodo.bloq_D2[a]=0;
   bloq_inodo.bloq_D3[a]=0;
   bloq_inodo.bloq_D4[a]=0;
   bloq_inodo.bloq_i1[a]=0;
   }
  }
      }

  int limpiar(char lim[10]){
  int x ;
  for(x=0;x<10;x++){
   lim[x]=0;
  }

return 1;
}

int limpiarnom(){
  int x ;
  for(x=0;x<10;x++){
   bloq_arch.nombre[x]=0;
  }

return 1;
}

int limpiar2(char lim[64]){
  int x;
  for(x=0;x<64;x++){
   lim[x]=0;
  }

return 1;
}


 int limpiar_path(char lim[120]){
  int x;
  for(x=0;x<120;x++){
   lim[x]=0;
  }

return 1;
}

 /************** FUNCION PARA DARLE EL FORMATO EXT3 AL DISCO....*/
void ext3_j(int tamanio,int inicio,FILE *archivo){
  limpiarinodo();
int  aux_op=0;  //auxiliar para las operacions de aputadores
int  aux2_op=0; // auxliar para las operaciones de inodo y log bloques

time_t tiempo = time(0);
struct tm *tlocal = localtime(&tiempo);// struct para la hora y fec

strcpy(super_b.tama_b,"64");
strcpy(super_b.cant_montage,"0");
strcpy(super_b.fecha_desmont,"0/0/0 0:0");
strcpy(super_b.fecha_mont,"0/0/0 0:0");
strcpy(super_b.firma_dd,"r0n1");

tamanio = tamanio -256;
aux_op = inicio + 256;// sumo los byte del super bloque y obtengo apuntador a bitmap de inodos
sprintf(super_b.apuntador_inicio,"%d",aux_op);

aux2_op= tamanio*0.60;
aux2_op= aux2_op/130;
sprintf(super_b.cant_ino,"%d",aux2_op);
sprintf(super_b.inodos_lib,"%d",aux2_op-1);

aux_op = aux_op + aux2_op; //sumo la cantidad de inodos y optengo apuntador al bitmap de bloque
sprintf(super_b.apuntador_bloque,"%d",aux_op);

aux2_op= tamanio*0.40;
aux2_op= aux2_op/68;
sprintf(super_b.cant_b,"%d",aux2_op);
sprintf(super_b.bloques_lib,"%d",aux2_op-1);

aux_op= aux_op + aux2_op; // apuntador a inodo raiz
sprintf(super_b.apuntador_raiz,"%d",aux_op);

fseek(archivo,aux_op,0);
aux2_op = atoi(super_b.cant_ino);
printf("%d--%d",aux2_op,aux_op);
strcpy(bloq_inodo.id_inodo,"0");
strcpy(bloq_inodo.bloq_D1,"0");
strcpy(bloq_inodo.bloq_D2,"0");
strcpy(bloq_inodo.bloq_D3,"0");
strcpy(bloq_inodo.bloq_D4,"0");

for(aux2_op= aux2_op;aux2_op > 0; aux2_op--){
fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
}

aux2_op = (tamanio*0.6) - atoi(super_b.cant_ino);
aux_op = aux_op + aux2_op;  // inicio de bloques de datos
sprintf(super_b.apuntador_bloq,"%d",aux_op);

fseek(archivo,aux_op,0);
aux2_op= atoi(super_b.cant_b);
printf("%d--%d",aux2_op,aux_op);


for(aux2_op= aux2_op; aux2_op > 0; aux2_op --){
fwrite(&bloq_dato,sizeof(bloq_dato),1,archivo);
}

aux2_op = (tamanio*0.4) - atoi(super_b.cant_b);
aux_op = aux_op + aux2_op;  // inicio de bitacora
sprintf(super_b.apuntador_bitacora,"%d",aux_op);

fseek(archivo,aux_op,0);
aux2_op = 1000;
printf("%d--%d",aux2_op,aux_op);
sprintf(super_b.cant_bita,"%d",aux2_op);
strcpy(bloq_bita.tipo,"2"); // ingreso 2 para tener  como referencia que esta vacio
for(aux2_op = aux2_op; aux2_op > 0; aux2_op--){
fwrite(&bloq_bita,sizeof(bloq_bita),1,archivo);
}

strcpy(super_b.primer_bit_inodo,"2");
strcpy(super_b.primer_bit_bloq,"2");
aux2_op = atoi(super_b.apuntador_raiz)+130;
sprintf(super_b.primer_ino_lib,"%d",aux2_op);


fseek(archivo,inicio,0);
fwrite(&super_b,sizeof(super_b),1,archivo);

//******** creacion y escritura de raiz "/" -/

aux2_op= atoi(super_b.apuntador_inicio); // escritura al bitmap de inodos
fseek(archivo,aux2_op,0);
fprintf(archivo,"1");

aux2_op= atoi(super_b.apuntador_bloque);//escritura al bitmap de bloques
fseek(archivo,aux2_op,0);
fprintf(archivo,"1");

strcpy(bloq_inodo.id_inodo,"1");
strcpy(bloq_inodo.tamanio ,"0");
strcpy(bloq_inodo.num_bloq,"1");
strcpy(bloq_inodo.bloq_D1,"1");
strcpy(bloq_inodo.bloq_D2,"0");
strcpy(bloq_inodo.bloq_D3,"0");
strcpy(bloq_inodo.bloq_D4,"0");
strcpy(bloq_inodo.bloq_i1,"0");
strftime(bloq_inodo.fecha_creacion,15,"%d/%m/%y %H:%M",tlocal);
strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
strftime(bloq_inodo.fecha_acceso,20,"%d/%m/%y %H:%M:%S",tlocal);

aux2_op= atoi(super_b.apuntador_raiz);//escritura al bitmap de bloques
fseek(archivo,aux2_op,0);
fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

aux2_op= atoi(super_b.apuntador_bloq);//escritura al bitmap de bloques

fseek(archivo,aux2_op,0);
strcpy(bloq_arch.nombre,".");
strcpy(bloq_arch.inodo,"1");
strcpy(bloq_arch.usado,"1");
fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);

strcpy(bloq_arch.nombre," ");
strcpy(bloq_arch.inodo,"0");
strcpy(bloq_arch.usado,"0");
fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);

}


void guarda_bita(char ruta[120],int opera,int tipo,char contenido[600],FILE *archivo){
int comienzo = atoi(super_b.apuntador_bitacora);
int blqs = atoi(super_b.cant_bita);
  time_t tiempo = time(0);
  struct tm *tlocal = localtime(&tiempo);// struct para la hora y fe
fseek(archivo,comienzo,0);

// revisar  bita acciones ext3
for(blqs = blqs ; blqs >0; blqs--){

   fread(&bloq_bita,sizeof(bloq_bita),1,archivo);
   if(atoi(bloq_bita.tipo)==2){
     switch(opera){
       case 1:
        strcpy(bloq_bita.opercion,"CREACION");
     break;
       case 2:
     strcpy(bloq_bita.opercion,"ELIMINACION");
     break;
     case 3:
       strcpy(bloq_bita.opercion,"RENOMBRACION");
     break;

     default:
     break;
     }

     strcpy(bloq_bita.direccion,ruta);
     strftime(bloq_bita.fecha,20,"%d/%m/%y %H:%M",tlocal);
     strcpy(bloq_bita.contenido,contenido);
     sprintf(bloq_bita.tipo,"%d",tipo);
      comienzo= ftell(archivo) - 1000;
     fseek(archivo,comienzo,0);
     fwrite(&bloq_bita,sizeof(bloq_bita),1,archivo);
    break;
   }
}

}


/********************funcion para sumar o restar la cantidad de inodoslibres************************************/
void opera_inodo(int cantidad,int op){
    int aux_bloque4;
     switch(op){
       case 0:
      aux_bloque4 = atoi(super_b.inodos_lib)-cantidad;
      sprintf(super_b.inodos_lib,"%d",aux_bloque4);
       break;
       case 1:
      aux_bloque4 = atoi(super_b.inodos_lib)+ cantidad;
      sprintf(super_b.inodos_lib,"%d",aux_bloque4);
       break;

       default :
     break;
     }


}

void opera_bloque(int cantidad,int op){
      int aux_bloque3;
     switch(op){
       case 0:
      aux_bloque3 = atoi(super_b.bloques_lib)-cantidad;
      sprintf(super_b.bloques_lib,"%d",aux_bloque3);
       break;
       case 1:
      aux_bloque3 = atoi(super_b.bloques_lib)+ cantidad;
      sprintf(super_b.bloques_lib,"%d",aux_bloque3);
       break;
       default :
     break;
     }


}
/***************** funcion para buscar en el bitmap el primer inodo libre**********************/
 void busk_primer_inodo_lib(FILE *archivo){
  int posicion_ini = atoi(super_b.apuntador_inicio);
  int taman =  atoi(super_b.cant_ino);
  int num_lib=1;
  char lectu ;
  fseek(archivo,posicion_ini,0);


  for(taman= taman ; taman > 0; taman--){
     lectu = fgetc(archivo);
     if(lectu == '0'){
     sprintf(super_b.primer_bit_inodo,"%d",num_lib);
     num_lib = atoi(super_b.apuntador_raiz)+ ((num_lib-1)*130);
     sprintf(super_b.primer_ino_lib,"%d",num_lib);

     break;
     }
     else{
      num_lib++;
     }

  }


}


/*****************funcion que lee bloques pra la buskeda de archivos y carpetas**********************/
int lee_busk(int ubicacion,char busk[10],FILE *archivo){
int result = 0;
int x;
fseek(archivo,ubicacion,0);
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
           x = strcmp(busk,bloq_arch.nombre);
       if(x == 0){
         result = atoi(bloq_arch.inodo);
      }
      else{
          fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
       x = strcmp(busk,bloq_arch.nombre);
       if(x == 0){
        result = atoi(bloq_arch.inodo);
      }
      else{
       fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
       x = strcmp(busk,bloq_arch.nombre);
       if(x == 0){
        result = atoi(bloq_arch.inodo);
      }
      else{
       result = 0;
      }
      }
      }

return result;
}


/***************** funcion para  buscar en el bitmap el primer bloque libre**********************/
 void busk_primer_bloq_lib(FILE *archivo){
  int posicion_ini = atoi(super_b.apuntador_bloque);
  int taman =  atoi(super_b.cant_b);
  int num_lib=1;
  char lectu ;
  fseek(archivo,posicion_ini,0);

  for(taman = taman; taman > 0; taman--){
     lectu = fgetc(archivo);
     if(lectu == '0'){
     sprintf(super_b.primer_bit_bloq,"%d",num_lib);

     break;
     }
     else{
      num_lib++;
     }

  }

}

/**** *** funcion para crear el registro del archivo o carpeta a crear*/
void crea_arch(char crea[10],int tipo,FILE *archivo){
 int aux_bloque = 0;
 time_t tiempo = time(0);
 struct tm *tlocal = localtime(&tiempo);// struct para la hora y fec

  switch(tipo){
   case 1:
     if(atoi(bloq_inodo.bloq_D1)== 0){
      strcpy(bloq_inodo.bloq_D1,super_b.primer_bit_bloq);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D1)-1)*67);

      fseek(archivo,aux_bloque,0);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre," ");
      strcpy(bloq_arch.inodo,"0");
     strcpy(bloq_arch.usado,"0");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);

      aux_bloque= atoi(super_b.apuntador_bloque) + (atoi(bloq_inodo.bloq_D1)-1);
      fseek(archivo,aux_bloque,0);
      fprintf(archivo,"1");

      aux_bloque=atoi(super_b.apuntador_raiz) + (atoi(bloq_inodo.id_inodo)-1)*130;
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
      busk_primer_bloq_lib(archivo);
      opera_bloque(1,0);

       }
          else{
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D1)-1)*67);
          fseek(archivo,aux_bloque,0);
          fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
          printf("---%s---\n",bloq_arch.usado);
        if(atoi(bloq_arch.usado) == 0){
          fseek(archivo,aux_bloque,0);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);


      }
      else{
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      if(atoi(bloq_arch.usado) == 0){
      fseek(archivo,aux_bloque,0);
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

      }
      else{
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      if(atoi(bloq_arch.usado) == 0){
      fseek(archivo,aux_bloque,0);
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

      }
      else{


       crea_arch(crea,2,archivo);

      }
      }
      }
      }
      break;

   case 2:
      if(atoi(bloq_inodo.bloq_D2)== 0){
      strcpy(bloq_inodo.bloq_D2,super_b.primer_bit_bloq);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D2)-1)*67);

      fseek(archivo,aux_bloque,0);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre," ");
      strcpy(bloq_arch.inodo,"0");
     strcpy(bloq_arch.usado,"0");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);

      aux_bloque= atoi(super_b.apuntador_bloque) + (atoi(bloq_inodo.bloq_D2)-1);
      fseek(archivo,aux_bloque,0);
      fprintf(archivo,"1");

      aux_bloque=atoi(super_b.apuntador_raiz) + (atoi(bloq_inodo.id_inodo)-1)*130;
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
      busk_primer_bloq_lib(archivo);
      opera_bloque(1,0);

       }
          else{
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D2)-1)*67);
          fseek(archivo,aux_bloque,0);
          fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
          printf("---%s---\n",bloq_arch.usado);
        if(atoi(bloq_arch.usado) == 0){
          fseek(archivo,aux_bloque,0);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);


      }
      else{
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      if(atoi(bloq_arch.usado) == 0){
      fseek(archivo,aux_bloque,0);
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

      }
      else{
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      if(atoi(bloq_arch.usado) == 0){
      fseek(archivo,aux_bloque,0);
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

      }
      else{


       crea_arch(crea,3,archivo);

      }
      }
      }
      }
        break;

   case 3:
  if(atoi(bloq_inodo.bloq_D3)== 0){
      strcpy(bloq_inodo.bloq_D3,super_b.primer_bit_bloq);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D3)-1)*67);

      fseek(archivo,aux_bloque,0);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre," ");
      strcpy(bloq_arch.inodo,"0");
     strcpy(bloq_arch.usado,"0");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);

      aux_bloque= atoi(super_b.apuntador_bloque) + (atoi(bloq_inodo.bloq_D3)-1);
      fseek(archivo,aux_bloque,0);
      fprintf(archivo,"1");

      aux_bloque=atoi(super_b.apuntador_raiz) + (atoi(bloq_inodo.id_inodo)-1)*130;
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
      busk_primer_bloq_lib(archivo);
      opera_bloque(1,0);

       }
          else{
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D3)-1)*67);
          fseek(archivo,aux_bloque,0);
          fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
          printf("---%s---\n",bloq_arch.usado);
        if(atoi(bloq_arch.usado) == 0){
          fseek(archivo,aux_bloque,0);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);


      }
      else{
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      if(atoi(bloq_arch.usado) == 0){
      fseek(archivo,aux_bloque,0);
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

      }
      else{
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      if(atoi(bloq_arch.usado) == 0){
      fseek(archivo,aux_bloque,0);
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

      }
      else{


       crea_arch(crea,4,archivo);

      }
      }
      }
      }
        break;
   case 4:
         if(atoi(bloq_inodo.bloq_D4)== 0){
      strcpy(bloq_inodo.bloq_D4,super_b.primer_bit_bloq);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D4)-1)*67);

      fseek(archivo,aux_bloque,0);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre," ");
      strcpy(bloq_arch.inodo,"0");
     strcpy(bloq_arch.usado,"0");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);

      aux_bloque= atoi(super_b.apuntador_bloque) + (atoi(bloq_inodo.bloq_D4)-1);
      fseek(archivo,aux_bloque,0);
      fprintf(archivo,"1");

      aux_bloque=atoi(super_b.apuntador_raiz) + (atoi(bloq_inodo.id_inodo)-1)*130;
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
      busk_primer_bloq_lib(archivo);
      opera_bloque(1,0);

       }
          else{
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D4)-1)*67);
          fseek(archivo,aux_bloque,0);
          fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
          printf("---%s ---\n",bloq_arch.usado);
        if(atoi(bloq_arch.usado) == 0){
          fseek(archivo,aux_bloque,0);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);


      }
      else{
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      if(atoi(bloq_arch.usado) == 0){
      fseek(archivo,aux_bloque,0);
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

      }
      else{
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      if(atoi(bloq_arch.usado) == 0){
      fseek(archivo,aux_bloque,0);
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y %H:%M",tlocal);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

      }
      else{


       crea_arch(crea,5,archivo);

      }
      }
      }
      }
        break;
       case 5:
       if(atoi(bloq_inodo.bloq_i1 )== 0){

        aux_bloque = atoi(super_b.apuntador_inicio) + (atoi(super_b.primer_bit_inodo)-1);
        fseek(archivo,aux_bloque,0);
        fprintf(archivo,"1");

      strcpy(bloq_inodo.bloq_i1,super_b.primer_bit_inodo);
      aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);


         strcpy(bloq_inodo.id_inodo,super_b.primer_bit_inodo);
         strftime(bloq_inodo.fecha_creacion,15,"%d/%m/%y%H:%M",tlocal);
             strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y%H:%M",tlocal);
             strftime(bloq_inodo.fecha_acceso,20,"%d/%m/%y %H:%M:%S",tlocal);
             strcpy(bloq_inodo.tamanio,"0");
             strcpy(bloq_inodo.num_bloq,"-2");
             strcpy(bloq_inodo.bloq_D1,super_b.primer_bit_bloq);
             strcpy(bloq_inodo.bloq_D2,"0");
             strcpy(bloq_inodo.bloq_D3,"0");
             strcpy(bloq_inodo.bloq_D4,"0");
             strcpy(bloq_inodo.bloq_i1,"0");

         busk_primer_inodo_lib(archivo);

     aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D1)-1)*67);

      fseek(archivo,aux_bloque,0);
      strcpy(bloq_arch.nombre,crea);
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre," ");
      strcpy(bloq_arch.inodo,"0");
      strcpy(bloq_arch.usado,"");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);

      aux_bloque= atoi(super_b.apuntador_bloque) + (atoi(bloq_inodo.bloq_D1)-1);
      fseek(archivo,aux_bloque,0);
      fprintf(archivo,"1");
       busk_primer_bloq_lib(archivo);

      opera_inodo(1,0);
     opera_bloque(1,0);
         }
         else{
         aux_bloque= atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.bloq_i1)-1)*130);
         fseek(archivo,aux_bloque,0);
         fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
         crea_arch(crea,1,archivo);
         }
        break;

   default :
        printf(" EROR EN LA CREACION  WTF");
   break;
 }

}

int primer_ajuste(FILE *archivo,int tamanio){
   int libres =0;
   char bit ='g';
   int inicio;
   int can_bloc = atoi(super_b.cant_b);
   int inicio_guar = atoi(super_b.primer_bit_bloq);
   int aux =  atoi(super_b.apuntador_bloque)+ (inicio_guar-1);
   fseek(archivo,aux,0);
  for(can_bloc = can_bloc;can_bloc >0 ;can_bloc--){
    bit =  fgetc(archivo);
    if(bit == '0' ){
       libres++;
       if(libres == tamanio){
     opera_bloque(tamanio,0);
    aux =  atoi(super_b.apuntador_bloque) + (inicio_guar-1);
        fseek(archivo,aux,0);
    for(tamanio = tamanio;tamanio>0;tamanio--){
       fprintf(archivo,"1");
    }
    inicio = inicio_guar;
    bit = 'g';
    break;
      }
    }
    else{
     inicio_guar = libres +1;
     libres=0;
    }

  }

 if(bit != 'g'){
  inicio =0;
  }

return inicio;
}

/****************** funcion para buskr la ruta deseada y verificar si existe ***********/
int busk_arch(char busk[10],int tipo,FILE *archivo){
  int aux_bloque = 0;
  int aux_bloque2 = 0;
  switch(tipo){
   case 1:
          aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D1)-1)*67);
          aux_bloque2 = lee_busk(aux_bloque,busk,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = busk_arch(busk,2,archivo);
      }
      break;

   case 2:
           if(atoi(bloq_inodo.bloq_D2 )== 0){

       }
          else{
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D2)-1)*67);
          aux_bloque2 = lee_busk(aux_bloque,busk,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = busk_arch(busk,3,archivo);
      }
      }
        break;

   case 3:
      if(atoi(bloq_inodo.bloq_D3)== 0){

       }
          else{
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D3)-1)*67);
          aux_bloque2 = lee_busk(aux_bloque,busk,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = busk_arch(busk,4,archivo);
      }
        }
        break;
   case 4:
      if(atoi(bloq_inodo.bloq_D4 )== 0){

       }
          else{
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D4)-1)*67);
          aux_bloque2 = lee_busk(aux_bloque,busk,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = busk_arch(busk,5,archivo);
      }
        }

        break;

   case 5:
             if(atoi(bloq_inodo.bloq_i1 )== 0){

       }
          else{
      aux_bloque= atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.bloq_i1)-1)*130);
          fseek(archivo,aux_bloque,0);
      fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
      aux_bloque2 = busk_arch(busk,1,archivo);
      }
      break;
   default :
        printf("----------ERROR EN BUSQUE  wtf --------------");
   break;
 }

 return aux_bloque2;
}

/**********  funcion pra guardar en bloq *****************/
void guar_inf(int ubicacion,char dato[64],FILE *archivo){
          fseek(archivo,ubicacion,0);
      strcpy(bloq_dato.datos,dato);
      fwrite(&bloq_dato,sizeof(bloq_dato),1,archivo);
}

/***************** ubica la el apuntador con el cual se apunta a el bloque de imfo*******************************/
int guarda_datos_en_bloq(char crea[64],char bloq_tur[9],int tipo,FILE *archivo){
  int usp_i1 =0;
 int aux_bloque = 0;
 time_t tiempo = time(0);
 struct tm *tlocal = localtime(&tiempo);// struct para la hora y fec

  switch(tipo){
   case 1:
     if(atoi(bloq_inodo.bloq_D1)== 0){
       strcpy(bloq_inodo.bloq_D1,bloq_tur);
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D1)-1)*67);
      guar_inf(aux_bloque,crea,archivo);
    }
      else{
       guarda_datos_en_bloq(crea,bloq_tur,2,archivo);

    }

      break;

   case 2:

         if(atoi(bloq_inodo.bloq_D2)== 0){
      strcpy(bloq_inodo.bloq_D2,bloq_tur);
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D2)-1)*67);
      guar_inf(aux_bloque,crea,archivo);
    }
      else{
       guarda_datos_en_bloq(crea,bloq_tur,3,archivo);
      }
       break;

   case 3:

       if(atoi(bloq_inodo.bloq_D3)== 0){
       strcpy(bloq_inodo.bloq_D3,bloq_tur);
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D3)-1)*67);
      guar_inf(aux_bloque,crea,archivo);
    }
      else{
       guarda_datos_en_bloq(crea,bloq_tur,4,archivo);
      }
        break;
   case 4:
       if(atoi(bloq_inodo.bloq_D4)== 0){
       strcpy(bloq_inodo.bloq_D4,bloq_tur);
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D4)-1)*67);
      guar_inf(aux_bloque,crea,archivo);
    }
      else{
       guarda_datos_en_bloq(crea,bloq_tur,5,archivo);

      }
       case 5:
       if(atoi(bloq_inodo.bloq_i1 )== 0){

        usp_i1=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
       fseek(archivo,usp_i1,0);
       fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

        strcpy(bloq_inodo.bloq_i1,super_b.primer_bit_inodo);
        aux_bloque = atoi(super_b.apuntador_inicio) + (atoi(bloq_inodo.bloq_i1)-1);
        fseek(archivo,aux_bloque,0);
        fprintf(archivo,"1");


         strcpy(aux_bloq_ind.id_inodo,super_b.primer_bit_inodo);
         strftime(aux_bloq_ind.fecha_creacion,15,"%d/%m/%y%H:%M",tlocal);
             strftime(aux_bloq_ind.fecha_mod,15,"%d/%m/%y%H:%M",tlocal);
             strftime(aux_bloq_ind.fecha_acceso,20,"%d/%m/%y %H:%M:%S",tlocal);
             strcpy(aux_bloq_ind.tamanio,"0");
             strcpy(aux_bloq_ind.num_bloq,"-3");
             strcpy(aux_bloq_ind.bloq_D1,bloq_tur);
             strcpy(aux_bloq_ind.bloq_D2,"0");
             strcpy(aux_bloq_ind.bloq_D3,"0");
             strcpy(aux_bloq_ind.bloq_D4,"0");
             strcpy(aux_bloq_ind.bloq_i1,"0");


     aux_bloque=atoi(super_b.apuntador_raiz) + ((atoi(aux_bloq_ind.id_inodo)-1)*130);
      fseek(archivo,aux_bloque,0);
      fwrite(&aux_bloq_ind,sizeof(aux_bloq_ind),1,archivo);

      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(aux_bloq_ind.bloq_D1)-1)*67);
       fseek(archivo,aux_bloque,0);
       strcpy(bloq_dato.datos,crea);
       fwrite(&bloq_dato,sizeof(bloq_dato),1,archivo);

       busk_primer_inodo_lib(archivo);
       opera_inodo(1,0);

       }
         else{
         aux_bloque= atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.bloq_i1)-1)*130);
         fseek(archivo,aux_bloque,0);
         fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
        guarda_datos_en_bloq(crea,bloq_tur,1,archivo);
         }
        break;

   default :
        printf(" ERROR EN LA CREACION  WTF");
   break;
 }
 return usp_i1;
}

/************* funcion para  guardar la imfo de un archilect ******************/
void guardando_info_arch_ext3(FILE *archivo ,char info_datos[600]){
    int x =0;
    int cant_blo_usa=0;
    char tur[9];
    int y=0;
    char dato [64];
    while(info_datos[x] != 0 ){
           x++;
    }
    cant_blo_usa = x/64;
    x= x%64;
    if(x != 0){
    cant_blo_usa ++;
     }
   x=  primer_ajuste(archivo,cant_blo_usa);
   if(x == 0){
      printf("*********** ERROR CANTIDAD  INSUFICIENTE PARA GUARDAR ********");
   }
   else{

     y= atoi(super_b.apuntador_bloq) + ((x -1)*67);
     fseek(archivo,x ,0);
     y=0;
    cant_blo_usa=0;
    while(info_datos[cant_blo_usa] != 0 ){
        dato[y]= info_datos[cant_blo_usa];
    cant_blo_usa++;
        y++;
    if(y == 65){
      y=0;
      sprintf(tur,"%d",x);
        guarda_datos_en_bloq(dato,tur,1,archivo);
        x++;
    limpiar2(dato);

    }
    }
    if(y != 0){
    sprintf(tur,"%d",x);
    guarda_datos_en_bloq(dato,tur,1,archivo);
    }

   }
    busk_primer_bloq_lib(archivo);
}

/********** fucion para crear archivos y carpetas**********************/
int craccion_guardado_ext3(char ruta[120],int tipo,char info_datos[600],FILE *archivo){
   int x =0;
   int y =0;
   int aux_puntero=0;
   char busk[10]=" ";
   time_t tiempo = time(0);
struct tm *tlocal = localtime(&tiempo);// struct para la hora y fec

  for(x=0; x < 120 ; x++ ){
    if(x > 0){
       if(ruta[x] == '/'){
      y = busk_arch(busk,1,archivo);

      if(y > 0){
        aux_puntero = atoi(super_b.apuntador_raiz) + ((y-1) * 130);
        fseek(archivo,aux_puntero,0);
        fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
        if(atoi(bloq_inodo.tamanio) == 0){
          y=0;
         limpiar(busk);

        }
        else{
          y=-1;
          x=120;
          printf("\n\n------------INTENTO DE CREACION DENTRO DE ARCHIVO----------");
        }

      }
      else{
         printf("\n\n------------ NO EXISTE %s----------",busk);
      y=-1;
      x=120;
      }

       }
       else{
           if(y < 10){
               busk[y]=ruta[x];
               }
        y++;

       }
    }

  else{
   if(x== 0 && ruta[x]== '/'){
      aux_puntero = atoi(super_b.apuntador_raiz);
      fseek(archivo,aux_puntero,0);
      fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
   }
    else{
     y=-1;
     break;
     printf("\n\n------------ERROR  RUTA NO VALIDA ----------\n\n");

    }
  }
  }

 printf("\n\n------------%d  --%s----------\n\n",y,busk);

  if(y >= 0){
crea_arch(busk,1,archivo);
strftime(bloq_inodo.fecha_creacion,15,"%d/%m/%y%H:%M",tlocal);
strftime(bloq_inodo.fecha_mod,15,"%d/%m/%y%H:%M",tlocal);
strftime(bloq_inodo.fecha_acceso,20,"%d/%m/%y %H:%M:%S",tlocal);
if(tipo == 0){
strcpy(bloq_inodo.tamanio,"0");
strcpy(bloq_inodo.num_bloq,"1");
strcpy(bloq_inodo.bloq_D1,super_b.primer_bit_bloq);
strcpy(bloq_inodo.bloq_D2,"0");
strcpy(bloq_inodo.bloq_D3,"0");
strcpy(bloq_inodo.bloq_D4,"0");
strcpy(bloq_inodo.bloq_i1,"0");


      aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D1)-1)*67);

      limpiarnom();
      fseek(archivo,aux_puntero,0);
      strcpy(bloq_arch.nombre,".");
      strcpy(bloq_arch.inodo,super_b.primer_bit_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre,"..");
      strcpy(bloq_arch.inodo,bloq_inodo.id_inodo);
      strcpy(bloq_arch.usado,"1");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      strcpy(bloq_arch.nombre," ");
      strcpy(bloq_arch.inodo,"0");
      strcpy(bloq_arch.usado,"0");
      fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);

      aux_puntero= atoi(super_b.apuntador_bloque) + (atoi(bloq_inodo.bloq_D1)-1);
      fseek(archivo,aux_puntero,0);
      fprintf(archivo,"1");

      aux_puntero=atoi(super_b.apuntador_inicio) + (atoi(super_b.primer_bit_inodo)-1);
      fseek(archivo,aux_puntero,0);
      fprintf(archivo,"1");

      strcpy(bloq_inodo.id_inodo,super_b.primer_bit_inodo);
      aux_puntero=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_puntero,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
      busk_primer_inodo_lib(archivo);
      busk_primer_bloq_lib(archivo);

      opera_inodo(1,0);
      opera_bloque(1,0);
      guarda_bita(ruta,1,0,info_datos,archivo);
      system("clear");
      printf("______________________EL DIRECTORIO %s FUE CREADO CON EXITO __________________\n", busk);
      printf("______________________ EN LA DIRECCION   %s  __________________ \n\n\n",ruta);

}
else{
   x=0;
    /*conteo de caracteres de contenido*/
    while(info_datos[x] != 0 ){
      //   printf("%c \n",info_datos[x]);
      x++;
    }

    /*calculos de bloques a utilizar*/
 sprintf(bloq_inodo.tamanio,"%d",x);
     y = x/64;
    x= x%64;
    if(x != 0){
     y++;
     }

sprintf(bloq_inodo.num_bloq,"%d",y);
strcpy(bloq_inodo.bloq_D1,"0");
strcpy(bloq_inodo.bloq_D2,"0");
strcpy(bloq_inodo.bloq_D3,"0");
strcpy(bloq_inodo.bloq_D4,"0");
strcpy(bloq_inodo.bloq_i1,"0");


      strcpy(bloq_inodo.id_inodo,super_b.primer_bit_inodo);
      aux_puntero=atoi(super_b.apuntador_inicio) + (atoi(super_b.primer_bit_inodo)-1);
      fseek(archivo,aux_puntero,0);
      fprintf(archivo,"1");

      busk_primer_inodo_lib(archivo);
      opera_inodo(1,0);

      guardando_info_arch_ext3(archivo ,info_datos);

      if(y <= 4){
      aux_puntero=atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.id_inodo)-1)*130);
      fseek(archivo,aux_puntero,0);
      fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
      }

      system("clear");
      printf("______________________EL ARCHIVO %s FUE CREADO CON EXITO __________________\n", busk);
      printf("______________________ EN LA DIRECCION   %s  __________________ \n\n\n",ruta);
      guarda_bita(ruta,1,1,info_datos,archivo);

}

  }
  else{
  printf("\n\n------------ERROR  RUTA NO VALIDA ----------\n\n");
  }

  return y;

}


/******** funcion para imprimir contenido de los bloques ******************/
void imprimir_cont(int ubicacion,int tipo, FILE *archivo){

fseek(archivo, ubicacion,0);
        if(tipo == 0){
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
      if(atoi(bloq_arch.usado ) == 0){
      }
      else{
          printf("*-* %s--> %s \n",bloq_arch.inodo,bloq_arch.nombre);
      }
        fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
        if(atoi(bloq_arch.usado ) == 0){
      }
      else{
       printf("*-* %s--> %s \n",bloq_arch.inodo,bloq_arch.nombre);
      }
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
        if(atoi(bloq_arch.usado ) == 0){
      }
      else{
       printf("*-* %s--> %s \n",bloq_arch.inodo,bloq_arch.nombre);
      }
       }
         else{
       fread(&bloq_dato,sizeof(bloq_dato),1,archivo);
       printf("%s",bloq_dato.datos);
      }

}


/*********************imprime estacios***************************/
void espacios(int cantidad){
    int a;
    for(a=cantidad;a>0;a--){
        printf(" ");
        }
    }


/***************************************funcion para poder listar carpetas en forma reecursiva*******************************/
void listar_recur(FILE *archivo,struct inodo listando,int cantidad){

 int aux_puntero;
 int ubicacion;
 int inicio = 1;
 int resultado;
 char verifica[10];
 struct inodo nodoI;
 struct archivo bloq_arch2;

     switch(inicio){
   case 1:
          if(atoi(listando.bloq_D1) == 0){

       }
       else{
      aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(listando.bloq_D1)-1)*67);
      fseek(archivo,aux_puntero,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
      if(atoi(bloq_arch2.usado ) == 0){
      }
      else{

      espacios(cantidad);
      printf("*-* %s--> %s \n",bloq_arch2.inodo,bloq_arch2.nombre);
      strcpy(verifica,".");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
          listar_recur(archivo,nodoI,cantidad+4);
      }
          }
      }

      fseek(archivo,aux_puntero+22,0);
        fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
          espacios(cantidad);
      printf("*-* %s--> %s \n",bloq_arch2.inodo,bloq_arch2.nombre);
      strcpy(verifica,"..");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
          listar_recur(archivo,nodoI,cantidad+4);
      }
          }

      }
      fseek(archivo,aux_puntero+44,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
          espacios(cantidad);
          printf("*-* %s--> %s \n",bloq_arch2.inodo,bloq_arch2.nombre);

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
          listar_recur(archivo,nodoI,cantidad+4);
      }

      }


       }

       inicio=2;

   case 2:
           if(atoi(listando.bloq_D2) == 0){

       }
          else{
      aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(listando.bloq_D2)-1)*67);
       fseek(archivo,aux_puntero,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
      if(atoi(bloq_arch2.usado ) == 0){
      }
      else{

      espacios(cantidad);
      printf("*-* %s--> %s \n",bloq_arch2.inodo,bloq_arch2.nombre);
      strcpy(verifica,".");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
          listar_recur(archivo,nodoI,cantidad+4);
      }
          }
      }

      fseek(archivo,aux_puntero+22,0);
        fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
          espacios(cantidad);
      printf("*-* %s--> %s \n",bloq_arch2.inodo,bloq_arch2.nombre);
      strcpy(verifica,"..");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
          listar_recur(archivo,nodoI,cantidad+4);
      }
          }

      }
      fseek(archivo,aux_puntero+44,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
          espacios(cantidad);
      printf("*-* %s--> %s \n",bloq_arch2.inodo,bloq_arch2.nombre);
      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
          listar_recur(archivo,nodoI,cantidad+4);
      }

      }

        }
         inicio=3;

   case 3:
       if(atoi(listando.bloq_D3) == 0){
       }
          else{
       aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(listando.bloq_D3)-1)*67);
          fseek(archivo,aux_puntero,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
      if(atoi(bloq_arch2.usado ) == 0){
      }
      else{

      espacios(cantidad);
      printf("*-* %s--> %s \n",bloq_arch2.inodo,bloq_arch2.nombre);
      strcpy(verifica,".");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){

      aux_puntero = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,aux_puntero,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
          listar_recur(archivo,nodoI,cantidad+2);
      }
          }
      }
        fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
          espacios(cantidad);
      printf("*-* %s--> %s \n",bloq_arch2.inodo,bloq_arch2.nombre);
      strcpy(verifica,"..");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){

       aux_puntero = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,aux_puntero,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
          listar_recur(archivo,nodoI,cantidad+2);
      }
          }

      }
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
          espacios(cantidad);
      printf("*-* %s--> %s \n",bloq_arch2.inodo,bloq_arch2.nombre);
      aux_puntero = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,aux_puntero,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
          listar_recur(archivo,nodoI,cantidad+2);
      }

      }
        }
        inicio = 4;
   case 4:
       if(atoi(listando.bloq_D4) == 0){

          }
          else{
        aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(listando.bloq_D4)-1)*67);
         fseek(archivo,aux_puntero,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
      if(atoi(bloq_arch2.usado ) == 0){
      }
      else{

      espacios(cantidad);
      printf("*-* %s--> %s \n",bloq_arch2.inodo,bloq_arch2.nombre);
      strcpy(verifica,".");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
          listar_recur(archivo,nodoI,cantidad+4);
      }
          }
      }

      fseek(archivo,aux_puntero+22,0);
        fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
          espacios(cantidad);
      printf("*-* %s--> %s \n",bloq_arch2.inodo,bloq_arch2.nombre);
      strcpy(verifica,"..");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
          listar_recur(archivo,nodoI,cantidad+4);
      }
          }

      }
      fseek(archivo,aux_puntero+44,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
          espacios(cantidad);
      printf("*-* %s--> %s \n",bloq_arch2.inodo,bloq_arch2.nombre);
      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
          listar_recur(archivo,nodoI,cantidad+4);
      }

      }


        }
        inicio=5;

   case 5:
       if(atoi(listando.bloq_i1) == 0){

          }
          else{
      aux_puntero = atoi(super_b.apuntador_raiz) + ((atoi(listando.bloq_i1)-1)*130);
      fseek(archivo,aux_puntero ,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      listar_recur(archivo,nodoI,cantidad);
      }
     break;

   default :
   break;
 }

}


/***************************************funcion para poder listar carpetas en forma reecursiva*******************************/
int busk_archivo_carpeta(FILE *archivo,struct inodo listando,int tipo,char ruta[120],char busk[10]){

 int aux_puntero;
 int ubicacion;
 int inicio = 1;
 int resultado;
 int cantidad = 0;

 char path[120];
 char verifica[10];
 struct inodo nodoI;
 struct archivo bloq_arch2;

     switch(inicio){
   case 1:
          if(atoi(listando.bloq_D1) == 0){

       }
       else{

      aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(listando.bloq_D1)-1)*67);
      fseek(archivo,aux_puntero,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
      if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
      strcpy(verifica,".");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){
      resultado = strcmp(busk,bloq_arch2.nombre);

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
           if((resultado == 0) && (tipo == 0)){
          printf("-> path : %s%s  FECHA CREACOIN : %s\n\n",ruta,bloq_arch2.nombre,nodoI.fecha_creacion);
          cantidad++;
              }
            strcpy(path,ruta);
            strcat(path,bloq_arch2.nombre);
            strcat(path,"/");
            cantidad= cantidad + busk_archivo_carpeta(archivo,nodoI,tipo,path,busk);
      }
      else{
          if((resultado == 0) && (tipo == 1)){
          printf("-> path : %s%s  TAMAÑO : %s  bytes FECHA CREACION %s  \n\n",ruta,bloq_arch2.nombre,nodoI.tamanio,nodoI.fecha_creacion);
            cantidad++;
              }
          }

          }
      }

      fseek(archivo,aux_puntero+22,0);
        fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
      strcpy(verifica,"..");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){
         resultado = strcmp(busk,bloq_arch2.nombre);

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
           if((resultado == 0) && (tipo == 0)){

          printf("-> path : %s%s  FECHA CREACOIN : %s\n",ruta,bloq_arch2.nombre,nodoI.fecha_creacion);
          cantidad++;
              }
            strcpy(path,ruta);
            strcat(path,bloq_arch2.nombre);
            strcat(path,"/");
            cantidad = cantidad + busk_archivo_carpeta(archivo,nodoI,tipo,path,busk);
      }
      else{
          if((resultado == 0) && (tipo == 1)){
          printf("-> path : %s%s  TAMAÑO : %s  bytes  FECHA CREACION %s  \n",ruta,bloq_arch2.nombre,nodoI.tamanio,nodoI.fecha_creacion);
             cantidad++;
              }
          }
          }

      }
      fseek(archivo,aux_puntero+44,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
     resultado = strcmp(busk,bloq_arch2.nombre);
      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
           if((resultado == 0) && (tipo == 0)){
         printf("-> path : %s%s  FECHA CREACOIN : %s\n",ruta,bloq_arch2.nombre,nodoI.fecha_creacion);
          cantidad ++;
              }
            strcpy(path,ruta);
            strcat(path,bloq_arch2.nombre);
            strcat(path,"/");
           cantidad = cantidad + busk_archivo_carpeta(archivo,nodoI,tipo,path,busk);
      }
      else{
          if((resultado == 0) && (tipo == 1)){
          printf("-> path : %s%s  TAMAÑO : %s  bytes  FECHA CREACION %s  \n",ruta,bloq_arch2.nombre,nodoI.tamanio,nodoI.fecha_creacion);
              cantidad++;
              }
          }

      }
       }

       inicio=2;

   case 2:
      if(atoi(listando.bloq_D2) == 0){

       }
          else{
      aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(listando.bloq_D2)-1)*67);
        fseek(archivo,aux_puntero,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);

        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
      strcpy(verifica,".");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){
      resultado = strcmp(busk,bloq_arch2.nombre);

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
           if((resultado == 0) && (tipo == 0)){
          printf("-> path : %s%s  FECHA CREACOIN : %s\n\n",ruta,bloq_arch2.nombre,nodoI.fecha_creacion);
          cantidad++;
              }
            strcpy(path,ruta);
            strcat(path,bloq_arch2.nombre);
            strcat(path,"/");
            cantidad= cantidad + busk_archivo_carpeta(archivo,nodoI,tipo,path,busk);
      }
      else{
          if((resultado == 0) && (tipo == 1)){
          printf("-> path : %s%s  TAMAÑO : %s  bytes FECHA CREACION %s  \n\n",ruta,bloq_arch2.nombre,nodoI.tamanio,nodoI.fecha_creacion);
             cantidad++;
              }
          }

          }
      }

      fseek(archivo,aux_puntero+22,0);
        fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
      strcpy(verifica,"..");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){
         resultado = strcmp(busk,bloq_arch2.nombre);

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
           if((resultado == 0) && (tipo == 0)){

          printf("-> path : %s%s  FECHA CREACOIN : %s\n",ruta,bloq_arch2.nombre,nodoI.fecha_creacion);
          cantidad++;
              }
            strcpy(path,ruta);
            strcat(path,bloq_arch2.nombre);
            strcat(path,"/");
            cantidad = cantidad + busk_archivo_carpeta(archivo,nodoI,tipo,path,busk);
      }
      else{
          if((resultado == 0) && (tipo == 1)){
          printf("-> path : %s%s  TAMAÑO : %s  bytes  FECHA CREACION %s  \n",ruta,bloq_arch2.nombre,nodoI.tamanio,nodoI.fecha_creacion);
             cantidad++;
             }
          }
          }

      }
      fseek(archivo,aux_puntero+44,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
     resultado = strcmp(busk,bloq_arch2.nombre);
      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
           if((resultado == 0) && (tipo == 0)){
         printf("-> path : %s%s  FECHA CREACOIN : %s\n",ruta,bloq_arch2.nombre,nodoI.fecha_creacion);
          cantidad ++;
              }
            strcpy(path,ruta);
            strcat(path,bloq_arch2.nombre);
            strcat(path,"/");
           cantidad = cantidad + busk_archivo_carpeta(archivo,nodoI,tipo,path,busk);
      }
      else{
          if((resultado == 0) && (tipo == 1)){
          printf("-> path : %s%s  TAMAÑO : %s  bytes  FECHA CREACION %s  \n",ruta,bloq_arch2.nombre,nodoI.tamanio,nodoI.fecha_creacion);
             cantidad++;
              }
          }

      }
        }
         inicio=3;

   case 3:
      if(atoi(listando.bloq_D3) == 0){
       }
          else{
      aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(listando.bloq_D3)-1)*67);
        fseek(archivo,aux_puntero,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
    if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
      strcpy(verifica,".");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){
      resultado = strcmp(busk,bloq_arch2.nombre);

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
           if((resultado == 0) && (tipo == 0)){
          printf("-> path : %s%s  FECHA CREACOIN : %s\n\n",ruta,bloq_arch2.nombre,nodoI.fecha_creacion);
          cantidad++;
              }
            strcpy(path,ruta);
            strcat(path,bloq_arch2.nombre);
            strcat(path,"/");
            cantidad= cantidad + busk_archivo_carpeta(archivo,nodoI,tipo,path,busk);
      }
      else{
          if((resultado == 0) && (tipo == 1)){
          printf("-> path : %s%s  TAMAÑO : %s  bytes FECHA CREACION %s  \n\n",ruta,bloq_arch2.nombre,nodoI.tamanio,nodoI.fecha_creacion);
             cantidad++;
              }
          }

          }
      }

      fseek(archivo,aux_puntero+22,0);
        fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
      strcpy(verifica,"..");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){
         resultado = strcmp(busk,bloq_arch2.nombre);

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
           if((resultado == 0) && (tipo == 0)){

          printf("-> path : %s%s  FECHA CREACOIN : %s\n",ruta,bloq_arch2.nombre,nodoI.fecha_creacion);
          cantidad++;
              }
            strcpy(path,ruta);
            strcat(path,bloq_arch2.nombre);
            strcat(path,"/");
            cantidad = cantidad + busk_archivo_carpeta(archivo,nodoI,tipo,path,busk);
      }
      else{
          if((resultado == 0) && (tipo == 1)){
          printf("-> path : %s%s  TAMAÑO : %s  bytes  FECHA CREACION %s  \n",ruta,bloq_arch2.nombre,nodoI.tamanio,nodoI.fecha_creacion);
              cantidad++;
              }
          }
          }

      }
      fseek(archivo,aux_puntero+44,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
     resultado = strcmp(busk,bloq_arch2.nombre);
      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
           if((resultado == 0) && (tipo == 0)){
         printf("-> path : %s%s  FECHA CREACOIN : %s\n",ruta,bloq_arch2.nombre,nodoI.fecha_creacion);
          cantidad ++;
              }
            strcpy(path,ruta);
            strcat(path,bloq_arch2.nombre);
            strcat(path,"/");
           cantidad = cantidad + busk_archivo_carpeta(archivo,nodoI,tipo,path,busk);
      }
      else{
          if((resultado == 0) && (tipo == 1)){
          printf("-> path : %s%s  TAMAÑO : %s  bytes  FECHA CREACION %s  \n",ruta,bloq_arch2.nombre,nodoI.tamanio,nodoI.fecha_creacion);
             cantidad++;
              }
          }

      }
        }
        inicio = 4;
   case 4:
       if(atoi(listando.bloq_D4) == 0){

          }
          else{
       aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(listando.bloq_D4)-1)*67);
        fseek(archivo,aux_puntero,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
      if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
      strcpy(verifica,".");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){
      resultado = strcmp(busk,bloq_arch2.nombre);

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
           if((resultado == 0) && (tipo == 0)){
          printf("-> path : %s%s  FECHA CREACOIN : %s\n\n",ruta,bloq_arch2.nombre,nodoI.fecha_creacion);
          cantidad++;
              }
            strcpy(path,ruta);
            strcat(path,bloq_arch2.nombre);
            strcat(path,"/");
            cantidad= cantidad + busk_archivo_carpeta(archivo,nodoI,tipo,path,busk);
      }
      else{
          if((resultado == 0) && (tipo == 1)){
          printf("-> path : %s%s  TAMAÑO : %s  bytes FECHA CREACION %s  \n\n",ruta,bloq_arch2.nombre,nodoI.tamanio,nodoI.fecha_creacion);
             cantidad++;
              }
          }

          }
      }

      fseek(archivo,aux_puntero+22,0);
        fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
      strcpy(verifica,"..");
      resultado = strcmp(verifica,bloq_arch2.nombre);
      if(resultado != 0 ){
         resultado = strcmp(busk,bloq_arch2.nombre);

      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
           if((resultado == 0) && (tipo == 0)){

          printf("-> path : %s%s  FECHA CREACOIN : %s\n",ruta,bloq_arch2.nombre,nodoI.fecha_creacion);
          cantidad++;
              }
            strcpy(path,ruta);
            strcat(path,bloq_arch2.nombre);
            strcat(path,"/");
            cantidad = cantidad + busk_archivo_carpeta(archivo,nodoI,tipo,path,busk);
      }
      else{
          if((resultado == 0) && (tipo == 1)){
          printf("-> path : %s%s  TAMAÑO : %s  bytes  FECHA CREACION %s  \n",ruta,bloq_arch2.nombre,nodoI.tamanio,nodoI.fecha_creacion);
             cantidad++;
              }
          }
          }

      }
      fseek(archivo,aux_puntero+44,0);
      fread(&bloq_arch2,sizeof(bloq_arch2),1,archivo);
        if(atoi(bloq_arch2.usado ) == 0){
      }
      else{
     resultado = strcmp(busk,bloq_arch2.nombre);
      ubicacion = atoi(super_b.apuntador_raiz) + ((atoi(bloq_arch2.inodo)-1)*130);
      fseek(archivo,ubicacion,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      if(atoi(nodoI.tamanio) == 0){
           if((resultado == 0) && (tipo == 0)){
         printf("-> path : %s%s  FECHA CREACOIN : %s\n",ruta,bloq_arch2.nombre,nodoI.fecha_creacion);
          cantidad ++;
              }
            strcpy(path,ruta);
            strcat(path,bloq_arch2.nombre);
            strcat(path,"/");
           cantidad = cantidad + busk_archivo_carpeta(archivo,nodoI,tipo,path,busk);
      }
      else{
          if((resultado == 0) && (tipo == 1)){
          printf("-> path : %s%s  TAMAÑO : %s  bytes  FECHA CREACION %s  \n",ruta,bloq_arch2.nombre,nodoI.tamanio,nodoI.fecha_creacion);
             cantidad++;
              }
          }

      }
        }
        inicio=5;

   case 5:
       if(atoi(listando.bloq_i1) == 0){

          }
          else{
      aux_puntero = atoi(super_b.apuntador_raiz) + ((atoi(listando.bloq_i1)-1)*130);
      fseek(archivo,aux_puntero ,0);
      fread(&nodoI,sizeof(nodoI),1,archivo);
      busk_archivo_carpeta(archivo,nodoI,tipo,ruta,busk);
      }
     break;

   default :
   break;
 }

  return cantidad;
}



/******** funcion que  reccores los bloques para listar carpeta s ***************/
void listar_arch(FILE *archivo,int tipo){
 int aux_puntero;
 int inicio = 1;
     switch(inicio){
   case 1:
          if(atoi(bloq_inodo.bloq_D1) == 0){

       }
       else{
       aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D1)-1)*67);
           imprimir_cont(aux_puntero,tipo,archivo);
       }
       inicio=2;

   case 2:
           if(atoi(bloq_inodo.bloq_D2) == 0){

       }
          else{
      aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D2)-1)*67);
           imprimir_cont(aux_puntero,tipo,archivo);
        }
         inicio=3;

   case 3:
       if(atoi(bloq_inodo.bloq_D3) == 0){
       }
          else{
       aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D3)-1)*67);
            imprimir_cont(aux_puntero,tipo,archivo);
        }
        inicio = 4;
   case 4:
       if(atoi(bloq_inodo.bloq_D4) == 0){

          }
          else{
        aux_puntero= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D4)-1)*67);
        imprimir_cont(aux_puntero,tipo,archivo);
        }
        inicio=5;

   case 5:
       if(atoi(bloq_inodo.bloq_i1) == 0){

          }
          else{
      aux_puntero = atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.bloq_i1)-1)*130);
          fseek(archivo,aux_puntero ,0);
      fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
      listar_arch(archivo,tipo);
      }
     break;

   default :
   break;
 }

}

/********************* funcion para listar archivos y carpestas **************************/
void ver_directrio_y_archivo_ext3(char ruta[120],int tipo ,FILE *archivo){
  int x =0;
   int home =0;
   int y =0;
   int aux_puntero=0;
   char busk[10]=" ";

  while(ruta[x] != 0){
    if(x > 0){
       if(ruta[x] == '/'){
      y = busk_arch(busk,1,archivo);
      if(y > 0){
        aux_puntero = atoi(super_b.apuntador_raiz) + ((y-1) * 130);
        fseek(archivo,aux_puntero,0);
        fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
        y=0;
     limpiar(busk);
      }
      else{
      y=-1;
      break;
      }

       }
       else{
           if(y<10){
         busk[y]=ruta[x];
            }
     y++;
     home++;

       }
    }

  else{
   if(x== 0 && ruta[x]== '/'){
      aux_puntero = atoi(super_b.apuntador_raiz);
      fseek(archivo,aux_puntero,0);
      fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
   }
    else{
     y=-1;
     break;
     printf("\n\n------------ERROR  RUTA NO VALIDA v----------\n\n");

    }
  }
  x++;
  }

  if(y >= 0){

         if(home != 0){
          y = busk_arch(busk,1,archivo);
       printf("\n______________________ %s___________--> %d\n",busk,y);
       aux_puntero = atoi(super_b.apuntador_raiz) + ((y-1) * 130);
        fseek(archivo,aux_puntero,0);
        fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
              }
              else{
          y=2;
          }

if(y > 0){
        printf("\nFECHA CREACION : %s \nTAMAÑO : %s bytes \nFECHA DE MODIFICACION : %s \n",bloq_inodo.fecha_creacion,bloq_inodo.tamanio,bloq_inodo.fecha_mod);
       if(tipo == 1){
          printf("\nCONTENIDO\n");
        }
        else{
            printf("\nlista de archivos\n");

        }
        if(tipo == 3){
            listar_recur(archivo,bloq_inodo,0);
            }
        else{
        listar_arch(archivo,tipo);
           }
  printf("\n\n________________________________________________\n\n");

     }
    else{
      printf("\n\n------------ERROR  RUTA NO VALIDA -->%s  NO EXISTE----------\n\n",busk);
    }
  }
  else{
      printf("\n\n------------ERROR  RUTA NO VALIDA----------\n\n");
    }

}


//lee y busca bloques para archivos y carpetas
int lee_busk2(int ubicacion,char busk[10],char nuevo[10],int op,FILE *archivo){
int result = 0;
int x;
        fseek(archivo,ubicacion,0);
       fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
        x = strcmp(busk,bloq_arch.nombre);
       if(x == 0){
         fseek(archivo,ubicacion,0);
         if(op == 0){
         strcpy(bloq_arch.nombre,nuevo);
         fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
         result = atoi(bloq_arch.inodo);
         }
         else{
         result = atoi(bloq_arch.inodo);
         strcpy(bloq_arch.nombre," ");
         strcpy(bloq_arch.inodo,"0");
         strcpy(bloq_arch.usado,"0");
         fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
         }
      }
      else{
          fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
       x = strcmp(busk,bloq_arch.nombre);
       if(x == 0){
         fseek(archivo,ubicacion+22,0);
        if(op == 0){
         strcpy(bloq_arch.nombre,nuevo);
         fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
         result = atoi(bloq_arch.inodo);
         }
         else{
         result = atoi(bloq_arch.inodo);
         strcpy(bloq_arch.nombre," ");
         strcpy(bloq_arch.inodo,"0");
         strcpy(bloq_arch.usado,"0");
         fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      }
       }
      else{
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
       x = strcmp(busk,bloq_arch.nombre);
       if(x == 0){
         fseek(archivo,ubicacion+44,0);
        if(op == 0){
         strcpy(bloq_arch.nombre,nuevo);
         fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
         result = atoi(bloq_arch.inodo);
         }
         else{
         result = atoi(bloq_arch.inodo);
         strcpy(bloq_arch.nombre," ");
         strcpy(bloq_arch.inodo,"0");
         strcpy(bloq_arch.usado,"0");
         fwrite(&bloq_arch,sizeof(bloq_arch),1,archivo);
      }
       }
      else{
       result = 0;

      }

      }
      }
return result;
}


/*****************************funcion para renombrar archivo**************************************************/

int renombre_elim_arch(char busk[10],char nuevo[10],int op,int tipo,FILE *archivo){
  int aux_bloque = 0;
  int aux_bloque2 = 0;
  switch(tipo){
   case 1:
         aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D1)-1)*67);
          aux_bloque2 = lee_busk2(aux_bloque,busk,nuevo,op,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = renombre_elim_arch(busk,nuevo,op,2,archivo);
      }
      break;

   case 2:
           if(atoi(bloq_inodo.bloq_D2 )== 0){

       }
          else{
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D2)-1)*67);
          aux_bloque2 = lee_busk2(aux_bloque,busk,nuevo,op,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = renombre_elim_arch(busk,nuevo,op,3,archivo);
      }
      }
        break;

   case 3:
      if(atoi(bloq_inodo.bloq_D3)== 0){

       }
          else{

      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D3)-1)*67);
          aux_bloque2 = lee_busk2(aux_bloque,busk,nuevo,op,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = renombre_elim_arch(busk,nuevo,op,4,archivo);
      }
        }
        break;
   case 4:
      if(atoi(bloq_inodo.bloq_D4 )== 0){

       }
          else{

      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D4)-1)*67);
          aux_bloque2 = lee_busk2(aux_bloque,busk,nuevo,op,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = renombre_elim_arch(busk,nuevo,op,5,archivo);
      }
        }

        break;

   case 5:
             if(atoi(bloq_inodo.bloq_i1 )== 0){

       }
          else{

      aux_bloque= atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.bloq_i1)-1)*130);
          fseek(archivo,aux_bloque,0);
      fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
     aux_bloque2 = renombre_elim_arch(busk,nuevo,op,1,archivo);
      }

      break;
   default :
        printf("----------ERROR EN BUSQUE  wtf --------------");
   break;
 }

 return aux_bloque2;
}


 void renom_elimi(char ruta[120],char nuevo[10],int op,int tipo ,FILE *archivo){
  int x =0;
   int home =0;
   int y =0;
   int aux_puntero=0;
   char busk[10]=" ";
   char contenido[600];

  while(ruta[x] != 0 ){
    if(x > 0){
       if(ruta[x] == '/'){
      y = busk_arch(busk,1,archivo);
      if(y > 0){
        aux_puntero = atoi(super_b.apuntador_raiz) + ((y-1) * 130);
        fseek(archivo,aux_puntero,0);
        fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
        y=0;
     limpiar(busk);
      }
      else{
      y=-1;
      printf("\n\n------------CARPETA %s NO EXITE----------\n",busk);
      break;
      }

       }
       else{
           if( y < 10){
              busk[y]=ruta[x];
               }
     y++;
     home++;

       }
    }

  else{
   if(x== 0 && ruta[x]== '/'){
      aux_puntero = atoi(super_b.apuntador_raiz);
      fseek(archivo,aux_puntero,0);
      fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

   }
    else{
     y=-1;
     break;
     printf("\n\n------------ERROR  RUTA NO VALIDA R----------\n\n");

    }
  }
  x++;
  }

  if(y >= 0){
         if(home != 0){
         if(op== 0){

          y= renombre_elim_arch(busk,nuevo,op,1,archivo);
          if(y == 0){
          printf("\n\n------------ remnom ERROR ARCHIVO NO EXISTE -----------\n\n");
          }else{
          guarda_bita(ruta,3,1,contenido,archivo);
           printf("\n\n------------ RENOMBREMIENTO EXITOSO  %s ---> %s  -----------\n\n",busk,nuevo);
          }
         }
         else{
          y=  renombre_elim_arch(busk,nuevo,op,1,archivo);
          if(y != 0){
           aux_puntero = atoi(super_b.apuntador_inicio) + (y-1) ;
           fseek(archivo,aux_puntero,0);
           fprintf(archivo,"0");

           aux_puntero = atoi(super_b.apuntador_raiz) + ((y-1) * 130);
           fseek(archivo,aux_puntero,0);
           fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
           y=atoi(bloq_inodo.num_bloq);
           opera_bloque(y,1);

           aux_puntero = atoi(super_b.apuntador_bloque) + (atoi(bloq_inodo.bloq_D1 )-1);
           fseek(archivo,aux_puntero,0);
           for(y =y; y>0 ; y--){
           fprintf(archivo,"0");
           }

           aux_puntero = atoi(bloq_inodo.bloq_i1);
           if(aux_puntero != 0){
           aux_puntero = atoi(super_b.apuntador_inicio) + (aux_puntero-1) ;
           fseek(archivo,aux_puntero,0);
           fprintf(archivo,"0");

           opera_inodo(2,1);
           }
           else{
           opera_inodo(1,1);
           }
           busk_primer_bloq_lib(archivo);
           busk_primer_inodo_lib(archivo);
           guarda_bita(ruta,2,1,contenido,archivo);
          printf("\n\n------------ ELIMINACION DEL ARCHIVO %s   EXITOSA -----------\n\n",busk);
          }
          else{
          printf("\n\n------------ ERROR ARCHIVO NO EXISTE -----------\n\n");
          }
         }

     }
              else{
          printf("\n\n------------ error NO SE PERMITE LA ACCION ----------\n\n");
                  }
  }
  else{
      printf("\n\n------------ERROR  RUTA NO VALIDA----------\n\n");
    }

}


/******************************************************************************************************************/
/*********************************funcion para modificar el archivo***********************************************/
int lee_busk4(int ubicacion,char busk[10],FILE *archivo){
int result = 0;
int x;
        fseek(archivo,ubicacion,0);
       fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
        x = strcmp(busk,bloq_arch.nombre);
       if(x == 0){
         result = atoi(bloq_arch.inodo);
      }
      else{
          fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
       x = strcmp(busk,bloq_arch.nombre);
       if(x == 0){
         result = atoi(bloq_arch.inodo);
       }
      else{
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
       x = strcmp(busk,bloq_arch.nombre);
       if(x == 0){
         result = atoi(bloq_arch.inodo);
      }
      else{
       result = 0;

      }
      }
      }

return result;
}

int busk_arhivo_modificar(char busk[10],int tipo,FILE *archivo){
  int aux_bloque = 0;
  int aux_bloque2 = 0;
  switch(tipo){
   case 1:
         aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D1)-1)*67);
          aux_bloque2 = lee_busk4(aux_bloque,busk,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = busk_arhivo_modificar(busk,2,archivo);
      }
      break;

   case 2:
           if(atoi(bloq_inodo.bloq_D2 )== 0){

       }
          else{
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D2)-1)*67);
          aux_bloque2 = lee_busk4(aux_bloque,busk,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = busk_arhivo_modificar(busk,3,archivo);
      }
      }
        break;

   case 3:
      if(atoi(bloq_inodo.bloq_D3)== 0){

       }
          else{

      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D3)-1)*67);
          aux_bloque2 = lee_busk4(aux_bloque,busk,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = busk_arhivo_modificar(busk,4,archivo);
      }
        }
        break;
   case 4:
      if(atoi(bloq_inodo.bloq_D4 )== 0){

       }
          else{

      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D4)-1)*67);
          aux_bloque2 = lee_busk4(aux_bloque,busk,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = busk_arhivo_modificar(busk,5,archivo);
      }
        }

        break;

   case 5:
             if(atoi(bloq_inodo.bloq_i1 )== 0){

       }
          else{

      aux_bloque= atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.bloq_i1)-1)*130);
          fseek(archivo,aux_bloque,0);
      fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
     aux_bloque2 = busk_arhivo_modificar(busk,1,archivo);
      }

      break;
   default :
        printf("----------ERROR EN BUSQUE  wtf --------------");
   break;
 }

 return aux_bloque2;
}


void modifica(int ubicacion,char conte[600],FILE *archivo ){
           int y = ubicacion;
           int x =0;
           int aux_puntero =0;
           aux_puntero = atoi(super_b.apuntador_raiz) + ((y-1) * 130);
           fseek(archivo,aux_puntero,0);
           fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
           y=atoi(bloq_inodo.num_bloq);
           opera_bloque(y,1);
           aux_puntero = atoi(super_b.apuntador_bloque) + (atoi(bloq_inodo.bloq_D1 )-1);
           fseek(archivo,aux_puntero,0);
           for(y =y; y>0 ; y--){
           fprintf(archivo,"0");
           }
           aux_puntero = atoi(bloq_inodo.bloq_i1);
           if(aux_puntero != 0){
           aux_puntero = atoi(super_b.apuntador_inicio) + (aux_puntero-1) ;
           fseek(archivo,aux_puntero,0);
           fprintf(archivo,"0");
           opera_inodo(2,1);
           }
           else{
           opera_inodo(1,1);
           }
           busk_primer_bloq_lib(archivo);
           busk_primer_inodo_lib(archivo);
                   x=0;
           while(conte[x] != 0){
                  x++;
               }
            sprintf(bloq_inodo.tamanio,"%d",x);
             y = x/64;
             x= x%64;
             if(x != 0){
             y ++;
               }

           sprintf(bloq_inodo.num_bloq,"%d",y);
           strcpy(bloq_inodo.bloq_D1,"0");
           strcpy(bloq_inodo.bloq_D2,"0");
           strcpy(bloq_inodo.bloq_D3,"0");
           strcpy(bloq_inodo.bloq_D4,"0");
           strcpy(bloq_inodo.bloq_i1,"0");
           guardando_info_arch_ext3(archivo,conte);
           aux_puntero = atoi(super_b.apuntador_raiz) + ((ubicacion-1) * 130);
           fseek(archivo,aux_puntero,0);
           fwrite(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
         //  guarda_bita(ruta,2,1,conte,archivo);


    }


 int  modificar(char ruta[120],FILE *archivo){
  int x =0;
   int home =0;
   int y =0;
   int aux_puntero=0;
   char busk[10]=" ";
   int existe =0;
  while(ruta[x] != 0 ){
    if(x > 0){
       if(ruta[x] == '/'){
      y = busk_arch(busk,1,archivo);
      if(y > 0){
        aux_puntero = atoi(super_b.apuntador_raiz) + ((y-1) * 130);
        fseek(archivo,aux_puntero,0);
        fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
        y=0;
     limpiar(busk);
      }
      else{
      y=-1;
      printf("\n\n------------CARPETA %s NO EXITE----------\n",busk);
      break;
      }

       }
       else{
           if( y < 10){
              busk[y]=ruta[x];
               }
     y++;
     home++;

       }
    }

  else{
   if(x== 0 && ruta[x]== '/'){
      aux_puntero = atoi(super_b.apuntador_raiz);
      fseek(archivo,aux_puntero,0);
      fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

   }
    else{
     y=-1;
     break;
     printf("\n\n------------ERROR  RUTA NO VALIDA R----------\n\n");

    }
  }
  x++;
  }

  if(y >= 0){
         if(home != 0){

          y= busk_arhivo_modificar(busk,1,archivo);

          if(y != 0){
           existe =y;
           aux_puntero = atoi(super_b.apuntador_raiz) + ((y-1) * 130);
           fseek(archivo,aux_puntero,0);
           fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
           printf("\n\n___________________________________________________\n\n");
           printf("NOMBRE : %s \n",busk);
           printf("TAMAÑO : %s \n",bloq_inodo.tamanio);
           printf("FECHA DE CREACION: %s",bloq_inodo.fecha_creacion);
           printf("\n\n__________________ CONTENIDO ACTUAL _________________\n\n");
           listar_arch(archivo,1);
           printf("\n\n____________________________________________________\n\n");

          }
          else{
          printf("\n\n------------ ERROR ARCHIVO NO EXISTE  * %s *  -----------\n\n",busk);
          }


     }
              else{
          printf("\n\n------------ error NO SE PERMITE LA ACCION ----------\n\n");
                  }
  }
  else{
      printf("\n\n------------ERROR  RUTA NO VALIDA----------\n\n");
    }
  return existe;
}


/******************************************************************************************************************/


/*******************************************************************************************************************/

int lee_busk3(int bloque,char busk[10],FILE *archivo){
int result = 0;
char contenido[100]=" ";
int ubicacion;
int x;
       ubicacion = atoi(super_b.apuntador_bloq) + ((bloque - 1)*67);
       fseek(archivo,ubicacion,0);
      fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
       strcat(contenido,bloq_arch.nombre);
        strcat(contenido,"__");
       strcat(contenido,bloq_arch.inodo);

           x = strcmp(busk,bloq_arch.nombre);
       if(x == 0){
         result = atoi(bloq_arch.inodo);
      }

          fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
          strcat(contenido,"  ");
          strcat(contenido,bloq_arch.nombre);
          strcat(contenido,"__");
          strcat(contenido,bloq_arch.inodo);
       x = strcmp(busk,bloq_arch.nombre);
       if(x == 0){
        result = atoi(bloq_arch.inodo);
      }

       fread(&bloq_arch,sizeof(bloq_arch),1,archivo);
       strcat(contenido,"  ");
       strcat(contenido,bloq_arch.nombre);
       strcat(contenido,"__");
       strcat(contenido,bloq_arch.inodo);
       x = strcmp(busk,bloq_arch.nombre);
       if(x == 0){
        result = atoi(bloq_arch.inodo);
      }


      if(result != 0){
          printf("___________________________ %d_______________________\n\n",bloque);
          printf(" %s\n\n",contenido);
          printf("___________________________ %d_______________________\n\n",bloque);
          printf("                             |\n");
          printf("                             |\n");
          printf("                             v\n");



          }

return result;
}


int busk_arch2(char busk[10],int tipo,FILE *archivo){
  int aux_bloque = 0;
  int aux_bloque2 = 0;
  switch(tipo){
   case 1:

          aux_bloque2 = lee_busk3(atoi(bloq_inodo.bloq_D1),busk,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = busk_arch2(busk,2,archivo);
      }
      break;

   case 2:
           if(atoi(bloq_inodo.bloq_D2 )== 0){

       }
          else{
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D2)-1)*67);
          aux_bloque2 = lee_busk3(aux_bloque,busk,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = busk_arch2(busk,3,archivo);
      }
      }
        break;

   case 3:
      if(atoi(bloq_inodo.bloq_D3)== 0){

       }
          else{
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D3)-1)*67);
          aux_bloque2 = lee_busk3(aux_bloque,busk,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = busk_arch2(busk,4,archivo);
      }
        }
        break;
   case 4:
      if(atoi(bloq_inodo.bloq_D4 )== 0){

       }
          else{
      aux_bloque= atoi(super_b.apuntador_bloq) + ((atoi(bloq_inodo.bloq_D4)-1)*67);
          aux_bloque2 = lee_busk3(aux_bloque,busk,archivo);
      if(aux_bloque2 == 0){
       aux_bloque2 = busk_arch2(busk,5,archivo);
      }
        }

        break;

   case 5:
             if(atoi(bloq_inodo.bloq_i1 )== 0){

       }
          else{
      aux_bloque= atoi(super_b.apuntador_raiz) + ((atoi(bloq_inodo.bloq_i1)-1)*130);
          fseek(archivo,aux_bloque,0);
      fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
      aux_bloque2 = busk_arch2(busk,1,archivo);
      }
      break;
   default :
        printf("----------ERROR EN BUSQUE  wtf --------------");
   break;
 }

 return aux_bloque2;
}



void ver_directrio_especial_bloques(char ruta[120] ,FILE *archivo){
  int x =0;
   int home =0;
   int y =0;
   int aux_puntero=0;
   char busk[10]=" ";
  printf("\n\n___________________________INICIO DE GRAFICA_______________________\n");
  while(ruta[x] != 0){
    if(x > 0){
       if(ruta[x] == '/'){
      y = busk_arch2(busk,1,archivo);
      if(y > 0){
        aux_puntero = atoi(super_b.apuntador_raiz) + ((y-1) * 130);
        fseek(archivo,aux_puntero,0);
        fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
        y=0;
     limpiar(busk);

      }
      else{
      y=-1;
      break;
      }

       }
       else{
           if(y <10){
         busk[y]=ruta[x];
        }
     y++;
     home++;

       }
    }

  else{
   if(x== 0 && ruta[x]== '/'){
      aux_puntero = atoi(super_b.apuntador_raiz);
      fseek(archivo,aux_puntero,0);
      fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);

   }
    else{
     y=-1;
     break;
     printf("\n\n------------ERROR  RUTA NO VALIDA ----------\n\n");

    }
  }
  x++;
  }

  if(y >= 0){

         if(home != 0){
          y = busk_arch(busk,1,archivo);
       aux_puntero = atoi(super_b.apuntador_raiz) + ((y-1) * 130);
        fseek(archivo,aux_puntero,0);
        fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
          }
              else{
          y=2;
          }

if(y > 0){
         if(atoi(bloq_inodo.tamanio) >0){
              printf("\nCONTENIDO\n");

        listar_arch(archivo,1);
             }
             else{
                printf("\nlista de archivos\n");

        listar_arch(archivo,0);
                 }


  printf("\n\n______________________________________________________-\n\n");

     }
    else{
      printf("\n\n------------ERROR  RUTA NO VALIDA -->%s  NO EXISTE----------\n\n",busk);
    }
  }
  else{
      printf("\n\n------------ERROR  RUTA NO VALIDA----------\n\n");
    }

}


/****************************************************************************************************************/


/*******  fucion especial para recorrido de inodos*****************/
void ver_directrio_especial(char ruta[120] ,FILE *archivo){
  int x =0;
   int home =0;
   int y =0;
   int aux_puntero=0;
   char busk[10]=" ";
  printf("\n\n___________________________INICIO DE GRAFICA_______________________\n");
  while(ruta[x] != 0){
    if(x > 0){
       if(ruta[x] == '/'){
      y = busk_arch(busk,1,archivo);
      if(y > 0){
        aux_puntero = atoi(super_b.apuntador_raiz) + ((y-1) * 130);
        fseek(archivo,aux_puntero,0);
        fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
        printf("\n\n_________________________%s____________________________\n",bloq_inodo.id_inodo);
        printf("\nApuntador D1 : %s \nApuntador D2 : %s \nApuntador D3 : %s \nApuntador D4 : %s \nApuntador I1 : %s",bloq_inodo.bloq_D1,bloq_inodo.bloq_D2,bloq_inodo.bloq_D3,bloq_inodo.bloq_D4,bloq_inodo.bloq_i1);
        printf("\nTAMAÑO : %s \nCamtidad de Bloues asig : %s \nFecha de modificacion : %s \nFecha de creacion : %s",bloq_inodo.tamanio,bloq_inodo.num_bloq,bloq_inodo.fecha_mod,bloq_inodo.fecha_creacion);
        printf("\n\n_______________________ %s____________________________\n",bloq_inodo.id_inodo);
        printf("                          |\n");
        printf("                          |\n");
        printf("                          v\n");
        y=0;
     limpiar(busk);

      }
      else{
      y=-1;
      break;
      }

       }
       else{
           if(y <10){
         busk[y]=ruta[x];
        }
     y++;
     home++;

       }
    }

  else{
   if(x== 0 && ruta[x]== '/'){
      aux_puntero = atoi(super_b.apuntador_raiz);
      fseek(archivo,aux_puntero,0);
      fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
      printf("\n\n________________________ %s___________________________\n",bloq_inodo.id_inodo);
      printf("\nApuntador D1 : %s \nApuntador D2 : %s \nApuntador D3 : %s \nApuntador D4 : %s \nApuntador I1 : %s",bloq_inodo.bloq_D1,bloq_inodo.bloq_D2,bloq_inodo.bloq_D3,bloq_inodo.bloq_D4,bloq_inodo.bloq_i1);
      printf("\nTAMAÑO: %s \nCamtidad de Bloues asig : %s \nFecha de modificacion : %s \nFecha de creacion : %s",bloq_inodo.tamanio,bloq_inodo.num_bloq,bloq_inodo.fecha_mod,bloq_inodo.fecha_creacion);
      printf("\n\n_______________________ %s____________________________\n",bloq_inodo.id_inodo);
      printf("                           |\n");
      printf("                           |\n");
      printf("                           v\n");
   }
    else{
     y=-1;
     break;
     printf("\n\n------------ERROR  RUTA NO VALIDA ----------\n\n");

    }
  }
  x++;
  }

  if(y >= 0){

         if(home != 0){
          y = busk_arch(busk,1,archivo);
       aux_puntero = atoi(super_b.apuntador_raiz) + ((y-1) * 130);
        fseek(archivo,aux_puntero,0);
        fread(&bloq_inodo,sizeof(bloq_inodo),1,archivo);
        printf("____________________________ %s___________________________\n",bloq_inodo.id_inodo);
        printf("\nApuntador D1 : %s \nApuntador D2 : %s \nApuntador D3 : %s \nApuntador D4 : %s \nApuntador I1 : %s",bloq_inodo.bloq_D1,bloq_inodo.bloq_D2,bloq_inodo.bloq_D3,bloq_inodo.bloq_D4,bloq_inodo.bloq_i1);
        printf("\nTAMAÑO : %s \nCamtidad de Bloues asig : %s \nFecha de modificacion : %s \nFecha de creacion : %s",bloq_inodo.tamanio,bloq_inodo.num_bloq,bloq_inodo.fecha_mod,bloq_inodo.fecha_creacion);
        printf("\n\n_______________________ %s____________________________\n",bloq_inodo.id_inodo);
        printf("                            |\n");
        printf("                            |\n");
        printf("                            v\n");

          }
              else{
          y=2;
          }

if(y > 0){
         if(atoi(bloq_inodo.tamanio) >0){
              printf("\nCONTENIDO\n");

        listar_arch(archivo,1);
             }
             else{
                printf("\nlista de archivos\n");

        listar_arch(archivo,0);
                 }


  printf("\n\n______________________________________________________-\n\n");

     }
    else{
      printf("\n\n------------ERROR  RUTA NO VALIDA -->%s  NO EXISTE----------\n\n",busk);
    }
  }
  else{
      printf("\n\n ruta no valida \n\n");
    }

}

//REPORTES
void reporte_bitmap_ino(char nombre[25],FILE *archivo){
  int inicio = atoi(super_b.apuntador_inicio);
  char fecha[15];
  char ruta2[150]= "./carpetaRaiz/";;
  int line;
  char lectura;
  time_t tiempo = time(0);
  struct tm *tlocal = localtime(&tiempo);// struct para la hora y fe
  strftime(fecha,15,"%d/%m/%y %H:%M",tlocal);

   strcat(ruta2,datauni.nombre);
   strcat(ruta2,"/reportes/");
   strcat(ruta2,nombre);
   strcat(ruta2,".txt");
   FILE  *reportee;
    reportee= fopen(ruta2,"w");
    if(reportee != NULL){
       fseek(archivo,inicio,0);
       fputs("Reporte del estado de bitmap de inodos EXT3 " , reportee );
       fputs(" \n \n" , reportee );
       fputs("FECHA DE CREACION : " , reportee );
       fputs(fecha, reportee );
       fputs(" \n \n" , reportee );
       fputs(" \n \n" , reportee );
       inicio = atoi(super_b.cant_ino) -1;
        line =39;
       lectura=fgetc(archivo);
        if(lectura == '0'){
          fputs("|0" , reportee );
          printf("|0");
          }
        else{
           fputs("|1" , reportee );
           printf("|1");
              }
       for(inicio = inicio;inicio > 0;inicio--){
         lectura=fgetc(archivo);
         if(lectura == '0'){
           fputs("|0" , reportee );
           printf("|0");
          }
       else{
           fputs("|1" , reportee );
           printf("|1");
              }
         line--;
     if(line == 0){
       fputs(" \n ",reportee );
       printf("\n");
     line= 40;}
       }
       printf("\n\n reporte generado satisfactoriamente \n\n");
       fclose(reportee);

}
}

void reporte_bitmap_bloq(char nombre[25],FILE *archivo){
  int inicio = atoi(super_b.apuntador_bloque);
  char fecha[15];
  char ruta2[150]= "./carpetaRaiz/";
  int line;
  char lectura;
  time_t tiempo = time(0);
  struct tm *tlocal = localtime(&tiempo);// struct para la hora y fe
  strftime(fecha,15,"%d/%m/%y %H:%M",tlocal);

   strcat(ruta2,datauni.nombre);
   strcat(ruta2,"/reportes/");
   strcat(ruta2,nombre);
   strcat(ruta2,".txt");
   FILE  *reportee;
    reportee= fopen(ruta2,"w");
    if(reportee != NULL){
       fseek(archivo,inicio,0);
       fputs("Reporte del estado de bitmap de bloques EXT3 " , reportee );
       fputs(" \n \n" , reportee );
       fputs("FECHA DE CREACION : " ,reportee );
       fputs(fecha, reportee );
        fputs(" \n \n" , reportee );
    fputs(" \n \n" , reportee );
       inicio = atoi(super_b.cant_b) -1;
       line =39;
       lectura=fgetc(archivo);
        if(lectura == '0'){
           fputs("|0" , reportee );
           printf("|0");
          }
        else{
           fputs("|1" , reportee );
           printf("|1");
              }
       for(inicio= inicio;inicio > 0;inicio--){
         lectura=fgetc(archivo);
         if(lectura == '0'){
           fputs("|0" , reportee );
           printf("|0");
          }
       else{
           fputs("|1" , reportee );
           printf("|1");
              }

         line--;
     if(line == 0){
       fputs(" \n ", reportee );
       printf("\n");
     line= 40;}
       }
       printf("\n\n reporte generado satisfactoriamente \n\n");
       fclose(reportee);

}
}

void reporte_bita(char nombre[25],FILE *archivo){
  int ini = atoi(super_b.apuntador_bitacora);
  char fech[15];
  char rut[150]= "./carpetaRaiz/";

  time_t tiempo = time(0);
  struct tm *tlocal = localtime(&tiempo);
  strftime(fech,15,"%d/%m/%y %H:%M",tlocal);
   strcat(rut,datauni.nombre);
   strcat(rut,"/reportes/");
   strcat(rut,nombre);
   strcat(rut,".txt");
   FILE  *bitacora;
     bitacora= fopen(rut,"w");
    if(bitacora != NULL){

       fputs("Reporte del estado de bitmap de Bloques EXT3 " ,bitacora);
       fputs(" \n \n" , bitacora );
       fputs("FECHA DE CREACION : " ,bitacora );
       fputs(fech,bitacora);
        fputs(" \n \n" ,bitacora);
    fputs(" \n \n" ,bitacora);
       fseek(archivo,ini,0);
    ini = atoi(super_b.cant_bita);
    for(ini = ini ; ini > 0 ; ini-- ){
    fread(&bloq_bita,sizeof(bloq_bita),1,archivo);
     if(atoi(bloq_bita.tipo) == 1){
      fputs("ACCION : ",bitacora );
      fputs(bloq_bita.opercion,bitacora);
      fputs("       TIPO: ",bitacora );
      fputs(" ARCHIVO ",bitacora );
      fputs("       DIRECCION: ",bitacora );
      fputs(bloq_bita.direccion,bitacora);
      fputs("       FECHA : ",bitacora );
      fputs(bloq_bita.fecha,bitacora);
      fputs("       CONTENIDO : ",bitacora );
      fputs(bloq_bita.contenido,bitacora);
       fputs("\n\n" ,bitacora);
     }
     else{
        if(atoi(bloq_bita.tipo) == 0){
      fputs("ACCION : ",bitacora );
      fputs(bloq_bita.opercion,bitacora);
      fputs("       TIPO: ",bitacora );
      fputs(" CAPETA ",bitacora );
      fputs("       DIRECCION: ",bitacora );
      fputs(bloq_bita.direccion,bitacora);
      fputs("       FECHA : ",bitacora );
      fputs(bloq_bita.fecha,bitacora);

       fputs("\n\n" ,bitacora);
     }
         }
    }

       printf("\n\n reporte generado satisfactoriamente \n\n");
       fclose(bitacora);

}
}



//reportes
void reportes(){
   char selec [2];
   int  opcion =0;
   system("clear");
   do{

   printf("                                                     Reportes\n\n");
   printf("1- Reporte de bitmap de Inodos\n");
   printf("2- Reporte de bitmap de bloques\n");
   printf("3- Reporte de bitacora (LOG) \n");
   printf("4- Volver\n");
   printf("Seleccione la opcion que deseas ejecutar:\n");
   scanf("%s",selec);
   opcion= atoi(selec);
   switch(opcion){
     case 1:
         if(estado.unidad1 == '1'){
                 reporte_bitmap_ino("BITMAPI",estado.disco1);

            }
            else{
                reporte_bitmap_ino("BITMAP_I",estado.disco2);

                }
     break;
     case 2:
         if(estado.unidad1 == '1'){
                       reporte_bitmap_bloq("BITMAP_B",estado.disco1);

            }
            else{
                       reporte_bitmap_bloq("BITMAP_B",estado.disco2);
                }
    break;
    case 3:
         if(estado.unidad1 == '1'){
                reporte_bita("LOG",estado.disco1);
            }
            else{
                reporte_bita("LOG",estado.disco2);
                }
    break;
      case 4:

    break;

     default:
       printf(" Opcion no valida ");
       break;
   }

 } while(opcion != 4 );
 system("clear");
 }


// ARCHIVOS DE DATOS..................................................................

void archivos_de_datos(){
  int selec=0;
  char opcion[2];
  char ruta[120] ;
  char conte[600];
  char nuevo3[10];
  char ruta2[120];
   system("clear");
  do{
  printf("                                         Manejador de archivos\n\n");
  printf("1- Crear archivo \n");
  printf("2- Leer archivo: \n");
  printf("3- Eliminar archivo: \n");
  printf("4- Buscar archivo:  \n");
  printf("5- Renombrar archivo:   \n");
  printf("6- Editar archivo: \n");
   printf("7- Volver \n");
  printf("Selecciona la opcion a realizar: \n");
  scanf("%s",opcion);

  selec= atoi(opcion);

  switch(selec){
    case 1:
       system("clear");
       printf("Ingrese la ruta para el nuevo archivo: \n");
       scanf("%s",ruta);
       printf("Ingrese el contenido para el archivo: \n");
      scanf("%*c%[^\n]",conte);

     if(estado.unidad1 != '2'){
            craccion_guardado_ext3(ruta,1,conte,estado.disco1); //creo la carpeta en el disco1
            fseek(estado.disco1,512,0);
            fwrite(&super_b,sizeof(super_b),1,estado.disco1); //guardo los cambios del super bloque
            }
      if(estado.unidad2 != '2'){
            fseek(estado.disco2,512,0); //leeo el super bloque del disco2 para optener el estado
            fread(&super_b,sizeof(super_b),1,estado.disco2);
            craccion_guardado_ext3(ruta,1,conte,estado.disco2);//creo la carpeta en el disco1
            fseek(estado.disco2,512,0);
            fwrite(&super_b,sizeof(super_b),1,estado.disco2);//creo la carpeta en el disco1
            }

      break;
  case 2:
        system("clear");
       printf("Ingrese la ruta del archivo que desea leer: \n");
       scanf("%s",ruta);

      /* verificacion de unidad activa */
       if(estado.unidad1 == '1'){
        ver_directrio_y_archivo_ext3(ruta,1,estado.disco1);
            }
        else{
        ver_directrio_y_archivo_ext3(ruta,1,estado.disco2);
         }

      break;
  case 3:
       system("clear");
       printf("Ingrese ruta del archivo que desea eliminar: \n");
       scanf("%s",ruta);

       if(estado.unidad1 != '2'){
            renom_elimi(ruta,nuevo3,1,1,estado.disco1);
            fseek(estado.disco1,512,0);
            fwrite(&super_b,sizeof(super_b),1,estado.disco1); //guardo los cambios del super bloque
            }
      if(estado.unidad2 != '2'){
            fseek(estado.disco2,512,0);
            fread(&super_b,sizeof(super_b),1,estado.disco2);
            renom_elimi(ruta,nuevo3,1,1,estado.disco2);
            fseek(estado.disco2,512,0);
            fwrite(&super_b,sizeof(super_b),1,estado.disco2);//creo la carpeta en el disco1
            }


      break;
  case 4:
      system("clear");
      printf("Ingrese el nombre del archivo que desea buscar: \n");
      scanf("%s",nuevo3);

        system("clear");
        printf("Resultados: \n\n");
        strcpy(ruta2,"/");
        selec =atoi(super_b.apuntador_raiz);

                     /* verificacion de unidad activa */
       if(estado.unidad1 == '1'){

        fseek(estado.disco1,selec,0);
        fread(&aux_bloq_ind,sizeof(aux_bloq_ind),1,estado.disco1);
        selec=0;
        selec = busk_archivo_carpeta(estado.disco1,aux_bloq_ind,1,ruta2,nuevo3);

            }
        else{

        fseek(estado.disco2,selec,0);
        fread(&aux_bloq_ind,sizeof(aux_bloq_ind),1,estado.disco2);
        selec =0;
        selec = busk_archivo_carpeta(estado.disco2,aux_bloq_ind,1,ruta2,nuevo3);

         }

       printf("*-*  %d  resultados de la busqueda \n\n\n",selec);

      break;
  case 5:
        system("clear");
       printf("Ingrese ruta del archivo que desea renombrar: \n");
       scanf("%s",ruta);
       printf("Ingrese el nuevo nombre para el archivo: \n");
      scanf("%s",nuevo3);

      if(estado.unidad1 != '2'){
           renom_elimi(ruta,nuevo3,0,1,estado.disco1);
            }
      if(estado.unidad2 != '2'){
           renom_elimi(ruta,nuevo3,0,1,estado.disco2);
            }

      break;
   case 6:
    system("clear");
       printf("Ingresar ruta del archivo que deseas modificar: \n");
       scanf("%s",ruta);
       if(estado.unidad1 == '1'){
        selec = modificar(ruta,estado.disco1);
            }
        else{
         selec = modificar(ruta,estado.disco2);
         }
           if(selec != 0 ){
               printf("Ingrese el contenido para el nuevo archivo: \n");
                scanf("%*c%[^\n]",conte);
               }

       if(estado.unidad1 != '2' && selec != 0){
            modifica(selec,conte,estado.disco1);
            fseek(estado.disco1,512,0);
            fwrite(&super_b,sizeof(super_b),1,estado.disco1); //guardo los cambios del super bloque
            printf("\n\n     modificacion de archivo: satisfactorio   \n\n");
            }
      if(estado.unidad2 != '2' && selec != 0){
            fseek(estado.disco2,512,0); //leeo el super bloque del disco2 para optener el estado
            fread(&super_b,sizeof(super_b),1,estado.disco2);
            modifica(selec,conte,estado.disco2);
            fseek(estado.disco2,512,0);
            fwrite(&super_b,sizeof(super_b),1,estado.disco2);//creo la carpeta en el disco1
            printf("\n\n     modificacion de archivo: satisfactorio   \n\n");
            }

      break;

   case 7:
      system("clear");
     break;

   default:
     break;
  }

  }while(selec != 7);

}

void  directorios(){
  int selec=0;
  char opcion[2];
  char ruta[120] ;
  char conte [600];
  char ruta2[120] ;
  char nuevo3[10];

   system("clear");
  do{

  printf("                                         Manejo de directorios\n\n");
  printf("1- Crear carpeta \n");
  printf("2- Eliminar carpeta \n");
  printf("3- Listar carpeta \n");
  printf("4- Listar recursivo  \n");
  printf("5- Buscar carpeta \n");
  printf("6- Volver \n\n");
  printf("Seleccione la opcion a ejecutar: \n");
  scanf("%s",opcion);
  selec= atoi(opcion);

  switch(selec){
    case 1:
       system("clear");
       printf("Ingrese ruta para la nueva carpeta: \n");
       scanf("%s",ruta);
       if(estado.unidad1 != '2'){
            craccion_guardado_ext3(ruta,0,conte,estado.disco1); //creo la carpeta en el disco1
            fseek(estado.disco1,512,0);
            fwrite(&super_b,sizeof(super_b),1,estado.disco1); //guardo los cambios del super bloque
            }
      if(estado.unidad2 != '2'){
            fseek(estado.disco2,512,0); //leeo el super bloque del disco2 para optener el estado
            fread(&super_b,sizeof(super_b),1,estado.disco2);
            craccion_guardado_ext3(ruta,0,conte,estado.disco2);//creo la carpeta en el disco1
            fseek(estado.disco2,512,0);
            fwrite(&super_b,sizeof(super_b),1,estado.disco2);//creo la carpeta en el disco1
            }

      break;

  case 2:
      break;

  case 3:
    system("clear");
       printf("Ingrese ruta para listar carpetas: \n");
       scanf("%s",ruta);

      /* verificacion de unidad activa */
       if(estado.unidad1 == '1'){
        ver_directrio_y_archivo_ext3(ruta,0,estado.disco1);
            }
        else{
        ver_directrio_y_archivo_ext3(ruta,0,estado.disco2);
         }

      break;
  case 4:
        system("clear");
       printf("Ingrese ruta para listar carpetas:\n");
       scanf("%s",ruta);

      /* verificacion de unidad activa */
       if(estado.unidad1 == '1'){
        ver_directrio_y_archivo_ext3(ruta,3,estado.disco1);
            }
        else{
        ver_directrio_y_archivo_ext3(ruta,3,estado.disco2);
         }
      break;
  case 5:
           system("clear");
      printf("Ingrese el nombre de la carpeta que desea buscar:\n");
      scanf("%s",nuevo3);


        system("clear");
        printf(" \n\n");
        strcpy(ruta2,"/");
        selec =atoi(super_b.apuntador_raiz);

                     /* verificacion de unidad activa */
       if(estado.unidad1 == '1'){

        fseek(estado.disco1,selec,0);
        fread(&aux_bloq_ind,sizeof(aux_bloq_ind),1,estado.disco1);
        selec=0;
        selec = busk_archivo_carpeta(estado.disco1,aux_bloq_ind,0,ruta2,nuevo3);

            }
        else{

        fseek(estado.disco2,selec,0);
        fread(&aux_bloq_ind,sizeof(aux_bloq_ind),1,estado.disco2);
        selec=0;
        selec = busk_archivo_carpeta(estado.disco2,aux_bloq_ind,0,ruta2,nuevo3);

         }
      printf("_________________________________________\n\n");

      printf("*-*  %d  resultados de la busqueda \n\n\n",selec);

      break;
   case 6:
     system("clear");
      break;

   default:
     break;

  }

  }while(selec != 6);

}

//otras funciones
void funciones_especiales(){
   char selec2 [2];
   int  opcion2 =0;
   char rut[120];
   int posssb;
   int canti_b = atoi(super_b.cant_b);
   system("clear");
   do{

   printf("___________________ MENU DE OPCIONES  ESPECIALES _________________\n\n");
   printf("1- VER RUTA CON INODOS \n");
   printf("2- VER RUTA POR  BLOQES\n");
   printf("3- LISTAR UN BLOQUE POR ID \n");
   printf("4- REGRESAR \n");
   printf("SELECIONE LA  OPCION QUE DESEA REALIZAR\n");
   scanf("%s",selec2);
   opcion2= atoi(selec2);
   switch(opcion2){
     case 1:
            system("clear");
           printf("\n\n Ingresa ruta que deseas ver:\n");
           scanf("%s",rut);
           system("clear");
           if(estado.unidad1 == '1'){
       ver_directrio_especial(rut,estado.disco1);
              }
              else{
                  ver_directrio_especial(rut,estado.disco2);
              }
     break;

     case 2:
       system("clear");
           printf("\n\n Ingresa ruta que deseas ver:\n");
           scanf("%s",rut);
           system("clear");
           if(estado.unidad1 == '1'){
                 ver_directrio_especial_bloques(rut,estado.disco1);
              }

    break;
    case 3:
        system("clear");
       printf("\n\n Ingrese ID del bloque que deseas ver: \n");
       scanf("%s",rut);
       posssb= atoi(rut);
       if(posssb>0 &&  posssb < canti_b){
        canti_b = atoi(super_b.apuntador_bloq) + ((posssb -1)* 67);

              if(estado.unidad1 == '1'){
        fseek(estado.disco1,canti_b,0);
        printf("\n\n******************%d******************\n\n",posssb);

        fread(&bloq_arch,sizeof(bloq_arch),1,estado.disco1);
        if(atoi(bloq_arch.usado)>0){
        printf("%s       %s      %s",bloq_arch.nombre,bloq_arch.inodo,bloq_arch.usado);
        fread(&bloq_arch,sizeof(bloq_arch),1,estado.disco1);
        printf("  %s       %s      %s",bloq_arch.nombre,bloq_arch.inodo,bloq_arch.usado);
        fread(&bloq_arch,sizeof(bloq_arch),1,estado.disco1);
        printf(" %s       %s      %s",bloq_arch.nombre,bloq_arch.inodo,bloq_arch.usado);
          }
          else{
        fseek(estado.disco1,canti_b,0);
        fread(&bloq_dato,sizeof(bloq_dato),1,estado.disco1);
        printf("%s ",bloq_dato.datos);

               }
       printf("\n\n*******************%d**************************\n\n\n",posssb);
              }
              else{
            fseek(estado.disco2,canti_b,0);
        printf("\n\n******************%d********************\n\n",posssb);

        fread(&bloq_arch,sizeof(bloq_arch),1,estado.disco2);
        if(atoi(bloq_arch.usado)>0){
        printf("%s       %s      %s",bloq_arch.nombre,bloq_arch.inodo,bloq_arch.usado);
        fread(&bloq_arch,sizeof(bloq_arch),1,estado.disco2);
        printf("  %s       %s      %s",bloq_arch.nombre,bloq_arch.inodo,bloq_arch.usado);
        fread(&bloq_arch,sizeof(bloq_arch),1,estado.disco2);
        printf(" %s       %s      %s",bloq_arch.nombre,bloq_arch.inodo,bloq_arch.usado);
          }
          else{
        fseek(estado.disco2,canti_b,0);
        fread(&bloq_dato,sizeof(bloq_dato),1,estado.disco2);
        printf("%s ",bloq_dato.datos);

               }
               printf("\n\n *******************%d**************************\n\n\n",posssb);
              }

       }

    break;
     case 4:
      break;

     default:
       printf(" Opcion no disponible  \n\n");
       break;
   }

 } while(opcion2 != 4 );
 system("clear");
 }

//ARCHIVOS Y CARPETAS
void manejador_de_archi_y_carpe(){
   char selec [2];
   int  opcion =0;
   time_t tiempo = time(0);
   struct tm *tlocal = localtime(&tiempo);// struct para la hora y fecha


   system("clear");
   do{

   printf("                                                  Submenu\n\n");
   printf("1- Archivos \n");
   printf("2- Carpertas\n");
   //printf("3- FUNCIONES ESPECIALES\n");
   printf("4- Reportes\n");
   printf("5- Salir \n\n");
   printf("Seleccionar numero de opcion a ejecutar: \n");
   scanf("%s",selec);
   opcion= atoi(selec);
   switch(opcion){
     case 1:
        archivos_de_datos();
     break;
     case 2:
        directorios();
    break;
    case 3:
        // funciones_especiales();
    break;
     case 4:
             reportes();
       break;
     case 5:
     if(estado.unidad1 != '2'){
            strftime(super_b.fecha_desmont,20,"%d/%m/%y %H:%M:%S",tlocal);
            fseek(estado.disco1,512,0);
            fwrite(&super_b,sizeof(super_b),1,estado.disco1);
            }
      if(estado.unidad2 != '2'){
              strftime(super_b.fecha_desmont,20,"%d/%m/%y %H:%M:%S",tlocal);
            fseek(estado.disco2,512,0);
            fwrite(&super_b,sizeof(super_b),1,estado.disco2);
            }
            system("clear");

       break;
     default:
       printf(" Opcion no disponible  \n\n");
       break;
   }

 } while(opcion != 5 );
 system("clear");
 }

//SE SELECCIONA EL DISCO
void montardisco(){

int aux=0;
int total_d=1;
char carac[2];

FILE *archilect;
  do{
    total_d=1;
    char noms[120]="./carpetaRaiz/";
archilect= fopen("./carpetaRaiz/centralizador.xxx","r");
if(archilect == NULL){
  aux=1;
printf("Error");
}
else{
       printf("\n\n                                Montar disco duro\n");

    fread(&datauni, sizeof(datauni), 1,archilect);

 while (feof(archilect)==0)
            {
            printf("\n%d- Nombre:%s     Tamaño:%s (MB)",total_d, datauni.nombre,datauni.tamanio);
                fread(&datauni, sizeof(datauni), 1,archilect);
        total_d++;

            }

            printf("\n%d- Volver\n\n",total_d);


printf("Seleccione el disco duro a utilizar: \n");
scanf("%s",carac);
aux= atoi(carac);
       if(aux == total_d){
            system("clear");
       }
       else if(aux >0 && aux< total_d){
       total_d=57*(aux-1);//cris formula
       rewind(archilect);
       fseek(archilect,total_d,0);
       fread(&datauni, sizeof(datauni), 1,archilect);
       fclose(archilect);

       strcpy(estado.direccion,noms);
       strcat(estado.direccion,datauni.nombre);
       strcat(estado.direccion,"/");
       strcat(estado.direccion,datauni.nombre);

    // VERIFICA SI EL ARCHIVO1 ESTA BORRADO..
       strcpy(noms,estado.direccion);
       strcat(noms,".bin");
       if( fopen(noms,"r") == NULL){
              estado.unidad1 ='2';
           }
        else{
            estado.disco1 = fopen(noms,"r+");
            }

    // VERIFICA1 SI EL ARCHIVO ESTA BORRADO..
       strcpy(noms,estado.direccion);
       strcat(noms,"2.bin");
       if( fopen(noms,"r") == NULL){
              estado.unidad2 ='2';
           }
           else{
               estado.disco2 = fopen(noms,"r+");
               }
            system("clear");
       do{
      /* printf("SELECIONE CON QUE UNIDAD DESEA ARRANCAR \n");
       printf("1- %s1  \n",datauni.nombre);
       printf("2- %s2 \n",datauni.nombre);
       printf("3- REGRESAR MENU ANTERIOR\n"); */
       //scanf("%s",carac);

       aux= atoi(carac);
       aux = 1; //cris
       switch(aux){
          case 1:
       if(estado.unidad1 == '2'){// verifica si la unidad esta activa
            printf("\n Disco duro no disponible \n\n");
            aux=4;
            }
            else{
       /* coloca la unidad como activa y  obtengo los datos del superbloque*/
         estado.unidad1= '1';
         fseek(estado.disco1,512,0);
         fread(&super_b, sizeof(super_b),1,estado.disco1);
                }
         break;
       case 2:

       if(estado.unidad2 == '2'){  // verifica si la unidad esta activa
            printf("\n Disco duro no disponible \n\n");
            aux=4;
            }
            else{
         /*coloca la unidad como activa y  obtengo los datos del superbloque*/
                estado.unidad2 = '1';
         fseek(estado.disco2,512,0);
         fread(&super_b, sizeof(super_b),1,estado.disco2);
                }

             break;
          case 3:
                   system("clear");
            break;

         default :
              printf("\n Opcion no disponible \n\n");
         break;
           }


       }
       while((aux <1) | (aux >3));

    if((aux >0) &&(aux < 3)){
        manejador_de_archi_y_carpe();
        }
    if(estado.unidad2 != '2'){
    fclose(estado.disco2);
    }
    if(estado.unidad1 != '2'){
    fclose(estado.disco1);
   }

       }
       else {
         aux= 2;
         printf("\n Opcion no disponible \n\n");
       }
    }
 } while( aux != total_d);

}

//CREA ARCHIVOS Y DA FORMATO EXT3
 void menucrear(){

 int t=0;
  char auxt[7];
  int tama=0;
  char nom1[100]="./carpetaRaiz/";

  char creaC[100]="mkdir ./carpetaRaiz/";

printf("\n Ingrese el nombre para el disco: \n");
scanf("%s",datauni.nombre);
/*do{
  if(t != 0){  printf("\nTAMAÑO DE DISCO INVALINO TIENE QUE SER MULTIPLO DE 4\n\n");}*/
  printf("Ingresar tamaño de disco duro a crear ( MB)\n");
scanf("%d",&t);

/*}while( t%4 != 0);*/ //cris
sprintf(auxt,"%d",t);
strcpy(datauni.tamanio,auxt);

/* creacion de carpetas */
strcat(creaC,datauni.nombre);
system(creaC);
strcat(creaC,"/reportes");
system(creaC);

strcat(nom1,datauni.nombre);
strcat(nom1,"/");
strcat(nom1,datauni.nombre);
strcat(nom1,".bin");

 /*creacion  del MBR*/
    strcpy(datos.inicioP,"512");
    strcpy(datos.tipo_sis,"EXT3_J");
    strcpy(datos.tipo_p,"EX3");
    strcpy(datos.parti_act,"0");
    sprintf(datos.tamanio,"%d",t);

FILE *archivo;

//SE CREA EL DISCO DURO
archivo= fopen(nom1,"a");
tama= (t*1000*1000);
 for(tama = tama;tama>0;tama--){
  fprintf(archivo,"0");
 }

fclose(archivo);

archivo= fopen(nom1,"r+");
 //ESCRIBIENDO MBR
    fwrite(&datos,sizeof(datos),1,archivo);
 //SE LE DA FORMATO EXT3
   tama = ((t-1)*1000*1000) -512;

   ext3_j(tama,512,archivo);

fclose(archivo);

archivo= fopen("./carpetaRaiz/centralizador.xxx","a");
fwrite(&datauni,sizeof(datauni),1,archivo);

    fclose(archivo);
}

//MENU RAIZ
 void menuInicio(){
  system("clear");
  int i=0;
  char se[2];
  do{
   i=0;
printf("                                          MENU RAIZ \n");
printf("1- Crear disco duro\n");
printf("2- Manejador de discos duros\n");
printf("3- Salir\n\n");


printf("Seleccione el numero de opcion que desea ejecutar: \n");
scanf("%s",se);
i = atoi(se);
switch(i){
  case 1:
    system("clear");
    menucrear();
     i=200;
  break;
  case 2:
    system("clear");
    montardisco();
   i=100;
  break;
  case 3:
    system("clear");
   printf("\n sistema apagado/inactivo n\n");
    void exit(int status);
    i=3;
  break;
  default:
    system("clear");
    printf("\n  Opcion no disponible\n\n");
    i=10000;
  break;
}
} while(i!=1 && i!=2 && i!=3 );
}

 /*

int main(){

system("mkdir carpetaRaiz");
system("clear");
 FILE *archivo;
archivo = fopen("./carpetaRaiz/centralizador.xxx","r");
    if (archivo == NULL){
     archivo = fopen("./carpetaRaiz/centralizador.xxx","w+");
    }
   fclose(archivo);
menuInicio();

return 0;
}

*/
