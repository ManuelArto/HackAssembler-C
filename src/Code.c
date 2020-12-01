#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Code.h"

char *destBinary(char *destString) {
	char *destB = (char *) malloc(sizeof(char) * 4);
	destB[0] = '0'; destB[1] = '0'; destB[2] = '0';
	for (int i = 0; i < strlen(destString); i++) {
		if (destString[i] == 'M')
			destB[2] = '1';
		else if (destString[i] == 'D')
			destB[1] = '1';
		else if (destString[i] == 'A')
			destB[0] = '1';
	}
	
	return destB;
}

char *compBinary(char *compString) {
	char *compB;
	if (!strcmp(compString, "0"))
		compB = "0101010";
	else if (!strcmp(compString, "1"))
		compB = "0111111";
	else if (!strcmp(compString, "-1"))
		compB = "0111010";
	else if (!strcmp(compString, "D"))
		compB = "0001100";
	else if (!strcmp(compString, "A"))
		compB = "0110000";
	else if (!strcmp(compString, "M"))
		compB = "1110000";
	else if (!strcmp(compString, "!D"))
		compB = "0001101";
	else if (!strcmp(compString, "!A"))
		compB = "0110001";
	else if (!strcmp(compString, "!M"))
		compB = "1110001";
	else if (!strcmp(compString, "-D"))
		compB = "0001111";
	else if (!strcmp(compString, "-A"))
		compB = "0110011";
	else if (!strcmp(compString, "-M"))
		compB = "1110011";
	else if (!strcmp(compString, "D+1"))
		compB = "0011111";
	else if (!strcmp(compString, "A+1"))
		compB = "0110111";
	else if (!strcmp(compString, "M+1"))
		compB = "1110111";
	else if (!strcmp(compString, "D-1"))
		compB = "0001110";
	else if (!strcmp(compString, "A-1"))
		compB = "0110010";
	else if (!strcmp(compString, "M-1"))
		compB = "1110010";
	else if (!strcmp(compString, "D+A"))
		compB = "0000010";
	else if (!strcmp(compString, "D+M"))
		compB = "1000010";
	else if (!strcmp(compString, "D-A"))
		compB = "0010011";
	else if (!strcmp(compString, "D-M"))
		compB = "1010011";
	else if (!strcmp(compString, "A-D"))
		compB = "0000111";
	else if (!strcmp(compString, "M-D"))
		compB = "1000111";
	else if (!strcmp(compString, "D&A"))
		compB = "0000000";
	else if (!strcmp(compString, "D&M"))
		compB = "1000000";
	else if (!strcmp(compString, "D|A"))
		compB = "0010101";
	else if (!strcmp(compString, "D|M"))
		compB = "1010101";

	return compB;
}

char *jumpBinary(char *jumpString) {
	char *jumpB = "000";
	if (!strcmp(jumpString, "JGT"))
		jumpB = "001";
	else if (!strcmp(jumpString, "JEQ"))
		jumpB = "010";
	else if (!strcmp(jumpString, "JGE"))
		jumpB = "011";
	else if (!strcmp(jumpString, "JLT"))
		jumpB = "100";
	else if (!strcmp(jumpString, "JNE"))
		jumpB = "101";
	else if (!strcmp(jumpString, "JLE"))
		jumpB = "110";
	else if (!strcmp(jumpString, "JMP"))
		jumpB = "111";

	return jumpB;
}

char *intToBin (int number) {
	int lenght = 15;
	char *bin = (char *) malloc(sizeof(char) * lenght);
	for(int i = 0; i < lenght; i++) {
		bin[i] = (number & (int)1<<(lenght-i-1)) ? '1' : '0';
	}
	return bin;
}