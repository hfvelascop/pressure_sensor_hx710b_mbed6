
#include "mbed.h"
DigitalIn ADDO(A0); //OUT
DigitalOut ADSK(A1); //SCK
float pressure;

float ReadPressure(void){
    int Count;
    unsigned char i;
    float sample;
    ADSK=0;
    Count=0;
    
    while(ADDO); //Until ADDO is high the data are not ready

    for (i=0;i<24;i++){
        ADSK=1;
        Count=Count<<1;
        wait_us(1);
        ADSK=0;
        if(ADDO) Count++;
        wait_us(1);
    }
    ADSK=1;
    wait_us(1);
    Count=Count<<8;
    ADSK=0;
    wait_us(1);
    sample=Count/2147483647.0;
    return(sample);
}


// main() runs in its own thread in the OS
int main()
{
    pressure=0.0;
    ADSK=1;
    wait_us(70);
    ADSK=0;
    while (true) {
        pressure=ReadPressure();
        pressure=pressure*40.0;
        printf("C2: %3.3f [%16X]\n\r", pressure, pressure);
        wait_us(10);
    }
}


