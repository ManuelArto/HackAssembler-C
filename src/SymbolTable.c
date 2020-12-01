#include "string.h"
#include "stdlib.h"

#include "SymbolTable.h"

void initializeTable(SymbolTable *S){
	int index = 0;
	S->keys[index] = "SP"; S->addresses[index] = 0;
	index++;
	S->keys[index] = "LCL"; S->addresses[index] = 1;
	index++;
	S->keys[index] = "ARG"; S->addresses[index] = 2;
	index++;
	S->keys[index] = "THIS"; S->addresses[index] = 3;
	index++;
	S->keys[index] = "THAT"; S->addresses[index] = 4;
	index++;
	S->keys[index] = "R0"; S->addresses[index] = 0;
	index++;
	S->keys[index] = "R1"; S->addresses[index] = 1;
	index++;
	S->keys[index] = "R2"; S->addresses[index] = 2;
	index++;
	S->keys[index] = "R3"; S->addresses[index] = 3;
	index++;
	S->keys[index] = "R4"; S->addresses[index] = 4;
	index++;
	S->keys[index] = "R5"; S->addresses[index] = 5;
	index++;
	S->keys[index] = "R6"; S->addresses[index] = 6;
	index++;
	S->keys[index] = "R7"; S->addresses[index] = 7;
	index++;
	S->keys[index] = "R8"; S->addresses[index] = 8;
	index++;
	S->keys[index] = "R9"; S->addresses[index] = 9;
	index++;
	S->keys[index] = "R10"; S->addresses[index] = 10;
	index++;
	S->keys[index] = "R11"; S->addresses[index] = 11;
	index++;
	S->keys[index] = "R12"; S->addresses[index] = 12;
	index++;
	S->keys[index] = "R13"; S->addresses[index] = 13;
	index++;
	S->keys[index] = "R14"; S->addresses[index] = 14;
	index++;
	S->keys[index] = "R15"; S->addresses[index] = 15;
	index++;
	S->keys[index] = "SCREEN"; S->addresses[index] = 16384;
	index++;
	S->keys[index] = "KBD"; S->addresses[index] = 24576;
	index++;
	S->index = index;
	S->varIndex = 16;
}

void addEntry(SymbolTable *S, char *symbol, int address){
	S->keys[S->index] = symbol; S->addresses[S->index] = address;
	S->index++;
}

int getIndexOf(SymbolTable *S, char *symbol){
	for (int i = 0; i < S->index; i++) {
		if (!strcmp(S->keys[i], symbol))
			return i;
	}
	return -1;
}

int getAddress(SymbolTable *S, char *symbol){
	int index = getIndexOf(S, symbol);
	if (index == -1) {
		addEntry(S, symbol, S->varIndex);
		S->varIndex++;
		return S->varIndex - 1;
	} else 
		return S->addresses[index];
}