/*  
# Ejemplo Análisis Temporal

Este ejemplo muestra como realizar un análisis de correlación cruzada sobre una señal de almacenada en flash con una plantilla también almacenada en memoria flash.

## Cómo usar el ejemplo

### Hardware requerido

Este ejemplo no requiere ningún elemento de Hardware adicional.

### Configurar el proyecto

Descomentar solo uno de los *#include signal_[n]seg.h*, para determinar cuál de las señales será analizada.

### Ejecutar la aplicación

Luego de compilar y cargar el programa en la ESP32, para poder ver los resultados de la ejecución del programa es necesario abrir un monitor serie. Para los ejemplos de este curso utilizamos el puerto serie configurado a 921.600 baudios.
Si se desea utilizar un monitor integrado a la consola de VSCode, primero abra un nuevo ``ESP-IDF Terminal`` y luego ejecute la siguiente línea:

```
idf.py -p "COMX" -b 921600 monitor
```

Para cerrar el monitor ejecute en la terminal ``Ctrl-T`` y luego ``Ctrl-X``.
*/

/*==================[INCLUSIONS]=============================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/dac.h"
#include "driver/gptimer.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include <math.h>
#include "esp_dsp.h"
#include "rtc_wdt.h"

/* Include audio signals headers */
#include "kernel.h"
//#include "signal_7seg.h"
#include "signal_15seg.h"


/*==================[MACROS AND DEFINITIONS]=================================*/
   
#define SAMPLE_FREQ     50                      // Signal's sample frequency 50kHz
#define PLOT_WIDTH      128                     // Plot width in characters
#define PLOT_HEIGHT     20                      // Plot height in characters
#define TAG             "Cross_Correlation_Analysis"         // Tag for LOG

/*==================[INTERNAL DATA DEFINITION]===============================*/

// Input signal
__attribute__((aligned(16))) float corr[N_SIGNAL-N_KERNEL];
__attribute__((aligned(16))) float corr_norm[N_SIGNAL-N_KERNEL];
/*==================[INTERNAL FUNCTIONS DEFINITION]==========================*/

void app_main(void){
    /* UART configuration */
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

    float signal_peak = 0;
    /* Cross Correlation  */
    dsps_corr_f32_ansi(signal, N_SIGNAL, kernel, N_KERNEL, corr);

    float max = corr[0];              // Signal maximum
    uint16_t i_corr = 0;
    for(uint16_t i=0; i<N_SIGNAL-N_KERNEL; i++){
        /* Maximum */
        if(corr[i] > max){
            max = corr[i];
            i_corr = i;
        }
    }
    /* Cross Correlation Normalization */
    dsps_mulc_f32(corr, corr_norm, (N_SIGNAL-N_KERNEL), (1/max), 1, 1);

    /* Plot signal*/
    ESP_LOGI(TAG, "Signal plot");
    dsps_view(signal, N_SIGNAL, PLOT_WIDTH, PLOT_HEIGHT, -2, 2, '*');
    ESP_LOGI(TAG, "Kernel plot");
    dsps_view(kernel, N_KERNEL, PLOT_WIDTH, PLOT_HEIGHT, -2, 2, '*');
    ESP_LOGI(TAG, "Correlation plot");
    dsps_view(corr_norm, N_SIGNAL-N_KERNEL, PLOT_WIDTH, PLOT_HEIGHT, -2, 2, '*');

    signal_peak = (float)(i_corr);
    ESP_LOGI(TAG, "Signal found at: %fs", signal_peak);
}