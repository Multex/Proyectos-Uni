#include <16f877a.h>
#fuses xt
#use delay(clock = 4M)
/**************************/
#byte trisb = 0x86
#byte trisc = 0x87
#byte portb = 0x06
#byte portc = 0x07
#bit P1 = portc.0 // Botón 1
#bit P2 = portc.1 // Botón 2
#bit UNI = portc.2 // Variable para las unidades
#bit DEC = portc.3 // Variable para las decenas
/**************************/
void main() {
   trisb = 0b00000000;
   trisc = 0b00000011;
   
   // Array de números en binario
   int datos[10] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001,
                    0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000};
   int contador = 0; // Contador de los números a mostrar
   int R, U, D; // Variables para la conversión de números
   
   while(true) {
      UNI = 1; DEC = 0; //* Muestra las unidades
      portb = datos[contador]; //* Muestra el número en el display

      if(P1 == 0) { //* Si se presiona el botón 1
         contador++; // Incrementa el contador

         if(contador == 10) {contador = 0;} // Si el contador llega a 10, se reinicia
         portb = datos[contador]; // Muestra el número en el display

         while(P1 == 0) { } // Anti-rebote
      }
      
      if(P2 == 0) { //* Si se presiona el botón 2
         R = contador * 6; // Realiza la conversión de números
         D = R / 10; // Obtiene las decenas
         U = R % 10; // Obtiene las unidades

         for(int t=0; t<30; t++) { // Tiempo de visualización
            // Muestra las decenas
            DEC = 1;
            portb = datos[D];
            delay_ms(50);
            DEC = 0;
            
            // Muestra las unidades
            UNI = 1;
            portb = datos[U];
            delay_ms(50);
            UNI = 0;
         }
      }
   }
}
