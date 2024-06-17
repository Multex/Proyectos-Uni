#include <16f877a.h>
#fuses xt
#use delay(clock = 4M)
#byte trisb = 0x86
#byte trisc = 0x87
#byte portb = 0x06
#byte portc = 0x07
#bit T2 = portc.1
#bit T3 = portc.2
#bit T4 = portc.3

void main() {
   
   int datos[10] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001,
                    0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000};
   int i;
   int j;
   int k;
   int t;
   
   trisb = 0b00000000;
   trisc = 0b00000000;
   portb = 0b00000000;
   portc = 0b00000000;
   
   while(true){
      for(k=0; k<10; k++) {
         for(j=0; j<10; j++) {
            for(i=0; i<10; i++) {
               for(t=0; t<10; t++) {
                  T4 = 1;
                  portb = datos[i];
                  delay_ms(25);
                  T4 = 0;
                  
                  T3 = 1;
                  portb = datos[j];
                  delay_ms(25);
                  T3 = 0;
                  
                  T2 = 1;
                  portb = datos[k];
                  delay_ms(25);
                  T2 = 0;
               }
            }
         }
      }
   }
}
