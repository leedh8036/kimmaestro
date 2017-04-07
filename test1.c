#include <stdio.h>
#include <wiringPi.h>

#define LED1 1 // BCM_GPIO 18

int main(void)
{
if(wiringPiSetup () == -1)
return 1;

pinMode(LED1,OUTPUT);

for(;;)
{
digitalWrite(LED1,1); // On

delay(1000);

digitalWrite(LED1,0);

delay(1000);
}
return 0;
}
