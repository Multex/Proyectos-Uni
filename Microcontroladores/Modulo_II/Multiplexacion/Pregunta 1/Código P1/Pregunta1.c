#include <16f877a.h>
#fuses xt
#use delay(clock = 4M)
/**************************/
#byte trisb = 0x86
#byte trisc = 0x87
#byte portb = 0x06
#byte portc = 0x07
#bit T1 = portc.0
#bit T2 = portc.1
#bit T3 = portc.2
#bit T4 = portc.3
/**************************/
void main(){
   
   trisb = 0b00000000;
   trisc = 0b00000000;
   portb = 0x00;
   portc = 0x00;
   
   //? No tengo idea de que haga esto
   while(true) {
      T2 = 1;
      portb = 0b11000111;
      delay_ms(10);
      T2 = 0;
      
      T3 = 1;
      portb = 0b10000110;
      delay_ms(10);
      T3 = 0;
      
      T4 = 1;
      portb = 0b11000000;
      delay_ms(10);
      T4 = 0;
   }
}
