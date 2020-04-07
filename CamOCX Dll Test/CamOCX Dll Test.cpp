// CamOCX Dll Test.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>
#include "Header.h"
#include "CmDefine.h"
using namespace std;

// DLL function signature  
typedef CAMSDK_ERR (*camInitCameraLib)();
typedef CAMSDK_ERR (*camUnInitCameraLib)();
typedef CAMSDK_ERR (*camGetDevCount)(long& count);
typedef char* (*camGetDevName)(long devIndex);
typedef CAMSDK_ERR (*camCaptureImageFile)(long devIndex, char* filePath);
typedef CAMSDK_ERR (*camSetImageAutoCrop)(long devIndex, long CropType);
typedef CAMSDK_ERR (*camOpenDev)(long devIndex, long subtype, long width, long height);
typedef CAMSDK_ERR (*camCloseDev)(long devIndex);
typedef CAMSDK_ERR (*camSetImageJPGQuanlity)(long devIndex, long quanlity);
typedef CAMSDK_ERR (*camGetCurResolution)(long devIndex, long& subtype, long& width, long& height);
typedef bool (CALLBACK* callBackPreviewImage)(std::byte* src, long width, long height, long size);
typedef CAMSDK_ERR (*camRegCallBackPreviewImage)(long devIndex, callBackPreviewImage fun);
typedef CAMSDK_ERR (*camSetPreviewWindow)(long devIndex, HWND hPreviewWindow);
typedef CAMSDK_ERR (*camSetImageDPI)(long devIndex, long xDPI, long yDPI);
typedef long(*camGetImageCusCropRect)(long devIndex, long& left, long& top, long& right, long& bottom);

int main()
{
    wstring dllName = L"CmCapture.dll";
    HMODULE m_hMod = LoadLibrary(dllName.c_str());
    if (m_hMod == nullptr)    
        cout << "LoadLibrary failed!\n";
    else
        cout << "LoadLibrary success.\n";

    // init function pointers
    auto init = (camInitCameraLib)GetProcAddress(m_hMod, "camInitCameraLib");
    if (init == nullptr)
        cout << "Get camInitCameraLib address failed.\n";

    auto unInit = (camUnInitCameraLib)GetProcAddress(m_hMod, "camUnInitCameraLib");
    if (unInit == nullptr)
        cout << "Get camUnInitCameraLib address failed.\n";

    auto getDeviceCount = (camGetDevCount)GetProcAddress(m_hMod, "camGetDevCount");
    if (getDeviceCount == nullptr)
        cout << "Get camGetDevCount address failed.\n";

    auto getDeviceName = (camGetDevName)GetProcAddress(m_hMod, "camGetDevName");
    if (getDeviceName == nullptr)
        cout << "Get camGetDevName address failed.\n";

    auto openDevice = (camOpenDev)GetProcAddress(m_hMod, "camOpenDev");
    if (openDevice == nullptr)
        cout << "Get camOpenDev address failed.\n";

    auto closeDevice = (camCloseDev)GetProcAddress(m_hMod, "camCloseDev");
    if (openDevice == nullptr)
        cout << "Get camCloseDev address failed.\n";

    auto capture = (camCaptureImageFile)GetProcAddress(m_hMod, "camCaptureImageFile");
    if (capture == nullptr)
        cout << "Get camCaptureImageFile address failed.\n";

    auto autoCrop = (camSetImageAutoCrop)GetProcAddress(m_hMod, "camSetImageAutoCrop");
    if (autoCrop == nullptr)
        cout << "Get camSetImageAutoCrop address failed.\n";

    auto setJpegQuality = (camSetImageJPGQuanlity)GetProcAddress(m_hMod, "camSetImageJPGQuanlity");
    if (setJpegQuality == nullptr)
        cout << "Get camSetImageJPGQuanlity address failed.\n";

    auto getCurResolution = (camGetCurResolution)GetProcAddress(m_hMod, "camGetCurResolution");
    if (getCurResolution == nullptr)
        cout << "Get camGetCurResolution address failed.\n";

    auto registerCallback = (camRegCallBackPreviewImage)GetProcAddress(m_hMod, "camRegCallBackPreviewImage");
    if (registerCallback == nullptr)
        cout << "Get camRegCallBackPreviewImage address failed.\n";

    auto setPreviewWindow = (camSetPreviewWindow)GetProcAddress(m_hMod, "camSetPreviewWindow");
    if (setPreviewWindow == nullptr)
        cout << "Get camSetPreviewWindow address failed.\n";

    auto setDPI = (camSetImageDPI)GetProcAddress(m_hMod, "camSetImageDPI");
    if (setDPI == nullptr)
        cout << "Get camSetImageDPI address failed.\n";

    // 初始化
    CAMSDK_ERR lR = init();
    if (ERR_NONE != lR && ERR_NOLICENSE != lR)
        cout << "Init result = " << lR << endl;
    else
        cout << "Init success.\n";

    // 获取设备个数
    long count = 0;
    lR = getDeviceCount(count);
    if (lR != ERR_NONE)
        cout << "Get device count fail. result = " << lR << endl;
    else
        cout << "Get device count = " << count << endl;

    for (long i = 0; i < count; i++)
    {
        string strDev = getDeviceName(i);
        cout << " - " << strDev << endl;
    }

    int index = 0;

    //lR = registerCallback(index, nullptr);
    //if (ERR_NONE != lR && ERR_NOLICENSE != lR)
    //    cout << "registerCallback result = " << lR << endl;
    //else
    //    cout << "registerCallback success.\n";

    // 获取视频设备列表并选择第一个
    // CropType:
    // 0 不裁切
    // 1 单图裁切
    // 2 多图裁切
    // 3 单图裁切 & 补边
    // 5 裁切人脸
    long croptype = 0;
    lR = autoCrop(index, croptype);
    if (lR != ERR_NONE)
        cout << "Set auto crop fail. result = " << lR << endl;
    else
        cout << "Set auto crop success." << endl;

    // quanlity 压缩率值范围：0~100。100不压缩，质量最好尺寸最大
    lR = setJpegQuality(index, 100);
    if (lR != ERR_NONE)
        cout << "Set jpeg quality fail. result = " << lR << endl;
    else
        cout << "Set jpeg quality success.\n";

    // open device
    // subtype   媒体格式ID，不同设备支持的格式可能不同，常见0：mjpeg，1：yuy2，不支持mjpeg的设备则 0：yuy2。
    lR = openDevice(index, 0, 0, 0);
    if (lR != ERR_NONE)
        cout << "Open fail. result = " << lR << endl;
    else
        cout << "Open success.\n";

    long xDPI = 300, yDPI = 300;
    lR = setDPI(index, xDPI, yDPI);
    if (lR != ERR_NONE)
        cout << "Set DPI fail. result = " << lR << endl;
    else
        cout << "Set DPI success.\n";

    //lR = setPreviewWindow(index, nullptr);
    //if (ERR_NONE != lR && ERR_NOLICENSE != lR)
    //    cout << "setPreviewWindow result = " << lR << endl;
    //else
    //    cout << "setPreviewWindow success.\n";

    long subtype = 0, width = 0, height = 0;
    lR = getCurResolution(index, subtype, width, height);
    if (lR != ERR_NONE)
        cout << "getCurResolution fail. result = " << lR << endl;
    else
        cout << "getCurResolution success. subtype=" << subtype << ", width=" << width << ", height=" << height << endl;

    Sleep(1800);

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H-%M-%S");
    string timeString = oss.str();
    string fileName = "C:\\Users\\Tenny\\Pictures\\PPScanner\\CAMX\\test " + timeString + ".jpg";
    char cFilePath[2048] = { 0 };
    sprintf(cFilePath, (char*)fileName.c_str());
    lR = capture(index, cFilePath);
    while (lR != ERR_NONE)
    {
        cout << "Capture fail. result = " << lR << endl;
        system("pause");
        lR = capture(index, cFilePath);
    }
    cout << "Capture success.\n";

    lR = closeDevice(index);
    cout << "Close device result = " << lR << endl;

    lR = unInit();
    cout << "Uninit result = " << lR << endl;

    //std::cout << "Hello World!\n";
    system("pause");
}

// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
