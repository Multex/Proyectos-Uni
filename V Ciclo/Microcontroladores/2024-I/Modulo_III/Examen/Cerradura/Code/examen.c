#include <16f877a.h>
#fuses XT
#use delay(clock=4M)
/********************/
#byte trisb = 0x86
#byte portb = 0x06
#byte trisc = 0x87
#byte portc = 0x07
/********************/
#bit C1 = portb.5
#bit C2 = portb.6
#bit C3 = portb.7
#bit F1 = portb.0
#bit F2 = portb.1
#bit F3 = portb.2
#bit F4 = portb.3
#bit LED = portc.0 // Puerto para el led
#bit MT = portc.7 // Puerto para el motor
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

//* NUNCA LLAMAR A ESTA VARIABLE "input", EL PEOR ERROR DE MI VIDA
int inputs[3]; // Arreglo para guardar la entrada del usuario

int pswd[3] = {4, 7, 3}; // Arreglo para guardar la clave
int attempts = 0; // Contador de intentos

void keyDetection(){ //* Usado para detectar la tecla presionada
    C1 = 1;
    if (F1 == 1){key = 1; digit = 1; while(F1 == 1){};}
    if (F2 == 1){key = 4; digit = 4; while(F2 == 1){};}
    if (F3 == 1){key = 7; digit = 7; while(F3 == 1){};}
    if (F4 == 1){key = 10;}
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
    if (F4 == 1){key = 11; while(F4 == 1){};}
    C3 = 0;
}

void main(){
    trisb = 0b00001111;
    trisc = 0b00000000;
    portb = 0x00; //? Por que puse esto?
    portc = 0x00; // Empieza con el motor apagado

    lcd_init(); // Inicializar el LCD

    // Mensaje de bienvenida
    lcd_gotoxy(1, 1);
    lcd_putc("   BIENVENIDO   ");
    lcd_gotoxy(1, 2);
    lcd_putc(" INGRESAR CLAVE ");
    delay_ms(3000); // 3 segundos
    lcd_putc("\f"); // Limpiar el LCD
  
    while(true){
        lcd_gotoxy(1, 1);
        lcd_putc("Ingrese la clave:");

        for(int i = 0; i < 3; i++){ //* For loop para ingresar la clave
            while(key == 12){keyDetection();} // Esperar a que se presione una tecla

            inputs[i] = digit; // Guardar el valor de la tecla presionada

            lcd_gotoxy((i+1), 2); // Mover el cursor a la siguiente posicion
            lcd_putc("*"); // Mostrar un asterisco

            key = 12; // Resetear el valor de la tecla
        }

        // Verificar si la clave es correcta
        if(inputs[0] == pswd[0] && inputs[1] == pswd[1] && inputs[2] == pswd[2]){ //* Clave correcta
            lcd_putc("\f");
            MT = 1; // Encender el motor
            lcd_gotoxy(1, 1);
            lcd_putc(" Clave correcta ");
            delay_ms(3000); // 3 segundos
            MT = 0; // Apagar el motor
            
            attempts = 0; // Resetear el contador de intentos
        } else { //* Clave incorrecta
            attempts++; // Aumentar el contador de intentos

            if(attempts == 3){ //* Si se equivoca 3 veces
                lcd_putc("\f"); //? No se por que, pero si no pongo esto aqui el LCD se vuelve loco

                LED = 1; // Encender el led
                for(int j = 0; j < 10; j++){ //* Bloquear la cerradura por 10 segundos
                    lcd_gotoxy(1, 1);
                    lcd_putc("3 FALLOS");
                    lcd_gotoxy(1, 2);
                    printf(lcd_putc, "BLOQUEADO POR: %u", (j+1)); // Contador de tiempo bloqueado
                    delay_ms(1000); // 1 segundo
                    attempts = 0;
                }
                LED = 0; // Apagar el led
                
                lcd_putc("\f"); //? Este si tiene sentido, limpia despues de cada intento
            } else { //* Si se equivoca
                lcd_putc("\f"); // Limpiar el LCD

                lcd_gotoxy(1, 1);
                lcd_putc("Clave incorrecta");
                LED = 1; // Encender el led
                delay_ms(2000); // 2 segundos
                LED = 0; // Apagar el led
            }
        }
    }

    lcd_putc("\f"); //? Es esto necesario?
    
    key = 12; // Resetear el valor de la tecla
}
