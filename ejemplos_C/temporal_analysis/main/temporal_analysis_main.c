/*  
# Ejemplo Análisis Temporal

Este ejemplo muestra como realizar un análisis de parámetros temporales sobre una señal de audio almacenada en flash.

## Cómo usar el ejemplo

### Hardware requerido

Este ejemplo no requiere ningún elemento de Hardware adicional.

### Configurar el proyecto

Descomentar solo uno de los *#include chord_[letra].h*, para determinar cuál de las señales será analizada.

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
#include "chord-C.h"
//#include "chord-D.h"
//#include "chord-E.h"
//#include "chord-Em.h"
//#include "chord-F.h"
//#include "chord-G.h"

/*==================[MACROS AND DEFINITIONS]=================================*/

#define MAX_ADC         65536                   // 16 bit audio signals
#define VDD             3300                    // VDD is 3.3V, 3300mV
#define TO_MV(x)        (float)(x)*VDD/MAX_ADC  // Data convertion to mV        
#define SAMPLE_FREQ     16000                   // Signal's sample frequency 16kHz
#define PLOT_WIDTH      128                     // Plot width in characters
#define PLOT_HEIGHT     20                      // Plot height in characters
#define TAG             "Temp_Analysis"         // Tag for LOG

/*==================[INTERNAL DATA DEFINITION]===============================*/

// Input signal
__attribute__((aligned(16))) float signal[N_CHORD];
__attribute__((aligned(16))) float envelope[N_CHORD];

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

    /* Signal in mV */
    for(uint16_t i=0; i<N_CHORD; i++){
        signal[i] = TO_MV(chord[i]);     
    }

    /* Calculate temporal parameters */
    float max = signal[0];              // Signal maximum
    float min = signal[0];              // Signal minimun
    float signal_width = 0;             // Signal width

    for(uint16_t i=0; i<N_CHORD; i++){
        /* Maximum */
        if(signal[i] > max){
            max = signal[i];
        }
        /* Minimum */
        if(signal[i] < min){
            min = signal[i];
        }       
    }

    /* Print paramaters */
    ESP_LOGI(TAG, "Maximum: %fmV", max);
    ESP_LOGI(TAG, "Minimum: %fmV", min);

    /* Plot signal*/
    ESP_LOGI(TAG, "Signal plot");
    dsps_view(signal, N_CHORD, PLOT_WIDTH, PLOT_HEIGHT, min, max, '*');

    /* Envelope detection */
    /* Using moving RMS calculation */
    const uint16_t window = 512;    // Number of samples of moving window
    float rms, env_max = 0;
    for(uint16_t i=0; i<N_CHORD; i++){
        rms = 0;
        if(i < window){
            for(uint16_t j=0; j<=i; j++){
                rms += signal[j] * signal[j]; 
            }
        }else{
            for(uint16_t j=i-window; j<=i; j++){
                rms += signal[j] * signal[j]; 
            }
        }
        envelope[i] = sqrt(rms/window);
        if(envelope[i] > env_max){
            env_max = envelope[i];
        }
    }
    dsps_mulc_f32(envelope, envelope, N_CHORD, (max/env_max), 1, 1);    // Adjust scale

    /* Plot envelope */
    ESP_LOGI(TAG, "Envelope plot");
    dsps_view(envelope, N_CHORD, PLOT_WIDTH, PLOT_HEIGHT, min, max, '*');

    /* Signal duration */
    float threshold = max / 4;      // Height where to measure width
    uint16_t start = 0, end;
    for(uint16_t i=1; i<N_CHORD; i++){
        if((envelope[i-1]<threshold)&&(envelope[i]>=threshold)){
            start = i;
            break;
        }
    }
    for(uint16_t i=1; i<N_CHORD; i++){
        if((envelope[i-1]>threshold)&&(envelope[i]<=threshold)){
            end = i;
        }
    }
    signal_width = (float)(end - start) / SAMPLE_FREQ;
    ESP_LOGI(TAG, "Signal width: %fs", signal_width);
}