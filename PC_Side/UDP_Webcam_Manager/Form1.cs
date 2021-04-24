using System;
using System.Drawing;
using System.Windows.Forms;

namespace UDP_Webcam_Manager
{

    public partial class Form1 : Form
    {
        
        private Camera_Handler camera_handler = new Camera_Handler(480, 272);
        private UDP_Handler udp_handler = new UDP_Handler("192.168.1.68", 1234);
        private int button_counter = 0;

        const int x_sub_frame = 16;
        const int y_sub_frame = 16;

        int counter = 0;
        byte[] udp_buffer = new byte[x_sub_frame * y_sub_frame * 4+4];

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            camera_handler.Camera_Init();
            foreach( string camera_names in camera_handler.camera_names)
            {
                comboBox2.Items.Add(camera_names);
            }
            comboBox2.Text = camera_handler.camera_names[0];
            timer2.Interval = 1;
            timer2.Start();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            button_counter++;
            if (button_counter % 2 == 1)
            {
                camera_handler.Camera_Start();
                button2.Text = "Stop";
            }
            else
            {
                camera_handler.Camera_Stop();
                button2.Text = "Start";
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if (camera_handler.frame != null)
            {
                pictureBox2.Image = camera_handler.frame;
                int y_limit = 0;
                int seq_num = 0;

                while (seq_num < 30 * 17)
                {
                    for (int y = y_limit * y_sub_frame; y < y_limit * y_sub_frame + y_sub_frame; y++)
                    {
                        for (int x = (seq_num % 30) * x_sub_frame; x < (seq_num % 30) * x_sub_frame + x_sub_frame; x++)
                        {
                            Buffer.BlockCopy(BitConverter.GetBytes(camera_handler.frame.GetPixel(x, y).ToArgb()), 0, udp_buffer, 4 * (counter++) + 4, 4);
                        }
                    }

                    Buffer.BlockCopy(BitConverter.GetBytes(seq_num), 0, udp_buffer, 0, 4);

                    udp_handler.Send(udp_buffer);         
                    counter = 0;
                    seq_num++;

                    if (seq_num % 30 == 0)
                    {
                        y_limit++;

                        if (y_limit > 17)
                        {
                            y_limit = 0;
                        }
                    }
                }
            }

        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (button_counter % 2 == 1)
            {
                camera_handler.Camera_Stop();
            }
        }
    }

}
