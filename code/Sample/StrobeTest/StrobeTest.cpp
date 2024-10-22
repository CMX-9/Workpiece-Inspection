// StrobeTest.cpp : Defines the entry point for the console application.
//

// 本示例使用软触发采集，演示闪光灯自定义输出

#include "stdafx.h"
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include "..\\..\\inc\\HVDAILT.h"
#include "..\\..\\inc\\HVdef.h"
#pragma comment(lib,"..\\..\\lib\\HVDailt.lib")

// 定义自定义输出信号类型
#define SIGNAL_HIGH_IMPULSE 0 // 正脉冲
#define SIGNAL_LOW_IMPULSE  1 // 负脉冲
#define SIGNAL_HIGH_LEVEL   2 // 高电平
#define SIGNAL_LOW_LEVEL    3 // 低电平

// 采集计数
unsigned long g_nImageCount = 0;

// 获取最大分辨率
HVSTATUS GetMaxResolution(HHV hhv, HV_RESOLUTION resMode, int *pMaxWidth, int *pMaxHeight);

// 简单的回调函数
int CALLBACK SnapProc(HV_SNAP_INFO *pInfo)
{
	printf("Image %d:\n",g_nImageCount++);
	return 0;
}


int main(int argc, char* argv[])
{
	HHV hhv = NULL;
	HVSTATUS status = STATUS_NOT_SUPPORT_INTERFACE;
	HV_SIGNAL_MODE strobe = {HIGH,SIGNAL_IMPULSE};
	int nSize = sizeof(HV_SIGNAL_MODE);
	BYTE *imageBuff;
	
	
	printf("\n---------------------------------------\n");
	printf("StrobeTest.exe用于设置Strobe输出信号:\n");
	printf("请输入0 ~ 3间的一个数字，0: 正脉冲; 1: 负脉冲; 2: 高电平; 3:低电平\n");	
	scanf("%s",argv[0]);

	// 检验输入参数
	assert(argv);
	int nSignal  = atoi(argv[0]);
	assert(nSignal>-1);
	assert(nSignal<4);

	// 打开设备
	status = BeginHVDevice(1,&hhv);
	assert(HV_SUCCESS(status));
	
	// 闪光灯只有在触发采集状态下，才能输出有效信号
	//
	
	// 1 设置RES_MODE0的触发采集方式
	//
	status = HVSetResolution(hhv,RES_MODE0);
	assert(HV_SUCCESS(status));
	status = HVSetSnapMode(hhv,TRIGGER);
	assert(HV_SUCCESS(status));

	// 2 打开连续采集
	//
	// 获取分辨率
	int nMaxWidth = 0; 
    int nMaxHeight = 0;
	status = GetMaxResolution(hhv,RES_MODE0,&nMaxWidth,&nMaxHeight);
	assert(HV_SUCCESS(status));

	// 打开采集
	status = HVOpenSnap(hhv,SnapProc,NULL);//没有回调输入参数
	assert(HV_SUCCESS(status));
	imageBuff = new BYTE[nMaxWidth*nMaxHeight];
	status = HVStartSnap(hhv,&imageBuff,1);
	assert(HV_SUCCESS(status));


	// 3 设置Strobe输出信号
	switch(nSignal){
	case SIGNAL_HIGH_IMPULSE://正脉冲信号
		strobe.Mode     = SIGNAL_IMPULSE;
		strobe.Polarity = HIGH;
		status = HVCommand(hhv,CMD_SET_STROBE_SIGNAL_MODE,&strobe,&nSize);
		break;
	case SIGNAL_LOW_IMPULSE://负脉冲信号
		strobe.Mode     = SIGNAL_IMPULSE;
		strobe.Polarity = LOW;
		status = HVCommand(hhv,CMD_SET_STROBE_SIGNAL_MODE,&strobe,&nSize);
		break;
	case SIGNAL_HIGH_LEVEL://高电平信号	
		strobe.Mode     = SIGNAL_LEVEL;
		strobe.Polarity = HIGH;
		status = HVCommand(hhv,CMD_SET_STROBE_SIGNAL_MODE,&strobe,&nSize);
		break;
	case SIGNAL_LOW_LEVEL://低电平信号	
		strobe.Mode     = SIGNAL_LEVEL;
		strobe.Polarity = LOW;
		status = HVCommand(hhv,CMD_SET_STROBE_SIGNAL_MODE,&strobe,&nSize);
		break;
	default:
		printf("Invalid Parameter argv[0]=%d\n",nSignal);
		break;
	}	

	// 采集20帧
	while (g_nImageCount<20)
	{
		status = HVTriggerShot(hhv);
		Sleep(1000);
		
	}	

	// 4 结束采集
	status = HVStopSnap(hhv);
	assert(HV_SUCCESS(status));
	status = HVCloseSnap(hhv);
	assert(HV_SUCCESS(status));

	delete []imageBuff;

	status = EndHVDevice(hhv);
	assert(HV_SUCCESS(status));
	
	return 0;
}


HVSTATUS GetMaxResolution(HHV hhv, HV_RESOLUTION resMode, int *pMaxWidth, int *pMaxHeight)
{
	int nBuffSize = 0; 

	// 首先要获得信息数据的大小 
	HVGetDeviceInfo(hhv,DESC_RESOLUTION,NULL,&nBuffSize);
    
	// 再次调用函数获得设备分辨率的信息 
	BYTE *pbContext = new BYTE[nBuffSize]; 
	DWORD *pdContext = (DWORD *)pbContext; 
	HVSTATUS status = HVGetDeviceInfo(hhv,DESC_RESOLUTION,pdContext,&nBuffSize);  
	if (HV_SUCCESS(status))
	{
		*pMaxWidth  = *(pdContext + 2 * resMode); 
		*pMaxHeight = *(pdContext + 2 * resMode + 1); 
	}
	// 获得当前分辨率输出窗口的最大尺寸
	delete []pbContext;
	return status;
}
