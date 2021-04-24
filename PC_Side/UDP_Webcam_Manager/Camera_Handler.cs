using AForge.Video;
using AForge.Video.DirectShow;
using System.Drawing;
using System.Drawing.Imaging;
using System.Collections.Generic;

namespace UDP_Webcam_Manager
{
    public class Camera_Handler
    {
        private FilterInfoCollection filter_info_collection;
        private VideoCaptureDevice video_capture_device;
        private Size size;
        private int frame_width = 480;
        private int frame_height = 272;
        public List<string> camera_names = new List<string>();
        public int index;
        public Bitmap frame;

        public Camera_Handler(int width, int height)
        {
            this.frame_width = width;
            this.frame_height = height;
            this.index = 0;
        }

        public void Camera_Init()
        {
            filter_info_collection = new FilterInfoCollection(FilterCategory.VideoInputDevice);

            foreach (FilterInfo filterInfo in filter_info_collection)
            {
                camera_names.Add(filterInfo.Name);
            }

        }

        public void Camera_Start()
        {
            video_capture_device = new VideoCaptureDevice(filter_info_collection[index].MonikerString);

            video_capture_device.NewFrame += Video_capture_device_NewFrame;
            video_capture_device.Start();

            
        }

        private void Video_capture_device_NewFrame(object sender, NewFrameEventArgs eventArgs)
        {
            size.Width = frame_width;
            size.Height = frame_height;
            frame     = (Bitmap)(new Bitmap((Bitmap)eventArgs.Frame.Clone(), size));
        }

        public bool Camera_Running()
        {
            return video_capture_device.IsRunning;
        }
        public void Camera_Stop()
        {
            video_capture_device.Stop();
        }
    }
}
