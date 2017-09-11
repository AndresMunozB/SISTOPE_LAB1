/*pid_t pid1,pid2;
    int status1,status2;
    
    
    if ((pid1=fork()) == 0){
       //HIJO
       printf("Soy el primer hijo (%d,hijode %d)\n",getpid(),getppid());
    }
    else{
        if((pid2=fork()) == 0){
            //Segundo hijo
            printf("Soy el segundo hijo (%d, hijo de %d)\n",getpid(),getppid());
        }
        else{
            //PADRE
            //Esperamos al primer hijo
            waitpid(pid1,&status1,0);
            //Esperamos al segundo hijo
            waitpid(pid2,&status2,0);
            printf("Soy el padre (%d, hijo de %d)\n",getpid(),getppid());
        }
    }*/
    /*int i,j,k;
    for(i=0;i<3;i++){
        if(fork() == 0){
            if (i==1){
                for(j=0;j<2;j++){
                    if(fork() == 0){
                        if(j==1){
                            for(k=0;k<2;k++){
                                if(fork()!= 0){
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
            break;
        }
    }
    while(1);*/





    //MAIN

    char buffer[61];
	char buffer2[100000];
	//memset(buffer,0,sizeof(buffer));
	FILE* file = fopen("ejemplo1.txt","r");
	FILE* file2 = fopen("copia.txt","w");
	fseek(file, 0L, SEEK_END);

	fileSize = ftell(file);
	printf("ejemplo.txt ocupa %ld bytes\n", fileSize);
	printf("sizeof(char): %ld\n",sizeof(char));
	
	fread(buffer2,sizeof(char),ftell(file),file);
	fwrite(buffer2,sizeof(char),ftell(file),file2);
	rewind(file);
	fread(buffer,60,sizeof(char),file);
	fread(buffer,60,sizeof(char),file);
	fread(buffer,61,sizeof(char),file);
	//buffer[61] = '\0';
	if (buffer[61] == '\0'){
		printf("son iguales\n");
	}
	else{
		printf("no son iguales:|a||%c|\n",buffer[61]);

	}
	//printf("%s",buffer);