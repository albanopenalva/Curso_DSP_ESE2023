/*  
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
*/

/*==================[INCLUSIONS]=============================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include "esp_dsp.h"

/*==================[MACROS AND DEFINITIONS]=================================*/

/* Do not modify */
#define BUFFER_SIZE     1024                    // Buffer for continuous ADC
#define MAX_ADC         4096                    // ADC 12 bit
#define VDD             3300                    // VDD is 3.3V, 3300mV
#define TO_MV(x)        (float)(x)*VDD/MAX_ADC  // Data convertion to mV   

/* User modificable Macros */
#define N_SAMPLES       512                     // Number of samples to plot 
#define PLOT_WIDTH      64                     // Plot width in characters
#define PLOT_HEIGHT     16                      // Plot height in characters
#define TAG             "uart_plot"           // Tag for LOG

/*==================[INTERNAL DATA DEFINITION]===============================*/

/* FreeRTOS variables */
TaskHandle_t plotTaskHandle = NULL;
TaskHandle_t uartRxTaskHandle = NULL;

// Input signal
__attribute__((aligned(16)))
float signal[N_SAMPLES];

/*==================[INTERNAL FUNCTIONS DEFINITION]==========================*/

void uartRxTask(void *arg){
    uint8_t data[N_SAMPLES*sizeof(int16_t)];
    ESP_LOGI(TAG, "Start UART Task");
    while (1) {
        const int rxBytes = uart_read_bytes(UART_NUM_0, data, sizeof(data), 1000);
        if (rxBytes > 0) {
            for(uint16_t i=0; i<N_SAMPLES; i++){
                signal[i] = TO_MV(((int16_t*)data)[i]);
            }
        } else{
        }
        xTaskNotifyGive(plotTaskHandle);
    }
}

void plotTask(void *arg){   
    ESP_LOGI(TAG, "Start plot Task");
    float max, min;

    while(1){  
        /* Wait untill next convertion done event*/
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        max = signal[0];
        min = signal[0];
        for(uint16_t i=0; i<N_SAMPLES; i++){
            if(signal[i]>max){
                max = signal[i];
            }
            if(signal[i]<min){
                min = signal[i];
            }
        }        
        dsps_view(signal, N_SAMPLES, PLOT_WIDTH, PLOT_HEIGHT, min, max, '*');
    }
}

void app_main(void){

    /* Configure UART*/
    uart_config_t uart_config = {
        .baud_rate = 921600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    uart_param_config(UART_NUM_0, &uart_config);
    uart_set_pin(UART_NUM_0, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM_0, 1024 * 2, 0, 0, NULL, 0);
    ESP_LOGI(TAG, "UART Configured");

    ESP_LOGI(TAG, "*** Start Example. ***");
    
    /* Create task */
    xTaskCreatePinnedToCore(uartRxTask, "uartRxTask", 8192, NULL, 10, &uartRxTaskHandle, 0);
    xTaskCreatePinnedToCore(plotTask, "plotTask", 8192, NULL, 10, &plotTaskHandle, 1);
}