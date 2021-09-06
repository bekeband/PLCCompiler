
#include "../PLCController/PLCHardware.h"

/*
* PLCController PLCCompiler compile the source file to PLC binary.
*/

#include <stdlib.h>
#pragma warning(disable : 4996)

#define LOG_MESSAGES

#define MAX_INPUT_BUFFER_SIZE 512
#define MAX_COMMAND_TOKEN_SIZE	24
#define MAX_DATA_TOKEN_SIZE	24

typedef int (*t_commFunc)();

typedef int (*t_dataFunc)(int shift);


struct commStruct {
	const char comm[MAX_COMMAND_TOKEN_SIZE];
	t_commFunc commFunct;
};

struct dataStruct {
	char comm[MAX_DATA_TOKEN_SIZE];
	t_dataFunc dataFunct;
	int intData;
};

int loadCommand();
int byteData(int dataShift);
int wordData(int dataShift);
int bitData(int dataShift);
int callCommand();

struct commStruct commStructs[] = { { "ld", loadCommand }, {"call", callCommand },  {NULL, NULL}};

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

#ifdef LOG_MESSAGES
	fprintf(stdout, "loadCommand()");
#endif // LOG_MESSAGES

	return 0;
}

/*
*/

int callCommand() {

#ifdef LOG_MESSAGES
	fprintf(stdout, "callCommand()");
#endif // LOG_MESSAGES

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

/* char* convertRawLine(char* inputLine) 
*/
char* convertRawLine(char* inputLine) {

	char* token;
	int i = 0;
	t_commFunc commandFunct = NULL;

	/* get the first token */
	token = strtok(inputLine, " ");

	while ((commStructs[i].commFunct != NULL)) {
		if (!strcmp(commStructs[i].comm, token)) {
			if ((commandFunct = commStructs[i].commFunct) != NULL) {
				commandFunct();
			}
			break;
		}
		i++;
	}

/*	if (commandFunct != NULL) {
		
	}*/

	/* walk through other tokens */
/*	while (token != NULL) {
		printf(" %s\n", token);
		token = strtok(NULL, " ");
	}*/
	printf(" \n");
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

		strcpy(inputFileName, "C:\\Users\\bekeband\\repos\\PLCCompiler\\test.plcfile");
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
#ifdef LOG_MESSAGES
		printf("Line %d: ", linenumb++);
#endif
	}

	fclose(inputHandle);

	MakeTestProgram("test.bin", inputBuffer);

	return 0;
}