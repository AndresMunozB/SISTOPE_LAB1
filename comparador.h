#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef COMPARADOR_H
#define COMPARADOR_H

int compare(char *line, char *succession);

void printFile(FILE* fileSalida,char* buffer, char* succession);

#endif