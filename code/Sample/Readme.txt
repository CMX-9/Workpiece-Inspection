MVDevice SDK Visual C++ 6.0 示例程序简介


************************************************************
***********************注意*********************************
*****支持设备热插拔时必须安装Microsoft Platform SDK文件*****
***************Microsoft Platform SDK文件路径：*************
**************第三方软件/Microsoft Platform SDK*************
******************Sample下的MVMPNPDemo和MVSnapPnp，*********
**************必须要安装Microsoft Platform SDK**************
************************************************************

1. MVStoreBmp
CN:
演示保存一幅BMP文件到指定目录。
利用HVSnapShot抓取一帧图像到内存，利用ConvertBayer2Rgb 转换成RGB 24位格式位图，然后直接从内存读取图像数据，保存数据到BMP文件。图像的大小由视频输出窗口和视频格式确定。

EN:
Store a BMP file to the specified directory.
It can snap a image to the memory by HVSnapShot function. ConvertBayer2Rgb function is used to convert the source data into RGB_24 format. Then, the image can be read from memory and store as BMP file. The size of the image is determined by output window and video format.

2. MVSnapSingle
CN:
演示采集单帧数图像到内存，利用ConvertBayer2Rgb 转换成RGB 24位格式位图，然后显示。

EN:
Snap single image to the memory. Convert the source image data into RGB_24 format by ConvertBayer2Rgb function, and display the image.

3. MVSnapContinuous
CN:
演示利用回调方式，实现连续循环采集图像到内存，并转换成RGB 24位格式位图。
在回调函数中，实现对采集数据的处理和显示。

EN:
Store sequence images into memory by call-back function, and convert them into RGB_24 format.
The snapped image will be processed and displayed in the call-back function.

4. MVRealtime
CN:
在HVSnapContinuous基础上，演示采集图像的反色。
对采集数据的反色处理和显示都在回调函数中实现。

EN:
Display color-inversed image on the basis of HVSnapContinuous.
The snapped image will be inversed and displayed in the call-back function.

5. MVStoreAvi
CN:
演示保存AVI文件到指定目录，利用回调方式，实现AVI视频流的存储。

EN:
Store a AVI file to the specified directory in the call-back function.

6. StrobeTest
CN:
测试闪光灯输出信号功能，闪光灯信号包括：脉冲信号和电平信号。
闪光灯只有在触发采集状态下，才能输出有效信号。

EN:
Test the strobe signal features, strobe signals include: impulse signal and level signal.
The strobe signal is invalid only on the TRIGGER mode.

7. MVViewer
CN:
一个综合摄像机采集示例，实现功能包括：
(1) 抓取一帧图像至内存；
(2) 循环采集图像之内存；
(3) 转换成RGB 24格式位图
(4) 摄像机参数调节；
(5) 图像白平衡。 

EN:
This is an integrated sample, it includes the following functions:
(1) Snap an image, and store it to the memory.
(2) Recycle the snapping memory.
(3) Convert image into RGB_24 format.
(4) Adjust camera parameter.
(5) Do WhiteBalance.

8. MVSnapPnp
CN:
演示摄像机在采集中热插拔

EN:
This procedure for the demonstration of the functions of the camera in the acquisition of hot-swappable.

9.MVMPNPDemo
CN:
演示USB摄像机的多机掉线重连功能
(1)程序目前最多支持四个摄像机进行掉线重连演示，并且程序运行前，要保证所有设备都已连入电脑。
(2)程序以设备的序列号为唯一标示。界面上会显示每个设备的序列号,当某设备被拔掉后,显示为NULL;
   再次接入该设备,序列号重新显示
(3)有设备被拔掉后，其余设备正常采集不受影响
(4)有设备插入后，程序需要重新枚举设备，所有设备都将重新采集


EN:
To Demonstrate the funtion of Off-line re-connected for multi-cameras.
(1)The program currently supports up to four cameras, and run before, to ensure that all devices are connected to the computer
(2)The serial number of devices is the only mark. The program will show the serial number of each device, when a device is disconnected, the display is NULL; Access the device again, re-display the serial number.
(3)When a device is disconnected, the remaining devices is not affected.
(4)When a device is plugged, the program needs to re-enumerate the device, all devices will be re-acquisition.

10.HVSnapContinuous(软件触发抓图)
CN:
演示USB相机软件触发（鼠标右键触发）抓图功能
