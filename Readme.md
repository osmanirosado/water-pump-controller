# Documentación

## Componentes

- [Seeeduino v4.2](https://wiki.seeedstudio.com/Seeeduino_v4.2/)
- [Base Shield V2](https://wiki.seeedstudio.com/Base_Shield_V2/)
- [Grove - 2-Channel SPDT Relay](https://wiki.seeedstudio.com/Grove-2-Channel_SPDT_Relay/)
- [Grove - Touch Sensor](https://wiki.seeedstudio.com/Grove-Touch_Sensor/)
- [Grove - Red LED](https://wiki.seeedstudio.com/Grove-Red_LED/)
- [Grove - Blue LED](https://www.seeedstudio.com/Grove-Blue-LED.html)
- [Grove - Green LED](https://www.seeedstudio.com/Grove-Green-LED.html)

## Conexión

1. Montar la placa base (Base Shield) sobre la placa del controlador Seeeduino.
   Los componentes se conectan en los puertos de la placa base.
2. Conectar el led verde en el puerto D2.
3. Conectar el led azul en el puerto D3.
4. Conectar el led rojo en el puerto D4.
5. Conectar dos botones de contacto (touch sensor) en los puertos D5 y D6.
6. Conectar los relés (2-Channel SPDT Relay) en el puerto D7.  
   El puerto D8 es usado por uno de los reles conectados en el puerto D7.  
   Esto sucede porque el pin digital 8 está disponible también en el puerto D7.

## Comportamiento

Hay dos botones de contacto, uno para encender la bomba de agua y el otro 
para detenerla.

Al hacer contacto en el botón de inicio, 
empieza un proceso de bombeo y recuperación que se repite tres veces.
Primero se inicia un temporizador que, detiene el bombeo después de un
tiempo. Luego se inicia otro temporizador,
que garantiza un tiempo de recuperación del pozo, 
antes de iniciar el proceso nuevamente.

El número de veces que se repite el proceso, el tiempo de bombeo
y el tiempo de reposo, son constantes definidas en el código.

Al hacer contacto en el botón de apagado, se detiene el proceso.
Si la bomba está funcionando se apaga. Si el temporizador de recuperación
está funcionando, se deja terminar para evitar un inicio apresurado.

El led rojo indica que el proceso está detenido. El led verde indica que la 
bomba está en funcionamiento. El led azul indica que el sistema está en el tiempo
de recuperación.

Un relé simula el botón de encendido del magnético. El contacto normalmente abierto
del relé se conecta al magnético. Al cerrar el contacto normalmente
abierto del relé durante algunos milisegundos, se enciende la bomba.

El otro relé simula el botón de apagado del magnético.
El contacto normalmente cerrado del relé se conecta al magnético.
Al abrir el contacto normalmente cerrado del relé durante
algunos milisegundos, se apaga la bomba.


