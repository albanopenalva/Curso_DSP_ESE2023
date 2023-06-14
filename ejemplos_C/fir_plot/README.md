# Ejemplo IIR plot

Este ejemplo muestra como cargar un filtro IIR generado utilizando la aplicación online [Micromodeler DSP](https://micromodeler.com/dsp/) o en python utilizando PyFDA o SciPy, graficando luego su respuesta al impulso y respuesta en frecuencia.

## Cómo usar el ejemplo

### Hardware requerido

Este ejemplo no requiere ningún elemento de Hardware adicional.

### Configurar el proyecto

En este ejemplo se prueban dos filtros precargados (uno de ventana rectangular y un Equiripple). 
Si se desea probar un filtro distinto generado con [Micromodeler DSP](https://micromodeler.com/dsp/) o en python, se deben copiar los coeficientes generados tal y como los devuelve la aplicación.
```
float window_coefs[FIR_ORDER] = {
    -0.071488410, -0.072959286, -0.071854345, -0.062158068, 
    -0.039125342, -0.0022398888, 0.043459476, 0.088364179, 
    0.12130080, 0.13340178, 0.12130080, 0.088364179,
    0.043459476, -0.0022398888, -0.039125342, -0.062158068, 
    -0.071854345, -0.072959286, -0.071488410		
}; 
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
I (353) FIR plot: *** Start Example. ***
I (353) FIR plot: window
I (353) FIR plot: FIR of 19 coeficients take 110165 cycles for 1024 samples
I (353) FIR plot: Impulse response
I (353) view: Data min[1] = -0.072959, Data max[9] = 0.133402
 ________________________________________________________________________________________________________________________________
0                                                                                                                                |
1                                                                                                                                |
2                                                                                                                                |
3                                                                                                                                |
4                                                                                                                                |
5        ooo                                                                                                                     |
6       o   o                                                                                                                    |
7                                                                                                                                |
8      o     o                                                                                                                   |
9     o       o     ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo|
0    o         o                                                                                                                 |
1oooo           oooo                                                                                                             |
2                                                                                                                                |
3                                                                                                                                |
4                                                                                                                                |
5                                                                                                                                |
6                                                                                                                                |
7                                                                                                                                |
8                                                                                                                                |
9                                                                                                                                |
 01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
I (393) view: Plot: Length=128, min=-0.300000, max=0.300000
I (393) FIR plot: Frequency response
I (393) view: Data min[0] = 0.000000, Data max[65] = 0.001067
 ________________________________________________________________________________________________________________________________
0                                                           **************                                                       |
1                                                        ***              ***                                                    |
2                                                     ***                    **                                                  |
3                                                   **                         **                                                |
4                                                 **                             **                                              |
5                                                *                                 **                                            |
6                                              **                                    *                                           |
7                                            **                                       **                                         |
8                                           *                                           **                                       |
9                                         **                                              **                                     |
0                                       **                                                  *                                    |
1                                     **                                                     **                                  |
2                                   **                                                         **                                |
3                                 **                                                             **                              |
4                               **                                                                 ***                           |
5                             **                                                                      **                         |
6                         ****                                                                          ***                      |
7                     ****                                                                                 *****                 |
8 ********************                                                                                          *****************|
9*                                                                                                                               |
 01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
I (433) view: Plot: Length=128, min=0.000000, max=0.001067
W (443) : 
W (443) : *******************************************************************************************************
W (443) : 
I (443) FIR plot: equiripple
I (453) FIR plot: FIR of 328 coeficients take 1376071 cycles for 1024 samples
I (453) FIR plot: Impulse response
I (453) view: Data min[67] = -0.037179, Data max[82] = 0.069772
 ________________________________________________________________________________________________________________________________
0                                                                                                                                |
1                                                                                                                                |
2                                                                                                                                |
3                                                                                                                                |
4                                                                                                                                |
5                                                                                                                                |
6                                                                                                                                |
7                                                                              ooooooooo                                         |
8 oo                                                                        ooo         ooo                                      |
9   oooooooooooooooooooooooooooooooooooooooooooooooooooooooooo           ooo               ooo           oooooooooooooooooooooooo|
0o                                                            ooooooooooo                     ooooooooooo                        |
1                                                                                                                                |
2                                                                                                                                |
3                                                                                                                                |
4                                                                                                                                |
5                                                                                                                                |
6                                                                                                                                |
7                                                                                                                                |
8                                                                                                                                |
9                                                                                                                                |
 01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
I (493) view: Plot: Length=128, min=-0.300000, max=0.300000
I (493) FIR plot: Frequency response
I (493) view: Data min[113] = 0.000000, Data max[28] = 0.001085
 ________________________________________________________________________________________________________________________________
0                ***       ****        ****                                                                                      |
1               *   *     *    *      *                                                                                          |
2                    *   *      **   *     *                                                                                     |
3                     ***         ***                                                                                            |
4              *                            *                                                                                    |
5                                                                                                                                |
6                                                                                                                                |
7             *                              *                                                                                   |
8                                                                                                                                |
9                                                                                                                                |
0                                             *                                                                                  |
1            *                                                                                                                   |
2                                              *                                                                                 |
3                                                                                                                                |
4           *                                   *                                                                                |
5                                                                                                                                |
6                                                *                                                                               |
7          *                                      *                                                                              |
8**********                                        ******************************************************************************|
9                                                                                                                                |
 01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567
I (533) view: Plot: Length=128, min=0.000000, max=0.001085
I (533) FIR plot: *** End Example. ***
```