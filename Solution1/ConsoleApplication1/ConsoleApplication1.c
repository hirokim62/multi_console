#include <stdio.h>
#include <Windows.h>

char filename[] = "TestFile";

typedef struct {
	LONG cnt;
} SHARED_DATA;

int main()
{
	printf("Hello World\n");

	HANDLE hMap; /* ファイルマッピングオブジェクトのハンドル */
	HANDLE hMutex = NULL; /* 共有データへの排他アクセス用ミューテックスオブジェクトのハンドル */
	SHARED_DATA	CurrentData, * pData; /* 共有するデータ */
	BOOL bAlreadyExists; /* 既にファイルマッピングオブジェクトが作成されているかどうかを表す真偽値 */
	char msg[1000];

	/* ファイルマッピングオブジェクトの作成 */
	hMap = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE | SEC_COMMIT,
		0, sizeof(SHARED_DATA),
		filename);

	/* 既に作成されていた? */
	DWORD createFileError = GetLastError();

	/* ビューの作成 */
	if (hMap != NULL)
	{
		pData = (SHARED_DATA*)MapViewOfFile(hMap, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SHARED_DATA));
		// 初期化
		if (pData)
		{
			pData->cnt = 0;

			while (1)
			{
				system("cls");
				printf("input data:");
				scanf_s("%d", &pData->cnt);
			}
		}
	}

	return 0;
}

