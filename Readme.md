# Documentación

## Componentes

- [Seeeduino v4.2](https://wiki.seeedstudio.com/Seeeduino_v4.2/)
- [Base Shield V2](https://wiki.seeedstudio.com/Base_Shield_V2/)
- [Grove - 2-Channel SPDT Relay](https://wiki.seeedstudio.com/Grove-2-Channel_SPDT_Relay/)
- [Grove - Touch Sensor](https://wiki.seeedstudio.com/Grove-Touch_Sensor/)
- [Grove - Red LED](https://wiki.seeedstudio.com/Grove-Red_LED/)
- [Grove - Blue LED](https://www.seeedstudio.com/Grove-Blue-LED.html)
- [Grove - Green LED](https://www.seeedstudio.com/Grove-Green-LED.html)

## Dependencias

- [neotimer](https://github.com/jrullan/neotimer)

## Conexión

1. Montar la placa base (Base Shield) sobre la placa del controlador Seeeduino.
   Los componentes se conectan en los puertos de la placa base.
2. Conectar el led verde en el puerto D2.
3. Conectar el led azul en el puerto D3.
4. Conectar el led rojo en el puerto D4.
5. Conectar los relés (2-Channel SPDT Relay) en el puerto D7.
   El puerto D8 es usado por uno de los reles conectados en el puerto D7.  
   Esto sucede porque el pin digital 8 está disponible también en el puerto D7.

## Comportamiento

Existen tres estados: espera, bombeo y reposo.
La espera comienza al conectar el controlador a la fuente de alimentación.
Le sigue el proceso de bombeo y reposo.
Este proceso puede repetirse varias veces.

El led rojo indica que el proceso está detenido.
El led verde indica que la bomba está en funcionamiento.
El led azul indica que el sistema está en reposo o en espera.

## Configuración

El número de veces que se repite el proceso, el tiempo de espera,
el tiempo de bombeo y el tiempo de reposo, son constantes definidas en el código.

## Detalles

Un relé simula el botón de encendido del magnético.
El contacto normalmente abierto del relé se conecta al magnético.
Al cerrar ese contacto durante unos milisegundos, se enciende la bomba.

El otro relé simula el botón de apagado del magnético.
El contacto normalmente cerrado del relé se conecta al magnético.
Al abrir ese contacto durante unos milisegundos, se apaga la bomba.

## Colaboradores

- [Adrian Jesús Pérez-Borroto Vega](https://github.com/adrianpbv) montó los componentes y probó el código.
- [Jose Daniel Rodríguez](https://github.com/josedanielr) revisó la biblioteca [neotimer](https://github.com/jrullan/neotimer).
