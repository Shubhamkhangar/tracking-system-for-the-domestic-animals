# tracking-system-for-the-domestic-animals
it is an embedded system project based on the idea of tracking the exact location of the animals from the farmer's mobile phone.
this embedded system project is designed using the ARM Cortex M3-based STM32F103C8T6 as the microcontroller unit integrated with the SIMCOM technology's SIM800l as the GSM module and Ublox's NEO 6M GPS receiver module. the GPS module receives the signals from the GPS satellites and processes them to give the location of the Ublox's receiving antenna node and the real-time data in the NMEA format. gsm module is interfaced with the controller by the UART serial interface, the gsm module can be programmed using the AT commands to perform actions such as handling the short message service (SMS) and handling the call over the 2G gsm network.
the microcontroller is programmed in such a way as to optimize the low power consumption of the entire integrated system, all the processing script is written inside the interrupt service routine hence when there is an interrupt request present only then the controller processes the task. GPS module generates the interrupt when it successfully calculates the nmea data and the location data and the internal clock of the ublox module is synchronized with the calculated clock time after processing the signal coming from the satellite's revolving around the earth and the gsm module is programmed to generate an interrupt signal when any kind of activity is detected on the gsm node i.e during the reception of the sms and the call.
when there is no interruption present the controller operates in sleep mode in this mode the clock to all special functional peripherals has been withdrawn resulting in a reduction in the power consumption of the controller system. The GSM and GPS models are already programmed to work in the low power consumption mode setting.
again when any incoming call or message is detected the controller wakes up from sleep mode processes the data and sends the message to the farmer's phone containing the information about the latitude and longitude coordinates data via gsm, the gsm module requires a subscriber identity module (SIM) to perform these activities of sending and receiving the call's and sms.
the whole unit is powered by the Li-ion battery pack and can be recharged using the TP4056 charging module.



# Hardware used 
STM32F103C8T6, SIMCOM SIM800l, Ublox Neo 6M, TP4056, li-ion battery 2400mAh

# Software uses  
Keil uVision for programming and debuging the microcontroller unit 


