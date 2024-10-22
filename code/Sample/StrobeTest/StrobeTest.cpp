// StrobeTest.cpp : Defines the entry point for the console application.
//

// ��ʾ��ʹ�������ɼ�����ʾ������Զ������

#include "stdafx.h"
#include <stdlib.h>
#include <assert.h>
#include <windows.h>
#include "..\\..\\inc\\HVDAILT.h"
#include "..\\..\\inc\\HVdef.h"
#pragma comment(lib,"..\\..\\lib\\HVDailt.lib")

// �����Զ�������ź�����
#define SIGNAL_HIGH_IMPULSE 0 // ������
#define SIGNAL_LOW_IMPULSE  1 // ������
#define SIGNAL_HIGH_LEVEL   2 // �ߵ�ƽ
#define SIGNAL_LOW_LEVEL    3 // �͵�ƽ

// �ɼ�����
unsigned long g_nImageCount = 0;

// ��ȡ���ֱ���
HVSTATUS GetMaxResolution(HHV hhv, HV_RESOLUTION resMode, int *pMaxWidth, int *pMaxHeight);

// �򵥵Ļص�����
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
	printf("StrobeTest.exe��������Strobe����ź�:\n");
	printf("������0 ~ 3���һ�����֣�0: ������; 1: ������; 2: �ߵ�ƽ; 3:�͵�ƽ\n");	
	scanf("%s",argv[0]);

	// �����������
	assert(argv);
	int nSignal  = atoi(argv[0]);
	assert(nSignal>-1);
	assert(nSignal<4);

	// ���豸
	status = BeginHVDevice(1,&hhv);
	assert(HV_SUCCESS(status));
	
	// �����ֻ���ڴ����ɼ�״̬�£����������Ч�ź�
	//
	
	// 1 ����RES_MODE0�Ĵ����ɼ���ʽ
	//
	status = HVSetResolution(hhv,RES_MODE0);
	assert(HV_SUCCESS(status));
	status = HVSetSnapMode(hhv,TRIGGER);
	assert(HV_SUCCESS(status));

	// 2 �������ɼ�
	//
	// ��ȡ�ֱ���
	int nMaxWidth = 0; 
    int nMaxHeight = 0;
	status = GetMaxResolution(hhv,RES_MODE0,&nMaxWidth,&nMaxHeight);
	assert(HV_SUCCESS(status));

	// �򿪲ɼ�
	status = HVOpenSnap(hhv,SnapProc,NULL);//û�лص��������
	assert(HV_SUCCESS(status));
	imageBuff = new BYTE[nMaxWidth*nMaxHeight];
	status = HVStartSnap(hhv,&imageBuff,1);
	assert(HV_SUCCESS(status));


	// 3 ����Strobe����ź�
	switch(nSignal){
	case SIGNAL_HIGH_IMPULSE://�������ź�
		strobe.Mode     = SIGNAL_IMPULSE;
		strobe.Polarity = HIGH;
		status = HVCommand(hhv,CMD_SET_STROBE_SIGNAL_MODE,&strobe,&nSize);
		break;
	case SIGNAL_LOW_IMPULSE://�������ź�
		strobe.Mode     = SIGNAL_IMPULSE;
		strobe.Polarity = LOW;
		status = HVCommand(hhv,CMD_SET_STROBE_SIGNAL_MODE,&strobe,&nSize);
		break;
	case SIGNAL_HIGH_LEVEL://�ߵ�ƽ�ź�	
		strobe.Mode     = SIGNAL_LEVEL;
		strobe.Polarity = HIGH;
		status = HVCommand(hhv,CMD_SET_STROBE_SIGNAL_MODE,&strobe,&nSize);
		break;
	case SIGNAL_LOW_LEVEL://�͵�ƽ�ź�	
		strobe.Mode     = SIGNAL_LEVEL;
		strobe.Polarity = LOW;
		status = HVCommand(hhv,CMD_SET_STROBE_SIGNAL_MODE,&strobe,&nSize);
		break;
	default:
		printf("Invalid Parameter argv[0]=%d\n",nSignal);
		break;
	}	

	// �ɼ�20֡
	while (g_nImageCount<20)
	{
		status = HVTriggerShot(hhv);
		Sleep(1000);
		
	}	

	// 4 �����ɼ�
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

	// ����Ҫ�����Ϣ���ݵĴ�С 
	HVGetDeviceInfo(hhv,DESC_RESOLUTION,NULL,&nBuffSize);
    
	// �ٴε��ú�������豸�ֱ��ʵ���Ϣ 
	BYTE *pbContext = new BYTE[nBuffSize]; 
	DWORD *pdContext = (DWORD *)pbContext; 
	HVSTATUS status = HVGetDeviceInfo(hhv,DESC_RESOLUTION,pdContext,&nBuffSize);  
	if (HV_SUCCESS(status))
	{
		*pMaxWidth  = *(pdContext + 2 * resMode); 
		*pMaxHeight = *(pdContext + 2 * resMode + 1); 
	}
	// ��õ�ǰ�ֱ���������ڵ����ߴ�
	delete []pbContext;
	return status;
}
