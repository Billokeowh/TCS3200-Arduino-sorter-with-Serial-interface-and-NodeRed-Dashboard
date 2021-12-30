# TCS3200-Arduino-sorter-with-Serial-interface-and-NodeRed-Dashboard
Arduino TCS3200 based Colour sorter with Serial interface and  NodeRed Dashboard
![image](https://user-images.githubusercontent.com/80263068/147758723-37c2aaa9-f911-4d8d-bc9c-af70d651d663.png)


![image](https://user-images.githubusercontent.com/80263068/147758567-ad1bc078-ff11-4df5-963e-6aa9f2d5b4b8.png)




As a fun project I have chosen to create an automated sorting machine that visually presents information to a user cia an LCD and an on-screen dashboard. The machine is built from an Arduino Uno with a TCS3200 Colour sensor attached. M&M's/Smarties are loaded into a hopper and when the machine is started, it cycles through the contents of the hopper and sorts them by colour. The contents of the hopper are moved by a servo motor via a carousell to the TCS3200 colour sensor. This sensor determines what colour of sweet is in the read area and then passes it on to another servo. This servo then positions itself to move the detected sweet to the correct container. Once the sweet is distributed correctly, the cycle begins again. The amounts of each colour sorted as well as the status of the system are displayed on a 20x4 lcd display on the machine itself. Additionally, this information is sent via a serial connection to a PC running a software called Node-red. This is a Javascript based program that ingests the information from the serial connection, displays it in the form of a dashboard on a computer monitor and also saves all information to a file in a csv format. The system has the ability to detect when the hopper is empty and alerts the operator of this fact. In addition to the colour sensor of the machine itself, there is also a Raspberry Pi zero W attached which can be used to remotely observe the machine from anywhere on the local network. This offers an additional method of quality assurance while running the machine. 

![image](https://user-images.githubusercontent.com/80263068/147758442-98e99097-e977-4900-9ffd-e1ca92311143.png)

![image](https://user-images.githubusercontent.com/80263068/147758461-9b06b556-0732-4276-b220-d38356a239d8.png)

![image](https://user-images.githubusercontent.com/80263068/147758518-929bddec-dd43-4f1d-8304-e1bfa8787eeb.png)

![image](https://user-images.githubusercontent.com/80263068/147758578-c705a562-c331-42f1-a9d7-2c3df8e64a28.png)

![image](https://user-images.githubusercontent.com/80263068/147758596-78b16d73-3c80-44f1-9683-6861cced83f9.png)

![image](https://user-images.githubusercontent.com/80263068/147758609-88afd4e4-520f-4b77-85ea-e04d2cd03436.png)

![image](https://user-images.githubusercontent.com/80263068/147758621-c6991c04-9aa3-4247-8f22-28a53ec359bf.png)

![image](https://user-images.githubusercontent.com/80263068/147758634-d9f054e7-d622-46eb-92bd-b37bc873eadf.png)

