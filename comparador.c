#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void printFile(FILE* fileSalida,char* buffer, char* succession){
    if(compare(buffer,succession)){
        fprintf(fileSalida, "%s SI\n", buffer);
    }else{
        fprintf(fileSalida, "%s NO\n", buffer);
    }
      
}
int main(int argc,char *argv[]){
    //printf("Hola,gi soy el programa comparador!\n");
    //char *args[] = {fileName,position,succession,lines,id,lastProcess,NULL};
    long int position = atoll(argv[1]); //posicion de donde comienza el proceso
    int lines = atoi(argv[3]); //lineas totales
    int lastProcess = atoi(argv[5]); //Indica si es el último proceso
    int i = 0;	
    	

    char buffer[200];
    char fileName[50];
    memset(fileName,0,sizeof(fileName));
    
    strcat(fileName,"./rp/rp_");
    strcat(fileName,argv[2]);
    strcat(fileName,"_");
    strcat(fileName, argv[4]);
    strcat(fileName,".txt");
    //printf("NOMBRE ARCHIVO: %s\n",fileName);
    FILE *fileSalida = fopen(fileName,"w");	
    FILE *file = fopen(argv[0],"r");
    fseek(file,position,SEEK_SET);
    if(lastProcess == 1){
        while(!feof(file)){
           fscanf(file,"%s",buffer);
           //printf("linea %d-> %s:%s y compare: %d\n",i,argv[4],buffer,compare(buffer,argv[2])); 
	       printFile(fileSalida, buffer,argv[2]);         		
 	       i++;
        }
    }else{
	   while(i < lines){	
	       fscanf(file,"%s",buffer);
           //printf("linea %d-> %s:%s y compare: %d\n",i,argv[4],buffer,compare(buffer,argv[2]));  
           printFile(fileSalida, buffer,argv[2]);  
	       i++;	
	   }
    }
    /*fseek(file,position,SEEK_SET);
    fscanf(file,"%s",buffer);
    printf("%s:%s\n",argv[4],buffer);*/
    fclose(file);
    fclose(fileSalida);
    
    return 1;
}
