#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char** argv){
	/*
	int aflag = 0;
	int bflag = 0;
	char cvalue[300];
	int index;
	int c;
	opterr = 0; 
	while((c = getopt(argc, argv, "ab:c:")) != -1){
		switch(c){
			case 'a':
				aflag = 1;
				break;

			case 'b':
				sscanf(optarg, "%d", &bflag);
				break;

			case 'c':
				strcpy(cvalue,optarg);
				//cvalue = optarg; //optarg es string
				break;

			case '?':
				if(optopt == 'c')
					fprintf(stderr, "Opcion -%c requiere un argumento.\n", optopt);
				else if(isprint(optopt))
					fprintf(stderr, "Opcion desconocida '-%c'.\n", optopt);
				else
					fprintf(stderr, "Opcion con caracter desconocido '\\x%x' .\n",optopt );
				return 1;
			default:
				abort();
		}
	}
	printf("aflag = %d, bflag = %d, cvalue = %s \n", aflag, bflag,cvalue);
	*/
	
	char ivalue[300];
	int nvalue;
	int cvalue;
	char pvalue[300];
	int dflag;

	opterr = 0; //No se si es necesariaa
	int c;
	
	while ((c = getopt(argc,argv,"i:n:c:p:d")) != -1){
		
		switch(c){
			printf("hola while!");
			case 'i':
				strcpy(ivalue,optarg);
				//ivalue = optarg;
				break;
			case 'n':
				sscanf(optarg, "%d", &nvalue);
				break;
			case 'c':
				sscanf(optarg, "%d", &cvalue);
				break;
			case 'p':
				strcpy(pvalue,optarg);
				//pvalue = optarg;
				break;
			case 'd':
				dflag = 1;
				break;
			default:
				abort();
		}
	}
	
	printf("ivalue = %s, nvalue = %d, cvalue = %d, pvalue = %s, dflag = %d  \n", ivalue , nvalue, cvalue, pvalue, dflag);
	
	return 0;
}