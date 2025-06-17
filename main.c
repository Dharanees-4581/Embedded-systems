#include <LPC21xx.h>

#include "types.h"

#include "spi.c"

#include "mcp3208.c"

#include "4_bit_mode.c"

#include "GSM_MSG.c"

#include "DC_Motor.c"

#include "rtc.c"

unsigned char ptr = (unsigned char )0x80;

int main()

{	int flag=1,i=0,j;

    u8 hr,sec,min;

    f32 f;

	char display_Text[50]="Weather Monitoring System";

	

	Init_SPI0(); 

	LCD_INIT();

	init_i2c();	

	UART0_config();
		motot_init();
	
//	str("V24CE3D1");
    //        Delay_milliseconds(1000);

	IOPIN0 |= 1<<7;



	while(1)

    {

	 

     LCD_COMMAND(0x01);

	 LCD_COMMAND(0x80);

	 hr=i2c_rtc_read(0X68,0X02);

	 

	 min=i2c_rtc_read(0X68,0X01);

	 

	 sec=i2c_rtc_read(0X68,0X00);


	 

	 

    for (i = 0; i < strlen(display_Text) - 16; i++) 

        {

            LCD_COMMAND(0x80); // Move cursor to first line


            // Print substring of display_Text (16 characters at a time)

            for (j = 0; j < 16; j++) 

            {

                LCD_DATA(display_Text[i + j]);  

            }
			
			LCD_COMMAND(0xc0);
			str("V24CE3D1");
            Delay_milliseconds(300); // Adjust speed of scrolling


			 

		

        }	 


	 	 f=Read_ADC_MCP3208(0);

		 LCD_COMMAND(0x01);

		  LCD_COMMAND(0x80);

		  str("RTC: ");

		 LCD_DATA((hr/16)+48);

		 LCD_DATA((hr%16)+48);

		 LCD_DATA(':');

		 LCD_DATA((min/16)+48);

		 LCD_DATA((min%16)+48);

		 LCD_DATA(':');

		 LCD_DATA((sec/16)+48);

		 LCD_DATA((sec%16)+48);

		LCD_COMMAND(0xc0);

		Float_display(f);
		Delay_milliseconds(500);

		if(f>32.0&&flag)

		{

		  UART0_STR("AT\r\n");

	      Delay_milliseconds(1000);

	      UART0_STR("AT+CMGF=1\r\n");

	      Delay_milliseconds(1000);

	      UART0_STR("AT+CMGS=\"+91\"\r\n");

	      Delay_milliseconds(1000);

	      UART0_STR("Temperature Exceeds 32 celcius\r\n");

	      UART0_TX(0x1A);

	      Delay_milliseconds(1000);

		  motor_run();

		  delay_motor(5);

		  motor_stop();

		  flag=0;	

		}  

		

	 }	


	  

	

}

					
