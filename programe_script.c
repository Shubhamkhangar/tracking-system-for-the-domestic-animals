/*
author     - Shubham Anil Khangar
Course     - Msc(Electronics Science) 
University - Savitribai Phule Pune Unniversity
Proejct    - Tracking Belt For The Domestic Animals Using ARM Cortex M-3, SIMCOM GSM, UBLOX NEO 6M GPS 
Date       - 30 june 2023
*/
 

/*Library included here */
#include "stm32f10x.h"
#include <string.h>
#include <stdlib.h>

/*Global Function and Varible declaration*/
void delay(int n);
void u1_init(void);   //gsm module is connected with the U1
void u1_print(char*); //gps module is connected to the U2
void u1_txChar(char);
void u2_init(void);
void u2_print(char*);
void u2_txChar(char);
void intr_adc_init(void);
void intr_adc_ck(void);
void gsm_confg(void);
void gsm_msg(void);
void batCheck(void);
void bat_extract(void);

void NMEA_Degree(char array[12],char y);
void gts(void);


char u1_buff[100];
char u1_ptr=0;
char u2_buff[300];
char u2_ptr=0;
char clip[]="+CLI";
char cbc[] ="+CBC";
//char gps[]="$GPGGA";
char gps[]="$GPRMC";
char lat[12];
char lng[12];
char msg[150];
char bat[4];
char y_ar[]="0";
char x;
char tmprg[5];
int adc;
double volt,tempr;
char z=0;

int main()
{
RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN;
RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
GPIOA->CRL &= 0x00000000;
GPIOA->CRH &= 0x00000000;
GPIOA->CRL |= 0x00008B33;    //PA0-1 as out and  PA2-TX2 PA3-RX2
GPIOA->CRH |= 0x000008B0;   //PA9-TX1 and PA10-RX1	
GPIOC->CRH &= 0x00000000;
GPIOC->CRH |= 0x00300000;
	GPIOA->ODR |= 0x1;
	u1_init();
	u2_init();
	intr_adc_init();
	gsm_confg();
	GPIOA->ODR &= ~0x1;
	batCheck();
	bat_extract();
	intr_adc_ck();
	//gsm_msg();    //very first message
	delay(1000);
	x=0;
	u2_print("\nentering into the loop->");
  //loop for contineous functioning 
	while(1)
{    //u2_print("\ngood morning\n");
		 if(x==1){
			USART2->CR1 |= USART_CR1_RE;
			delay(100);
			u2_print("\n");
			u2_print(u1_buff);
			GPIOC->ODR &= ~0x2000; //PA1 blink
			u1_print("ATA\n\r");
			delay(5000);
			u1_print("ATH\n\r");
			u1_ptr=0;
			memset(u1_buff,0,100);
			delay(1000);
			batCheck();
			delay(2000);
			bat_extract();
			delay(500);
			//gsm_msg();
			//delay(5000);
			GPIOC->ODR |= 0x2000; //PA1 blink
			x=0;
		        }
		  else if(x==2){
			u2_print("\n");
                        u2_print(u2_buff);			
			GPIOC->ODR &= ~0x2000; //PA1 blink
			for(char ptr=0;ptr<10;ptr++){
			 lat[ptr]=u2_buff[ptr+19];
				                    }	
		         for(char pt=0;pt<10;pt++){
			 lng[pt]=u2_buff[pt+32];
					          }
			
			    
		         NMEA_Degree(lat,1);
		         delay(100);
		    	 NMEA_Degree(lng,2);
           		 delay(100);
			 u2_print("\ncoordinates: ");
                         u2_print(lat);
			 u2_print(",");							 
		         u2_print(lng);
          		 delay(500);										
		         GPIOC->ODR |= 0x2000; //PA1 blink			
		         x=0;
			 //gsm_msg();
			 memset(u2_buff,0,300);
		         u2_ptr=0;
			 //if(z==4){
             		 USART2->CR1 &= ~USART_CR1_RE;
			 x=3;
			 u2_print("\nrecording gps data stoped");
			// }  					
		             }	
		 else if(x==3){
			 delay(1000);
			 batCheck();
			 delay(1000);
			 bat_extract();
			 delay(1000);
			 intr_adc_ck();
			 u2_print("\n sending the sms");
			 delay(2000);
			 gsm_msg();
			 delay(2000);
			 memset(lat,0,12);	
	                 memset(lng,0,12);
			 x=0;
		           }
		
    		else {
		//z++;
		//u2_print();
		//if there is nothing to do then go to sleep mode for power saving 
		gts(); }
	}
}		


void delay(int n)
{
	 SysTick->LOAD = 72000;
	 SysTick->VAL =0;
	 SysTick->CTRL = 0x5;
	 for(int c=0;c<n;c++)
	   {
			while(!(SysTick->CTRL & 0x10000));
     }			 
		SysTick->CTRL = 0x0;		 
}


//GSM Module is connected to the Usart1
void u1_init()
{
 USART1->BRR = 0x1D4C;
 USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_RXNEIE;
 NVIC_SetPriority(USART1_IRQn,0);	
 NVIC_EnableIRQ(USART1_IRQn);
 __enable_irq();
 USART1->CR2 |= 0x0000;
 USART1->CR3 |= 0x0000;
 USART1->CR1 |= USART_CR1_UE;                 //activating the usart1 system
}


//GPS Module is connected with the Usart2 
void u2_init()
{
 USART2->BRR = 0xEA6;
 USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_RXNEIE ; //RX and TX enabled
 NVIC_SetPriority(USART2_IRQn,1);
 NVIC_EnableIRQ(USART2_IRQn);
 __enable_irq();
 USART2->CR2 |= 0x0000;
 USART2->CR3 |= 0x0000;
 USART2->CR1 |= USART_CR1_UE;                                  //activating the usart1 system
}


//initialiazing the uart1 module 
void u1_print(char *print1)
{
 while(*print1)
      {
	    u1_txChar(*print1++);			
			}   	
} 
void  u1_txChar(char TXD1)
{
 while(!(USART1->SR & USART_SR_TC));
 USART1->DR = TXD1;	
}


void u2_print(char *print2)
{
 while(*print2)
      {
	    u2_txChar(*print2++);			
			}
		 //memset(u2_buff,0,50);
		 //u2_ptr=0;	
}
void  u2_txChar(char TXD2)
{
 while(!(USART2->SR & USART_SR_TC));
 USART2->DR = TXD2;	
}


//function to configure the gsm module with the at commands
void gsm_confg()
{
 u1_print("AT\n\r");
 delay(2000);	
 u1_print("AT+IPR=9600\n\r");
 delay(2000);	
 u1_print("AT+CMGF=1\n\r");
 delay(2000);
 u1_print("AT+CNMI=1,2,0,0,0\n\r");
 delay(2000);	
 u1_print("AT+CLIP=1\n\r");
 delay(2000);	
 u1_print("ATD+ +919823366535;\n\r");
 delay(20000);
 u1_print("ATH\n\r");
 delay(5000);
 memset(u1_buff,0,100);
 u1_ptr=0;
}


//GSM Module Responce Handler
void USART1_IRQHandler(void)
{ 	
	 if(USART1->SR & USART_SR_RXNE){
		 u1_buff[u1_ptr++] = USART1->DR;
	
		 if(u1_ptr-1 <= 3)
			 {
			 if(! ((u1_buff[u1_ptr-1] == clip[u1_ptr-1]) || (u1_buff[u1_ptr-1] == cbc[u1_ptr-1])) )   
				{
					u1_ptr=0;
				}
			 }		 
	  		else if(u1_ptr > 15)
		 {
	       if(strstr(u1_buff,clip)){
				 x=1;
			 }
		 }	
		 }
}


//GPS Module Responce Handler
void USART2_IRQHandler(void)
{ 
	 if(USART2->SR & USART_SR_RXNE){
			u2_buff[u2_ptr++]= USART2->DR;
     if(u2_ptr-1 <= 5)
		 { 
       if(u2_buff[u2_ptr-1] != gps[u2_ptr-1])
         { u2_ptr=0;}			 	
		 }			 
		  else if(u2_ptr>80){
		   x=2;
			 //z++;
				}	 
      // u2_ptr++;
} 
}


//function to generate the message and sending it to recievers end using the gsm network
void gsm_msg()
{
strcat(msg,"Tracking Device Response");
strcat(msg,"\nCharge Remaining_");
strcat(msg,bat);
strcat(msg,"\nTemprature_");
strcat(msg,tmprg);
strcat(msg,"degC\nhttp://maps.google.com/maps?q=loc:");
strcat(msg,lat);
strcat(msg,",");
strcat(msg,lng);
u1_print("AT+CMGS=\"+919823366535\"\n\r");
delay(100);	
u1_print(msg);
delay(10);
u1_txChar(0x1A);
delay(500);
memset(msg,0,150);
delay(1000);
u1_ptr=0;
memset(u1_buff,0,100);
}	


//AT command to get the battery charge Capacity Data
void batCheck()
{ delay(2000);
	u1_print("AT+CBC\n\r");
	delay(2000);	
	//intr_adc_ck();
}


void bat_extract()
{   
	    //u2_print(u1_buff); responce from the bat command
      char *y = strstr(u1_buff,y_ar);
      *y++;
			*y++;
			bat[0] =*y;
			*y++;
      bat[1] =*y;
      bat[2] = '%';			
			u1_ptr=0;
			memset(u1_buff,0,100);
	    u2_print("bat");	
      u2_print(bat);	
}


//For Converting the NMEA data to the degree Format for the further use in the google map
void NMEA_Degree(char array[12],char y)
{
 float decimal_value,temp,position;
 long int degree;
 float F_data = atof(array);
 decimal_value = (F_data / 100);
 degree = (int) (decimal_value);
 temp = (decimal_value - (int)decimal_value)/0.6;
 position = (float)degree + temp;
 if(y==1){
	 sprintf(lat,"%f",position);
	 y=0;
 }
 else if(y==2){
	  sprintf(lng,"%f",position);
	  y=0;
}
}

//function to initializing the sleep mode 
void gts()
 {
 RCC->APB1ENR |= RCC_APB1ENR_PWREN; //enabling the power controll reg clock
 SCB->SCR &= ~SCB_SCR_SLEEPDEEP;    //sleep
 SCB->SCR &= ~SCB_SCR_SLEEPONEXIT; // Do not sleep when returning to Thread mode
 u2_print("\ngoing to sleep\n");
 delay(1000);	
 __WFI();
 }
 
 
//function to initialize the internal adc module present in the cortex M3
 void intr_adc_init(void)
{
RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;    //divide the fre. s.t it will not exceed the14 mhz	
RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;  //ADC1 enabled
ADC1->CR2 |= ADC_CR2_TSVREFE;       //enabled the int.temprature sensor
ADC1->SMPR1 |= 0x001C0000;         //sampling the channel connected to the sensor
ADC1->SQR3 |= 16;                 //CH16 first priority
ADC1->SQR1 |= 0;                 //one conversion only
ADC1->CR1 |= ADC_CR1_SCAN;      //adcin scan mode
ADC1->CR2 |= ADC_CR2_EXTTRIG;  //external triggering enabled
ADC1->CR2 |= 0xE0000;         //swstart as start method
//ADC1->CR2 |= ADC_CR2_CONT | ADC_CR2_ADON; //adc in cont mode
ADC1->CR2 &=  ~ADC_CR2_ADON;
delay(1);
ADC1->CR2 |= ADC_CR2_ADON;
delay(1);
} 

//function to read adc data
void intr_adc_ck(void)
{
	ADC1->CR2 |= ADC_CR2_SWSTART;
	while(!(ADC1->SR & ADC_SR_EOC));
    adc = ADC1->DR;
	  volt = (double) adc*0.0008056;
	  tempr = ((1.43 - volt)/4.3)+25;
	  sprintf(tmprg,"%lf",tempr);
	  u2_print("\ntemprature-->");
	  u2_print(tmprg);
}
