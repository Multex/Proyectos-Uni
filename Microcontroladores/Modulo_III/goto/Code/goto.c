#include <16f877a.h>
#fuses XT
#use delay(clock=4M)
/*******************/
#byte trisb = 0x86
#byte portb = 0x06
#byte trisc = 0x87
#byte portc = 0x07
/*******************/
#bit PUL1 = portb.0
#bit PUL2 = portb.1
#bit RC0 = portc.0
#bit RC1 = portc.1
#bit RC2 = portc.2
#bit RC3 = portc.3
/*******************/
void main(){
    trisb = 0b00000011;
    trisc = 0b00000000;
    portc = 0b00000000;

    while(true){
        if(PUL1 == 1){
            LOOP1:
            while(true){
                portc = 0b00001111;
                delay_ms(100);
                portc = 0b00000000;
                delay_ms(100);
                if(PUL2 == 1){
                    break;
                    goto LOOP2;
                }
            }
        }
        if(PUL2 == 1){
            LOOP2:
            while(true){
                portc = 0b00001000;
                delay_ms(100);
                portc = 0b00000100;
                delay_ms(100);
                portc = 0b00000010;
                delay_ms(100);
                portc = 0b00000001;
                delay_ms(100);
                if(PUL1 == 1){
                    break;
                    goto LOOP1;
                }   
            }
        }
    }
}