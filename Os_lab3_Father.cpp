/************************************************
*              �����ź�ͨ��                      *
*		 ���������¼�ʵ�ָ��ӽ���ͨ��              *
*************************************************/
#include"iostream"
#include<windows.h>
#define APPLICATION_NAME "C:\\Users\\LJL\\source\\repos\\Os_lab3_Child\\Debug\\Os_lab3_Child.exe"
//������
int main() {
	/*
	@brief CreateEvent
	@paramp[in] 1\IpEventAttributes 2\bManualReset 3\bInitialState 4\IpName
	@return HANDLE
	*/
	HANDLE hEvent=CreateEvent(NULL,TRUE,FALSE,"YesOrNo");//���������¼�,��Ϊ�ֶ��¼�������ҪResetEvent
	
	//���� STARTUPINFO�ṹ����� cb��Ա��ֵ
	STARTUPINFO sui;
	ZeroMemory(&sui, sizeof(sui));
	sui.cb = sizeof(STARTUPINFO);
	//����PROCESS_INFORMATION�ṹ����������ڽ��մ������̺󷵻ص���Ϣ
	PROCESS_INFORMATION pi;
	//�����ӽ���
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
		printf("�ӽ��̴���ʧ�ܣ�\n");
		return -1;
	}
	printf("Wait for event.\n");
	if (WAIT_FAILED == WaitForSingleObject(hEvent,INFINITE)) {//�ȴ��¼��ź�
		printf("�ȴ��¼��ź�ʧ�ܣ�\n");
		return -1;
	}
	printf("Get the event!\n");
	CloseHandle(hEvent);//�رվ��
	system("pause");
	return 0;
}
