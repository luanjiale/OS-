#include<stdio.h>
#include<string.h>
#include<windows.h>

//�ӽ��̳���
int main(int argc, char* argv[]) {
	printf("Welcome to use child.exe!\n");
	/*
	@brief OpenEvent()
	@paramp[in] 1\dwDesiredAccess 2\binheritHandle 3\IpName
	@return
	*/
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS,NULL,"YesOrNo");//�������¼�
	printf("Signal the event to Parent? [y\\n]\n");
	char c = getchar();
	if (c == 'Y' || c == 'y') {
		SetEvent(hEvent);//���¼���Ϊ���ź�״̬
		return 0;
	}
	else {
		ResetEvent(hEvent);//��Ϊ���ź�״̬
	}
	CloseHandle(hEvent);
	Sleep(1000);
	return -1;
}