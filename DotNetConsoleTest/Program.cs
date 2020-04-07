using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using CamClr;

namespace DotNetConsoleTest
{
    class Program
    {
        //[DllImport("CmCapture.dll", EntryPoint = "camInitCameraLib", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        //private static extern long camInitCameraLib();

        //[DllImport("CmCapture.dll", EntryPoint = "camUnInitCameraLib", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        //private static extern long camUnInitCameraLib();

        //[DllImport("CmCapture.dll", EntryPoint = "camGetDevCount", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        //private static extern long camGetDevCount(out long count);

        //[DllImport("CmCapture.dll", EntryPoint = "camGetDevName", CallingConvention = CallingConvention.Cdecl, ExactSpelling = true)]
        //private static extern IntPtr camGetDevName(long devIndex);

        static void Main(string[] args)
        {
            using (Cam camLibrary = new Cam())
            {
                CAMSDK_ERR result = camLibrary.Init();
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("camInitCameraLib failed! result = " + result);

                int count = camLibrary.GetDeviceCount();
                if (count < 0)
                    Console.WriteLine("GetDeviceCount failed!");
                else
                {
                    Console.WriteLine("count = " + count);
                    for (int i = 0; i<count; i++)
                    {
                        string name = camLibrary.GetDeviceName(i);
                        Console.WriteLine("Device name = " + name);
                    }
                }

                int device = 0, subtype = 0, width = 0, height = 0;

                result = camLibrary.GetModles(device, out string fwVersion, out string model, out string vid_pid);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("GetModles failed! result = " + result);

                result = camLibrary.SetAutoCrop(device, CropType.Multiple);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("SetAutoCrop failed! result = " + result);

                result = camLibrary.SetJpegQuality(device, 100);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("SetJpegQuality failed! result = " + result);

                result = camLibrary.OpenDevice(device, subtype, width, height);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("OpenDevice failed! result = " + result);

                result = camLibrary.SetDpi(device, 0, 0);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("SetDpi failed! result = " + result);

                //result = camLibrary.ShowVideoSetting(device);
                //if (result != CAMSDK_ERR.ERR_NONE)
                //    Console.WriteLine("ShowSetting failed! result = " + result);

                // 拍照前要等夠久
                System.Threading.Thread.Sleep(1800);

                result = camLibrary.GetCurrentResolution(device, out subtype, out width, out height);
                result = camLibrary.SetImageCropRect(device, 0, 0, width, height);
                result = camLibrary.GetImageCropRect(device);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("GetImageCropRect failed! result = " + result);

                string filePath = "C:\\Users\\Tenny\\Pictures\\PPScanner\\CAMX\\" + DateTime.Now.ToString("yyyy-M-d HHmmss") + ".jpg";
                result = camLibrary.CaptureFile(device, ref filePath);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("CaptureFile failed! result = " + result);
                else
                {
                    Console.WriteLine("filePath = " + filePath);

                }

                result = camLibrary.CloseDevice(device);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("CloseDevice failed! result = " + result);

                if (!camLibrary.UnInit())
                    Console.WriteLine("camUnInitCameraLib failed!");
            }
            Console.WriteLine("Done.\nPress any key to continue..");
            Console.ReadLine();
        }
    }
}
