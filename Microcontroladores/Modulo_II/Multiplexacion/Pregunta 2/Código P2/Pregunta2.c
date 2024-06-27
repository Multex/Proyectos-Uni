#include <16f877a.h>
#fuses xt
#use delay(clock = 4M)
/**************************/
#byte trisb = 0x86
#byte trisc = 0x87
#byte portb = 0x06
#byte portc = 0x07
#bit T4 = portc.3
/**************************/
void main(){
   
   // Array de números en binario
   int datos[10] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001,
                    0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000};
   int i;
   
   trisb = 0b00000000;
   trisc = 0b00000000;
   portb = 0x00;
   portc = 0x00;
   
   while(true){
      //* Ciclo para mostrar los números en el display
      for(i = 0; i < 10; i++) { // Unidades
         T4 = 1;
         portb = datos[i];
         delay_ms(500);
         T4 = 0;
      }
   }
}
