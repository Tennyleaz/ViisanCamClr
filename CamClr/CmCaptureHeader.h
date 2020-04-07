#pragma once
#include <windows.h>
#include "CmDefine.h"

//// DLL function signature  
//typedef CAMSDK_ERR(*camInitCameraLib)();
//typedef CAMSDK_ERR(*camUnInitCameraLib)();
//typedef CAMSDK_ERR(*camGetDevCount)(long & count);
//typedef CAMSDK_ERR(*camGetDevCountCur)(long & count);
//typedef char* (*camGetDevName)(long devIndex);
//typedef CAMSDK_ERR(*camCaptureImageFile)(long devIndex, char* filePath);
//typedef CAMSDK_ERR(*camSetImageAutoCrop)(long devIndex, long CropType);
//typedef CAMSDK_ERR(*camOpenDev)(long devIndex, long subtype, long width, long height);
//typedef CAMSDK_ERR(*camCloseDev)(long devIndex);
//typedef CAMSDK_ERR(*camSetImageJPGQuanlity)(long devIndex, long quanlity);
//typedef CAMSDK_ERR(*camGetCurResolution)(long devIndex, long& subtype, long& width, long& height);
//typedef bool (CALLBACK* callBackPreviewImage)(unsigned char src, long width, long height, long size);
//typedef CAMSDK_ERR(*camRegCallBackPreviewImage)(long devIndex, callBackPreviewImage fun);
//typedef CAMSDK_ERR(*camSetPreviewWindow)(long devIndex, HWND hPreviewWindow);
//typedef CAMSDK_ERR(*camSetImageDPI)(long devIndex, long xDPI, long yDPI);