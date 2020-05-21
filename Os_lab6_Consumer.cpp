/************************************************
*              �����ź���ʵ�ֽ���ͬ��             *
*************************************************/

#include<stdio.h>
#include<windows.h>
#define APPLICATION_NAME "C:\\Users\\LJL\\source\\repos\\Os_lab6_Producer\\Debug\\Os_lab6_Producer.exe"
int count = 1;
/*
��������������
HANDLE CreateMutex(lpMutexAttributes,	//���ⰲȫ����
					bInitialOwner,		//�ƶ������������Ľ����Ƿ��г�ʼӵ��Ȩ
					lpName);			//����������
*/
/*
�ͷŻ���������������Ϊ���������
BOOL ReleaseMutex(hMutex);
*/

//���廥����,ֻ�Ǵ�����һ������WaitForSingleObject(hMutex,INFINTE);����
HANDLE hMutex=NULL;

//ȫ�ֶ�����п��ź����Ͳ�Ʒ���ź���
HANDLE hemopty=NULL;
HANDLE hproduct=NULL;


//�߳�1����
DWORD WINAPI Fun1Proc(LPVOID IpParameter) {
	printf("Thread 1 start.\n");
	printf("Thread 1 says: product available.\n");
	printf("Thread 2 consume 1 product per 1.5 seconds.\n\n");
	//whileѭ��Ϊ���ѹ��̣����ϼ�黺������Ʒ���ź�����
	//ֻҪ�в�Ʒ���ź����������Ѳ�Ʒ��
	//���Ѳ�Ʒ֮ǰȡ�û����������������ͷ��ź���
	while (TRUE) {
		//��黺������Ʒ���ź���������в�Ʒ����Ʒ��������һ������ȴ���
		WaitForSingleObject(hproduct, INFINITE);
		printf("\n");
		//���Ѳ�Ʒ���ȼ���
		WaitForSingleObject(hMutex, INFINITE);
		printf("���� %d :\n", count);
		printf("Thread 1 get Mutex.\n");
		//���Ѳ�Ʒ
		printf("Thread 1 is consumering a NO.%d product.\n",count++);
		ReleaseSemaphore(hproduct, -1, NULL);//��������Ʒ������һ��
		ReleaseSemaphore(hemopty, 1, NULL);//���������п����ͷ�һ��
		//�ͷŻ�����
		ReleaseMutex(hMutex);
		printf("Thread 1 Release Mutex.\n");
		Sleep(1500);//�ȴ�1.5s
	}
	return 0;
}

//�߳�2����
DWORD WINAPI Fun2Proc(LPVOID IpParameter) {
	printf("Thread 2 start.\n");
	//WaitForSingleObject(hproduct, INFINITE);//���ͷ�һ���ź���
	printf("Thread 2 says: product available.\n");
	printf("Thread 2 consume 1 product per 3.5 seconds.\n\n");
	//whileѭ��Ϊ���ѹ��̣����ϼ�黺������Ʒ���ź�����
	//ֻҪ�в�Ʒ���ź����������Ѳ�Ʒ��
	//���Ѳ�Ʒ֮ǰȡ�û����������������ͷ��ź���
	while (TRUE) {
		//��黺������Ʒ���ź���������в�Ʒ����Ʒ��������һ������ȴ���
		WaitForSingleObject(hproduct, INFINITE);
		printf("\n");
		//���Ѳ�Ʒ���ȼ���
		WaitForSingleObject(hMutex, INFINITE);
		printf("���� %d :\n", count);
		printf("Thread 2 get Mutex.\n");
		//���Ѳ�Ʒ
		printf("Thread 2 is consumering a NO.%d product.\n", count++);
		ReleaseSemaphore(hproduct, -1, NULL);//��������Ʒ������һ��
		ReleaseSemaphore(hemopty, 1, NULL);//���������п����ͷ�һ��
		//�ͷŻ�����
		ReleaseMutex(hMutex);
		printf("Thread 2 Release Mutex.\n");
		Sleep(3500);//�ȴ�3.5s
	}
	return 0;
}


//�����߽���
int main() {
	//���������ź���
	 hMutex = CreateMutex(NULL, FALSE, "MUTEX");
	 //�������߿��п��ź���
	 hemopty = CreateSemaphore(NULL, 4, 4, "EMOPTY_SEMAPHORE");
	 //�������߲�Ʒ���ź���
	 hproduct = CreateSemaphore(NULL, 0, 4, "PRODUCT_SEMAPHORE");

	//���������߽���
	STARTUPINFO sui;
	ZeroMemory(&sui, sizeof(sui));
	sui.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
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
		printf("���̴���ʧ�ܣ�\n");
		return -1;
	}
	//���������������߳�,�������߳������Ѳ�Ʒ
	HANDLE ConsumerThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	HANDLE ConsumerThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	
	//�ȴ����������߳�����
	WaitForSingleObject(ConsumerThread1, INFINITE);
	WaitForSingleObject(ConsumerThread2, INFINITE);
	//�ȴ��ӽ��̽���
	WaitForSingleObject(pi.hProcess, INFINITE);
	//�ر��ӽ��̵Ľ��̾�����߳̾��
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	//�رջ��������
	CloseHandle(hMutex);
	//�ر��߳̾��
	CloseHandle(ConsumerThread1);
	CloseHandle(ConsumerThread2);
}