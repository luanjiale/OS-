/************************************************
*              �̹߳����������                   *
*************************************************/

#include<stdio.h>
#include<windows.h>

static int count;//����ȫ�ֱ���
//�̺߳���
DWORD WINAPI ThreadProc(LPVOID IpParameter)
{
	for (count = 1; count <= 10; count++) {
		printf("count = %d\n", count);
	}
	printf("�߳̽�����\n");
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