# Examen Módulo I

> Recuerden que las preguntas están mezcladas, revisen bien todo.
>
> Además, solo pondré la respuesta correcta.

## Pregunta 1
Permite configurar las entradas y salidas en un puerto del microcontrolador.

**Respuesta correcta:** Tris

## Pregunta 2
El código que se visualiza a continuación presenta uno o más errores de compilación.

```cpp
#include <16f877a.h>
#fuses hs
#use delay (clock=16M)
#byte trisb=0x86
#byte portb=0x06
#bit LED=portb.0
#bit PUL1=portb.1
void main() {
trisb=0be9000010;
portb=0be9900000;
while(true){
 if (PUL1==1) {LED=1;}
 }
}
```

**Respuesta correcta:** Falso

## Pregunta 3
El lenguaje de alto nivel difiere de nuestra forma de razonar.

**Respuesta correcta:** Falso

## Pregunta 4

El lenguaje de bajo nivel se caracterizan por su sencillez y portabilidad.

**Respuesta correcta:** Falso

## Pregunta 5

Extensión del tipo de dato que se almacena en la memoria del microcontrolador.

**Respuesta correcta:** Bin

## Pregunta 6

Si tengo un cristal de 16 MHz como debería definirlo.

**Respuesta correcta:** HS

## Pregunta 7

La siguiente expresión
```cpp
trisc = 00100101
```

**Respuesta correcta:** No esta configurado

## Pregunta 8

Si decido crear subrutinas, corresponde a una característica de:

**Respuesta correcta:** Modularidad

## Pregunta 9

Que tipo de dato le corresponde a una constante igual a 37835

**Respuesta correcta:** Int16

## Pregunta 10

Calcular el valor de "x" para que realice todo el proceso en 120 segundos.

```cpp
for (i=0; i<=19; i++) {
    delay_ms (500);
    for(j=0; j<=49; j++) {
        delay_ms(10);
        for (k=0; k<=4; k++) {
            delay_ms (5);
            delay_ms(x);
        }
    }
}
```

**Respuesta correcta:** 15