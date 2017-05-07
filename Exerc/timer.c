#include <stdio.h>
#include "windows.h"  

/*
#pragma comment( comment-type ,["commentstring"] )
comment-type是一个预定义的标识符，指定注释的类型，应该是compiler，exestr，lib，linker之一。
commentstring是一个提供为comment - type提供附加信息的字符串。
Winmm.lib:可以支持windows多媒体编程
*/
#pragma comment(lib,"Winmm.lib")   //UINT , UINT ,DWORD ,DWORD ,DWORD 

int gtime_ID1, gtime_ID2;          //返回得到的ID

void CALLBACK print100ms(UINT wTimerID, UINT msg, DWORD data, DWORD dwl, DWORD dw2)
{
	printf("100ms print:%d\n", data);
}


void CALLBACK print1000ms(UINT wTimerID, UINT msg, DWORD data, DWORD dwl, DWORD dw2)
{
	printf("~~~~~~1000ms print:%d\n", data);
}

//DWORD_PRTd
//word   双字 就是四个字节
//ptr     pointer缩写 即指针
//[]里的数据是一个地址值，这个地址指向一个双字型数据
//比如mov eax, dword ptr[12345678]  把内存地址12345678中的双字型（32位）数据赋给ea
void DataAcq(DWORD_PTR data)    
{

	/*
	MMRESULT timeSetEvent（ UINT uDelay, UINT uResolution,  LPTIMECALLBACK lpTimeProc, WORD dwUser, UINT fuEvent ）
	其中: uDelay：以毫秒指定事件的周期。
	Uresolution：以毫秒指定延时的精度，数值越小定时器事件分辨率越高。缺省值为1ms。
	LpTimeProc：指向一个回调函数。
	DwUser：存放用户提供的回调数据。
	FuEvent：指定定时器事件类型：
		TIME_ONESHOT：uDelay毫秒后只产生一次事件
		TIME_PERIODIC ：每隔uDelay毫秒周期性地产生事件
	*/
	gtime_ID1 = timeSetEvent(100, 1, (LPTIMECALLBACK)print100ms, data, TIME_PERIODIC);
	gtime_ID2 = timeSetEvent(1000, 1, (LPTIMECALLBACK)print1000ms, data, TIME_PERIODIC);
	if (gtime_ID1 == NULL || gtime_ID2 == NULL)
	{
		printf("time ID is not created\n");
		return;
	}
	return;
}

void main()
{
	int i = 0;
	while (1)
	{
		DataAcq(i);	
		Sleep(1000);
		i++;

		/*
		timeKillEvent 关掉定时器的函数，一定要一一对应，每次timeSetEvent返回的定时器的ID是不一样的，也就是说调用一次timeSetEvent就会产生一次Id
		调用几次timeSetEvent，就需要调用几次timeKillEvent ，而且必须是相对应的ID,否则可能出现程序崩溃
		*/
		timeKillEvent(gtime_ID1);
		timeKillEvent(gtime_ID2);
	}
}

