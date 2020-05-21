/************************************************
*                  一、创建子进程                *
*************************************************/
#include<stdio.h>
#include<windows.h>
#define APPLICATION_NAME "C:\\Users\\LJL\\source\\repos\\Os_lab1_Child\\Debug\\Os_lab1_Child.exe"
int main() {
	/*
	@brief CreateProcess
	@paramp[in] 1\IpApplicationName 2\IpcommandLine    3\IpProcessAttributes 4\IpThreadAttribute
	            5\blnheritHandles   6\dwCreationFalgs  7\ipEnvironment       8\IpcurrentDiectory 
				9\IpStartupInfo		10\IpProcessInformation
	@return TRUE or FALSE
	*/
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
	if (!ret){
		printf("子进程创建失败！\n");
		return -1;
	}
	printf("子进程创建成功！\n");
	//等待子进程结束
	WaitForSingleObject(pi.hProcess, INFINITE);
	printf("子进程结束！\n");
	//关闭子进程的进程句柄和线程句柄
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	printf("父进程结束! \n");
	printf("5秒后关闭窗口。\n");
	Sleep(5 * 1000);
	return 0;
}