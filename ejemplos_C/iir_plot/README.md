# Ejemplo IIR plot

Este ejemplo muestra como cargar un filtro IIR generado utilizando la aplicación online [Micromodeler DSP](https://micromodeler.com/dsp/) o en python utilizando PyFDA o SciPy, graficando luego su respuesta al impulso y respuesta en frecuencia.

## Cómo usar el ejemplo

### Hardware requerido

Este ejemplo no requiere ningún elemento de Hardware adicional.

### Configurar el proyecto

En este ejemplo se prueban dos filtros precargados (un Butterworth y un Chebyshev). 
Si se desea probar un filtro distinto, se deben copiar los coeficientes generados en forma de secciones de orden 2 (SOS).
Si el filtro fue generado con [Micromodeler DSP](https://micromodeler.com/dsp/), este devuelve los coeficiente ordenados como:
```
b0, b1, b2, a1, a2
```
Para utilizarlos en el ESP32 se deben cargar como:
```
float sos_1_but[5] = {b0, b1, b2, -a1, -a2};
```
Si el filtro fue generado en python (PyFDA o SciPy), lo coeficientes son ordenados como:
```
b0, b1, b2, a0, a1, a2
```
Para utilizarlos en el ESP32 se deben cargar como:
```
float sos_1_but[5] = {b0, b1, b2, a1, a2};
```

### Ejecutar la aplicación

Luego de compilar y cargar el programa en la ESP32, para poder ver los resultados de la ejecución del programa es necesario abrir un monitor serie. Para los ejemplos de este curso utilizamos el puerto serie configurado a 921.600 baudios.
Si se desea utilizar un monitor integrado a la consola de VSCode, primero abra un nuevo ``ESP-IDF Terminal`` y luego ejecute la siguiente línea:

```
idf.py -p "COMX" -b 921600 monitor
```

Para cerrar el monitor ejecute en la terminal ``Ctrl-T`` y luego ``Ctrl-X``.

## Salida esperada

```
I (360) IIR plot: *** Start Example. ***
I (360) IIR plot: Butterworth order 8
I (360) IIR plot: IIR for 1024 samples take 73579 cycles
I (360) IIR plot: Impulse response
I (360) view: Data min[22] = -0.053814, Data max[37] = 0.055109
 ________________________________________________________________________________________________________________________________
0                                                                                                                                |
1                                                                                                                                |
2                                                                                                                                |
3                                                                                                                                |
4                                                                                                                                |
5                                                                                                                                |
6                                                                                                                                |
7                                   oooooo                                                                                       |
8       ooooo                   oooo      ooooo                                                                                  |
9ooooooo     oooo             oo               ooooooo    ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo|
0                oooo     oooo                        oooo                                                                       |
1                    ooooo                                                                                                       |
2                                                                                                                                |
3                                                                                                                                |
4                                                                                                                                |
5                                                                                                                                |
6                                                                                                                                |
7                                                                                                                                |
8                                                                                                                                |
9                                                                                                                                |
 01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
I (400) view: Plot: Length=128, min=-0.300000, max=0.300000
I (400) IIR plot: Frequency response
I (400) view: Data min[0] = 0.000000, Data max[26] = 0.000977
 ________________________________________________________________________________________________________________________________
0                 ********************                                                                                           |
1                                     *                                                                                          |
2                *                     *                                                                                         |
3                                       *                                                                                        |
4                                        *                                                                                       |
5               *                                                                                                                |
6                                         *                                                                                      |
7                                                                                                                                |
8                                          *                                                                                     |
9                                                                                                                                |
0              *                            *                                                                                    |
1                                            *                                                                                   |
2                                                                                                                                |
3                                             *                                                                                  |
4                                              *                                                                                 |
5             *                                 *                                                                                |
6                                                **                                                                              |
7            *                                     ***                                                                           |
8   *********                                         ***************************************************************************|
9***                                                                                                                             |
 01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
I (440) view: Plot: Length=128, min=0.000000, max=0.000977
W (440) : 
W (440) : *******************************************************************************************************
W (440) : 
I (440) IIR plot: Chebyshev order 4
I (440) IIR plot: IIR for 1024 samples take 35515 cycles
I (440) IIR plot: Impulse response
I (440) view: Data min[17] = -0.071976, Data max[4] = 0.065440
 ________________________________________________________________________________________________________________________________
0                                                                                                                                |
1                                                                                                                                |
2                                                                                                                                |
3                                                                                                                                |
4                                                                                                                                |
5                                                                                                                                |
6                                                                                                                                |
7   ooooo                                                                                                                        |
8 oo     oo                      ooo                                                                                             |
9o         o               oooooo   ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo|
0           ooo        oooo                                                                                                      |
1              oooooooo                                                                                                          |
2                                                                                                                                |
3                                                                                                                                |
4                                                                                                                                |
5                                                                                                                                |
6                                                                                                                                |
7                                                                                                                                |
8                                                                                                                                |
9                                                                                                                                |
 01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
I (480) view: Plot: Length=128, min=-0.300000, max=0.300000
I (480) IIR plot: Frequency response
I (480) view: Data min[0] = 0.000000, Data max[37] = 0.000976
 ________________________________________________________________________________________________________________________________
0                ***               ******                                                                                        |
1               *   *            **      *                                                                                       |
2                    **       ***         *                                                                                      |
3                      *******             *                                                                                     |
4              *                            *                                                                                    |
5                                            *                                                                                   |
6                                             *                                                                                  |
7                                              *                                                                                 |
8             *                                                                                                                  |
9                                               *                                                                                |
0                                                *                                                                               |
1                                                 **                                                                             |
2            *                                      *                                                                            |
3                                                    *                                                                           |
4                                                     **                                                                         |
5           *                                           ***                                                                      |
6          *                                               ****                                                                  |
7         *                                                    ********                                                          |
8 ********                                                             **********************************************************|
9*                                                                                                                               |
 01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
I (520) view: Plot: Length=128, min=0.000000, max=0.000976
I (520) IIR plot: *** End Example. ***
```