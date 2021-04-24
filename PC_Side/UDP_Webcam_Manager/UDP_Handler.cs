using System;
using System.Net.Sockets;
using System.Text;

namespace UDP_Webcam_Manager
{
    public class UDP_Handler
    {
        public string received_message;
        public string ip_address;
        public int port_no;
        private UdpClient udp = new UdpClient(1234);

        public UDP_Handler(string ip_address, int port_no)
        {
            this.ip_address = ip_address;
            this.port_no = port_no;
        }

        

        public void UDP_Start_Listening()
        {
            udp.BeginReceive(new AsyncCallback(Receive), null);
        }

        private void Receive(IAsyncResult receiever)
        {
            System.Net.IPEndPoint ip = new System.Net.IPEndPoint(System.Net.IPAddress.Parse(ip_address), port_no);
            byte[] bytes = udp.EndReceive(receiever, ref ip);
            received_message = Encoding.ASCII.GetString(bytes);
            UDP_Start_Listening();
        }

#if true

        public void Send(string message)
        {
            using (var client = new UdpClient())
            {
                System.Net.IPEndPoint ip = new System.Net.IPEndPoint(System.Net.IPAddress.Parse(ip_address), port_no);
                byte[] bytes = Encoding.ASCII.GetBytes(message);
                client.Send(bytes, bytes.Length, ip);
                client.Close();
            }
        }

#endif

        public void Send(byte[] payload)
        {
            using (var client = new UdpClient())
            {
                System.Net.IPEndPoint ip = new System.Net.IPEndPoint(System.Net.IPAddress.Parse(ip_address), port_no);
                client.Send(payload, payload.Length, ip);
            }
        }

    }
}

