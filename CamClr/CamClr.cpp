#include "pch.h"
#include "CamClr.h"
#include "CmCaptureHeader.h"

using namespace std;
using namespace CamClr;

CamClr::Cam::~Cam()
{
    if (m_hMod != nullptr)
        FreeLibrary(m_hMod);
}

CAMSDK_ERR CamClr::Cam::Init()
{
    wstring dllName = L"CmCapture.dll";
    m_hMod = LoadLibrary(dllName.c_str());
    if (m_hMod == nullptr)
    {
        cout << "LoadLibrary failed!\n";
        return CAMSDK_ERR::ERR_INIT;
    }
    else
        cout << "LoadLibrary success.\n";

    // init function pointers
    init = (camInitCameraLib)GetProcAddress(m_hMod, "camInitCameraLib");
    if (init == nullptr)
    {
        cout << "Get camInitCameraLib address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    unInit = (camUnInitCameraLib)GetProcAddress(m_hMod, "camUnInitCameraLib");
    if (unInit == nullptr)
    {
        cout << "Get camUnInitCameraLib address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    getDeviceCount = (camGetDevCount)GetProcAddress(m_hMod, "camGetDevCount");
    if (getDeviceCount == nullptr)
    {
        cout << "Get camGetDevCount address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    getDeviceCountCurrent = (camGetDevCountCur)GetProcAddress(m_hMod, "camGetDevCountCur");
    if (getDeviceCount == nullptr)
    {
        cout << "Get camGetDevCountCur address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    getDeviceName = (camGetDevName)GetProcAddress(m_hMod, "camGetDevName");
    if (getDeviceName == nullptr)
    {    
        cout << "Get camGetDevName address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    getFWVersion = (camGetFwVersion)GetProcAddress(m_hMod, "camGetFwVersion");
    if (getFWVersion == nullptr)
    {
        cout << "Get camGetFwVersion address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }
    
    getLensModel = (camGetLensModel)GetProcAddress(m_hMod, "camGetLensModel");
    if (getLensModel == nullptr)
    {
        cout << "Get camGetLensModel address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    getCameraModel = (camGetCameraModel)GetProcAddress(m_hMod, "camGetCameraModel");
    if (getCameraModel == nullptr)
    {
        cout << "Get camGetCameraModel address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    openDevice = (camOpenDev)GetProcAddress(m_hMod, "camOpenDev");
    if (openDevice == nullptr)
    {
        cout << "Get camOpenDev address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    closeDevice = (camCloseDev)GetProcAddress(m_hMod, "camCloseDev");
    if (openDevice == nullptr)
    {
        cout << "Get camCloseDev address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    captureFile = (camCaptureImageFile)GetProcAddress(m_hMod, "camCaptureImageFile");
    if (captureFile == nullptr)
    {
        cout << "Get camCaptureImageFile address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    setAutoCrop = (camSetImageAutoCrop)GetProcAddress(m_hMod, "camSetImageAutoCrop");
    if (setAutoCrop == nullptr)
    {
        cout << "Get camSetImageAutoCrop address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    setJpegQuality = (camSetImageJPGQuanlity)GetProcAddress(m_hMod, "camSetImageJPGQuanlity");
    if (setJpegQuality == nullptr)
    {
        cout << "Get camSetImageJPGQuanlity address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    getCurrentResolution = (camGetCurResolution)GetProcAddress(m_hMod, "camGetCurResolution");
    if (getCurrentResolution == nullptr)
    {
        cout << "Get camGetCurResolution address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    registerCallback = (camRegCallBackPreviewImage)GetProcAddress(m_hMod, "camRegCallBackPreviewImage");
    if (registerCallback == nullptr)
    {
        cout << "Get camRegCallBackPreviewImage address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    setPreviewWindow = (camSetPreviewWindow)GetProcAddress(m_hMod, "camSetPreviewWindow");
    if (setPreviewWindow == nullptr)
    {
        cout << "Get camSetPreviewWindow address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    setDPI = (camSetImageDPI)GetProcAddress(m_hMod, "camSetImageDPI");
    if (setDPI == nullptr)
    {
        cout << "Get camSetImageDPI address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    setImageCropRect = (camSetImageCusCropRect)GetProcAddress(m_hMod, "camSetImageCusCropRect");
    if (setImageCropRect == nullptr)
    {
        cout << "Get camSetImageCusCropRect address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    getImageCropRect = (camGetImageCusCropRect)GetProcAddress(m_hMod, "camGetImageCusCropRect");
    if (getImageCropRect == nullptr)
    {
        cout << "Get camGetImageCusCropRect address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    showImageSetting = (camShowImageSettingWindow)GetProcAddress(m_hMod, "camShowImageSettingWindow");
    if (showImageSetting == nullptr)
    {
        cout << "Get camShowImageSettingWindow address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    showVideoSetting = (camShowDevSettingWindow)GetProcAddress(m_hMod, "camShowDevSettingWindow");
    if (showVideoSetting == nullptr)
    {
        cout << "Get camShowDevSettingWindow address failed.\n";
        return CAMSDK_ERR::ERR_INIT;
    }

    return init();
}

long CamClr::Cam::GetDeviceCount()
{    
    long count = 0;
    long err = getDeviceCount(count);
    if (err == 0)
        return count;
    return -1;
}

String^ CamClr::Cam::GetDeviceName(long deviceIndex)
{
    string strDev = getDeviceName(deviceIndex);
    String^ str2 = gcnew String(strDev.c_str());
    return str2;
}

CAMSDK_ERR CamClr::Cam::GetModles(long deviceIndex, String^% fwVersion, String^% model, String^% vid_pid)
{
    char buffer[100];
    CAMSDK_ERR err = (CAMSDK_ERR)getFWVersion(deviceIndex, buffer);
    if (err == CAMSDK_ERR::ERR_NONE)
    {
        //cout << "FW version = " << buffer << endl;
        string str(buffer);
        fwVersion = gcnew String(str.c_str());
    }
    else
        fwVersion = nullptr;

    err = (CAMSDK_ERR)getLensModel(deviceIndex, buffer);
    if (err == CAMSDK_ERR::ERR_NONE)
    {
        //cout << "Lens model = " << buffer << endl;
        string str(buffer);
        model = gcnew String(str.c_str());
    }
    else
        model = nullptr;

    err = (CAMSDK_ERR)getCameraModel(deviceIndex, buffer);
    if (err == CAMSDK_ERR::ERR_NONE)
    {
        //cout << "Camera model = " << buffer << endl;
        string str(buffer);
        vid_pid = gcnew String(str.c_str());
    }
    else
        vid_pid = nullptr;

    return err;
}

CAMSDK_ERR CamClr::Cam::OpenDevice(long deviceIndex, long subType, long width, long height)
{
    return openDevice(deviceIndex, subType, width, height);
}

CAMSDK_ERR CamClr::Cam::CloseDevice(long deviceIndex)
{
    return (CAMSDK_ERR)closeDevice(deviceIndex);
}

CAMSDK_ERR CamClr::Cam::SetAutoCrop(long deviceIndex, CropType cropType)
{
    return (CAMSDK_ERR)setAutoCrop(deviceIndex, (long)cropType);
}

CAMSDK_ERR CamClr::Cam::SetJpegQuality(long deviceIndex, long quality)
{
    return (CAMSDK_ERR)setJpegQuality(deviceIndex, quality);
}

CAMSDK_ERR CamClr::Cam::SetDpi(long deviceIndex, long xDpi, long yDpi)
{
    return (CAMSDK_ERR)setDPI(deviceIndex, xDpi, yDpi);
}

CAMSDK_ERR CamClr::Cam::GetCurrentResolution(long deviceIndex, long% subType, long% width, long% height)
{
    long local_subType = 0, local_width = 0, local_height = 0;
    CAMSDK_ERR err = (CAMSDK_ERR)getCurrentResolution(deviceIndex, local_subType, local_width, local_height);
    if (err == CAMSDK_ERR::ERR_NONE)
    {
        subType = local_subType;
        width = local_width;
        height = local_height;
    }
    return err;
}

CAMSDK_ERR CamClr::Cam::CaptureFile(long deviceIndex, String^% filePath)
{
    const char* charFilePath = string_to_char_array(filePath);
    //cout << "charFilePath=" << charFilePath << endl;
    char buffer[2048] = { 0 };
    sprintf(buffer, charFilePath);
    CAMSDK_ERR err = (CAMSDK_ERR)captureFile(deviceIndex, buffer);
    //cout << "buffer=" << buffer << endl;
    if (err == CAMSDK_ERR::ERR_NONE)
    {
        filePath = gcnew String(buffer);
    }
    return err;
}

CAMSDK_ERR CamClr::Cam::SetImageCropRect(long deviceIndex, long left, long top, long right, long bottom)
{
    CAMSDK_ERR err = (CAMSDK_ERR)setImageCropRect(deviceIndex, left, top, right, bottom);
    return err;
}

CAMSDK_ERR CamClr::Cam::GetImageCropRect(long deviceIndex)
{
    long left, top, right, bottom;
    CAMSDK_ERR err = (CAMSDK_ERR) getImageCropRect(deviceIndex, left, top, right, bottom);
    //printf("getImageCropRect err=%d left=%d top=%d rignt=%d bottom=%d\n", left, top, right, bottom, err);
    return err;
}

CAMSDK_ERR CamClr::Cam::ShowImageSetting(long deviceIndex)
{
    CAMSDK_ERR err = (CAMSDK_ERR)showImageSetting(deviceIndex);
    return err;
}

CAMSDK_ERR CamClr::Cam::ShowVideoSetting(long deviceIndex)
{
    CAMSDK_ERR err = (CAMSDK_ERR)showVideoSetting(deviceIndex);
    return err;
}

bool CamClr::Cam::UnInit()
{
	auto result = unInit();
    return result == CAMSDK_ERR::ERR_NONE;
}
