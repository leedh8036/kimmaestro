#include <wiringPi.h>
#include <stdio.h>

#define 	SDI	0
#define		RCLK	1
#define		SRCLK	2

unsigned char LED[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void pulse(int pin)
{
	digitalWrite(pin, 0);
	digitalWrite(pin, 1);
}

void SIPO(unsigned char byte)
{
	int i;

	for(i=0;i<8;i++){
		digitalWrite(SDI, ((byte & (0x80 >> i)) > 0));
		pulse(SRCLK);
	}
}

void init(void)
{
	pinMode(SDI, OUTPUT);
	pinMode(RCLK, OUTPUT);
	pinMode(SRCLK, OUTPUT);

	digitalWrite(SDI, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);
}

int main(void)
{
	int i;

	if(wiringPiSetup() == -1){
		printf("setup wiringPi failed !");
		return 1;
	}

	init();

	while(1){
		for(i=0;i<8;i++){
			SIPO(LED[i]);
			pulse(RCLK);
			delay(150);

		}
		delay(500);

		for(i=0;i<3;i++){
			SIPO(0xff);
			pulse(RCLK);
			delay(100);
			SIPO(0x00);
			pulse(RCLK);
			delay(100);
		}
		delay(500);
	}

	return 0;
}


