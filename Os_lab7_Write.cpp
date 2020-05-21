/************************************************
*              �ߡ���������ʵ�ֽ���ͨ��           *
* д���̴����������棬������ӳ�䵽�Լ��������ַ�ռ� *
*************************************************/
/*
@brief �����ļ�ӳ���ں˶�����
@return success:HANDLE  failed�� ERROR_ALREADY_EXISTS / NULL
CreateFileMapping(
	hFile,						//�ļ����
	lPFileMappingAttributes,	//�ļ���ȫ���ԣ�NULL��ʾʹ��Ĭ�ϰ�ȫ����
	flProtect,					//�ļ���������
	dwMaximumSizeHigh,			//��λ�ļ���С��ͨ��Ϊ0
	dwMaximumSizeLow,			//λ�ļ���С
	lPName);					//�����ļ���
*/
/*
@brief ��һ���ļ�ӳ�䵽��ǰӦ�ó���ĵ�ַ�ռ�
MapViewOfFile(
			hFileMappingObject,			//�ļ�ӳ�������
			dwDesiredAccess,			//�����ļ���дȨ���趨��Ҫ��CreateFileMapping����һ��
			dwFileOffsetHigh,			//�����ļ�ƫ����
			dwFileOffsetLow,			//�����ļ�ƫ����
			dwNumberOfBytesToMap		//ӳ���ֽ���
			)
*/
#include<stdio.h>
#include<windows.h>
#define APPLICATION_NAME "C:\\Users\\LJL\\source\\repos\\Os_lab7_Read\\Debug\\Os_lab7_Read.exe"
#define BUF_SIZE 1025

int  main() {
	//���� STARTUPINFO�ṹ����� cb��Ա��ֵ
	STARTUPINFO sui;
	ZeroMemory(&sui, sizeof(sui));
	sui.cb = sizeof(STARTUPINFO);
	//����PROCESS_INFORMATION�ṹ����������ڽ��մ������̺󷵻ص���Ϣ
	PROCESS_INFORMATION pi;
	//�����ӽ���
	BOOL ret = CreateProcess(
		APPLICATION_NAME,				//�ӽ������ƣ�ȫ·����������չ��)
		NULL,							//�����в���
		NULL,							//���̳и����̵Ľ��̾��
		NULL,							//���̳и����̵��߳̾��
		FALSE,							//����̳б�־ΪFALSE
		CREATE_NEW_CONSOLE,				//�½���������һ������
		NULL,							//ʹ�ø����̵Ļ���
		NULL,							//ʹ�ø����̵�ǰĿ¼
		&sui,							//ָ��STARTUPINFO
		&pi);							//ָ��PROCESS_INFORMATION 
	if (!ret) {
		printf("�ӽ��̴���ʧ�ܣ�\n");
		return -1;
	}
	//���������ڴ�
	HANDLE hFile;
	hFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, "FILE_MAPPING");
	//�����ڴ�ӳ�䵽�����ڴ��ַ�ռ�
	char *pBuf = (char*)MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
	if (hFile!=NULL) {//�����ɹ�
		printf("Create Success!\n");
		while (true) {
			//������ĸд�빲���ڴ���
			printf("input......\n");
			char Info[BUF_SIZE] = { 0 };
			gets_s(Info);
			strncpy_s(pBuf,BUF_SIZE-1, Info,BUF_SIZE-1);
			
		}
	}
	else {
		printf("����ʧ�ܣ�\n");
	}
	//�ͷŹ����ļ�ӳ��
	UnmapViewOfFile(hFile);
	//�رչ����ļ����
	CloseHandle(hFile);
	system("pause");
	return 0;
}
