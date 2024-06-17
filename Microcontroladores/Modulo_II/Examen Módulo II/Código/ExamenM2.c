#include <16f877a.h>
#fuses xt
#use delay(clock = 4M)
#byte trisb = 0x86
#byte trisc = 0x87
#byte portb = 0x06
#byte portc = 0x07
#bit P1 = portc.0
#bit P2 = portc.1
#bit UNI = portc.2
#bit DEC = portc.3

void main() {
   trisb = 0b00000000;
   trisc = 0b00000011;
   
   int datos[10] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001,
                    0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000};
   int contador = 0;
   int R, U, D;
   
   while(true) {
      UNI = 1; DEC = 0;
      portb = datos[contador];
      if(P1 == 0) {
         contador++;
         if(contador == 10) {contador = 0;}
         portb = datos[contador];
         while(P1 == 0) { }
      }
      
      if(P2 == 0) {
         R = contador * 6;
         D = R / 10;
         U = R % 10;
         for(int t=0; t<30; t++) {
            DEC = 1;
            portb = datos[D];
            delay_ms(50);
            DEC = 0;
            UNI = 1;
            portb = datos[U];
            delay_ms(50);
            UNI = 0;
         }
      }
   }
}
