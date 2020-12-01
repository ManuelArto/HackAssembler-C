assembler: main.o parser.o code.o symbolTable.o
	gcc -o assembler Main.o Parser.o Code.o SymbolTable.o

main.o: Main.c Parser.h Code.h SymbolTable.h
	gcc -c Main.c

parser.o: Parser.c Parser.h
	gcc -c Parser.c

code.o: Code.c Code.h
	gcc -c Code.c

symbolTable.o: SymbolTable.c SymbolTable.h
	gcc -c SymbolTable.c

clean:
	rm -f *.o assembler