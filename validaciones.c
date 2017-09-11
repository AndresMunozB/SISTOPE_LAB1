#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verifyProcess(int number){
	if(number < 1)
		return 0;
	else
		return 1;
}

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

int fileExists(char* nombreArchivo){
	FILE* archivo;
	archivo = fopen(nombreArchivo, "r");
	if(archivo == NULL)
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

int main(){
	if(verifyArguments("ejemplo.txt", 10, 30, "ATGC") == 0)
		exit(0);
}