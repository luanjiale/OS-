/************************************************
*              七、共享主存实现进程通信           *
* 写进程创建共享主存，读进程映射到自己的虚拟地址空间 *
*************************************************/
/*
@brief 创建文件映射内核对象函数
@return success:HANDLE  failed： ERROR_ALREADY_EXISTS / NULL
CreateFileMapping(
	hFile,						//文件句柄
	lPFileMappingAttributes,	//文件安全属性，NULL表示使用默认安全对象
	flProtect,					//文件保护设置
	dwMaximumSizeHigh,			//高位文件大小，通常为0
	dwMaximumSizeLow,			//位文件大小
	lPName);					//共享文件名
*/
/*
@brief 将一个文件映射到当前应用程序的地址空间
MapViewOfFile(
			hFileMappingObject,			//文件映射对象句柄
			dwDesiredAccess,			//共享文件读写权限设定，要与CreateFileMapping函数一致
			dwFileOffsetHigh,			//决定文件偏移量
			dwFileOffsetLow,			//决定文件偏移量
			dwNumberOfBytesToMap		//映射字节数
			)
*/
#include<stdio.h>
#include<windows.h>
#define APPLICATION_NAME "C:\\Users\\LJL\\source\\repos\\Os_lab7_Read\\Debug\\Os_lab7_Read.exe"
#define BUF_SIZE 1025

int  main() {
	//定义 STARTUPINFO结构体变量 cb成员赋值
	STARTUPINFO sui;
	ZeroMemory(&sui, sizeof(sui));
	sui.cb = sizeof(STARTUPINFO);
	//定义PROCESS_INFORMATION结构体变量，用于接收创建进程后返回的信息
	PROCESS_INFORMATION pi;
	//创建子进程
	BOOL ret = CreateProcess(
		APPLICATION_NAME,				//子进程名称（全路径，包含拓展名)
		NULL,							//命令行参数
		NULL,							//不继承父进程的进程句柄
		NULL,							//不继承父进程的线程句柄
		FALSE,							//句柄继承标志为FALSE
		CREATE_NEW_CONSOLE,				//新进程新启用一个窗口
		NULL,							//使用父进程的环境
		NULL,							//使用父进程当前目录
		&sui,							//指向STARTUPINFO
		&pi);							//指向PROCESS_INFORMATION 
	if (!ret) {
		printf("子进程创建失败！\n");
		return -1;
	}
	//创建共享内存
	HANDLE hFile;
	hFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, BUF_SIZE, "FILE_MAPPING");
	//共享内存映射到虚拟内存地址空间
	char *pBuf = (char*)MapViewOfFile(hFile, FILE_MAP_ALL_ACCESS, 0, 0, BUF_SIZE);
	if (hFile!=NULL) {//创建成功
		printf("Create Success!\n");
		while (true) {
			//输入字母写入共享内存中
			printf("input......\n");
			char Info[BUF_SIZE] = { 0 };
			gets_s(Info);
			strncpy_s(pBuf,BUF_SIZE-1, Info,BUF_SIZE-1);
			
		}
	}
	else {
		printf("创建失败！\n");
	}
	//释放共享文件映射
	UnmapViewOfFile(hFile);
	//关闭共享文件句柄
	CloseHandle(hFile);
	system("pause");
	return 0;
}
