/************************************************
*              六、信号量实现进程同步             * 
*           并发程序对有界共享主存区的访问         *
*************************************************/
#include<Stdio.h>
#include<windows.h>

int ProductID=0;//产品ID

/*
创建信号量函数
HANDLE CreateSemaphore(IpSemaphoreAttributes,  //信号量安全属性，NULL
						IInitialCount,			//信号量初始值，>0
						IMaximumCount,			//信号量最大值
						IpName);				//信号量名字,若信号量名已使用，则表示打开信号量
*/
/*
释放信号量函数
HANDLE ReleaseSemaphore(hSemaphore,				//信号量句柄
						lReleaseCount,			//释放信号量数量
						lpPreviousCount);		//指向信号量之前值，设为NULL
*/
//OpenSemaphore(); 打开信号量
//Semaphores可以跨进程使用，对其名称对整个系统而言时全局的，命名不能过于普通
//获取信号量的一个占有权：WaitForSingleObject(),WaitForMultipleObjects()等一类函数...

//定义缓冲区空闲块信号量
HANDLE hemopty;
//定义缓冲区产品数信号量
HANDLE hproduct;

//生产产品函数
void Produce() {
	ProductID++;
	printf("Producing No.%d .\n", ProductID);
	printf("Producer has producted %d products all together.\n",ProductID);
	ReleaseSemaphore(hproduct, 1, NULL);//缓冲区产品数增加一个
	ReleaseSemaphore(hemopty, -1, NULL);//缓冲区空闲块数释放一个
	printf("Append Success!\n\n");
}

//生产者线程函数
DWORD WINAPI ThreadProc(LPVOID IpParameter) {
	printf("Producer Thread start!\n");
	printf("Buffer available!\n");
	printf("Producer is producting....\n");
	printf("Successfully producted!\n");
	printf("Producer produce 1 Product per 4 seconds.\n\n");
	while (true) {
		//检查缓冲区信号量，如果有继续执行，没有则等待；
		WaitForSingleObject(hemopty, INFINITE);
		Produce();//生产一个产品，放入缓冲区
		Sleep(4*1000);//等待4秒
	}
	CloseHandle(hemopty);
	CloseHandle(hproduct);

	return 0;
}
//生产者进程
int main() {
	printf("缓冲区大小为 4 .\n");
	hemopty = CreateSemaphore(NULL, 4, 4, "EMOPTY_SEMAPHORE");
	hproduct = CreateSemaphore(NULL, 0, 4, "PRODUCT_SEMAPHORE");
	//创建线程，线程生产产品
	HANDLE Producer = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);
	//进程等待线程运行
	WaitForSingleObject(Producer, INFINITE);
	//关闭线程句柄
	CloseHandle(Producer);
	return 1;
}