#include <iostream>
#include <Windows.h>

using namespace std;

int main() {

	cout << ".........NAMED PIPE SERVER........." << endl;
	// Local Variable
		//NamedPipe
	HANDLE hCreateNamedPipe = nullptr;
	char szInputBuffer[1023];
	char szOutputBuffer[1023];
	DWORD dwInput = sizeof(szInputBuffer);
	DWORD dwOutput = sizeof(szOutputBuffer);
		//ConnectNamedPipe
	BOOL bConnectNamedPipe;


		//WriteFile
	BOOL bWriteFile = 0;
	char szWriteBuffer[1023] = "hello from NamedPipe server";
	DWORD dwWriteSize = sizeof(szWriteBuffer);
	DWORD dwNumBytesWrite = 0;

		//FlushBuffer
	BOOL bFlushFile;

		//ReadFile
	BOOL bReadFile = 0;
	char szReadBuffer[1023];
	DWORD dwReadSize = sizeof(szReadBuffer);
	DWORD dwNumBytesRead = 0;

	//create namedPipe
	hCreateNamedPipe = CreateNamedPipe(L"\\\\.\\pipe\\MUTSPIPE",
		PIPE_ACCESS_DUPLEX, 
		// двунаправленный как серверные, так и клиентские
		//процессы могут выполнять чтение из канала и запись в него
		PIPE_TYPE_MESSAGE|PIPE_READMODE_MESSAGE|PIPE_WAIT,
		//Данные записываются и считываются в канал в виде потока сообщений
		//Канал дожидается, пока появятся данные для чтения или клиент не 
		//будет подключен
		PIPE_UNLIMITED_INSTANCES,
		//количество создаваемых экземпляров канала ограничено только
		//доступностью системных ресурсов
		dwOutput,
		dwInput,
		0, // timeout
		NULL // security params
	);
	if (hCreateNamedPipe == INVALID_HANDLE_VALUE)
	{
		cout << "Creation Pipe failed, error: " << GetLastError() << endl;
		return 0;
	}

	cout << "creation pipe success" << endl;

	//Connect Pipe
	bConnectNamedPipe = ConnectNamedPipe(hCreateNamedPipe, NULL);
	if (bConnectNamedPipe == FALSE)
	{
		cout << "connection failed, erroe" << GetLastError() << endl;
	}
	cout << "connection success" << endl;

	//write operation
	bWriteFile = WriteFile(hCreateNamedPipe, szWriteBuffer, dwWriteSize, &dwNumBytesWrite, NULL);
	if (bWriteFile == FALSE)
	{
		cout << "WriteFile failed, erroe" << GetLastError() << endl;
	}
	cout << "WriteFile success" << endl;


	//Flush the File
	//Очищает буферы указанного файла и приводит к записи всех буферных данных в файл.
	bFlushFile = FlushFileBuffers(hCreateNamedPipe);
	if (bFlushFile == FALSE)
	{
		cout << "Flush the File failed, erroe" << GetLastError() << endl;
	}
	cout << "Flush the File success" << endl;

	//read file

	bReadFile = ReadFile(hCreateNamedPipe, szReadBuffer, dwReadSize, &dwNumBytesRead, NULL);
	if (bReadFile == FALSE)
	{
		cout << "read file failed, erroe" << GetLastError() << endl;
	}
	cout << "read file success" << endl;

	cout << "DATA READING FROM CLIENT -> " << szReadBuffer << endl;

	DisconnectNamedPipe(hCreateNamedPipe);
	CloseHandle(hCreateNamedPipe);
	system("PAUSE");

	return 1;
}