# Ejemplo UART Plot

Este ejemplo muestra como recibir señales a través de la UART para su graficación. Está pensado para ser usado junto con la *Jupyter notebook* `UART.ipynb`. 

## Cómo usar el ejemplo

### Hardware requerido

Ningún hardware extra es necesario.

### Configurar el proyecto

Seleccionar número de muetras a graficar:
```
#define N_SAMPLES       512                   
```
Configurar el tamaño de las gráficas:
```
#define PLOT_WIDTH      64                     // Plot width in characters
#define PLOT_HEIGHT     16                      // Plot height in characters
```

### Ejecutar la aplicación

Para usar este ejemplo, se debe primero cargar el firmware en el ESP, y luego correr la *Jupyter notebook* `UART.ipynb`. 
La salida del *monitor* se puede observar en la misma notebook.

## Salida esperada

```
I (340) uart_plot: *** Start Example. ***
I (340) uart_plot: Start UART Task
I (340) uart_plot: Start plot Task
I (1780) view: Data min[497] = -110.375977, Data max[275] = 346.435547
 ________________________________________________________________
0    *                             *                            *|
1    *                             *                            *|
2    *                             *                            *|
3    **                            *                            *|
4    **                            *                            *|
5    **                           **                             |
6    **                           **                             |
7    **                           **                           * |
8    **                           **                           * |
9     *        **                 *                            * |
0     *       *  *         **     *         ***                * |
1   * *      *   **       ** *    * *     **  **        ***    * |
2** * ** ****      ********  **   * *    * *   ** ******   *   * |
3  ** * *                     ***** *****        *          **** |
4   *                            **                           ** |
5                                                                |
 0123456789012345678901234567890123456789012345678901234567890123
I (1790) view: Plot: Length=512, min=-110.375977, max=346.435547
I (3190) view: Data min[221] = -109.570312, Data max[232] = 336.767578
 ________________________________________________________________
0                            **                            *     |
1                            **                            *     |
2                            **                            *     |
3                            **                           **     |
4                            **                           **     |
5                            **                           **     |
6                            **                           **     |
7                            **                           **     |
8*                           **                           **     |
9*        *                  **         *                 **     |
0*       * *          *      **       ** *                *      |
1*      *   *        * **    **      *   **       ***     *      |
2**  ***    *********   *    **    ***     ******* * *    * *****|
3* **                    **** *****                   ***** *    |
4*                          * *                          **      |
5                                                                |
 0123456789012345678901234567890123456789012345678901234567890123
I (3210) view: Plot: Length=512, min=-109.570312, max=336.767578
.
.
.
```