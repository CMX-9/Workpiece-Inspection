#define  WHITEPIXEL   255
#define  BLACKPIXEL   0
#define  UP           0
#define  DOWN         1
#define  LEFT         2
#define  RIGHT        3
#define  COIN         2               //硬币
#define  NUT          1               //螺母
#define  SCREW        0               //螺钉
#define  INVALID      3               //无效目标

typedef struct ClassInFomation{
	unsigned int         centerX;   //该类的几何中心横坐标
	unsigned int         centerY;   //该类的几何中心纵坐标
	unsigned int          length;   //该类所占区域的长度
	unsigned int            wide;   //该类所占区域的宽度
	BYTE            grayOfCenter;   //该类几何中心位置的像素值
	float              classDuty;   //该类元素在该区域的面积占空比
	float           lengthToWide;   //该类所占区域的长宽比
	float        membershipGrade;   //隶属度，为0属于螺母，为1属于螺钉;
}ClassInfo;


///////////////////////////////////////
//函数名:GrayOrRGBTo2
//输入参数:无
//输出参数:无						
//功能描述:对图像进行灰度化及二值化
///////////////////////////////////////

void CMainFrame::GrayOrRGBTo2()   
{ 
	unsigned int           x = 0;
	unsigned int           y = 0;
    unsigned int    max_gray = 0;
	unsigned int  min_gray = 255;
	unsigned int   threshold = 0;          //阈值
	unsigned int bwith = g_imageWidth;
	unsigned int bhight = g_imageHeight;
	
	unsigned int H[256] = {0};            //灰度直方图
	double sum0 = 0;          			  //前景灰度和
	double sum1 = 0;          			  //背景灰度和

	double N0 = 0;           		      //前景像素数
	double N1 = 0;          			  //背景像素数

	double u0 = 0;            			  //平均灰度 
	double u1 = 1;

	double w0 = 0;                        //像素占比
	double w1 = 0;

	double g = -1;            			  //类间方差
	double max = -1;                      //最大类间方差
	double temp = 0;
	double N = (double)bwith*bhight;

     /*以下为图像转换的算法实现。用加权平均法实现RGB颜色空间到YUV颜色空间的变换，公式为：Y = 0.299*R+0.587*G+0.114*B 
	  *并存储在预设的内存中
	  */
	for (x=0;x<g_imageWidth;x++)           
	{
		for (y=0;y<g_imageHeight;y++)
		{
			pImageBuffer[y * g_imageRow + x] = (BYTE)(m_pImageBuffer[(y*g_imageRow+x)*3+0]*0.3          
													 +m_pImageBuffer[(y*g_imageRow+x)*3+1]*0.59
													 +m_pImageBuffer[(y*g_imageRow+x)*3+2]*0.11);
			pImageBuffer0[y * g_imageRow + x] = (BYTE)(m_pImageBuffer[(y*g_imageRow+x)*3+0]*0.3          
													 +m_pImageBuffer[(y*g_imageRow+x)*3+1]*0.59
													 +m_pImageBuffer[(y*g_imageRow+x)*3+2]*0.11);
			H[pImageBuffer[y * g_imageRow + x]]++;                                                    
		}//for结束
	}//for结束
	
	/*以下部分确定二值化阈值*/
	for(int i=0;i<256;i++)
	{
		sum0 = 0;                        
		sum1 = 0;
		N0 += H[i];                      
		N1 = N - N0;
		if(N1 == 0)
		{
			break;
		}

		w0 = N0/N;                       
		w1 =  1-w0;
		for(int j = 0;j<=i;j++)
		{
			sum0 += j*H[j];              
		}
		u0 = sum0/N0;                    
		for(int k = i+1;k<256;k++)
		{
			sum1 += k*H[k];              
		}
		u1 = sum1/N1;                    
		g = w0*w1*(u0-u1)*(u0-u1);       
		if(max<g)
		{
			max = g;
			threshold = i;
		}
	}//for结束    

   /*以下部分为二值化过程*/
	for (x=0;x<g_imageWidth;x++)                 
	{
		for (y=0;y<g_imageHeight;y++)
		{
		    if (pImageBuffer[y*g_imageRow+x] >threshold)
			{
				pImageBuffer[y*g_imageRow+x] = 255;
				pImageBuffer0[y*g_imageRow+x] = 255;
			}
			else
			{
                pImageBuffer[y*g_imageRow+x] = 0;
				pImageBuffer0[y*g_imageRow+x] = 0;
			}
		}//for结束
	}//for结束
}

///////////////////////////////////////
//函数名:GrayOrRGBTo2
//输入参数:无
//输出参数:无						
//功能描述:对图像进行灰度化及二值化
///////////////////////////////////////

void CMainFrame::GrayOrRGBTo2()   
{ 
	unsigned int           x = 0;
	unsigned int           y = 0;
    unsigned int    max_gray = 0;
	unsigned int  min_gray = 255;
	unsigned int   threshold = 0;          //阈值
	unsigned int bwith = g_imageWidth;
	unsigned int bhight = g_imageHeight;
	
	unsigned int H[256] = {0};            //灰度直方图
	double sum0 = 0;          			  //前景灰度和
	double sum1 = 0;          			  //背景灰度和

	double N0 = 0;           		      //前景像素数
	double N1 = 0;          			  //背景像素数

	double u0 = 0;            			  //平均灰度 
	double u1 = 1;

	double w0 = 0;                        //像素占比
	double w1 = 0;

	double g = -1;            			  //类间方差
	double max = -1;                      //最大类间方差
	double temp = 0;
	double N = (double)bwith*bhight;

     /*以下为图像转换的算法实现。用加权平均法实现RGB颜色空间到YUV颜色空间的变换，公式为：Y = 0.299*R+0.587*G+0.114*B 
	  *并存储在预设的内存中
	  */
	for (x=0;x<g_imageWidth;x++)           
	{
		for (y=0;y<g_imageHeight;y++)
		{
			pImageBuffer[y * g_imageRow + x] = (BYTE)(m_pImageBuffer[(y*g_imageRow+x)*3+0]*0.3          
													 +m_pImageBuffer[(y*g_imageRow+x)*3+1]*0.59
													 +m_pImageBuffer[(y*g_imageRow+x)*3+2]*0.11);
			pImageBuffer0[y * g_imageRow + x] = (BYTE)(m_pImageBuffer[(y*g_imageRow+x)*3+0]*0.3          
													 +m_pImageBuffer[(y*g_imageRow+x)*3+1]*0.59
													 +m_pImageBuffer[(y*g_imageRow+x)*3+2]*0.11);
			H[pImageBuffer[y * g_imageRow + x]]++;                                                    
		}//for结束
	}//for结束
	
	/*以下部分确定二值化阈值*/
	for(int i=0;i<256;i++)
	{
		sum0 = 0;                        
		sum1 = 0;
		N0 += H[i];                      
		N1 = N - N0;
		if(N1 == 0)
		{
			break;
		}

		w0 = N0/N;                       
		w1 =  1-w0;
		for(int j = 0;j<=i;j++)
		{
			sum0 += j*H[j];              
		}
		u0 = sum0/N0;                    
		for(int k = i+1;k<256;k++)
		{
			sum1 += k*H[k];              
		}
		u1 = sum1/N1;                    
		g = w0*w1*(u0-u1)*(u0-u1);       
		if(max<g)
		{
			max = g;
			threshold = i;
		}
	}//for结束    

   /*以下部分为二值化过程*/
	for (x=0;x<g_imageWidth;x++)                 
	{
		for (y=0;y<g_imageHeight;y++)
		{
		    if (pImageBuffer[y*g_imageRow+x] >threshold)
			{
				pImageBuffer[y*g_imageRow+x] = 255;
				pImageBuffer0[y*g_imageRow+x] = 255;
			}
			else
			{
                pImageBuffer[y*g_imageRow+x] = 0;
				pImageBuffer0[y*g_imageRow+x] = 0;
			}
		}//for结束
	}//for结束
}

///////////////////////////////////////
//函数名:PreProcess
//输入参数:无
//输出参数:无						
//功能描述:图像预处理，用于去噪
///////////////////////////////////////
void CMainFrame::PreProcess()
{
	unsigned int             x = 0;
	unsigned int             y = 0;
	unsigned int         width = 0;
	unsigned int        height = 0; 
	unsigned int   pixelCounter = 0;    //邻域内黑点个数累计

	for (x=0;x<g_imageWidth;x++)    
	{
		for (y=0;y<g_imageHeight;y++)
		{
			/*以下部分实现对图像边缘的黑点的清除
			*实现黑点邻域内黑点数的搜索*/
			if(0 == x || 0 == y)                                     
			{
				pImageBuffer[y*g_imageRow+x] = WHITEPIXEL;
			}
		    if (BLACKPIXEL == pImageBuffer0[y*g_imageRow+x])        
			{
				pixelCounter = 0;                                   
				for (width=x-1;width<=x+1;width++)
				{
					for (height=y-1;height<=y+1;height++)
					{
						if (BLACKPIXEL == pImageBuffer0[height*g_imageRow+width])
						{
							pixelCounter++;
						}
					}//for结束
				}//for结束
				
				/*以下实现对噪声的消除*/
				if (pixelCounter <= 2)    
				{
					pImageBuffer[y*g_imageRow+x] = WHITEPIXEL;
					pImageBuffer0[y*g_imageRow+x] = WHITEPIXEL;
				}
			}//if结束
		}//for结束
	}//for结束
	
	
}

///////////////////////////////////////
//函数名:FindClass
//输入参数:无
//输出参数:无						
//功能描述:将图像中各个连通的区域找出来
//说明：遍历顺序：从左至右，从下至上
///////////////////////////////////////
void CMainFrame::FindClass()
{
	unsigned int pixelClass = 0;
    unsigned int          x = 0;
	unsigned int          y = 0;
	unsigned int    HeaderX = 0;        //各类起始点横坐标
	unsigned int    HeaderY = 0;        //各类起始点纵坐标
	unsigned int  classFlag = 0;        //0:还没有找到本类的第一个点；1：已找到本类的起始点，正准备找其连通点；2：已找到所有类

	g_classCoordinate[pixelClass][UP] = g_imageHeight-1;
	g_classCoordinate[pixelClass][DOWN] = 1;
	g_classCoordinate[pixelClass][LEFT] = 1;
	g_classCoordinate[pixelClass][RIGHT] = g_imageWidth-1;
	g_targetPixelLeft = 0; 
	g_targetPixelDown = 0;
	while (classFlag != 2)                                       
	{
		/*以下部分实现查找当前类的起始点并判断图中所有黑点是否全部归类
		*查找起始点时每次y均从上个类的最下界开始搜寻、x从1开始搜寻
		*调用MarkerNeighbourhood函数搜寻当前点邻域的黑点
		*/
		if(0 == classFlag)																  
		{           
			pixelClass++;																  
            if (pixelClass > 255)														 
			{
				g_imageClass[0] = 255;
				return;																	  
			}

			/*以下五行实现对当前类像素点个数清零及区域边界的初始化*/
			g_imageClass[pixelClass] = 0;                                                
			g_classCoordinate[pixelClass][UP] = 1;                                       
            g_classCoordinate[pixelClass][DOWN] = g_imageHeight-1;                       
			g_classCoordinate[pixelClass][LEFT] = g_imageWidth-1;                         
			g_classCoordinate[pixelClass][RIGHT] = 1;                                     

			for (y=g_classCoordinate[pixelClass-1][DOWN];y<g_imageHeight-1;y++)          
			{
				for (x=1;x<g_imageWidth-1;x++)                                            
				{
					if (BLACKPIXEL == pImageBuffer[y*g_imageRow+x])                       
					{
						HeaderX = x;                                                       
						HeaderY = y;
						g_classCoordinate[pixelClass][DOWN] = HeaderY;                    
						pImageBuffer[y*g_imageRow+x] = pixelClass;                       
						MarkerNeighbourhood(pixelClass,HeaderX,HeaderY);                  
						classFlag = 1;                                                    
						break;
					}
				}//for x 
				if(1 == classFlag)
				{
					break;     
				}
			}//for y
            if(0 == classFlag)               //图中所有黑点均已归类
			{
				pixelClass--;
				g_imageClass[0] = pixelClass;
				classFlag = 2;               //图像已遍历完全
			}
		}//if结束
		
		/*以下部分通过遍历全图找到当前类的联通点*/
        else if (1 == classFlag)
		{
		    for (y=g_classCoordinate[pixelClass][DOWN];y<g_imageHeight-1;y++)
			{
				g_rowTargetPixelNum = 0;                                   
				for (x=1;x<g_imageWidth-1;x++)
				{
					if(pixelClass == pImageBuffer[y*g_imageRow+x])       
					{
                        MarkerNeighbourhood(pixelClass,x,y);  
					}
					if (1 == g_targetPixelLeft)
					{
						x = 1;
						g_targetPixelLeft = 0;
					}
					if (1 == g_targetPixelDown)
					{
						y = y - 1;
						x = 1;
						if (y < 1)
						{
							y = 1;
						}
						g_targetPixelDown = 0;
					}
				}//for x结束
			}//for y结束
			classFlag = 0;           
		}//else if结束
	}//while结束
}


///////////////////////////////////////
//函数名:MarkerNeighbourhood
//输入参数:unsigned int pixelClass表示当前点的类别
///////////unsigned int width表示当前点的x
///////////unsigned int height表示当前点的y
//输出参数:无						
//功能描述:搜寻当前点邻域(上下左右四邻域)的黑点，查找并标记为当前类中元素
///////////同时通过调用UpdateBound函数实现对边界的更新
///////////////////////////////////////
void CMainFrame::MarkerNeighbourhood(unsigned int pixelClass,unsigned int width,unsigned int height)  
{
    unsigned int x = 0;
    unsigned int y = 0;

	x = width;
	y = height;

	g_rowTargetPixelNum++;                                     //当前行目标点累加
	UpdateBound(pixelClass,width,height);                      

	if (BLACKPIXEL == pImageBuffer[(y-1)*g_imageRow+x])        
	{
		pImageBuffer[(y-1)*g_imageRow+x] = pixelClass;
		g_targetPixelDown = 1;                                 
	}
	if (BLACKPIXEL == pImageBuffer[(y+1)*g_imageRow+x])        
	{
		pImageBuffer[(y+1)*g_imageRow+x] = pixelClass;
	}
	if (BLACKPIXEL == pImageBuffer[y*g_imageRow+x-1])          
	{
		pImageBuffer[y*g_imageRow+x-1] = pixelClass;
		g_targetPixelDown = 1;
	}
	if (BLACKPIXEL == pImageBuffer[y*g_imageRow+x+1])         
	{
		pImageBuffer[y*g_imageRow+x+1] = pixelClass;
	}
}


///////////////////////////////////////
//函数名:UpdateBound
//输入参数:unsigned int pixelClass表示当前点的类别
///////////unsigned int width表示当前点的x
///////////unsigned int height表示当前点的y
//输出参数:无						
//功能描述:当前点为本类中的点时，判断其是否为该类边界点并更新边界
///////////////////////////////////////
void CMainFrame::UpdateBound(unsigned int pixelClass,unsigned int width,unsigned int height)
{
	if (width < g_classCoordinate[pixelClass][LEFT])
	{
		g_classCoordinate[pixelClass][LEFT] = width;             
	}
	else if (width > g_classCoordinate[pixelClass][RIGHT])
	{
		g_classCoordinate[pixelClass][RIGHT] = width;            
	}

    if (height > g_classCoordinate[pixelClass][UP])          
	{ 
	   	g_classCoordinate[pixelClass][UP] = height;              
	}
}

///////////////////////////////////////
//函数名:ImageRecognize
//输入参数:无
//输出参数:无						
//功能描述:目标识别
///////////////////////////////////////
void CMainFrame::ImageRecognize()
{
	unsigned int        width = 0;
	unsigned int       height = 0;
    unsigned int   pixelClass = 0;
	unsigned int pixelCounter = 0;
	float             centerX = 0;
	float             centerY = 0;

	g_objectNum[SCREW] = 0;
	g_objectNum[NUT] = 0;
	g_objectNum[COIN] = 0;
	/*以下部分实现对各类目标点个数、边缘框长宽比、中心灰度值及边缘框内目标所占比例（即面积占空比）的计算
	*同时对螺钉、螺母及无效类进行识别*/
	for (pixelClass=2;pixelClass<=g_imageClass[0];pixelClass++)    
	{
		g_imageClass[pixelClass] = 0;
		for (width=g_classCoordinate[pixelClass][LEFT];width<=g_classCoordinate[pixelClass][RIGHT];width++)   
		{
			for (height=g_classCoordinate[pixelClass][DOWN];height<=g_classCoordinate[pixelClass][UP];height++)
			{
				if (pixelClass == pImageBuffer[height*g_imageRow+width])       
				{
					g_imageClass[pixelClass]++; 
				}
			}
		}
		if (g_imageClass[pixelClass] >100 && g_imageClass[pixelClass] < 20000)         
		{
			g_imageClassInfo[pixelClass].length = (unsigned int)(g_classCoordinate[pixelClass][RIGHT] - g_classCoordinate[pixelClass][LEFT]);
			g_imageClassInfo[pixelClass].wide = (unsigned int)(g_classCoordinate[pixelClass][UP] - g_classCoordinate[pixelClass][DOWN]);
			if (g_imageClassInfo[pixelClass].length > 0 && g_imageClassInfo[pixelClass].wide > 0)
			{
				if (g_imageClassInfo[pixelClass].length >g_imageClassInfo[pixelClass].wide)
				{
					g_imageClassInfo[pixelClass].lengthToWide = (float)((float)g_imageClassInfo[pixelClass].length/(float)g_imageClassInfo[pixelClass].wide);     
				}
				else
				{
					g_imageClassInfo[pixelClass].lengthToWide = (float)((float)g_imageClassInfo[pixelClass].wide/(float)g_imageClassInfo[pixelClass].length);     
				}
				g_imageClassInfo[pixelClass].classDuty = (float)((float)g_imageClass[pixelClass]/((float)g_imageClassInfo[pixelClass].length*(float)g_imageClassInfo[pixelClass].wide));    
				centerX = 0;
				centerY = 0;
				g_imageClassInfo[pixelClass].centerX = 0;
				g_imageClassInfo[pixelClass].centerY = 0;
				centerX = (float)(g_classCoordinate[pixelClass][LEFT] + g_classCoordinate[pixelClass][RIGHT])/2;
				centerY = (float)(g_classCoordinate[pixelClass][UP] + g_classCoordinate[pixelClass][DOWN])/2;
				g_imageClassInfo[pixelClass].centerX = (unsigned int)(centerX);
				g_imageClassInfo[pixelClass].centerY = (unsigned int)(centerY);
				g_imageClassInfo[pixelClass].grayOfCenter = (BYTE)((float)pImageBuffer[g_imageClassInfo[pixelClass].centerY*g_imageRow+g_imageClassInfo[pixelClass].centerX] * 0.2            
																 + (float)pImageBuffer[g_imageClassInfo[pixelClass].centerY*g_imageRow+g_imageClassInfo[pixelClass].centerX+1] * 0.2
																 + (float)pImageBuffer[g_imageClassInfo[pixelClass].centerY*g_imageRow+g_imageClassInfo[pixelClass].centerX-1] * 0.2
					                                             + (float)pImageBuffer[(g_imageClassInfo[pixelClass].centerY+1)*g_imageRow+g_imageClassInfo[pixelClass].centerX] * 0.2
																 + (float)pImageBuffer[(g_imageClassInfo[pixelClass].centerY-1)*g_imageRow+g_imageClassInfo[pixelClass].centerX] * 0.2);//中心点灰度值取其上下左右加本身共五个点的平均值
			   

				if ((g_imageClassInfo[pixelClass].grayOfCenter > 128)&&(g_imageClassInfo[pixelClass].lengthToWide<1.2)&&(g_imageClass[pixelClass] <2000))
				{
					g_classCategory[pixelClass] = NUT;                     //识别螺母
					g_objectNum[NUT]++;
				}
				else if(g_imageClass[pixelClass] <1500)
				{
					g_classCategory[pixelClass] = SCREW;                    //识别螺钉
					g_objectNum[SCREW]++;	
				}
				else 
				{
                    g_classCategory[pixelClass] = INVALID;                 //无效类
				}
			}//if结束
			else 
			{
				g_imageClassInfo[pixelClass].lengthToWide = 0;
                g_imageClassInfo[pixelClass].classDuty = 0;
				g_imageClassInfo[pixelClass].centerX = 0;
				g_imageClassInfo[pixelClass].centerY = 0;
				g_imageClassInfo[pixelClass].grayOfCenter = 125;
				g_classCategory[pixelClass] = INVALID;         			  //无效类
			}
		}//if结束
		else
		{
			g_classCategory[pixelClass] = INVALID;
		}
	}//for count结束
}

///////////////////////////////////////////
//函数名:PourObject
//输入参数:无
//输出参数:无						
//功能描述:在原图像中对已确定的目标进行填充
///////////////////////////////////////////
void CMainFrame::PourObject()
{
    unsigned int pixelClass = 0;               
    unsigned int      count = 0;
	unsigned int      width = 0;
	unsigned int     height = 0;

	for (pixelClass=2;pixelClass<=g_imageClass[0];pixelClass++)
	{
		/* 搜寻螺钉并将其改成绿色*/
        if (SCREW == g_classCategory[pixelClass])         
		{
            for (width=g_classCoordinate[pixelClass][LEFT];width<=g_classCoordinate[pixelClass][RIGHT];width++)   
			{
				for (height=g_classCoordinate[pixelClass][DOWN];height<=g_classCoordinate[pixelClass][UP];height++)
				{
					if (pixelClass == pImageBuffer[height*g_imageRow+width])      
					{
						m_pImageBuffer[(height*g_imageRow+width)*3+0] = 0;
						m_pImageBuffer[(height*g_imageRow+width)*3+1] = 255;
						m_pImageBuffer[(height*g_imageRow+width)*3+2] = 0;
					}
				}//for height结束
			}//for width结束
		}//if SCREW结束
		/* 搜寻螺母并将其改成红色*/
		else if(NUT == g_classCategory[pixelClass])        
		{
            for (width=g_classCoordinate[pixelClass][LEFT];width<=g_classCoordinate[pixelClass][RIGHT];width++)
			{
				for (height=g_classCoordinate[pixelClass][DOWN];height<=g_classCoordinate[pixelClass][UP];height++)
				{
					if (pixelClass == pImageBuffer[height*g_imageRow+width])
					{
						m_pImageBuffer[(height*g_imageRow+width)*3+0] = 0;
						m_pImageBuffer[(height*g_imageRow+width)*3+1] = 0;
						m_pImageBuffer[(height*g_imageRow+width)*3+2] = 255;
					}
				}//for height结束
			}//for width结束
		}//else if NUT结束
	}//for pixelClass结束
}



///////////////////////////////////////
//函数名:TargetObject
//输入参数:CDC *pDC
//输出参数:无						
//功能描述:在原图像中标注已确定的目标
///////////////////////////////////////
void CMainFrame::TargetObject(CDC *pDC)
{

	unsigned int pixelClass = 0;
	char           str[5] = {0};

	for (pixelClass=2;pixelClass<=g_imageClass[0];pixelClass++)
	{
		
		if (NUT == g_classCategory[pixelClass])
		{
            pDC->TextOut(g_classCoordinate[pixelClass][LEFT],g_imageHeight - g_classCoordinate[pixelClass][DOWN],"螺母");
			itoa(g_imageClass[pixelClass],str,10);
			pDC->TextOut(g_classCoordinate[pixelClass][LEFT]+40,g_imageHeight - g_classCoordinate[pixelClass][DOWN],str);
		}
		else if (SCREW == g_classCategory[pixelClass])
		{
			pDC->TextOut(g_classCoordinate[pixelClass][LEFT],g_imageHeight - g_classCoordinate[pixelClass][DOWN],"螺钉");
			itoa(g_imageClass[pixelClass],str,10);
			pDC->TextOut(g_classCoordinate[pixelClass][LEFT]+40,g_imageHeight - g_classCoordinate[pixelClass][DOWN],str);
		}
	}
	pDC->TextOut(30,30,"图中有：");
	pDC->TextOut(30,50,"螺钉：");
	itoa(g_objectNum[SCREW],str,10);
	pDC->TextOut(90,50,str);
    pDC->TextOut(110,50,"个");
	pDC->TextOut(30,70,"螺母：");
	itoa(g_objectNum[NUT],str,10);
	pDC->TextOut(90,70,str);
    pDC->TextOut(110,70,"个");
    pDC->TextOut(g_imageWidth - 170,g_imageHeight - 30,"制作人：");
	pDC->TextO///////////////////////////////////////////
//函数名:PourObject
//输入参数:无
//输出参数:无						
//功能描述:在原图像中对已确定的目标进行填充
///////////////////////////////////////////
void CMainFrame::PourObject()
{
    unsigned int pixelClass = 0;               
    unsigned int      count = 0;
	unsigned int      width = 0;
	unsigned int     height = 0;

	for (pixelClass=2;pixelClass<=g_imageClass[0];pixelClass++)
	{
		/* 搜寻螺钉并将其改成绿色*/
        if (SCREW == g_classCategory[pixelClass])         
		{
            for (width=g_classCoordinate[pixelClass][LEFT];width<=g_classCoordinate[pixelClass][RIGHT];width++)   
			{
				for (height=g_classCoordinate[pixelClass][DOWN];height<=g_classCoordinate[pixelClass][UP];height++)
				{
					if (pixelClass == pImageBuffer[height*g_imageRow+width])      
					{
						m_pImageBuffer[(height*g_imageRow+width)*3+0] = 0;
						m_pImageBuffer[(height*g_imageRow+width)*3+1] = 255;
						m_pImageBuffer[(height*g_imageRow+width)*3+2] = 0;
					}
				}//for height结束
			}//for width结束
		}//if SCREW结束
		/* 搜寻螺母并将其改成红色*/
		else if(NUT == g_classCategory[pixelClass])        
		{
            for (width=g_classCoordinate[pixelClass][LEFT];width<=g_classCoordinate[pixelClass][RIGHT];width++)
			{
				for (height=g_classCoordinate[pixelClass][DOWN];height<=g_classCoordinate[pixelClass][UP];height++)
				{
					if (pixelClass == pImageBuffer[height*g_imageRow+width])
					{
						m_pImageBuffer[(height*g_imageRow+width)*3+0] = 0;
						m_pImageBuffer[(height*g_imageRow+width)*3+1] = 0;
						m_pImageBuffer[(height*g_imageRow+width)*3+2] = 255;
					}
				}//for height结束
			}//for width结束
		}//else if NUT结束
	}//for pixelClass结束
}



///////////////////////////////////////////
//函数名:PourObject
//输入参数:无
//输出参数:无						
//功能描述:在原图像中对已确定的目标进行填充
///////////////////////////////////////////
void CMainFrame::PourObject()
{
    unsigned int pixelClass = 0;               
    unsigned int      count = 0;
	unsigned int      width = 0;
	unsigned int     height = 0;

	for (pixelClass=2;pixelClass<=g_imageClass[0];pixelClass++)
	{
		/* 搜寻螺钉并将其改成绿色*/
        if (SCREW == g_classCategory[pixelClass])         
		{
            for (width=g_classCoordinate[pixelClass][LEFT];width<=g_classCoordinate[pixelClass][RIGHT];width++)   
			{
				for (height=g_classCoordinate[pixelClass][DOWN];height<=g_classCoordinate[pixelClass][UP];height++)
				{
					if (pixelClass == pImageBuffer[height*g_imageRow+width])      
					{
						m_pImageBuffer[(height*g_imageRow+width)*3+0] = 0;
						m_pImageBuffer[(height*g_imageRow+width)*3+1] = 255;
						m_pImageBuffer[(height*g_imageRow+width)*3+2] = 0;
					}
				}//for height结束
			}//for width结束
		}//if SCREW结束
		/* 搜寻螺母并将其改成红色*/
		else if(NUT == g_classCategory[pixelClass])        
		{
            for (width=g_classCoordinate[pixelClass][LEFT];width<=g_classCoordinate[pixelClass][RIGHT];width++)
			{
				for (height=g_classCoordinate[pixelClass][DOWN];height<=g_classCoordinate[pixelClass][UP];height++)
				{
					if (pixelClass == pImageBuffer[height*g_imageRow+width])
					{
						m_pImageBuffer[(height*g_imageRow+width)*3+0] = 0;
						m_pImageBuffer[(height*g_imageRow+width)*3+1] = 0;
						m_pImageBuffer[(height*g_imageRow+width)*3+2] = 255;
					}
				}//for height结束
			}//for width结束
		}//else if NUT结束
	}//for pixelClass结束
}



///////////////////////////////////////
//函数名:TargetObject
//输入参数:CDC *pDC
//输出参数:无						
//功能描述:在原图像中标注已确定的目标
///////////////////////////////////////
void CMainFrame::TargetObject(CDC *pDC)
{

	unsigned int pixelClass = 0;
	char           str[5] = {0};

	for (pixelClass=2;pixelClass<=g_imageClass[0];pixelClass++)
	{
		
		if (NUT == g_classCategory[pixelClass])
		{
            pDC->TextOut(g_classCoordinate[pixelClass][LEFT],g_imageHeight - g_classCoordinate[pixelClass][DOWN],"螺母");
			itoa(g_imageClass[pixelClass],str,10);
			pDC->TextOut(g_classCoordinate[pixelClass][LEFT]+40,g_imageHeight - g_classCoordinate[pixelClass][DOWN],str);
		}
		else if (SCREW == g_classCategory[pixelClass])
		{
			pDC->TextOut(g_classCoordinate[pixelClass][LEFT],g_imageHeight - g_classCoordinate[pixelClass][DOWN],"螺钉");
			itoa(g_imageClass[pixelClass],str,10);
			pDC->TextOut(g_classCoordinate[pixelClass][LEFT]+40,g_imageHeight - g_classCoordinate[pixelClass][DOWN],str);
		}
	}
	pDC->TextOut(30,30,"图中有：");
	pDC->TextOut(30,50,"螺钉：");
	itoa(g_objectNum[SCREW],str,10);
	pDC->TextOut(90,50,str);
    pDC->TextOut(110,50,"个");
	pDC->TextOut(30,70,"螺母：");
	itoa(g_objectNum[NUT],str,10);
	pDC->TextOut(90,70,str);
    pDC->TextOut(110,70,"个");
    pDC->TextOut(g_imageWidth - 170,g_imageHeight - 30,"制作人：");
	pDC->TextOut(g_imageWidth - 120,g_imageHeight - 30,"陈明香");
}