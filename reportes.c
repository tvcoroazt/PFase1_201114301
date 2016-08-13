#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "reportes.h"
#include "particion.h"
#include "disk.h"



void reporteMbr(char* path, char* id){
    MBR mbr;
    EBR ebr;


    particiones parti;
    parti = ExisteParticion(id);

    if(strcmp(parti.path,"null")==0) {

        printf("\n X- Aun no existe -X\n");
    }
    else{
        FILE* disco;
        disco = fopen(parti.path,"r");
        if(disco==NULL){
            printf("X - ERROR no existe el disco - X");
        }
        else{
            fseek(disco,0,SEEK_SET);
            fread(&mbr,sizeof(mbr),1,disco);
            FILE* reporte;
            reporte = fopen("reporteMbr.txt","w");
            //reporte = fopen(path,"w");
            if(reporte == NULL){

              printf("\n X- UPSS!! No se pudo crear el reporte - X\n");

            }
            else{
                fprintf(reporte,"digraph G {\n\n");
                fprintf(reporte,"node [shape=plaintext]\n");
                fprintf(reporte,"a [label=<<table border=\"0\" cellborder=\"1\" cellspacing=\"0\">\n\n");
                fprintf(reporte,"<tr><td><b>Nombre</b></td><td><b>Valor</b></td></tr>\n");
                fprintf(reporte,"<tr><td> mbr_tamano         </td><td> %i </td></tr>\n", mbr.mbr_tamano);
                fprintf(reporte,"<tr><td> mbr_fecha_de_creacion  </td><td> %s </td></tr>\n",mbr.fecha_creacion);
                fprintf(reporte,"<tr><td> mbr_disk_signature </td><td> %i </td></tr>\n",mbr.mbr_signature);
                int i; int cont =1;
                for(i=0; i<4; i++){
                    part parti;
                   // part partiebr;
                    parti = mbr.particiones[i];
                 //   partiebr =
                //    if(parti.status=='1'){
                        fprintf(reporte,"<tr><td colspan=\"2\"><b> Particion No. %i</b></td></tr>",cont);
                        fprintf(reporte,"<tr><td> part_status_%i </td><td> %c </td></tr>\n",cont,parti.status);
                        fprintf(reporte,"<tr><td> part_type_%i   </td><td> %c </td></tr>\n",cont,parti.type);
                        fprintf(reporte,"<tr><td> part_fit_%i    </td><td> %c </td></tr>\n",cont,parti.fit);
                        fprintf(reporte,"<tr><td> part_start_%i  </td><td> %i </td></tr>\n",cont,parti.start);
                        fprintf(reporte,"<tr><td> part_size_%i   </td><td> %i </td></tr>\n",cont,parti.size);
                        fprintf(reporte,"<tr><td> part_name_%i   </td><td> %s </td></tr>\n",cont,parti.name);
                        cont++;
                //    }
                }
                //int byteInicio = byteStartLogica(ruta);
                //fseek(disco,byteInicio,SEEK_SET);
                //fread(&ebr,sizeof(ebr),1,disco);


                fprintf(reporte,"<tr><td colspan=\"2\"><b> EBR </b></td></tr>");
                fprintf(reporte,"<tr><td><b>Nombre</b></td><td><b>Valor</b></td></tr>\n");
                fprintf(reporte,"<tr><td> part_status         </td><td> %c </td></tr>\n",ebr.status);
                fprintf(reporte,"<tr><td> part_fit         </td><td> %c </td></tr>\n",ebr.fit);
                fprintf(reporte,"<tr><td> part_start         </td><td> %i </td></tr>\n",ebr.start);
                fprintf(reporte,"<tr><td> part_size         </td><td> %i </td></tr>\n",ebr.size);
                fprintf(reporte,"<tr><td> part_status         </td><td> %c </td></tr>\n",ebr.status);

                fprintf(reporte,"</table>>];\n\n");
                fprintf(reporte,"}");

                fclose(disco);
                fclose(reporte);

                system("dot -Tpng reporteMbr.txt -o reporteMbr.png");
                system("eog reporteMbr.png");
                printf("\n EXITO!! - Reporte Creado \n");
            }
        }
    }

}

void reporteDisco(char* path, char* id){
    particiones parti;
    parti = ExisteParticion(id);


    if(strcmp(parti.path,"null")==0)printf("\n X- Aun no existe -X\n");
    else{
        FILE* disco;
        disco = fopen(parti.path,"r");
        if(disco==NULL){
            printf("X - ERROR no existe el disco - X");
        }
        else{
            MBR mbr;
            fseek(disco,0,SEEK_SET);
            fread(&mbr,sizeof(mbr),1,disco);

            FILE* reporte;
            reporte = fopen("reporteDisco.txt","w");

            if(reporte == NULL){

              printf("\n X- UPSS!! No se pudo crear el reporte - X\n");

            }
            else{
                fprintf(reporte,"graph G {\n");
                fprintf(reporte,"\trankdir = TR;\n\n");
                fprintf(reporte,"\tgraph [bgcolor=\"#F2F2F2\"];\n");
                fprintf(reporte,"\tnode [shape=record style=filled fillcolor=\"#F5DA81\"]\n\n");
                fprintf(reporte,"\tsubgraph cluster0 {\n");
                fprintf(reporte,"\t\tlabel = \"Reporte de Discos %s\";\n",parti.path);
                fprintf(reporte,"\t\tcolor=black;\n");

                int i; int tamLibre = 0;
                tamLibre = tamDisco(parti.path);

                if(tamLibre>0) fprintf(reporte,"\t\tLIBRE [label = \"LIBRE\" ];\n");

                for(i=3; i>=0; i-- ){
                    int libre=0;
                    if(i<3){
                        libre= mbr.particiones[i].start+mbr.particiones[i].size -mbr.particiones[i+1].start;
                    }
                    if(mbr.particiones[i].status == '1'){
                        if(mbr.particiones[i].type == 'e'){
                            fprintf(reporte,"\t\tparti1_%i [label = \"EXTENDIDA\" ];\n",i);
                            if(libre>0)if(libre>0)fprintf(reporte,"\t\tLIBRE%i [label = \"LIBRE\" ];\n",i);

                        }else{
                            fprintf(reporte,"\t\tparti1_%i [label = \"PRIMARIA\" ];\n",i);;
                            if(libre>0)if(libre>0)fprintf(reporte,"\t\tLIBRE%i [label = \"LIBRE\" ];\n",i);
                        }



                        if(mbr.particiones[i].type == 'l'){
                            fprintf(reporte,"\t\tparti1_%i[label = \"LOGICA\" ] ;\n",i);
                            fprintf(reporte,"\t\tLOGICA;\n");
                        }

                    }

                    if(mbr.particiones[i].type == 'e'){
                        fprintf(reporte,"\t\tparti1_%i[label = \"EXTENDIDA\" ] ;\n",i);
                    }
                    if(mbr.particiones[i].type == 'l'){
                        fprintf(reporte,"\t\tparti1_%i[label = \"LOGICA\" ] ;\n",i);
                        fprintf(reporte,"\t\tLOGICA;\n");
                    }


                    EBR ebr;
              /*      int initpart = mbr.particiones[i].part;

                    do{
                        fseek(disk,initpart,SEEK_SET);
                        fread(&ebr,sizeof(EBR),1,disk);

                        if(firstlog == 0){
                            fprintf(tempfile,"%s","<");
                            firstlog = 1;
                        }else{
                            fprintf(tempfile,"%s","|<");
                        }
                        sprintf(dlog,"%d",iterlog);
                        iterlog = iterlog + 1;
                        fprintf(tempfile,d);
                        fprintf(tempfile,dlog);
                        fprintf(tempfile,"%s","> EBR");
                        if(ebr.status == 'a'){
                            fprintf(tempfile,"%s","|");
                            fprintf(tempfile,"%s",ebr.name);
                        }
                        if((ebr.next - (ebr.start + ebr.size)) > 0){
                            fprintf(tempfile,"%s","|Libre");
                        }
                        initpart = ebr.next;
                    }while(ebr.next > -1);*/



                    // probando
                }

                fprintf(reporte,"\t\tMBR;\n\n");
                fprintf(reporte,"\t}\n");
                fprintf(reporte,"}\n");
                fclose(reporte);
                fclose(disco);
                system("dot -Tpng reporteDisco.txt -o reporteDisco.png");
                system("eog reporteDisco.png");
                printf("\n EXITO!! - Reporte Creado \n");
            }
        }
    }
}
