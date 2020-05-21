/************************************************
*              线程共享进程数据                   *
*************************************************/

#include<stdio.h>
#include<windows.h>

static int count;//定义全局变量
//线程函数
DWORD WINAPI ThreadProc(LPVOID IpParameter)
{
	for (count = 1; count <= 10; count++) {
		printf("count = %d\n", count);
	}
	printf("线程结束！\n");
	return 0;
}
int main() {
	/*
	@brief CreateThread
	@param[in] 1\IpThreadAttributes 2\dwStackSize
			   3\IpStartAddress 4\IpParameter
		       5\dwCreationFlags 6\IpThreadld
	@return HANDLE
	*/
	HANDLE hThread=CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	WaitForSingleObject(hThread, INFINITE);
	Sleep(10 * 1000);
	return 0;

}