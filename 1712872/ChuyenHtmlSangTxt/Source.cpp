#include <stdio.h>
#include <stdlib.h>
#define SIZE 255
void makeDummyFile(char* sourceFile, char* dummyFile)
{
	FILE* oldFile = fopen(sourceFile, "rb");
	FILE* newFile = fopen(dummyFile, "wb");
	char string[SIZE];
	if (oldFile == NULL || newFile == NULL)
	{
		printf("Chuong trinh that bai\n");
		system("pause");
		exit(0);
	}
	while (fread(string, 1, SIZE, oldFile) != 0)
		fwrite(string, 1, SIZE, newFile);
	fclose(oldFile);
	fclose(newFile);
}