#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#include "Parser.h"


void initializeParser(Parser *P, char *asmfilename) {
	P->asmfile = fopen(asmfilename, "r");
	// check if file exists
	if (P->asmfile == NULL) {
		printf("%s file doesn't exist\n", asmfilename);
		exit(EXIT_FAILURE);
	}
	char *hackfilename = getHackFilename(asmfilename, strlen(asmfilename));
	P->hackfile = fopen(hackfilename, "w");
	advance(P);
}

void restartReading(Parser *P, char *asmfilename) {
	P->asmfile = fopen(asmfilename, "r");
	advance(P);
}

int hasMoreCommands(Parser *P) {
	return !feof(P->asmfile);
}

void advance(Parser *P) {
	fgets(P->line, 255, P->asmfile);
	P->lenght = strlen(P->line) - 2;
	P->index = 0;
}

instructionType commandType(Parser *P) {
	for (int i = 0; i < P->lenght; i++) {
		P->index = i;
		if (P->line[i] == '@')
			return A_COMMAND;
		if (P->line[i] == '/' && i < P->lenght - 1) {
			if (P->line[i + 1] == '/')
				return COMMENT;
		}
		else if (P->line[i] == '(')
			return L_COMMAND;
		else if (P->line[i] != ' ' && P->line[i] != '\t')
			return C_COMMAND;
	}
	return SKIP;
}

char *symbol(Parser *P) {
	int isNumber = TRUE;
	char *symbolXxx = (char *) malloc(sizeof(char) * 252);

	int index = 0;
	for (int i = P->index + 1; i < P->lenght && P->line[i] != ')' && P->line[i] != ' ' && P->line[i] != '\t'; i++) {
		if (P->line[i] < '0' || P->line[i] > '9')
			isNumber = FALSE;
		symbolXxx[index] = P->line[i];
		index++;
	}

	char *symbolString = (char *) malloc(sizeof(char) * 253);
	symbolString[0] = isNumber ?  '1' : '0';
	strcat(symbolString, symbolXxx);

	return symbolString;
}

int checkDestPart (Parser *P) {
	int check = FALSE;
	for(int i = 0; !check && i < P->lenght; i++) {
		if (P->line[i] == '=')
			check = TRUE;
	}
	return check;
}

char *dest(Parser *P) {
	char *destString = (char *) malloc(sizeof(char) * 4);
	if (checkDestPart(P)) {
		int index = 0;
		for(P->index; P->line[P->index] != '='; P->index++) {
			if ((P->line[P->index] == ' ' || P->line[P->index] == '\t' || P->line[P->index] == '/'))
				break;
			else {
				destString[index] = P->line[P->index];
				index++;
			}
		}
		P->index++;
		destString[index] = '\0';
	} else {
		for(int i = 0; i < 3; i++)
			destString[i] = NULL;
		destString[3] = '\0';
	}
	return destString;
}

char *comp(Parser *P) {
	int index = 0;
	char *compString = (char *) malloc(sizeof(char) * 4);
	for (P->index; index < 3 && P->line[P->index] != ';' && P->index < P->lenght; P->index++) {
		if ((P->line[P->index] == ' ' || P->line[P->index] == '\t' || P->line[P->index] == '/'))
			break;
		else {
			compString[index] = P->line[P->index];
			index++;
		}
	}
	compString[index] = '\0';
	return compString;
}

int checkJumpPart(Parser *P) {
	int check = FALSE;
	for(P->index; !check && P->index < P->lenght; P->index++) {
		if (P->line[P->index] == ';')
			check = TRUE;
	}
	return check;
}

char *jump(Parser *P) {
	char *jumpString = (char *) malloc(sizeof(char) * 4);
	if (checkJumpPart(P)) {
		int i = 0;
		for (P->index; i < 3 && P->index < P->lenght; P->index++) {
			jumpString[i] = P->line[P->index];
			i++;
		}
		jumpString[i] = '\0';
	} else {
		for(int i = 0; i < 3; i++)
			jumpString[i] = NULL;
		jumpString[3] = '\0';
	}
	return jumpString;
}

void writeAInstruction(Parser *P, char *bin) {
	fprintf(P->hackfile, "0%s\n", bin);
}

void writeCInstruction(Parser *P, char *comp, char *dest, char *jump) {
	fprintf(P->hackfile, "111%s%s%s\n", comp, dest, jump);
}


char *getHackFilename (char *asmfilename, int lenght) {
	char *hackfilename = (char *) malloc(sizeof(char) * lenght + 1);
	strcpy(hackfilename, asmfilename);
	int i = lenght + 1;
	while (hackfilename[i] != '.') {
		i -= 1;
	}
	hackfilename[i+1] = '\0';
	strcat(hackfilename, "hack");
	return hackfilename;
}