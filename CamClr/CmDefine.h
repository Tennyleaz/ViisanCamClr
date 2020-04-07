#pragma once
//CmCapture 枚举,类型，结构体，宏定义
//#include "../../../lib/CmImage/MImage.h"

//身份证信息，结构体
typedef struct _BASE_MSG
{
	//身份证
	wchar_t sName[30];          
	wchar_t sSex[4];            
	wchar_t sNation[20];                           
	wchar_t sBirthdate[16];      
	wchar_t sAddr[70];       
	wchar_t sID[36];              
	wchar_t sOffice[30];          
	wchar_t sBeginDate[16];     
	wchar_t sEndDate[16];        

	//外国证件添加
	wchar_t sEName[120];                        
	wchar_t sVersion[4];           

	//港澳台居住证添加
	wchar_t sPassPortID[18]; 
	wchar_t sTime[4]; 

	//卡类型
	wchar_t sType[2]; 
}BaseMsg;
//身份证信息扩展，结构体
 typedef struct _BASE_MSG_EX
{
	//UNI
	wchar_t sName[20];
	wchar_t sSex[4];
	wchar_t sNation[20];
	wchar_t sBirthdate[10];
	wchar_t sAddr[50];
	wchar_t sID[20];
	wchar_t sOffice[30];
	wchar_t sBeginDate[10];
	wchar_t sEndDate[10];
	//外国证件添加的
	wchar_t sEName[120];
	wchar_t sVersion[4];
	wchar_t sCategory[2];
	wchar_t sOther[6];//预留项
}BaseMsgEx;
 //银行卡信息
 typedef struct _BANK_BASE_MSG
{
	wchar_t sNumber[50];
}BankBaseMsg;
 //社保卡
typedef struct _SSSE_BASE_MSG
{
	wchar_t sID[20];
	wchar_t sName[20];
	wchar_t sSex[20];
	wchar_t sNation[20];
	wchar_t sAddr[50];
	wchar_t sBirthdate[20];
}SsseBaseMsg;
 //磁条卡信息
 typedef struct _MAGCARD_BASE_MSG
{
	wchar_t sPassOne[200];
	wchar_t sPassTwo[200];
	wchar_t sPassThree[200];
}MagCardMsg;
//#if SEARCH_FILE
//文件类型
typedef enum
{	
	//FILE_
	FILE_BMP	=	0x0001,
	FILE_JPG	=	0x0002,
	FILE_PNG	=	0x0004,
	FILE_TIF	=	0x0008,
	FILE_PDF	=	0x0010,
	FILE_TXT	=	0x0020,
	FILE_DOC	=	0x0040,
	FILE_DOCX	=	0x0080,
	FILE_XLS	=	0x0100,
	FILE_XLSX	=	0x0200,
	FILE_ALL = 0xFFFF

}CAMSDK_SEARCH_FILE;
//#endif

//设备变换
enum CAMSDK_DEVCHANGE
{
	DEVCHANGE_NONE = 0,			//无变化
	DEVCHANGE_DEV,				//列表变化，调用设备变化
	DEVCHANGE_DEVLOST			//设备丢失
};

struct barcodeInfo
{
	char cbarcodeType[256];
	char cbarcodeRet[1024];
	int x[4];
	int y[4];

	int cbarcodeTypeSize;
	int cbarcodeRetSize;


	barcodeInfo()
	{
		memset(this->cbarcodeType, 0, 256 * sizeof(char));
		memset(this->cbarcodeRet, 0, 1024 * sizeof(char));
		memset(this->x, -1, 4 * sizeof(int));
		memset(this->y, -1, 4 * sizeof(int));
		this->cbarcodeRetSize = 0;
		this->cbarcodeTypeSize = 0;
	}
};

struct barcodeInfoList
{
	barcodeInfo infos[64];
	int nbarcodeInfoCount;

	barcodeInfoList()
	{
		this->nbarcodeInfoCount = 0;
	}
};
typedef struct SIGNRECT
{
	int nLeft;
	int nTop;
	int nRight;
	int nBottom;
}signRect;
typedef struct SIGNBACKGROUND
{
	int nBR;
	int nBG;
	int nBB;
	int nBT;//透明度
}signBackground;
typedef struct SIGNBRUSHCOLOR
{
	int nR;
	int nG;
	int nB;
}signBrushColor;
//手写板
typedef struct SIGNINGOLIST
{
	//窗口位置的偏移
	signRect signDlgOFFSet;
	//背景设置
	signBackground signBack;
	//画笔颜色
	signBrushColor signColor;
	int nBackImage;
	char* szBackImagePath;
}signInfoList;

//typedef void(*fLiveBodyCallBack)(bool bIsLiving,MRectR LivingRect,MColor LivingColor);
