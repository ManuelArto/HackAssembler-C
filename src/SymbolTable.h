typedef struct symbolTable {
	char *keys[1000];
	int addresses[1000];
	int index, varIndex;
} symbolTable_t;

typedef symbolTable_t SymbolTable;

void initializeTable(SymbolTable *S);

void addEntry(SymbolTable *S, char *symbol, int address);

int getIndexOf(SymbolTable *S, char *symbol);

int getAddress(SymbolTable *S, char *symbol);
