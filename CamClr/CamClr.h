#pragma once
#include "CmDefine.h"
#include "CmCaptureHeader.h"
using namespace System;
using namespace System::Runtime::InteropServices;

namespace CamClr {
	/// <summary>錯誤代碼，0 代表正常</summary>
	public enum class CAMSDK_ERR : long
	{
		ERR_NONE = 0x0000,		//无错误
		ERR_UNKNOW,			//未知错误
		ERR_PROPERTY,		//属性设置错误
		ERR_INIT,			//初始化错误
		ERR_OUTOFBOUNDS,	//数组越界
		ERR_NULLPOINT,		//空指针
		ERR_PARAM,			//参数错误
		ERR_INVALIDPATH,	//无效的路径
		ERR_NONSUPPORT,		//不支持
		ERR_INUSE,			//使用中，忙
		ERR_NOCAMERA,			//没有找到任何摄像头
		ERR_UNOPENED,		//设备未开启
		ERROR_NOINIT,
		ERR_OPENDEVFAILD = 0x0101,	//开启设备失败
		ERR_STARTVIDEOFAILD,	    //开启视频失败
		ERR_SETRESOLUTIONFAILD,	    //设置分辨率失败
		ERR_AUTOFOCUSFAILD,		    //自动对焦失败
		ERR_CAPTURENULLBUF,		    //拍照空指针
		ERR_SAVEIMAGEFAILD,		    //保存图像失败
		ERR_NOLICENSE,		        //没有授权
		ERR_WRITEDEVFAILED,	        //写设备数据失败
		ERR_DISABLE,		        //无授权已反初始化SDK

		ERR_FTPCONNECTFAILED = 0x0401,	//FTP连接失败
		ERR_FTPDISCONNECTFAILED,	//FTP断开失败
		ERR_FTPADDRESSERROR,		//FTP路径有误
		ERR_FTPPUTFILEFAILED,	//FTP上传失败
		ERR_HTTPPUTFILEFAILED,	//HTTP连接失败

		ERR_LOADIDCARDOCRFAILED = 0x0501,	//加载证件识别失败	
		ERR_LOADBARCODEFAILED = 0x0511,		//加载条码识别失败
		ERR_OCRPARAM = 0x0601,     //识别参数错误

		//人脸识别
		CMFACE_ERROR_NOLICENSE = 10000,   //没有人脸授权
		CMFACE_ERROR_NODETECTFACE,        //没有DETECTFACE
		CMFACE_ERROR_SERVERCLOSE,         //服务没开启
		CMFACE_ERROR_LOADMODELFAILED,     //加载modele失败
		CMFACE_ERROR_DETECTINITFAILED,    //监测人脸失败
		CMFACE_ERROR_NOINIT,              //没有初始化
		CMFACE_ERROR_LOADCAMERADLLFAILED, //
		CMFACE_ERROR_DEVNOCONNECT,        //设备没连接
		CMFACE_ERROR_OPENCAMERAFAILED,    //打开摄像头失败
		CMFACE_ERROR_OVERTIME,            //超时
		CMFACE_ERROR_LOADCMFACE3FAILED,   //
		CMFACE_ERROR_ERRORXMLFROM,        //配置文件格式错误
		CMFACE_ERROR_LOADXMLFAILED,       //加载配置文件失败
		CMFACE_ERROR_FILESAVEFAILED,      //保存图片是失败
		CMFACE_ERROR_LiveBody_Fail,		 //非活体		

		//手写板
		CMSIGN_ERROR_FILETYPE = 2000,//文件保存类型错误
	};

	/// <summary>自動裁切</summary>
	public enum class CropType : long
	{
		None = 0,
		Single,
		Multiple,
		SingleAndFill,
		CropFace
	};

	/// <summary>連拍設定</summary>
	public enum class AutoCaptureType : long
	{
		Monitor = 0,
		FixTime = 1
	};

	/// <summary>相機解析度</summary>
	public value struct Resolution
	{
	public:
		long Width, Height;
	};

	// DLL function signature  
	typedef CAMSDK_ERR(*camInitCameraLib)();
	typedef CAMSDK_ERR(*camUnInitCameraLib)();
	typedef long(*camGetDevCount)(long& count);
	typedef CAMSDK_ERR(*camGetDevCountCur)(long& count);
	// 裝置資訊
	typedef char* (*camGetDevName)(long devIndex);
	typedef long(*camGetFwVersion)(int devIndex, char* cVersion);
	typedef long(*camGetLensModel)(int devIndex, char* cLensModel);
	typedef long(*camGetCameraModel)(int devIndex, char* cCameraModel);
	typedef long(*camCaptureImageFile)(long devIndex, char* filePath);
	typedef long(*camSetImageAutoCrop)(long devIndex, long CropType);
	typedef CAMSDK_ERR(*camOpenDev)(long devIndex, long subtype, long width, long height);
	typedef long(*camCloseDev)(long devIndex);
	typedef long(*camSetImageJPGQuanlity)(long devIndex, long quanlity);	
	typedef bool (CALLBACK* callBackPreviewImage)(unsigned char src, long width, long height, long size);
	typedef CAMSDK_ERR(*camRegCallBackPreviewImage)(long devIndex, callBackPreviewImage fun);
	typedef CAMSDK_ERR(*camSetPreviewWindow)(long devIndex, HWND hPreviewWindow);
	typedef long(*camSetImageDPI)(long devIndex, long xDPI, long yDPI);
	typedef long(*camSetImageCusCropRect)(long devIndex, long left, long top, long right, long bottom);
	typedef long(*camGetImageCusCropRect)(long devIndex, long& left, long& top, long& right, long& bottom);
	// 設定視窗
	typedef long(*camShowImageSettingWindow)(long devIndex);
	typedef long(*camShowDevSettingWindow)(long devIndex);
	// 解析度
	typedef long(*camGetResolutionCount)(long devIndex, long subtype, long& count);
	typedef long(*camGetResolution)(long devIndex, long subtype, long index, long& width, long& height);
	typedef long(*camSetResolution)(long devIndex, long width, long height);
	typedef long(*camGetCurResolution)(long devIndex, long& subtype, long& width, long& height);
	// 圖片效果
	typedef long(*camSetImageDenoise)(long devIndex, bool IsAvailabel);
	typedef long(*camSetImageOffsetCorrection)(long devIndex, long type);
	// 連拍
	typedef bool(CALLBACK* callBackAutoCapture)(long state);  // 連拍的 callback
	typedef long(*camStartAutoCapture)(long devIndex, long type, long param, callBackAutoCapture fun);
	typedef long(*camPauseAutoCapture)(long devIndex, long lstype);
	typedef long(*camStopAutoCapture)(long devIndex);
	// C++/CLI delegate
	public delegate void AutoCaptureDelgate(long state);

	public ref class Cam
	{
		// TODO: 請在此新增此類別的方法。
	private:
		// handle of DLL file
		HINSTANCE m_hMod;
		camInitCameraLib init;
		camUnInitCameraLib unInit;
		camGetDevCount getDeviceCount;
		camGetDevCountCur getDeviceCountCurrent;
		camGetDevName getDeviceName;
		camGetFwVersion getFWVersion;
		camGetLensModel getLensModel;
		camGetCameraModel getCameraModel;
		camCaptureImageFile captureFile;
		camSetImageAutoCrop setAutoCrop;
		camOpenDev openDevice;
		camCloseDev closeDevice;
		camSetImageJPGQuanlity setJpegQuality;
		camGetCurResolution getCurrentResolution;
		camRegCallBackPreviewImage registerCallback;
		camSetPreviewWindow setPreviewWindow;
		camSetImageDPI setDPI;
		camSetImageCusCropRect setImageCropRect;
		camGetImageCusCropRect getImageCropRect;
		camShowImageSettingWindow showImageSetting;
		camShowDevSettingWindow showVideoSetting;
		camGetResolutionCount getResolutionCount;
		camGetResolution getResolution;
		camSetResolution setResolution;
		camSetImageDenoise setImageDenoise;
		camSetImageOffsetCorrection setOffsetCorrection;
		camStartAutoCapture startAutoCapture;
		camPauseAutoCapture pauseAutoCapture;
		camStopAutoCapture stopAutoCapture;
		//callBackAutoCapture callback2;

		static const char* string_to_char_array(String^ string)
		{
			const char* str = (const char*)(Marshal::StringToHGlobalAnsi(string)).ToPointer();
			return str;
		}
		bool CALLBACK callback(long state);

	public:
		~Cam();
		/// <summary>先LoadLibrary再取得所有函數位址，最後初始化相機。</summary>
		CAMSDK_ERR Init();
		/// <summary>獲取攝像頭個數，-1即失敗。</summary>
		long GetDeviceCount();
		/// <summary>獲取設備名(攝像頭在裝置管理員中的名稱)</summary>
		/// <param name="deviceIndex">設備ID，即攝像頭序號,0號開始</param>
		String^ GetDeviceName(long deviceIndex);
		/// <summary>獲取鏡頭型號</summary>
		CAMSDK_ERR GetModles(long deviceIndex, [Out]String^% fwVersion, [Out]String^% model, [Out]String^% vid_pid);
		/// <summary>開啟影像裝置</summary>
		/// <param name="deviceIndex">設備ID，即攝像頭序號,0號開始</param>
		/// <param name="subType">媒體格式ID，不同設備支援的格式可能不同，常見 0=mjpeg，1=yuy2，不支援mjpeg的設備則 0=yuy2。</param>
		/// <param name="width">指定解析度的寬(設置0 為最大解析度的寬)</param>
		/// <param name="height">指定解析度的高(設置0 為最大解析度的高)</param>
		CAMSDK_ERR OpenDevice(long deviceIndex, long subType, long width, long height);
		/// <summary>關閉影像裝置</summary>
		/// <param name="deviceIndex">設備ID，即攝像頭序號,0號開始</param>
		CAMSDK_ERR CloseDevice(long deviceIndex);
		/// <summary>自動裁切；CropType=0~5 </summary>
		/// <param name="deviceIndex">設備ID，即攝像頭序號,0號開始</param>
		/// <param name="cropType">裁切方式</param>
		CAMSDK_ERR SetAutoCrop(long deviceIndex, CropType cropType);
		/// <summary>設置JPG壓縮率，100=不壓縮，品質最好。默認壓縮率為55。</summary>
		CAMSDK_ERR SetJpegQuality(long deviceIndex, long quality);
		/// <summary>設置圖片DPI (X Y DPI要一致，否則以X解析度為准)</summary>
		CAMSDK_ERR SetDpi(long deviceIndex, long xDpi, long yDpi);
		/// <summary>獲得當前視頻格式及解析度。</summary>
		CAMSDK_ERR GetCurrentResolution(long deviceIndex, [Out]long% subType, [Out]Resolution% resolution);
		/// <summary>獲取解析度個數，-1即失敗。</summary>
		long GetResolutionCount(long deviceIndex, long subType);
		/// <summary>獲取指定 ID 的解析度</summary>
		CAMSDK_ERR GetResolution(long deviceIndex, long subType, long index, [Out]Resolution% resolution);
		/// <summary>設置指定 ID 的解析度</summary>
		CAMSDK_ERR SetResolution(long deviceIndex, Resolution resolution);
		/// <summary>拍照至檔案，多圖裁切時返回以分號為分隔的多個全路徑。</summary>
		CAMSDK_ERR CaptureFile(long deviceIndex, String^% filePath);
		/// <summary>設置裁切區域</summary>
		CAMSDK_ERR SetImageCropRect(long deviceIndex, long left, long top, long right, long bottom);
		/// <summary>獲取裁切區域</summary>
		CAMSDK_ERR GetImageCropRect(long deviceIndex);
		/// <summary>彈出“視頻效果”設置視窗</summary>
		CAMSDK_ERR ShowImageSetting(long deviceIndex);
		/// <summary>彈出“視頻屬性”設置視窗</summary>
		CAMSDK_ERR ShowVideoSetting(long deviceIndex);
		/// <summary>去噪</summary>
		CAMSDK_ERR SetDenoise(long deviceIndex, bool enable);
		/// <summary>印刷偏移矯正</summary>
		CAMSDK_ERR SetOffsetCorrection(long deviceIndex, bool enable);
		CAMSDK_ERR StartAutoCapture(long deviceIndex, AutoCaptureType type, long param);
		CAMSDK_ERR PauseAutoCapture(long deviceIndex, AutoCaptureType type);
		CAMSDK_ERR StopAutoCapture(long deviceIndex);
		/// <summary>反初始化裝置 Library</summary>
		bool UnInit();
		event AutoCaptureDelgate^ MyEvent;
	};
}