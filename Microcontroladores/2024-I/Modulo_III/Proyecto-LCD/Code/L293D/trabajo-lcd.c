#include <16f877a.h>
#fuses XT
#use delay(clock=4M)
/*******************/
#byte trisa = 0x85
#byte porta = 0x05
#byte trisb = 0x86
#byte portb = 0x06
/*******************/
#bit C1 = portb.5
#bit C2 = portb.6
#bit C3 = portb.7
#bit F1 = portb.0
#bit F2 = portb.1
#bit F3 = portb.2
#bit F4 = portb.3
/*******************/
#define LCD_ENABLE_PIN  PIN_D3
#define LCD_RS_PIN      PIN_D1
#define LCD_RW_PIN      PIN_D2
#define LCD_DATA4       PIN_D4
#define LCD_DATA5       PIN_D5
#define LCD_DATA6       PIN_D6
#define LCD_DATA7       PIN_D7
#include <lcd.c>
/*******************/
int key = 12; //* Keypad (solo para saber que tecla es) - Valor maximo 11
int digit; //* Valor numerico de la tecla presionada
int ONES = 0; // Unidades
int TENS = 0; // Decimas
int digitFix; //* Fix digits - Usado para tomar los dos digitos
/*******************/
void keyDetection(){ //* Usado para detectar la tecla presionada
    C1 = 1;
    if (F1 == 1){key = 1; digit = 1; while(F1 == 1){};}
    if (F2 == 1){key = 4; digit = 4; while(F2 == 1){};}
    if (F3 == 1){key = 7; digit = 7; while(F3 == 1){};}
    if (F4 == 1){key = 10;} // "*" -> Clear/Stop | Limpiar/Parar
    C1 = 0;

    C2 = 1;
    if (F1 == 1){key = 2; digit = 2; while(F1 == 1){};}
    if (F2 == 1){key = 5; digit = 5; while(F2 == 1){};}
    if (F3 == 1){key = 8; digit = 8; while(F3 == 1){};}
    if (F4 == 1){key = 0; digit = 0; while(F4 == 1){};}
    C2 = 0;

    C3 = 1;
    if (F1 == 1){key = 3; digit = 3; while(F1 == 1){};}
    if (F2 == 1){key = 6; digit = 6; while(F2 == 1){};}
    if (F3 == 1){key = 9; digit = 9; while(F3 == 1){};}
    if (F4 == 1){key = 11; while(F4 == 1){};} // "#" -> Start | Iniciar
    C3 = 0;
}

void motorControl(){ //* Usado para controlar el motor
    porta = 0b00000010; // Manda señal a A1
    delay_ms(80);
    porta = 0b00000001; // Manda señal a A0
    delay_ms(80);
}

void main(){
    trisa = 0b00000000;
    trisb = 0b00001111;
    porta = 0x00; // Empieza con el motor apagado

    lcd_init(); // Inicializar el LCD

    // Mensaje de bienvenida
    lcd_gotoxy(1, 1);
    lcd_putc("  ENCENDIDO DE  ");
    lcd_gotoxy(1, 2);
    lcd_putc("    MOTOR DC    ");
    delay_ms(3000); // 3 segundos
    lcd_putc("\f"); // Limpiar el LCD

    while(true){
        keyDetection(); // Llamamos la funcion para detectar la tecla presionada
        
        if(key < 10){ //* Se activa si la tecla presionada es un número
            TENS = ONES;
            delay_ms(100);
            ONES = digit;
            delay_ms(100);

            digitFix = (TENS * 10) + ONES; //* Para tomar los dos digitos
        }
        if(key == 11){ //* 11 = "#" -> Start | Iniciar
            motorControl(); // Llamamos la funcion para controlar el motor
            
            lcd_putc("\f"); // Limpiamos el LCD

            int stableDigit = digitFix; //* Para mantener el valor de digitFix
            
            for(int i=0; i < stableDigit; i++){ // For loop para contar el tiempo
                keyDetection(); // Llamando la funcion de nuevo
                
                if(key == 10){break;} //* 10 = "*" -> Stop | Parar

                lcd_gotoxy(1, 1);
                printf(lcd_putc, "Motor: On");
                lcd_gotoxy(1, 2);
                printf(lcd_putc, "Tiempo: %02u", digitFix); // Ver: https://i.imgur.com/FZfBf59.png

                digitFix--;
                delay_ms(920); // 920(De este for loop) + 80(De la funcion motorControl) = 1 segundo
            }

            //* Resetear los valores despues del loop para evitar errores en el lcd
            ONES = 0;
            TENS = 0;
            digitFix = 0;

            porta = 0; // Apagamos el motor
        }
        if(key == 10){ //* 10 = "*" -> Clear | Limpiar
            TENS = 0;
            ONES = 0;
            digitFix = 0;
        }

        // Mensaje por defecto
        lcd_gotoxy(1, 1);
        lcd_putc("Motor: Off");
        lcd_gotoxy(1, 2);
        printf(lcd_putc, "Tiempo: %02u", digitFix);

        key = 12; // Resetear el valor de la tecla
    }
}