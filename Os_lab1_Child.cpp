#include<stdio.h>
#include<string.h>
#include<windows.h>
#pragma warning(disable:4996)
#define PATH "C:\\Users\\LJL\\source\\repos\\Os_lab1_Child\\Os_lab1_Child\\data.dat"
//子进程程序
int main(int argc ,char* argv[]) {
	printf("Welcome to use child.exe!\n");
	FILE *read = fopen(PATH, "r");
	char msg[2][100];
	memset(msg[0], 0, sizeof(msg[0]));
	memset(msg[1], 0, sizeof(msg[1]));
	for(int i=0;i<2;i++){
		fgets(msg[i], 100, read);
	}
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 100; j++) {
			if (msg[i][j] !=0)
				printf("%c", msg[i][j]);
		}
	}
	fclose(read);
	putchar('\n');
	printf("子进程结束！\n");
	Sleep(8* 1000);
	return 1;
}