#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(char *line, char *succession){
    if (strstr(line,succession) != NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int main(int argc,char *argv[]){
    //printf("Hola,gi soy el programa comparador!\n");
    char buffer[200];
    

    FILE *file = fopen("ejemplo1.txt","r");

    fscanf(file,"%s",buffer);
    printf("%s:%s\n",argv[0],buffer);
    fclose(file);
    
    return 1;
}