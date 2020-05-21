#include<stdio.h>
#include<string.h>
#include<windows.h>

//子进程程序
int main(int argc, char* argv[]) {
	printf("Welcome to use child.exe!\n");
	/*
	@brief OpenEvent()
	@paramp[in] 1\dwDesiredAccess 2\binheritHandle 3\IpName
	@return
	*/
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS,NULL,"YesOrNo");//打开有名事件
	printf("Signal the event to Parent? [y\\n]\n");
	char c = getchar();
	if (c == 'Y' || c == 'y') {
		SetEvent(hEvent);//将事件定为有信号状态
		return 0;
	}
	else {
		ResetEvent(hEvent);//设为无信号状态
	}
	CloseHandle(hEvent);
	Sleep(1000);
	return -1;
}