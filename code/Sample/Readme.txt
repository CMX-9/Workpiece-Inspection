MVDevice SDK Visual C++ 6.0 ʾ��������


************************************************************
***********************ע��*********************************
*****֧���豸�Ȳ��ʱ���밲װMicrosoft Platform SDK�ļ�*****
***************Microsoft Platform SDK�ļ�·����*************
**************���������/Microsoft Platform SDK*************
******************Sample�µ�MVMPNPDemo��MVSnapPnp��*********
**************����Ҫ��װMicrosoft Platform SDK**************
************************************************************

1. MVStoreBmp
CN:
��ʾ����һ��BMP�ļ���ָ��Ŀ¼��
����HVSnapShotץȡһ֡ͼ���ڴ棬����ConvertBayer2Rgb ת����RGB 24λ��ʽλͼ��Ȼ��ֱ�Ӵ��ڴ��ȡͼ�����ݣ��������ݵ�BMP�ļ���ͼ��Ĵ�С����Ƶ������ں���Ƶ��ʽȷ����

EN:
Store a BMP file to the specified directory.
It can snap a image to the memory by HVSnapShot function. ConvertBayer2Rgb function is used to convert the source data into RGB_24 format. Then, the image can be read from memory and store as BMP file. The size of the image is determined by output window and video format.

2. MVSnapSingle
CN:
��ʾ�ɼ���֡��ͼ���ڴ棬����ConvertBayer2Rgb ת����RGB 24λ��ʽλͼ��Ȼ����ʾ��

EN:
Snap single image to the memory. Convert the source image data into RGB_24 format by ConvertBayer2Rgb function, and display the image.

3. MVSnapContinuous
CN:
��ʾ���ûص���ʽ��ʵ������ѭ���ɼ�ͼ���ڴ棬��ת����RGB 24λ��ʽλͼ��
�ڻص������У�ʵ�ֶԲɼ����ݵĴ������ʾ��

EN:
Store sequence images into memory by call-back function, and convert them into RGB_24 format.
The snapped image will be processed and displayed in the call-back function.

4. MVRealtime
CN:
��HVSnapContinuous�����ϣ���ʾ�ɼ�ͼ��ķ�ɫ��
�Բɼ����ݵķ�ɫ�������ʾ���ڻص�������ʵ�֡�

EN:
Display color-inversed image on the basis of HVSnapContinuous.
The snapped image will be inversed and displayed in the call-back function.

5. MVStoreAvi
CN:
��ʾ����AVI�ļ���ָ��Ŀ¼�����ûص���ʽ��ʵ��AVI��Ƶ���Ĵ洢��

EN:
Store a AVI file to the specified directory in the call-back function.

6. StrobeTest
CN:
�������������źŹ��ܣ�������źŰ����������źź͵�ƽ�źš�
�����ֻ���ڴ����ɼ�״̬�£����������Ч�źš�

EN:
Test the strobe signal features, strobe signals include: impulse signal and level signal.
The strobe signal is invalid only on the TRIGGER mode.

7. MVViewer
CN:
һ���ۺ�������ɼ�ʾ����ʵ�ֹ��ܰ�����
(1) ץȡһ֡ͼ�����ڴ棻
(2) ѭ���ɼ�ͼ��֮�ڴ棻
(3) ת����RGB 24��ʽλͼ
(4) ������������ڣ�
(5) ͼ���ƽ�⡣ 

EN:
This is an integrated sample, it includes the following functions:
(1) Snap an image, and store it to the memory.
(2) Recycle the snapping memory.
(3) Convert image into RGB_24 format.
(4) Adjust camera parameter.
(5) Do WhiteBalance.

8. MVSnapPnp
CN:
��ʾ������ڲɼ����Ȳ��

EN:
This procedure for the demonstration of the functions of the camera in the acquisition of hot-swappable.

9.MVMPNPDemo
CN:
��ʾUSB������Ķ��������������
(1)����Ŀǰ���֧���ĸ���������е���������ʾ�����ҳ�������ǰ��Ҫ��֤�����豸����������ԡ�
(2)�������豸�����к�ΪΨһ��ʾ�������ϻ���ʾÿ���豸�����к�,��ĳ�豸���ε���,��ʾΪNULL;
   �ٴν�����豸,���к�������ʾ
(3)���豸���ε��������豸�����ɼ�����Ӱ��
(4)���豸����󣬳�����Ҫ����ö���豸�������豸�������²ɼ�


EN:
To Demonstrate the funtion of Off-line re-connected for multi-cameras.
(1)The program currently supports up to four cameras, and run before, to ensure that all devices are connected to the computer
(2)The serial number of devices is the only mark. The program will show the serial number of each device, when a device is disconnected, the display is NULL; Access the device again, re-display the serial number.
(3)When a device is disconnected, the remaining devices is not affected.
(4)When a device is plugged, the program needs to re-enumerate the device, all devices will be re-acquisition.

10.HVSnapContinuous(�������ץͼ)
CN:
��ʾUSB����������������Ҽ�������ץͼ����
