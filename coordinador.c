#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>

#include "coordinador.h"

/*ENTRADA: El nombre del archivo
  SALIDA: Entero (0 o 1)
  Esta función se encarga de verificar si el archivo con el nombre ingresado por parámetro
  existe o no. Si retorna 0, el archivo no existe y en caso contrario, retorna 1.*/
int fileExists(char* nombreArchivo){
	FILE* archivo;
	archivo = fopen(nombreArchivo, "r");
	if(archivo == NULL)
		return 0;
	else
		return 1;
}

/*ENTRADA: Caracter 
  SALIDA: Entero (0 o 1)
  Se validan si el caracter que ingresa como parametro es considerado como parte del nucleotido.*/
int isNucleotide(char letter){
	if (letter == 'A' || letter == 'C' || letter == 'G' || letter == 'T'){
		return 1;
	}
	else
	{
		return 0;
	}
}

/*ENTRADA: String que corresponde a la sucesión y un entero que representa al largo de la línea.
  SALIDA: Entero (0 o 1)
  Se encarga de verificar si la sucesión ingresada como parametro es válida. Se validan 3 condiciones:
  - Si el largo de la sucesión es mayor que 4
  - Si cumple con las condiciones de la función anterior 
  - Si el largo de la sucesión es menor que el largo de la línea.*/
int verifySuccession(char* succession, int lengthLine){
	int length = strlen(succession);
	if(length < 4){
		return 0;
	}
	for(int i = 0; i < length; i++){
		if(!isNucleotide(succession[i])){
			return 0;
		}		
	}
	if(lengthLine < strlen(succession))
		return 0;

	return 1;
}

/*ENTRADA: Entero que corresponde a la cantidad de procesos
  SALIDA: Entero (0 o 1)
  Esta función se encarga de verificar si la cantidad de procesos es menor que 1*/
int verifyProcess(int number){
	if(number < 1)
		return 0;
	else
		return 1;
}

/*ENTRADA: Todos los valores que ingresan por parametro con getopt
  SALIDA: Entero (0 o 1)
  Esta función abarca las pequeñas funciones anteriores, donde se verifican si todos
  los parametros cumplen las condiciones.*/
int verifyArguments(char* ivalue, int nvalue, int cvalue, char* pvalue){
	if(fileExists(ivalue) == 0){
		printf("ERROR: Archivo no Encontrado.\n");
		return 0;
	}
	else if(verifyProcess(nvalue) == 0){
		printf("ERROR: Cantidad de procesos debe ser 1 o mas.\n");
		return 0;
	}
	else if(verifySuccession(pvalue, cvalue) == 0){
		printf("ERROR: Sucesion Invalida.\n");
		return 0;
	}
	else 
		return 1;
}

/*ENTRADA: String que corresponde al nombre del archivo
  SALIDA: Un entero long
  Se encarga de obtener el tamaño del archivo en bytes*/
long int fileSizeBytes(char *fileName){
    long int fileSize;
    FILE* file = fopen(fileName,"r");
	fseek(file, 0L, SEEK_END);
    fileSize = ftell(file) + 1;
    fclose(file);
    return fileSize;
}

/*ENTRADA: Dos strings que corresponden al archivo de salida parcial y el archivo de salida completo
  SALIDA: Void
  Se encarga de obtener lo escrito en el archivo de salida parcial y lo copia al archivo de salida
  completo para tener todos los resultados en el mismo archivo de texto.*/
void appendFile(char *fileNameIn,char *fileNameOut){
	FILE* fileIn = fopen(fileNameIn,"r");
	FILE* fileOut = fopen(fileNameOut,"a");
	char buffer;
	while((buffer = fgetc ( fileIn )) != EOF){
		fputc(buffer,fileOut);
	} 
	fclose(fileIn);
    fclose(fileOut);
}

/*ENTRADA: Todos los parametros de getopt más un entero que representa la cantidad de lineas 
  que debería ejecutar cada proceso.
  SALIDA: Void
  La función se encarga de crear varios procesos para luego llamar al programa comparador. Una 
  vez terminado esto realiza la copia al archivo de salida completo con el apoyo de la función anterior.*/
void createProcess(char *ivalue ,int nvalue,int cvalue,char* pvalue,int linesProccess){

	int i;
    pid_t pidFather = getpid();
    pid_t *arrayPid = (pid_t*) malloc(sizeof(pid_t)*nvalue);
    int *arrayStatus = (int*) malloc(sizeof(int)*nvalue);
    char id[20];
    char positionStr[50];
    char linesStr[50];
	char* lastProcess;
	char fineNameBuffer[100];
   	
    
    for(i=0;i<nvalue;i++){
        arrayPid[i]=fork();
        if(arrayPid[i]==0){
            sprintf(id,"%d",i);
            sprintf(positionStr,"%ld",(long int)linesProccess*i*(cvalue+1));
			sprintf(linesStr,"%d",linesProccess);
		
			//SE ANALIZA SI ES EL ULTIMO PROCESO
			if(i == nvalue-1)
			{
				lastProcess = "1";
			}
			else
			{
				lastProcess = "0";
			}
			//SE JUNTAN LOS ARGUMENTOS Y SE EJECUTA EL PROGRAMA COMPARADOR PARA EL PROCESO RECIEN CREADO
           	char *args[] = {ivalue,positionStr,pvalue,linesStr,id,lastProcess,NULL};
            execvp("./comparador",args);
            break;
        }
	}
	
	//VERIFICACION PARA SABER SI EL PROCESO ES EL PADRE
    if(pidFather == getpid()){
		//SE HACE ESPERAR A TODOS LOS HIJOS
        for(i=0;i<nvalue;i++){
            waitpid(arrayPid[i],&arrayStatus[i],0);
		}
		
		//JUNTAR LOS RESULTADOS PARCIALES
		char id[20];
		char fileNameIn[100];
		char fileNameOut[100];
		for(i=0;i<nvalue;i++){

			//NOMBRE ARCHIVO DE RESULTADO PARCIAL
			memset(fileNameIn,0,sizeof(fileNameIn));
			strcat(fileNameIn,"rp_");
			strcat(fileNameIn,pvalue);
			strcat(fileNameIn,"_");
			sprintf(id,"%d",i);
			strcat(fileNameIn,id);
			strcat(fileNameIn,".txt");

			//NOMBRE DE ARCHIVO DE RESULTADO COMPLETO
			memset(fileNameOut,0,sizeof(fileNameOut));
			strcat(fileNameOut,"rc_");
			strcat(fileNameOut,pvalue);
			strcat(fileNameOut,".txt");

			//SE COPIA EL ARCHIVO PARCIAL AL ARCHIVO FINAL
			appendFile(fileNameIn,fileNameOut);

		}

    }
}


int main(int argc, char** argv){
	
	char ivalue[300];
	int nvalue;
	int cvalue;
	char pvalue[300];
	int dflag;

	opterr = 0;
	int c;

	if(argc > 10){
		printf("Sobran parametros.\n");
		return 0;
	}else if(argc < 8){
		printf("Faltan parametros.\n");
		return 0;
	}
	
	while ((c = getopt(argc,argv,"i:n:c:p:d")) != -1){
		//printf("%d\n",argc);
		switch(c){
			printf("hola while!");
			case 'i':
				strcpy(ivalue,optarg);
				break;
			case 'n':
				sscanf(optarg, "%d", &nvalue);
				break;
			case 'c':
				sscanf(optarg, "%d", &cvalue);
				break;
			case 'p':
				strcpy(pvalue,optarg);
				break;
			case 'd':
				dflag = 1;
				break;
			default:
				abort();
		}
	}

	//Se validan los argumentos
	if(verifyArguments(ivalue,nvalue,cvalue,pvalue) == 0)
		return 0;

	if(dflag == 1)
		printf("ivalue = %s, nvalue = %d, cvalue = %d, pvalue = %s, dflag = %d  \n", ivalue , nvalue, cvalue, pvalue, dflag);
	//VARIABLES 
	int lines;
	long int fileSize = fileSizeBytes(ivalue);
	int linesProccess;

	//CALCULO DE LINEAS POR PROCESO
	lines = fileSize /  (cvalue + 1) ;
	//ULTIMA VALIDACION 
	if(lines < nvalue){
		printf("ERROR: Numero de procesos debe ser menor que la cantidad de lineas.\n");
		return 0;
	}
	linesProccess = lines / nvalue ;


	//EJECUCION
	createProcess(ivalue ,nvalue,cvalue,pvalue,linesProccess);

	

	return 0;
}
