
enum instructionT {A_COMMAND, C_COMMAND, L_COMMAND, COMMENT, SKIP};

typedef enum instructionT instructionType;

typedef struct parser {
	FILE *asmfile, *hackfile;
	char line[256];
	int lenght;
	int index;
} parser_t;

typedef parser_t Parser;

void initializeParser(Parser *P, char *asmfilename);

void restartReading(Parser *P, char *asmfilename);

int hasMoreCommands(Parser *P);

void advance(Parser *P);

instructionType commandType(Parser *P);

char *symbol(Parser *P);

int checkDestPart(Parser *P);

char *dest(Parser *P);

char *comp(Parser *P);

int checkJumpPart(Parser *P);

char *jump(Parser *P);

void writeAInstruction(Parser *P, char *bin);

void writeCInstruction(Parser *P, char *comp, char *dest, char *jump);

char *getHackFilename (char *asmfilename, int lenght);