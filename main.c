#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

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

/*ENTRADA: String que corresponde a la sucesión
  SALIDA: Entero (0,1 o 2)
  Se encarga de verificar si la sucesión ingresada como parametro es válida. 
  Si retorna 0, la longitud es menor que la pedida, retorno 1 cuando se ingresan
  caracteres no correspondidos, y retorno 2 cuando es válido.*/
int isNucleotide(char letter){
	if (letter == 'A' || letter == 'C' || letter == 'G' || letter == 'T'){
		return 1;
	}
	else
	{
		return 0;
	}
}

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

int verifyProcess(int number){
	if(number < 1)
		return 0;
	else
		return 1;
}

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

int main(int argc, char** argv){
	
	char ivalue[300];
	int nvalue;
	int cvalue;
	char pvalue[300];
	int dflag;
	int numberArg = 0;

	opterr = 0; //No se si es necesariaa
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

	if(verifyArguments(ivalue,nvalue,cvalue,pvalue) == 0)
		return 0;

	if(dflag == 1)
		printf("ivalue = %s, nvalue = %d, cvalue = %d, pvalue = %s, dflag = %d  \n", ivalue , nvalue, cvalue, pvalue, dflag);


	//AHORA

	//VARIABLES 
	int lineSize = cvalue + 1;
	int proccesses = nvalue;
	int lines;
	long int fileSize;
	int linesProccess;

	//TAMAÑO ARCHIVO
	FILE* file = fopen("ejemplo1.txt","r");
	fseek(file, 0L, SEEK_END);
	fileSize = ftell(file) + 1;

	//CALCULO DE LINEAS POR PROCESO
	lines = fileSize / lineSize ;
	linesProccess = lines / proccesses ;
	printf("linesProccess: %d\n",linesProccess);

	return 0;
}