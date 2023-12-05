# Tracking System for Domestic Animals based on ARM Cortex M3
It is an embedded system project based on the idea of tracking the exact location of the animals from the farmer's mobile phone.
This embedded system project is designed using the ARM Cortex M3-based STM32F103C8T6 as the microcontroller unit integrated with the SIMCOM technology's SIM800l as the GSM module and Ublox's NEO 6M GPS receiver module. The GPS module receives the signals from the GPS satellites and processes them to give the location of the Ublox's receiving antenna node and the real-time data in the NMEA format. The gsm module is interfaced with the controller by the UART serial interface. The gsm module can be programmed using the AT commands to perform actions such as handling the short message service (SMS) and handling the call over the 2G gsm network.
The microcontroller is programmed in such a way as to optimize the low power consumption of the entire integrated system; all the processing script is written inside the interrupt service routine; hence, when there is an interrupt request present, only then does the controller process the task. The GPS module generates the interrupt when it successfully calculates the nmea data and the location data, and the internal clock of the ublox module is synchronized with the calculated clock time after processing the signal coming from the satellite's revolving around the earth. The gsm module is programmed to generate an interrupt signal when any kind of activity is detected on the gsm node, i.e., during the reception of the SMS and the call.
When there is no interruption present, the controller operates in sleep mode. In this mode, the clock for all special functional peripherals has been withdrawn, resulting in a reduction in the power consumption of the controller system. The GSM and GPS models are already programmed to work in the low power consumption mode setting.
Again, when any incoming call or message is detected, the controller wakes up from sleep mode, processes the data, and sends the message to the farmer's phone containing the information about the latitude and longitude coordinates via gsm. The gsm module requires a subscriber identity module (SIM) to perform these activities of sending and receiving the call's and SMS.
The whole unit is powered by the Li-ion battery pack and can be recharged using the TP4056 charging module.



# Hardware  
![Static Badge](https://img.shields.io/badge/STM32F103C8T6-blue)![Static Badge](https://img.shields.io/badge/SIM800l-red)![Static Badge](https://img.shields.io/badge/Ublox_Neo_6M-violet)


# Software  
![Static Badge](https://img.shields.io/badge/Keil_uVision5-green)![Static Badge](https://img.shields.io/badge/Ublox_Ucenter_2.0-white)





