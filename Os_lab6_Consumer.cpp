/************************************************
*              六、信号量实现进程同步             *
*************************************************/

#include<stdio.h>
#include<windows.h>
#define APPLICATION_NAME "C:\\Users\\LJL\\source\\repos\\Os_lab6_Producer\\Debug\\Os_lab6_Producer.exe"
int count = 1;
/*
创建互斥量函数
HANDLE CreateMutex(lpMutexAttributes,	//互斥安全属性
					bInitialOwner,		//制定创建互斥量的进程是否有初始拥有权
					lpName);			//互斥量名字
*/
/*
释放互斥量函数，参数为互斥量句柄
BOOL ReleaseMutex(hMutex);
*/

//定义互斥量,只是创建了一把锁，WaitForSingleObject(hMutex,INFINTE);加锁
HANDLE hMutex=NULL;

//全局定义空闲块信号量和产品数信号量
HANDLE hemopty=NULL;
HANDLE hproduct=NULL;


//线程1函数
DWORD WINAPI Fun1Proc(LPVOID IpParameter) {
	printf("Thread 1 start.\n");
	printf("Thread 1 says: product available.\n");
	printf("Thread 2 consume 1 product per 1.5 seconds.\n\n");
	//while循环为消费过程，不断检查缓冲区产品数信号量，
	//只要有产品数信号量，就消费产品，
	//消费产品之前取得互斥量，消费完再释放信号量
	while (TRUE) {
		//检查缓冲区产品数信号量，如果有产品，产品数数量减一，否则等待；
		WaitForSingleObject(hproduct, INFINITE);
		printf("\n");
		//消费产品，先加锁
		WaitForSingleObject(hMutex, INFINITE);
		printf("操作 %d :\n", count);
		printf("Thread 1 get Mutex.\n");
		//消费产品
		printf("Thread 1 is consumering a NO.%d product.\n",count++);
		ReleaseSemaphore(hproduct, -1, NULL);//缓冲区产品数增加一个
		ReleaseSemaphore(hemopty, 1, NULL);//缓冲区空闲块数释放一个
		//释放互斥量
		ReleaseMutex(hMutex);
		printf("Thread 1 Release Mutex.\n");
		Sleep(1500);//等待1.5s
	}
	return 0;
}

//线程2函数
DWORD WINAPI Fun2Proc(LPVOID IpParameter) {
	printf("Thread 2 start.\n");
	//WaitForSingleObject(hproduct, INFINITE);//会释放一个信号量
	printf("Thread 2 says: product available.\n");
	printf("Thread 2 consume 1 product per 3.5 seconds.\n\n");
	//while循环为消费过程，不断检查缓冲区产品数信号量，
	//只要有产品数信号量，就消费产品，
	//消费产品之前取得互斥量，消费完再释放信号量
	while (TRUE) {
		//检查缓冲区产品数信号量，如果有产品，产品数数量减一，否则等待；
		WaitForSingleObject(hproduct, INFINITE);
		printf("\n");
		//消费产品，先加锁
		WaitForSingleObject(hMutex, INFINITE);
		printf("操作 %d :\n", count);
		printf("Thread 2 get Mutex.\n");
		//消费产品
		printf("Thread 2 is consumering a NO.%d product.\n", count++);
		ReleaseSemaphore(hproduct, -1, NULL);//缓冲区产品数增加一个
		ReleaseSemaphore(hemopty, 1, NULL);//缓冲区空闲块数释放一个
		//释放互斥量
		ReleaseMutex(hMutex);
		printf("Thread 2 Release Mutex.\n");
		Sleep(3500);//等待3.5s
	}
	return 0;
}


//消费者进程
int main() {
	//创建互斥信号量
	 hMutex = CreateMutex(NULL, FALSE, "MUTEX");
	 //打开生产者空闲块信号量
	 hemopty = CreateSemaphore(NULL, 4, 4, "EMOPTY_SEMAPHORE");
	 //打开生产者产品数信号量
	 hproduct = CreateSemaphore(NULL, 0, 4, "PRODUCT_SEMAPHORE");

	//创建生产者进程
	STARTUPINFO sui;
	ZeroMemory(&sui, sizeof(sui));
	sui.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
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
		printf("进程创建失败！\n");
		return -1;
	}
	//创建两个消费者线程,在消费线程中消费产品
	HANDLE ConsumerThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	HANDLE ConsumerThread2 = CreateThread(NULL, 0, Fun2Proc, NULL, 0, NULL);
	
	//等待两个消费线程运行
	WaitForSingleObject(ConsumerThread1, INFINITE);
	WaitForSingleObject(ConsumerThread2, INFINITE);
	//等待子进程结束
	WaitForSingleObject(pi.hProcess, INFINITE);
	//关闭子进程的进程句柄和线程句柄
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	//关闭互斥量句柄
	CloseHandle(hMutex);
	//关闭线程句柄
	CloseHandle(ConsumerThread1);
	CloseHandle(ConsumerThread2);
}