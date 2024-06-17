#include <16f877a.h>
#fuses xt
#use delay(clock = 4M)
#byte trisb = 0x86
#byte trisd = 0x88
#byte portb = 0x06
#byte portd = 0x08
#bit C1 = portb .0
#bit C2 = portb .1
#bit C3 = portb .2
#bit C4 = portb .3
#bit F1 = portb .4
#bit F2 = portb .5
#bit F3 = portb .6
#bit F4 = portb .7
#define LCD_ENABLE_PIN PIN_D3 ////
#define LCD_RS_PIN PIN_D1     ////
#define LCD_RW_PIN PIN_D2     ////
#define LCD_DATA4 PIN_D4      ////
#define LCD_DATA5 PIN_D5      ////
#define LCD_DATA6 PIN_D6      ////
#define LCD_DATA7 PIN_D7
#include <lcd.c>
int TECLA;
void BUSCAR(){
    C1 = 1;
    if (F1 == 1){TECLA = 7;}
    if (F2 == 1){TECLA = 4;}
    if (F3 == 1){TECLA = 1;}
    if (F4 == 1){TECLA = "C";}
    C1 = 0;

    C2 = 1;
    if (F1 == 1){TECLA = 8;}
    if (F2 == 1){TECLA = 5;}
    if (F3 == 1){TECLA = 2;}
    if (F4 == 1){TECLA = 0;}
    C2 = 0;

    C3 = 1;
    if (F1 == 1){TECLA = 9;}
    if (F2 == 1){TECLA = 6;}
    if (F3 == 1){TECLA = 3;}
    if (F4 == 1){TECLA = "=";}
    C3 = 0;

    C4 = 1;
    if (F1 == 1){TECLA = "/";}
    if (F2 == 1){TECLA = "*";}
    if (F3 == 1){TECLA = "-";}
    if (F4 == 1){TECLA = "+";}
    C4 = 0;
}
void main(){
    trisb = 0b11110000;
    lcd_init();

    lcd_gotoxy(1, 1);
    lcd_putc("TECLADO");
    lcd_gotoxy(1, 2);
    lcd_putc("NUMERO: ");

    while (true){
        BUSCAR(); // LLAMANDO A LA SUBRUTINA "BUSCAR"

        lcd_gotoxy(1, 2);
        printf(lcd_putc, "NUMERO: %u", TECLA);
    }
}