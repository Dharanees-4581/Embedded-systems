#include<lpc21xx.h>	
#define motor_pin1 1<<12

#define motor_pin2 1<<13

void delay_motor(int );
void motor_run(void);
void motor_stop(void);
void motot_init(void);



void delay_motor(int s)

{

	T0PR=15000000-1;

	T0TCR =0x01;

	while(T0TC<s);

	T0TCR=0x03;

	T0TCR=0x00;

}


void motor_run(void)

{

	IOSET0=motor_pin1;

	IOCLR0=	motor_pin2;

}


void motor_stop(void)

{

    IOCLR0=motor_pin1;

	IOCLR0=	motor_pin2;		

}

void motot_init(void)

{

	IODIR0|=motor_pin1|motor_pin2;

}
