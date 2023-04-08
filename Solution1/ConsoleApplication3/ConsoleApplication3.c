#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char filename[] = "TestFile";

typedef struct {
	LONG cnt;
} SHARED_DATA;

int main()
{
	printf("console 2\n");

	HANDLE hShare = NULL;
	while (1)
	{
		if (hShare == NULL)
		{
			hShare = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, filename);
		}
		else
		{
			break;
		}
	}

	printf("file opened\n");

	SHARED_DATA	CurrentData, * pData; /* 共有するデータ */

	pData = (SHARED_DATA*)MapViewOfFile(hShare, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SHARED_DATA));

	SHARED_DATA OldData = { 0 };

	memcpy(&OldData, pData, sizeof(SHARED_DATA));

	printf("data : %d\n", pData->cnt);

	while (1)
	{
		if (memcmp(&OldData, pData, sizeof(SHARED_DATA)))
		{
			system("cls");

			printf("data : %d\n", pData->cnt);

			memcpy(&OldData, pData, sizeof(SHARED_DATA));
		}
	}
}

