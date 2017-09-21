#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comparador.h"

/*ENTRADA: String linea y string cadena de sucesión
  SALIDA: Entero (0 o 1)
  La función se encarga de buscar si existe una sucesión dentro de una línea 
  de caracteres. Si existe retorna un 1 y en caso contrario, retorna 0. */
int compare(char *line, char *succession){
    if (strstr(line,succession) != NULL){
        return 1;
    }
    else{
        return 0;
    }
}

/*ENTRADA: Archivo de salida, string que contiene la línea y string que contiene la cadena
  de sucesión.
  SALIDA: Void
  Se encarga de imprimir, dentro de un archivo de salida, la línea completa de la cadena de 
  caracteres y al lado una respuesta SI o NO en caso de que haya encontrado el nucleotido o no
  respectivamente.*/
void printFile(FILE* fileSalida,char* buffer, char* succession, int dflag, int processId){
    if(compare(buffer,succession)){
        if(dflag == 1)
            printf("Proceso %d. %s SI\n",processId,buffer);
        fprintf(fileSalida, "%s SI\n", buffer);
    }else{
        if(dflag == 1)
            printf("Proceso %d. %s NO\n",processId,buffer);
        fprintf(fileSalida, "%s NO\n", buffer);
    }   
}

int main(int argc,char *argv[]){
    //*args[] = {fileName,position,succession,lines,id,lastProcess,NULL};
    long int position = atoll(argv[1]); //posicion de donde comienza el proceso
    int lines = atoi(argv[3]); //lineas totales
    int processId = atoi(argv[4]); //numero de proceso
    int lastProcess = atoi(argv[5]); //Indica si es el último proceso
    int dflag = atoi(argv[6]);
    int i = 0;	
    	

    char buffer[200];

    //SE CREA EL NOMBRE DEL ARCHIVO DE SALIDA
    char fileName[50];
    memset(fileName,0,sizeof(fileName));
    strcat(fileName,"rp_");
    strcat(fileName,argv[2]);
    strcat(fileName,"_");
    strcat(fileName, argv[4]);
    strcat(fileName,".txt");

    //SE ABRE EL ARHCIVO  Y SE POSICIONA DESDE DONDE DEBE LEER
    FILE *fileSalida = fopen(fileName,"w");	
    FILE *file = fopen(argv[0],"r");
    fseek(file,position,SEEK_SET);

    /*
    SI EL PROCESO ES EL ULTIMO, ENTONCES PROCESARÁ TODAS LAS LINEAS DESDE DONDE
    DEBE LEER ESTE PROCESO HASTA EL FINAL DEL ARCHIVO.
    */
    if(lastProcess == 1){
        while(!feof(file)){
            fscanf(file,"%s",buffer);
            if(!feof(file)){
                printFile(fileSalida, buffer,argv[2],dflag,processId);         		
                i++;
            }
	      
        }
    }else{
	   while(i < lines){	
	       fscanf(file,"%s",buffer);
           printFile(fileSalida, buffer,argv[2],dflag,processId);  
	       i++;	
	   }
    }
    fclose(file);
    fclose(fileSalida);
    
    return 1;
}
