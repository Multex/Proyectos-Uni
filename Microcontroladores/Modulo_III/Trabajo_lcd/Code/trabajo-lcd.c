#include <16f877a.h>
#fuses XT
#use delay(clock=4M)
//! #include <stdbool.h> | This is not necessary
/*******************/
#byte trisa = 0x85
#byte porta = 0x05
#byte portb = 0x06
#byte trisb = 0x86
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
int key = 12; //* Keypad (only keys) - Max value: 12
int digit; //* Numeric value
int ONES = 0; // Unidades
int TENS = 0; // Decimas
int digitFix; //* Fix digits - Para tomar 2 digitos
//// bool motorStatus = false; //? false = OFF / true = ON
//// byte const motorSteps[5] = {0b00110000, 0b01100000, 0b11000000, 0b10010000, };
/*******************/
void keyDetection(){ //* Used to detect the key pressed
    C1 = 1;
    if (F1 == 1){key = 1; digit = 1; while(F1 == 1){};} 
    if (F2 == 1){key = 4; digit = 4; while(F2 == 1){};}
    if (F3 == 1){key = 7; digit = 7; while(F3 == 1){};}
    if (F4 == 1){key = 10;} // "*" - Clear/Stop
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
    if (F4 == 1){key = 11; while(F4 == 1){};} // "#" - Start
    C3 = 0;
}

//! void motorControl(){ //* Used to control the motor | This is the old function
//!    for(int A=0; A < 5; A++){ // Detectar el número de pasos
//!        portc = motorSteps[A];
//!        delay_ms(80);
//!    }
//!}

void motorControl(){ //* Used to control the motor
    porta = 0b00000010;
    delay_ms(80);
    porta = 0b00000001;
    delay_ms(80);
}

void main(){
    trisa = 0b00000000;
    trisb = 0b00001111;
    porta = 0x00;

    lcd_init(); // Initialize the LCD

    // Welcome message
    lcd_gotoxy(1, 1);
    lcd_putc("  ENCENDIDO DE  ");
    lcd_gotoxy(1, 2);
    lcd_putc("    MOTOR DC    ");
    delay_ms(3000); // 3 sec
    lcd_putc("\f"); // After 3 sec, clear the LCD

    while(true){
        keyDetection(); // Function to detect the key pressed
        
        if(key < 10){ //* If the key pressed is a number
            TENS = ONES;
            delay_ms(100);
            ONES = digit;
            delay_ms(100);

            digitFix = (TENS * 10) + ONES;
        } 
        if(key == 11){ //* 11 = "#" -> Start
            motorControl(); // Function to start the motor
            lcd_putc("\f"); // Clear the LCD

            int stableDigit = digitFix; //* To keep the value of digitFix
            
            for(int i=0; i < stableDigit; i++){ // For loop to count down
                keyDetection(); // Calling it again to detect the key pressed
                
                if(key == 10){break;} //* 10 = "*" -> Stop

                lcd_gotoxy(1, 1);
                printf(lcd_putc, "Motor: On");
                lcd_gotoxy(1, 2);
                printf(lcd_putc, "Tiempo: %02u", digitFix);

                digitFix--;
                delay_ms(920); // 920(For this case) + 80(From motorControl) = 1 sec
            }

            //* Reset the values after the loop
            ONES = 0;
            TENS = 0;
            digitFix = 0;

            porta = 0; // Reset the motor
        }
        if(key == 10){ //* 10 = "*" -> Clear
            TENS = 0;
            ONES = 0;
            digitFix = 0;
        }

        // Default message
        lcd_gotoxy(1, 1);
        lcd_putc("Motor: Off");
        lcd_gotoxy(1, 2);
        printf(lcd_putc, "Tiempo: %02u", digitFix);

        key = 12; // Reset the key
    }
}