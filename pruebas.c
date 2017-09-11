#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdlib.h>

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
int main(int argc,char *argv[]){
    
    /*
    int i;
    pid_t pidFather = getpid();
    pid_t *arrayPid = (pid_t*) malloc(sizeof(pid_t)*10);
    int *arrayStatus = (int*) malloc(sizeof(int)*10);
    char id[20];
    char positionStr[50];
    char linesStr[50];
    
    for(i=0;i<10;i++){
        arrayPid[i]=fork();
        if(arrayPid[i]==0){
            //sprintf(id,"%d",getpid());
            sprintf(id,"%d",i);
            sprintf(positionStr,"%ld",(long int)1*i*61);
            sprintf(linesStr,"%d",1);
            //char *args[] = {fileName,position,succession,lines,id,NULL};
            char *args[] = {"ejemplo1.txt",positionStr,"AAAA",linesStr,id,NULL};
            execvp("./comparador",args);
            break;
        }
    }
    

    //para ejecutar el programa comparador
    //execvp("./comparador",argv);
    
    
    
    if(pidFather == getpid()){
        printf("soy el padre: %d\n", pidFather );
        for(i=0;i<10;i++){
            //printf("%d: %d\n",i,arrayPid[i]);
            waitpid(arrayPid[i],&arrayStatus[i],0);
        }
        //while(1);
    }
    */
    appendFile("ejemplo1.txt","copia.txt");

    return 0;
}