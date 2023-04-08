// ConsoleApplication3.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <stdio.h>
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

	while (1)
	{
		system("cls");

		printf("data : %d\n", pData->cnt);
	}
}

