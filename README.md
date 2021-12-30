# TCS3200-Arduino-sorter-with-Serial-interface-and-NodeRed-Dashboard
Arduino TCS3200 based Colour sorter with Serial interface and  NodeRed Dashboard
![image](https://user-images.githubusercontent.com/80263068/147758723-37c2aaa9-f911-4d8d-bc9c-af70d651d663.png)
![image](https://user-images.githubusercontent.com/80263068/147759284-ac9563f1-529a-4e48-9cf7-e642c6c0dd73.png)


![image](https://user-images.githubusercontent.com/80263068/147758567-ad1bc078-ff11-4df5-963e-6aa9f2d5b4b8.png)




As a fun project I created an automated sorting machine that visually presents information to a user cia an LCD and an on-screen JavaScript dashboard. The machine is built from an Arduino Uno with a TCS3200 Colour sensor attached. M&M's/Smarties are loaded into a hopper and when the machine is started, it cycles through the contents of the hopper and sorts them by colour. The contents of the hopper are moved by a servo motor via a carousell to the TCS3200 colour sensor. This sensor determines what colour of sweet is in the read area and then passes it on to another servo. This servo then positions itself to move the detected sweet to the correct container. Once the sweet is distributed correctly, the cycle begins again. The amounts of each colour sorted as well as the status of the system are displayed on a 20x4 lcd display on the machine itself. Additionally, this information is sent via a serial connection to a PC running a software called Node-red. This is a Javascript based program that ingests the information from the serial connection, displays it in the form of a dashboard on a computer monitor and also saves all information to a file in a csv format. The system has the ability to detect when the hopper is empty and alerts the operator of this fact. In addition to the colour sensor of the machine itself, there is also a Raspberry Pi zero W attached which can be used to remotely observe the machine from anywhere on the local network. This offers an additional method of quality assurance while running the machine. 



