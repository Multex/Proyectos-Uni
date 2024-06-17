#include <16f877a.h>
#fuses XT
#use delay(clock=4M)
/*******************/
#byte trisb = 0x86
#byte portb = 0x06
#byte trisc = 0x87
#byte portc = 0x07
#byte trisd = 0x88
#byte portd = 0x08
/*******************/
#bit C1 = portc.0
#bit C2 = portc.1
#bit C3 = portc.2
#bit F1 = portd.4
#bit F2 = portd.5
#bit F3 = portd.6
#bit F4 = portd.7
/*******************/
void main(){
    trisb = 0b00000000;
    trisc = 0b00000111;
    trisd = 0b00000000;
    portb = 0b11111111;

    while(true){
        portd = 0b11100000;
        delay_ms(10);
        if(C1 == 0){portb = 0b11111001;}
        delay_ms(10);
        if(C2 == 0){portb = 0b10100100;}
        delay_ms(10);
        if(C3 == 0){portb = 0b10110000;}
        delay_ms(10);
        portd = 0b11010000;
        delay_ms(10);
        if(C1 == 0){portb = 0b10011001;}
        delay_ms(10);
        if(C2 == 0){portb = 0b10010010;}
        delay_ms(10);
        if(C3 == 0){portb = 0b10000010;}
        delay_ms(10);
        portd = 0b10110000;
        delay_ms(10);
        if(C1 == 0){portb = 0b11111000;}
        delay_ms(10);
        if(C2 == 0){portb = 0b10000000;}
        delay_ms(10);
        if(C3 == 0){portb = 0b10011000;}
        delay_ms(10);
        portd = 0b01110000;
        delay_ms(10);
        if(C1 == 0){portb = 0b10001000;}
        delay_ms(10);
        if(C2 == 0){portb = 0b10000011;}
        delay_ms(10);
        if(C3 == 0){portb = 0b11000110;}
        delay_ms(10);
        portd = 0b11110000;
        delay_ms(10);
    }
}
