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
                    Console.WriteLine("Device count = " + count);
                    for (int i = 0; i<count; i++)
                    {
                        string name = camLibrary.GetDeviceName(i);
                        Console.WriteLine($" - device {i} name = " + name);
                    }
                }

                int device = 0, subtype = 0;
                List<Resolution> resolutions = new List<Resolution>();

                result = camLibrary.GetModles(device, out string fwVersion, out string model, out string vid_pid);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("GetModles failed! result = " + result);

                result = camLibrary.SetAutoCrop(device, CropType.Multiple);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("SetAutoCrop failed! result = " + result);

                // Open 之後再設定其他值
                result = camLibrary.OpenDevice(device, subtype, 0, 0);
                if (result != CAMSDK_ERR.ERR_NONE)
                {
                    Console.WriteLine("OpenDevice failed! result = " + result);
                    camLibrary.UnInit();
                    Console.WriteLine("Press any key to continue..");
                    Console.ReadLine();
                    return;
                }

                result = camLibrary.SetJpegQuality(device, 100);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("SetJpegQuality failed! result = " + result);

                result = camLibrary.SetDpi(device, 300, 300);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("SetDpi failed! result = " + result);

                count = camLibrary.GetResolutionCount(device, subtype);
                if (count < 0)
                    Console.WriteLine("GetResolutionCount failed!");
                else
                {
                    Console.WriteLine("Resolution count = " + count);
                    for (int i = 0; i < count; i++)
                    {
                        camLibrary.GetResolution(device, subtype, i, out Resolution resolution);
                        Console.WriteLine($" - resolution {i} = {resolution.Width} x {resolution.Height}");
                        resolutions.Add(resolution);
                    }
                }

                resolutions.Sort((x, y) => x.Width.CompareTo(y.Width));
                Resolution max = resolutions.Last();
                result = camLibrary.SetResolution(device, max);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("SetResolution failed! result = " + result);

                result = camLibrary.GetCurrentResolution(device, out subtype, out Resolution r);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("GetCurrentResolution failed! result = " + result);
                else
                    Console.WriteLine($"Current width={r.Width}, height={r.Height}");

                //result = camLibrary.ShowVideoSetting(device);
                //if (result != CAMSDK_ERR.ERR_NONE)
                //    Console.WriteLine("ShowSetting failed! result = " + result);

                // 拍照前要等夠久
                System.Threading.Thread.Sleep(1800);

                //result = camLibrary.SetImageCropRect(device, 0, 0, width, height);
                //result = camLibrary.GetImageCropRect(device);

                string filePath = Environment.GetFolderPath(Environment.SpecialFolder.MyPictures) 
                                  + @"\PPScanner\CAMX\" + DateTime.Now.ToString("yyyy-M-d HHmmss") + ".jpg";
                result = camLibrary.CaptureFile(device, ref filePath);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("CaptureFile failed! result = " + result);
                else
                {
                    Console.WriteLine("Files:");
                    filePath = filePath.Replace(@"\\", @"\");
                    string[] files = filePath.Split(';');
                    foreach (var f in files)
                    {
                        Console.WriteLine(f);
                    }
                }

                result = camLibrary.CloseDevice(device);
                if (result != CAMSDK_ERR.ERR_NONE)
                    Console.WriteLine("CloseDevice failed! result = " + result);

                if (!camLibrary.UnInit())
                    Console.WriteLine("UnInit failed!");
            }
            Console.WriteLine("Done.\nPress any key to continue..");
            Console.ReadLine();
        }
    }
}
