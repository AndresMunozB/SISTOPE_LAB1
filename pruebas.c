#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdlib.h>


int main(int argc,char *argv[]){
    
    
    int i;
    pid_t pidFather = getpid();
    pid_t *arrayPid = (pid_t*) malloc(sizeof(pid_t)*10);
    int *arrayStatus = (int*) malloc(sizeof(int)*10);
    FILE **files = (FILE**) malloc(sizeof(FILE*)*10); 
    for(i=0;i<10;i++){
        arrayPid[i]=fork();
        if(arrayPid[i]==0){
            execvp("./comparador",argv);
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
    

    return 0;
}