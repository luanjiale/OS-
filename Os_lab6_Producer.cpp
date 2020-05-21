/************************************************
*              �����ź���ʵ�ֽ���ͬ��             * 
*           ����������н繲���������ķ���         *
*************************************************/
#include<Stdio.h>
#include<windows.h>

int ProductID=0;//��ƷID

/*
�����ź�������
HANDLE CreateSemaphore(IpSemaphoreAttributes,  //�ź�����ȫ���ԣ�NULL
						IInitialCount,			//�ź�����ʼֵ��>0
						IMaximumCount,			//�ź������ֵ
						IpName);				//�ź�������,���ź�������ʹ�ã����ʾ���ź���
*/
/*
�ͷ��ź�������
HANDLE ReleaseSemaphore(hSemaphore,				//�ź������
						lReleaseCount,			//�ͷ��ź�������
						lpPreviousCount);		//ָ���ź���֮ǰֵ����ΪNULL
*/
//OpenSemaphore(); ���ź���
//Semaphores���Կ����ʹ�ã��������ƶ�����ϵͳ����ʱȫ�ֵģ��������ܹ�����ͨ
//��ȡ�ź�����һ��ռ��Ȩ��WaitForSingleObject(),WaitForMultipleObjects()��һ�ຯ��...

//���建�������п��ź���
HANDLE hemopty;
//���建������Ʒ���ź���
HANDLE hproduct;

//������Ʒ����
void Produce() {
	ProductID++;
	printf("Producing No.%d .\n", ProductID);
	printf("Producer has producted %d products all together.\n",ProductID);
	ReleaseSemaphore(hproduct, 1, NULL);//��������Ʒ������һ��
	ReleaseSemaphore(hemopty, -1, NULL);//���������п����ͷ�һ��
	printf("Append Success!\n\n");
}

//�������̺߳���
DWORD WINAPI ThreadProc(LPVOID IpParameter) {
	printf("Producer Thread start!\n");
	printf("Buffer available!\n");
	printf("Producer is producting....\n");
	printf("Successfully producted!\n");
	printf("Producer produce 1 Product per 4 seconds.\n\n");
	while (true) {
		//��黺�����ź���������м���ִ�У�û����ȴ���
		WaitForSingleObject(hemopty, INFINITE);
		Produce();//����һ����Ʒ�����뻺����
		Sleep(4*1000);//�ȴ�4��
	}
	CloseHandle(hemopty);
	CloseHandle(hproduct);

	return 0;
}
//�����߽���
int main() {
	printf("��������СΪ 4 .\n");
	hemopty = CreateSemaphore(NULL, 4, 4, "EMOPTY_SEMAPHORE");
	hproduct = CreateSemaphore(NULL, 0, 4, "PRODUCT_SEMAPHORE");
	//�����̣߳��߳�������Ʒ
	HANDLE Producer = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	//���̵ȴ��߳�����
	WaitForSingleObject(Producer, INFINITE);
	//�ر��߳̾��
	CloseHandle(Producer);
	return 1;
}