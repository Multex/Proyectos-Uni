# EXAMEN DE PROGRAMACIÓN (EC3)

*Hice lo posible para recrear el pdf en un md, para saber que es lo que se supone que se debía hacer para todo este examen!*

Programe e implemente un sistema de clave, utilizando un keypad de 3 columnas y 4 filas.

Si la clave o combinación es correcta, activa un motor de 12 VDC por un tiempo de 3 segundos y se muestra en un LCD el mensaje: “CLAVE CORRECTA”, caso contrario si la clave es incorrecta se enciende un led rojo por 2 segundos indicando en el LCD:
“ERROR…!”. Después de 3 intentos fallidos, el sistema debe bloquearse por 10 segundos y mostrar el mensaje en el LCD: “BLOQUEADO…!”, transcurrido ese tiempo puede volver a intentar nuevamente.

### Combinación Correcta:
Número 4 – Número 7 – Número 3, en ese orden 

### Mostrar en un LCD lo siguiente de acuerdo a los casos que se presenten:
- Mensaje de Bienvenida (Tiempo 3 segundos):
    - Línea 1: BIENVENIDO
    - Línea 2: INGRESAR CLAVE

- Mensaje de espera (Hasta que se presione la primera tecla):
    - Línea 1: CLAVE:
    - Línea 2:

- Cuando se presione el primer pulsador:
    - Línea 1: CLAVE:
    - Línea 2: *

- Cuando se presione el segundo pulsador:
    - Línea 1: CLAVE:
    - Línea 2: **

- Cuando se presione el tercer pulsador:
    - Línea 1: CLAVE:
    - Línea 2: ***

- Si es correcta la combinación:
    - Línea 1: ********************
    - Línea 2: CLAVE CORRECTA…!

- Si es incorrecta la combinación
    - Línea 1: ********************
    - Línea 2: ERROR…!

- Si se falló la combinación es los 3 intentos
    - Línea 1: ********************
    - BLOQUEADO…!

### Rubrica de evaluación:

| **Presentación del trabajo de laboratorio** | **Calificación** |
| :----------- | :-----------: |
| Activación correcta de la clave y motor DC, con la combinación adecuada | 4 puntos |
| Encendido de led 2 segundos cuando la clave es incorrecta | 4 puntos |
| Sistema de bloqueo por 10 segundos después de 3 intentos errados | 8 puntos |
| Todas las visualizaciones en el LCD tal como se indican en los ejemplos | 4 puntos |
| **TOTAL** | 20 puntos |