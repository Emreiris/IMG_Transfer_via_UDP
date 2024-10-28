# STM32 UDP Image Transfer - V1.0

This project is designed to transmit 480x272 size images from computer to MCU([STM32F746-Disco](https://www.st.com/en/evaluation-tools/32f746gdiscovery.html)).

Project Structure  
\MCU_Side  
 \Modules       "Contains necessary software modules for project."  
 \Application   "Application Layer is coded in here."  
\PC_Side   
 \UDP_Webcam_Manager\Camera_Handler.cs   "Manages camera functionality."  
 \UDP_Webcam_Manager\UDP_Handler.cs      "Manages UDP data transmission functionality."  
 \UDP_Webcam_Manager\Form1.cs            "Application layer is coded in here." \s\s  

The algorithm for image transmission is as follows                                
PC_Side                          
1- Form Load                                  
2- Start Camera                                                                                          
3- Take the frame       
4- Resize to 480x272     
5- Write sequence number in first 4 bytes in an buffer   
6- take 16x16 sub-frame from image in position (0+x_step,0+y_step)   
7- write to the same buffer with a 4-byte offset.  
7- Send buffer via UDP  
8- Increase sequence number   
9- increase x_step 16   
10- Check if the sequence number is divided into 30. If divided increase y_step  
11- Else go to step 5  

MCU_Side  
1- Initialize components  
2- Check if the UDP packet is received  
3- If received, write to udp_buffer  
4- Read the first 4 bytes of udp_buffer ( sequence number is in there )  
5- Calculate the Remainder of the sequence number when divided by 30. That is the x position of the sub-frame  
6- Calculate sequence number minus x position divided by 30. That is the y position of the sub-frame  
7- Write UDP buffer to displayer driver memory with 4-byte offset  
8- Go to 2. step  

#How to Run
- Open STM32CubeIDE and import project
- Build Project
- Load to target device 
- Open Visual Studio Code and import the solution
- Build project
- Run

You can watch the demo [here](https://youtu.be/131t2ypqeBg)   
NOTE: To communicate with MCU, change IP settings from DHCP to static IP in the PC's ethernet driver settings.

