#include <16f877a.h>
#device adc = 10 // Selecciona la resolucion del ADC
#fuses xt
#use delay(clock = 4M)
/*************************/
#byte trisd = 0x88
#byte portd = 0x08
/*************************/ //* Definir los pines del L293D
#bit IN1 = portd.0
#bit IN2 = portd.1
#bit IN3 = portd.2
#bit IN4 = portd.3
/*************************/
#define LCD_ENABLE_PIN PIN_B0
#define LCD_RS_PIN PIN_B1
#define LCD_RW_PIN PIN_B2
#define LCD_DATA4 PIN_B4
#define LCD_DATA5 PIN_B5
#define LCD_DATA6 PIN_B6
#define LCD_DATA7 PIN_B7
#include <lcd.c>
/*************************/
void main(){
    trisd = 0b0000000;
    portd = 0x00;

    long adcValue1, adcValue2; // Variables para almacenar el valor del ADC
    int temp1, temp2, state = 0; // Variables para almacenar la temperatura y el estado del ventilador

    lcd_init(); // Inicializa el LCD
    
    setup_adc_ports(all_analog); // Configura los puertos analogicos
    setup_adc(adc_clock_internal); // Configura el reloj interno del ADC

    // Mensaje de bienvenida
    lcd_gotoxy(1, 1);
    lcd_putc("   CONTROL DE   ");
    lcd_gotoxy(1, 2);
    lcd_putc("  TEMPERATURA!  ");
    delay_ms(2000);

    lcd_putc("\f"); // Limpia la pantalla

    while (true){
        // Leer sensor 1
        set_adc_channel(0); // Selecciona el canal 0
        delay_us(20);
        adcValue1 = read_adc(); // Lee el valor del ADC
        temp1 = (100.0 * adcValue1) / 1023.0; // Convierte el valor del ADC a temperatura
        
        // Leer sensor 2
        set_adc_channel(1); // Selecciona el canal 1
        delay_us(20);
        adcValue2 = read_adc(); // Lee el valor del ADC
        temp2 = (100.0 * adcValue2) / 1023.0; // Convierte el valor del ADC a temperatura

        // Mostrar en LCD
        lcd_gotoxy(1, 1);
        printf(lcd_putc, "TEMP_01: %02u", temp1);
        lcd_gotoxy(1, 2);
        printf(lcd_putc, "TEMP_02: %02u", temp2);

        // Control de temperatura para ventiladores
        if(temp1 >= 50 && temp2 >= 50){ // Si ambas temperaturas son mayores o iguales a 50
            IN1 = 1; IN2 = 0; // Enciende el ventilador 1
            IN3 = 1; IN4 = 0; // Enciende el ventilador 2
            state = 2; //* State = 2 -> Ambos ventiladores encendidos
        }
        if(state == 2 && temp1 < 30 && temp2 < 30){ // Si ambas temperaturas son menores a 30
            portd = 0; // Apaga ambos ventiladores
            state = 0; //* State = 0 -> Ambos ventiladores apagados
        }
        if(temp1 >= 30 && temp2 < 50 && state != 2){ // Si la temperatura 1 es mayor o igual a 30 y la temperatura 2 es menor a 50
            IN1 = 1; IN2 = 0; // Enciende el ventilador 1
            IN3 = 0; IN4 = 0; // Apaga el ventilador 2
            state = 1; //* State = 1 -> Ventilador 1 encendido
        }
        if(state == 1 && temp1 <= 25){ // Si la temperatura 1 es menor o igual a 25
            portd = 0; // Apaga el ventilador 1
            state = 0; //* State = 0 -> Ambos ventiladores apagados
        }

        delay_ms(100); // Pequeño retardo para disminuir la velocidad del bucle
    }
}