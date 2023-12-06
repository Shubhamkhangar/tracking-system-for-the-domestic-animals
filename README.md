# Tracking System for Domestic Animals based on ARM Cortex M3

This project introduces a tracking belt for domestic animals, employing an ARM Cortex M-3 microcontroller, SIMCOM GSM, and UBLOX NEO 6M GPS. The system tracks animal locations, monitors environmental conditions, and communicates data to a remote receiver via GSM. Key features include power-efficient operation, battery monitoring, temperature sensing, and continuous tracking updates. The project aims to enhance animal safety, facilitate quick retrieval, and contribute to animal behavior studies through real-time monitoring and data collection.

The ARM Cortex M3-based MCU is programmed to register levels from scratch, and the controller is configured to connect with the gsm and gps modules with a UART-wired communication protocol.
The code for the project is provided in this repository. The controller is programmed to work in power consumption settings, and the flow of the code is an interrupt driver; hence, when there is no interrupt from any of the modules connected, the mcu can now operate in sleep mode, consuming less power by deactivating some of the units inside.

The user needs to request the system for its location data in the form of either a GPS call or a normal message from a registered mobile number, and after successfully receiving the request from the user, the MCU processes the GPS data and sends it to the user's registered mobile number along with some additional information such as the battery percentage of the system and the system's internal temperature.

#Click on the below buttons to jump to specific folders where the codes are stored.

[![Static Badge](https://img.shields.io/badge/Code-blue)](code.c)

# Hardware  
![Static Badge](https://img.shields.io/badge/ARM_CORTEX_M3-white)![Static Badge](https://img.shields.io/badge/STM32F103C8T6-blue)![Static Badge](https://img.shields.io/badge/SIM800l-red)![Static Badge](https://img.shields.io/badge/Ublox_Neo_6M-violet)



# Software  
![Static Badge](https://img.shields.io/badge/Keil_uVision5-green)![Static Badge](https://img.shields.io/badge/Ublox_Ucenter_2.0-white)





