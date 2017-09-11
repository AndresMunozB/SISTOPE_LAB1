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
	if (letter != 'A' || letter != 'C' || letter != 'G' || letter != 'T'){
		return 1;
	}
	else
	{
		return 0;
	}
}
int verifySuccession(char* succession){
	int length = strlen(succession);
	if(length < 4){
		return 0;
	}
	for(int i = 0; i < length; i++){
		if(!isNucleotide(succession[i])){
			return 0;
		}		
	}
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
	/*if(strlen(pvalue) > cvalue){
		printf("Error: Sucesion a buscar es mayor que las lineas del archivo.\n");
		exit(0);
	}
	if (numberArg < 5){
		printf("Faltan parametros.\n");
		exit(0);
	}
	else if(numberArg > 5){
		printf("Sobran parametros.\n");
		exit(0);
	}*/
	printf("ivalue = %s, nvalue = %d, cvalue = %d, pvalue = %s, dflag = %d  \n", ivalue , nvalue, cvalue, pvalue, dflag);
	/* ANTES
	
	char str[100];
	FILE* file = fopen("ejemplo1.txt","r");
	fseek(file, 0L, SEEK_END);
	fileSize = ftell(file);
	printf("ejemplo.txt ocupa %ld bytes\n", fileSize);
	rewind(file);
	fscanf(file, "%s\n", str);
	lineSize = ftell(file);
	printf("primera linea de ejemplo.txt ocupa %ld bytes\n", lineSize);
	lines = (fileSize+1)/lineSize;
	printf("Hay %d lineas \n", lines);

	fclose(file);*/

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