# Ejemplo UART ML

Este ejemplo muestra como recibir señales a través de la UART para aplicarle un modelo de ML y graficar la salida de el mismo. Está pensado para ser usado junto con la *Jupyter notebook* `2_ML_Clasification_Window_UART.ipynb`. 

## Cómo usar el ejemplo

### Hardware requerido

Ningún hardware extra es necesario.


### Ejecutar la aplicación

Para usar este ejemplo, se debe primero cargar el firmware en el ESP, y luego correr la *Jupyter notebook* `UART.ipynb`. 
La salida del *monitor* se puede observar en la misma notebook.

## Salida esperada

```
I (328) uart_ml: *** Start Example. ***
I (328) uart_ml: Start UART Task
I (728) uart_ml: Mild

I (828) uart_ml: Mild

I (928) uart_ml: Mild

I (1028) uart_ml: Mild
.
.
.
```