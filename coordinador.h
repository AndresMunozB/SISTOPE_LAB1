

#ifndef COORDINADOR_H
#define COORDINADOR_H

int fileExists(char* nombreArchivo);

int isNucleotide(char letter);

int verifySuccession(char* succession, int lengthLine);

int verifyProcess(int number);

int verifyArguments(char* ivalue, int nvalue, int cvalue, char* pvalue);

long int fileSizeBytes(char *fileName);

void appendFile(char *fileNameIn,char *fileNameOut);

void createProcess(char *ivalue ,int nvalue,int cvalue,char* pvalue,int linesProccess);

#endif