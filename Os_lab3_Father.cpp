/************************************************
*              三、信号通信                      *
*		 创建有名事件实现父子进程通信              *
*************************************************/
#include"iostream"
#include<windows.h>
#define APPLICATION_NAME "C:\\Users\\LJL\\source\\repos\\Os_lab3_Child\\Debug\\Os_lab3_Child.exe"
//父进程
int main() {
	/*
	@brief CreateEvent
	@paramp[in] 1\IpEventAttributes 2\bManualReset 3\bInitialState 4\IpName
	@return HANDLE
	*/
	HANDLE hEvent=CreateEvent(NULL,TRUE,FALSE,"YesOrNo");//创建有名事件,设为手动事件对象，需要ResetEvent
	
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
	printf("Wait for event.\n");
	if (WAIT_FAILED == WaitForSingleObject(hEvent,INFINITE)) {//等待事件信号
		printf("等待事件信号失败！\n");
		return -1;
	}
	printf("Get the event!\n");
	CloseHandle(hEvent);//关闭句柄
	system("pause");
	return 0;
}
