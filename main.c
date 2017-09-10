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
int verifySuccession(char* succession){
	int length = strlen(succession);

	if(length < 4)
		return 0;
	else{
		for(int i = 0; i < length; i++){
			if(succession[i] != 'A' && succession[i] != 'C' && succession[i] != 'G' && succession[i] != 'T')
				return 1;
		}
		return 2;
	}
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
		
		switch(c){
			printf("hola while!");
			case 'i':
				numberArg++;
				strcpy(ivalue,optarg);
				if(fileExists(ivalue) == 0){
					printf("Error: Archivo no Encontrado.\n");
					exit(0);
				}
				break;
			case 'n':
				numberArg++;
				sscanf(optarg, "%d", &nvalue);
				if(nvalue < 1){
					printf("Error: Cantidad de procesos debe ser 1 o mas.\n");
					exit(0);
				}
				break;
			case 'c':
				numberArg++;
				sscanf(optarg, "%d", &cvalue);
				break;
			case 'p':
				numberArg++;
				strcpy(pvalue,optarg);
				if(verifySuccession(pvalue) == 0){
					printf("Error: Cantidad de caracteres insuficiente.\n");
					exit(0);
				}else if(verifySuccession(pvalue) == 1){
					printf("Error: Sucesion invalida.\n");
					exit(0);
				}
				break;
			case 'd':
				numberArg++;
				dflag = 1;
				break;
			default:
				abort();
		}
	}
	if(strlen(pvalue) > cvalue){
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
	}

	printf("ivalue = %s, nvalue = %d, cvalue = %d, pvalue = %s, dflag = %d  \n", ivalue , nvalue, cvalue, pvalue, dflag);

	char buffer[61];
	char buffer2[100000];
	//memset(buffer,0,sizeof(buffer));
	FILE* file = fopen("ejemplo1.txt","r");
	FILE* file2 = fopen("copia.txt","w");
	fseek(file, 0L, SEEK_END);
	printf("ejemplo.txt ocupa %ld bytes\n", ftell(file));
	printf("sizeof(char): %ld\n",sizeof(char));
	
	fread(buffer2,sizeof(char),ftell(file),file);
	fwrite(buffer2,sizeof(char),ftell(file),file2);
	rewind(file);
	fread(buffer,60,sizeof(char),file);
	fread(buffer,60,sizeof(char),file);
	fread(buffer,60,sizeof(char),file);
	//buffer[61] = '\0';
	if (buffer[61] == '\0'){
		printf("son iguales\n");
	}
	else{
		printf("no son iguales:|a||%c|\n",buffer[61]);

	}
	printf("%s",buffer);
	fclose(file);
	fclose(file2);

 

	return 0;
}