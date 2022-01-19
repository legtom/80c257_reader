# 80c257_reader #

Short latched eprom reader program with Arduino Mega and Node-red for old Bosch Motronic (8051).


![This is an image](https://github.com/legtom/80c257_reader/blob/main/02_photo/01_stand_by.JPG)

I want to read my old '96 citroen zx 1.4i bosch monomotronic EPROM but i don't have any prom reader, so i create this one.

**You need :**
* 1 Arduino Mega.
* 1 PC with Node-red installed.
* 1 usb cable.
* 1 breadboard.
* 28 wire.
* 1 80c257 latched eprom.


**The arduino's pinout :**
* PORTA : input adress lsb, A0>A7, **pin 22 to 29.**
* PORTC : input adress msb, A8>A14, **pin 29 to 26.**
* PORTK : input command, !AS !E !G respectively **pin A10, A09 and A08.**
* PORTL : output data, Q0>Q7 **pin 42 to 49.**
* 5v and ground to supply the EPROM.

**Node-red flow :**

![This is an image](https://github.com/legtom/80c257_reader/blob/main/02_photo/00_node-red_flow.JPG)

Just import the json file in Node-red and configure serial port and dump file destination (or create au eprom nemed directory in C:\ if you are a windows user.).

**Easy to use :**
* For a partial reading just insert the adresses window you want to read and click on partial reading.
* For a full reading, just click on full reading, the reader reads the 32768 EPROM's adresses.
* When a partial or full reading is finished, it creates a binary file in *C:\eprom\eprom.bin* (sorry for linux  or mac user).
* If arduino can't read the serial command from Node-red or can't read the prom, it tells you in the status case. 
* You just have to reset the reader with the reset button.

You can also find the EPROM datasheet and pictures of this project in datasheet and photo directory.
Next step, build a programmer !

**Don't use this for a 27c EPROM without arduino's code modification !**

*I am not developper, just curious.*
