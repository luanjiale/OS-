/************************************************
*              �ߡ���������ʵ�ֽ���ͨ��           *
* д���̴����������棬������ӳ�䵽�Լ��������ַ�ռ� *
*************************************************/
#include<stdio.h>
#include<windows.h>
#define BUF_SIZE 1024

/*
��һ���ֳɵ��ļ�ӳ��
OpenFileMapping(dwDesiredAccess,	//�����ļ���дȨ��
				blnheritHandle,		//�̳б�־��������������ؾ�����ɵ�ǰ���������µĽ��̼̳У����������ΪTRUE
				lpName)				//�����ļ���
*/
int main() {
	//���干���ڴ���
	HANDLE hFile;
	//�򿪹����ڴ�
	hFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, "FILE_MAPPING");
	//�����ڴ�ӳ�䵽�����ڴ��ַ�ռ�
	char *pBuf = (char*)MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
	if (hFile != NULL) {
		while (true) {
			//��ȡ�����ڴ�
			printf("���س�����������.....\n");
			getchar();
			printf("%s\n", pBuf);
		}
	}
	else {
		printf("����ʧ�ܣ�\n");
	}
	//�ر�ӳ��
	UnmapViewOfFile(hFile);
	//�رչ����ļ����
	CloseHandle(hFile);
	system("pause");
	return 0;
}