
#include "../PLCController/PLCHardware.h"

/*
* PLCController PLCCompiler compile the source file to PLC binary.
*/

#include <stdlib.h>
#pragma warning(disable : 4996)

#define MAX_INPUT_BUFFER_SIZE 512

typedef int (*t_commFunc)();

typedef int (*t_dataFunc)(int shift);


struct commStruct {
	char comm[24];
	t_commFunc commFunct;
};

struct dataStruct {
	char comm[24];
	t_dataFunc dataFunct;
	int intData;
};

int loadCommand();
int byteData(int dataShift);
int wordData(int dataShift);
int bitData(int dataShift);

struct commStruct commStructs[] = {	{ "ld", loadCommand }, {NULL, NULL} };

struct dataStruct dataStructs[] = {	{"in", bitData, INPUTS_SHIFT}, 
										{"inb", byteData, INPUTS_SHIFT},
										{"inw", wordData, INPUTS_SHIFT},
										{"out", bitData, OUTPUTS_SHIFT},
										{"outb", byteData, OUTPUTS_SHIFT},
										{"outw", wordData, OUTPUTS_SHIFT},
										{"adb", byteData, AD_DATAS_SHIFT},
										{"adw", wordData, AD_DATAS_SHIFT},
										{"dad", byteData, DA_DATAS_SHIFT},
										{"daw", wordData, DA_DATAS_SHIFT},
										{"m", bitData, MARKERS_SHIFT},
										{"mb", byteData, MARKERS_SHIFT},
										{"mw", wordData, MARKERS_SHIFT},
										{"d", bitData, PLC_MEMORY_SHIFT},
										{"db", byteData, PLC_MEMORY_SHIFT},
										{"dw", wordData, PLC_MEMORY_SHIFT},
										{"dr", bitData, PLC_RETENT_MEMORY_SHIFT},
										{"drb", byteData, PLC_RETENT_MEMORY_SHIFT},
										{"drw", wordData, PLC_RETENT_MEMORY_SHIFT},
										{NULL, NULL } };

int MakeTestProgram(const char* fileName, const char* outBuffer) {
	FILE* outHandle;
	outHandle = fopen(fileName, "wb");
	if (outHandle != NULL) {
		fputs(outBuffer, outHandle);
		fclose(outHandle);
	}
	else return -1;
}

/*
*/

int loadCommand() {
	return 0;
}

/*
*/

int byteData(int dataShift) {
	return 0;
}

/*
*/

int bitData(int dataShift) {
	return 0;
}

/*
*/

int wordData(int dataShift) {
	return 0;
}

/* convertLoadLine(char* inputLine) 
*/
char* convertRawLine(char* inputLine) {

	char* token;
	int i = 0;
	t_commFunc commandFunct = NULL;

	/* get the first token */
	token = strtok(inputLine, " ");
	
	while (commStructs[i++].commFunct != NULL) {
		if (strcmp(commStructs[i].comm, token)) {
			commandFunct = commStructs[i].commFunct;
			i++;
			break;
		}
	}

	if (commandFunct != NULL) {

	}

	/* walk through other tokens */
	while (token != NULL) {
		printf(" %s\n", token);
		token = strtok(NULL, " ");
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	const char inputFileName[260];
	const char inputBuffer[MAX_INPUT_BUFFER_SIZE];
	FILE* inputHandle;

	if (argc > 1) {
		strcpy(inputFileName, argv[1]);
		inputHandle = fopen(inputFileName, "r");
	}
	else {
		strcpy(inputFileName, "C:\\Users\\Beke András\\source\\repos\\PLCCompiler\\test.plcfile");
		inputHandle = fopen(inputFileName, "r");
//		inputHandle = stdin;
	}

	if (inputHandle == NULL) {
		fprintf(stderr, "Couldn't open file: %s", inputFileName);
		return -1;
	}
	int linenumb = 0;
	while (!feof(inputHandle))
	{
		fgets(inputBuffer, sizeof(inputBuffer), inputHandle);

		convertRawLine(inputBuffer);

//		puts(inputBuffer);
		printf("Line %d: %s", linenumb++, inputBuffer);

	}

	fclose(inputHandle);

	MakeTestProgram("test.bin", inputBuffer);

	return 0;
}