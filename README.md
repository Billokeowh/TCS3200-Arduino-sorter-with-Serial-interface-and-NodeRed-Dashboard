# TCS3200-Arduino-sorter-with-Serial-interface-and-NodeRed-Dashboard
Arduino TCS3200 based Colour sorter with Serial interface and  NodeRed Dashboard

![image](https://user-images.githubusercontent.com/80263068/147759284-ac9563f1-529a-4e48-9cf7-e642c6c0dd73.png)
- Carousel used to transport the sweets from the hopper to the Sensor. 


As a fun project I created an automated sorting machine that visually presents information to a user cia an LCD and an on-screen JavaScript dashboard. The machine is built from an Arduino Uno with a TCS3200 Colour sensor attached. M&M's/Smarties are loaded into a hopper and when the machine is started, it cycles through the contents of the hopper and sorts them by colour. The contents of the hopper are moved by a servo motor via a carousell to the TCS3200 colour sensor. This sensor determines what colour of sweet is in the read area and then passes it on to another servo. This servo then positions itself to move the detected sweet to the correct container. Once the sweet is distributed correctly, the cycle begins again. The amounts of each colour sorted as well as the status of the system are displayed on a 20x4 lcd display on the machine itself. Additionally, this information is sent via a serial connection to a PC running a software called Node-red. This is a Javascript based program that ingests the information from the serial connection, displays it in the form of a dashboard on a computer monitor and also saves all information to a file in a csv format. The system has the ability to detect when the hopper is empty and alerts the operator of this fact. In addition to the colour sensor of the machine itself, there is also a Raspberry Pi zero W attached which can be used to remotely observe the machine from anywhere on the local network. This offers an additional method of quality assurance while running the machine. 

![image](https://user-images.githubusercontent.com/80263068/147758567-ad1bc078-ff11-4df5-963e-6aa9f2d5b4b8.png)
 - The nodeRed (JavaScript) dashboard use to display the received serial information. 

Node-red is a development tool that is based on the Node.js Javascript runtime environment. It is a flow based visual programmer and it is what I elected to use to create a dashboard for a user to observe vital data about the machine and its processes. Node-red is a service that must be started by entering the command prompt. Once running it can be accessed from your browser at http://127.0.0.1:1880/. Once started, it takes over all serial communication with the Arduino so the Arduino IDE’s port monitor no longer functions. the Arduino outputs a 15 character long string which contains all the relevant information about the machine. At this point Node-red must be configured to ingest this string and present the relevant information correctly. To do this the “function” node is employed. The function node takes the 15 character string and dissects it into its relevant parts. For every piece of information that is required a different part of the string is used. In the example below the entire string is taken and is assigned to the value m. The string is then broken into pieces and in this case from the 6th to the 9th characters are assigned to the variable “Green". We then output the green value and given that it is an integer we can use it to update charts, graphs and text boxes. This method is used to obtain the values of Red, Green and Blue and the same code is used only changing the output value to the relevant colour.

![image](https://user-images.githubusercontent.com/80263068/147759969-49463421-4a11-44e1-a287-8d64a8172473.png)
- How the String from the Arduino is parsed to get required values.

The Node-Red flow below is just a visual version of what is attached above. To get this working on your machine you will have to make sure that Node-Red is running and the correct port numnber and baud rate is selected. Once up and running this connection is very stable and there were never any issues with it while I was testing. 

![image](https://user-images.githubusercontent.com/80263068/147760832-b92952d0-bc3e-4cae-b2d0-4fac7508fee8.png)




