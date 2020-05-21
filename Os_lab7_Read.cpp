/************************************************
*              七、共享主存实现进程通信           *
* 写进程创建共享主存，读进程映射到自己的虚拟地址空间 *
*************************************************/
#include<stdio.h>
#include<windows.h>
#define BUF_SIZE 1024

/*
打开一个现成的文件映射
OpenFileMapping(dwDesiredAccess,	//共享文件读写权限
				blnheritHandle,		//继承标志，若这个函数返回句柄能由当前进程启动新的进程继承，则这个参数为TRUE
				lpName)				//共享文件名
*/
int main() {
	//定义共享内存句柄
	HANDLE hFile;
	//打开共享内存
	hFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, "FILE_MAPPING");
	//共享内存映射到虚拟内存地址空间
	char *pBuf = (char*)MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
	if (hFile != NULL) {
		while (true) {
			//读取共享内存
			printf("按回车键接受数据.....\n");
			getchar();
			printf("%s\n", pBuf);
		}
	}
	else {
		printf("创建失败！\n");
	}
	//关闭映射
	UnmapViewOfFile(hFile);
	//关闭共享文件句柄
	CloseHandle(hFile);
	system("pause");
	return 0;
}