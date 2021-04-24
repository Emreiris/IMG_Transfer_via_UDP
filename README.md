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

Algorithm for image transmission is as follows                                
PC_Side                          
1- Form Load                                  
2- Start Camera                                                                                          
3- Take frame       
4- Resize to 480x272     
5- Write sequence number in first 4 byte in an buffer   
6- take 16x16 sub-frame from image in position (0+x_step,0+y_step)   
7- write to same buffer with 4 byte offset.  
7- Send buffer via UDP  
8- Increase sequence number   
9- increse x_step 16   
10- Check if sequence number is divided to 30. If divided increase y_step  
11- Else go to step 5  

MCU_Side  
1- Initialize components  
2- Check if UDP packet is received  
3- If received, write to udp_buffer  
4- Read first 4 byte of udp_buffer ( sequence number is in there )  
5- Calculate Remainder of sequence number when divided by 30. That is the x position of sub-frame  
6- Calculate sequence number minus x position divided by 30. That is the y position of sub-frame  
7- Write udp buffer to displayer driver memory with 4 byte offset  
8- Go to 2. step  

#How to Run
- Open STM32CubeIDE and import project
- Build Project
- Load to target device 
- Open Visual Studio Code and import solution
- Build project
- Run

Video : https://www.youtube.com/watch?v=131t2ypqeBg   
NOTE : In order to communicate with MCU, change IP settings from DHCP to static IP in PC's ethernet driver settings.

