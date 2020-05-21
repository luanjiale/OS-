/************************************************
*                  һ�������ӽ���                *
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
	if (!ret){
		printf("�ӽ��̴���ʧ�ܣ�\n");
		return -1;
	}
	printf("�ӽ��̴����ɹ���\n");
	//�ȴ��ӽ��̽���
	WaitForSingleObject(pi.hProcess, INFINITE);
	printf("�ӽ��̽�����\n");
	//�ر��ӽ��̵Ľ��̾�����߳̾��
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	printf("�����̽���! \n");
	printf("5���رմ��ڡ�\n");
	Sleep(5 * 1000);
	return 0;
}