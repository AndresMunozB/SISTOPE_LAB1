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

int main(){
    
    return 1;
}