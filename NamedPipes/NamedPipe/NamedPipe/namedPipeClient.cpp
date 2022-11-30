#include <iostream>
#include <Windows.h>

using namespace std;

int client() {

	cout << ".........NAMED PIPE CLIENT........." << endl;
	// Local Variable
	HANDLE hCreateFile = nullptr;


	//WriteFile
	BOOL bWriteFile = 0;
	char szWriteBuffer[1023] = "hello from NamedPipe client";
	DWORD dwWriteSize = sizeof(szWriteBuffer);
	DWORD dwNumBytesWrite = 0;


	//ReadFile
	BOOL bReadFile = 0;
	char szReadBuffer[1023]{};
	DWORD dwReadSize = sizeof(szReadBuffer);
	DWORD dwNumBytesRead = 0;

	//create file for Pipe
	hCreateFile = CreateFile(L"\\\\.\\pipe\\MUTSPIPE",
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hCreateFile == INVALID_HANDLE_VALUE)
	{
		cout << "Creation file failed, error: " << GetLastError() << endl;
		return 0;
	}

	cout << "creation file success" << endl;



	//write operation
	bWriteFile = WriteFile(hCreateFile, szWriteBuffer, dwWriteSize, &dwNumBytesWrite, NULL);
	if (bWriteFile == FALSE)
	{
		cout << "WriteFile failed, erroe" << GetLastError() << endl;
	}
	cout << "WriteFile success" << endl;



	//read file

	bReadFile = ReadFile(hCreateFile, szReadBuffer, dwReadSize, &dwNumBytesRead, NULL);
	if (bReadFile == FALSE)
	{
		cout << "read file failed, erroe" << GetLastError() << endl;
	}
	cout << "read file success" << endl;

	cout << "DATA READING FROM CLIENT -> " << szReadBuffer << endl;

	CloseHandle(hCreateFile);
	system("PAUSE");

	return 1;

}