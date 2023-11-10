# tracking-system-for-the-domestic-animals
its an embedded system project based on the idea of tracking the exact location of the animals from the farmers mobile phone.

these embedded system project is designed using the ARM Cortex M3 based STM32F103C8T6 as the microcontroller unit integrated with the SIMCOM technologies SIM800l as the GSM gateway module and Ublox's NEO 6M GPS reciever module. the gps module recieve the signals from the GPS satellites and process them to give the location of the the Ublox's recieving node and the real time in the nmea data format.
gsm module is interfaced with controller by the uart serial interface, the gsm module can be programed using the at commands to perform actions such as handling the short message service (SMS) and handling the call over the 2G gsm network.

the microcontroller is programmed in such a way to optimize the low power consumption of the entire integrated system, all the processing script is written inside the interruptt service routine hence when there is an interrupt present only then the controller processes the task. gps module generates the interrupt when it succesfully calculates the nmea data and the gsm module is programmed to generate an interrupt signal when
any kind of data is recieved via the gsm node i.e during the reception of the sms  and the call.

when there is no interrupt present the controller is now operating in the sleep mode in these mode the clock to the all special functional peripheral's has been withdrawn that result's in the reduction in the power consumption of the controller system. the gsm and gps modele already programmed to work in the low power consumption mode setting.

again when the any incomming call or the message is detected  the controller wake's up from the sleep mode and processes the data and sends the message to the farmers phone containing the information about the lattitude and longitude coordinates data via gsm, the gsm module requires a subscriber identity module (SIM) to perform these activities of sending and recieving the call's and sms.

whole unit is powered by the li-ion battery pack and can be recharged using the TP4056 charging module. 



Hardware used : STM32F103C8T6, SIMCOM SIM800l, Ublox Neo 6M, TP4056, li-ion batteries 2400mAh
Software uses : Keil uVision 


