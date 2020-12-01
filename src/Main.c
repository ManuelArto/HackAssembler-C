#include <stdio.h>
#include <stdlib.h>

#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

int main (int argc, char **argv) {
	
	if (argc > 1) {
		Parser P;
		initializeParser(&P, argv[1]);

		SymbolTable S;
		initializeTable(&S);

		// First Pass
		int rom = 0;
		while(hasMoreCommands(&P)) {
			switch (commandType(&P)) {
				case A_COMMAND:
				case C_COMMAND:
					rom++;
					break;
				case L_COMMAND: ;
					char *symbolString = symbol(&P);
					addEntry(&S, ++symbolString, rom);
					break;
			}
			advance(&P);
		}

		// Second Pass
		restartReading(&P, argv[1]);
		while(hasMoreCommands(&P)) {
			switch (commandType(&P)) {
				case A_COMMAND: ;
					char *symbolString = symbol(&P);
					char *symbolB;
					if (symbolString[0] == '1')
						symbolB = intToBin(atoi(++symbolString));
					else
						symbolB = intToBin(getAddress(&S, ++symbolString));

					writeAInstruction(&P, symbolB);

					break;
				case C_COMMAND: ;
					char *destString = dest(&P);
					char *destB = destBinary(destString);

					char *compString = comp(&P);
					char *compB = compBinary(compString);

					char *jumpString = jump(&P);
					char *jumpB = jumpBinary(jumpString);

					writeCInstruction(&P, compB, destB, jumpB);

					break;
			}
			advance(&P);
		}
	} else {
		printf("No .asm file was specified\n");
		return EXIT_FAILURE;
	}
}