#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>

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

long int fileSizeBits(char *fileName){
    long int fileSize;
    FILE* file = fopen(fileName,"r");
	fseek(file, 0L, SEEK_END);
    fileSize = ftell(file) + 1;
    fclose(file);
    return fileSize;
}
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
            //sprintf(id,"%d",getpid());
            sprintf(id,"%d",i);
            sprintf(positionStr,"%ld",(long int)linesProccess*i*(cvalue+1));
            sprintf(linesStr,"%d",linesProccess);
            //char *args[] = {fileName,position,succession,lines,id,NULL};
	    if(i == nvalue-1){
		lastProcess = "1";
	    }else{
		lastProcess = "0";
            }
            char *args[] = {ivalue,positionStr,pvalue,linesStr,id,lastProcess,NULL};
            execvp("./comparador",args);
            break;
        }
	}
	
    if(pidFather == getpid()){
        printf("soy el padre: %d\n", pidFather );
        for(i=0;i<nvalue;i++){
            //printf("%d: %d\n",i,arrayPid[i]);
            waitpid(arrayPid[i],&arrayStatus[i],0);
        }
		//while(1);
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
			//printf("NOMBRE ARCHIVO: %s\n",fileNameIn);
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



	//VARIABLES 
	int lines;
	long int fileSize = fileSizeBits(ivalue);
	int linesProccess;

	//CALCULO DE LINEAS POR PROCESO
	lines = fileSize /  (cvalue + 1) ;
	if(lines < nvalue){
		printf("ERROR: Numero de procesos debe ser menor que la cantidad de lineas.\n");
		return 0;
	}
	//./main -i ejemplo1.txt -n 5 -c 60 -p AAAA -d


	linesProccess = lines / nvalue ;
	printf("linesProccess: %d\n",linesProccess);
	createProcess(ivalue ,nvalue,cvalue,pvalue,linesProccess);

	//EJECUCION

	

	return 0;
}
