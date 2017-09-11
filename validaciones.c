#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNucleotide(char letter){
	if (letter == 'A' || letter == 'C' || letter == 'G' || letter == 'T'){
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

int main(){
    printf("%d\n",verifySuccession("AAAC"));
}