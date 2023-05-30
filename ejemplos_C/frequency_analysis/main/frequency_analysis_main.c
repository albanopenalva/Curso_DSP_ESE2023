/*  
# Ejemplo Análisis Frecuencial

Este ejemplo muestra como realizar un análisis de parámetros frecuenciales sobre una señal de audio almacenada en flash.

## Cómo usar el ejemplo

### Hardware requerido

Este ejemplo no requiere ningún elemento de Hardware adicional.

### Configurar el proyecto

Descomentar solo uno de los *#include [nombre_archivo].h*, para determinar cuál de las señales será analizada.

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
//#include "silbido.h"

/*==================[MACROS AND DEFINITIONS]=================================*/

#define MAX_ADC         32768                           // 16 bit audio signals
#define VDD             3300                            // VDD is 3.3V, 3300mV
#define TO_MV(x)        (float)(x)*VDD/MAX_ADC          // Data convertion to mV        
#define SAMPLE_FREQ     8000                            // Signal's sample frequency 8kHz
#define PLOT_WIDTH      128                             // Plot width in characters
#define PLOT_HEIGHT     20                              // Plot height in characters
#define TAG             "Freq_Analysis"                 // Tag for LOG
/*  Find the power of 2 nearest to number of samples (N_CHORD).
    FFT function needs the argument to be of length 2^n, 
    so we use the first 2^n samples of the signal. */
#define NEEDS_BIT(N, B) (((unsigned long)N >> B) > 0)
#define BITS_TO_REPRESENT(N)                                   \
                        (NEEDS_BIT(N,  0) + NEEDS_BIT(N,  1) + \
                        NEEDS_BIT(N,  2) + NEEDS_BIT(N,  3) +  \
                        NEEDS_BIT(N,  4) + NEEDS_BIT(N,  5) +  \
                        NEEDS_BIT(N,  6) + NEEDS_BIT(N,  7) +  \
                        NEEDS_BIT(N,  8) + NEEDS_BIT(N,  9) +  \
                        NEEDS_BIT(N, 10) + NEEDS_BIT(N, 11) +  \
                        NEEDS_BIT(N, 12) + NEEDS_BIT(N, 13))
#define POW2            (BITS_TO_REPRESENT(N_CHORD) -1 )
#define N_POW2          (1 << (POW2))                   // Power of two nearest to number of samples

/*==================[INTERNAL DATA DEFINITION]===============================*/

// Input signal
__attribute__((aligned(16))) float signal[N_POW2];
// Window coefficients
__attribute__((aligned(16))) float wind[N_POW2];
// working complex array
__attribute__((aligned(16))) float fft[N_POW2*2];

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

    /* Initialize FFT */
    esp_err_t ret = dsps_fft2r_init_fc32(NULL, CONFIG_DSP_MAX_FFT_SIZE);
    if (ret != ESP_OK){
        ESP_LOGE(TAG, "Not possible to initialize FFT. Error = %i", ret);
        return;
    }

    /* Generate Hann window */
    dsps_wind_hann_f32(wind, N_CHORD);

    ESP_LOGI(TAG, "*** Start Example. ***");
    ESP_LOGI(TAG, "Número de muestras: %d", N_CHORD);
    ESP_LOGI(TAG, "Potencia de 2 más cercana al número de muestras: %d", N_POW2);

    /* Signal in mV */
    for(uint16_t i=0; i<N_POW2; i++){
        signal[i] = TO_MV(chord[i]);  
    }

    /* Detect maximum */
    float max = signal[0];              // Signal maximum
    for(uint16_t i=0; i<N_POW2/2; i++){
        if(signal[i] > max){
            max = signal[i];
        }
    }
    dsps_view(signal, N_POW2, PLOT_WIDTH, PLOT_HEIGHT, -max, max, '*');

    /* Calculate FFT */
    // Multiply input array with window and store as real part
    dsps_mul_f32(signal, wind, fft, N_CHORD, 1, 1, 2);    
    // Clear imaginary part of the complex signal
    dsps_mulc_f32(&fft[1], &fft[1], N_CHORD, 0, 2, 2); 
    // Calculate FFT  
    dsps_fft2r_fc32(fft, N_POW2);
    // Bit reverse
    dsps_bit_rev_fc32(fft, N_POW2);
    // Convert one complex vector to two complex vectors
    dsps_cplx2reC_fc32(fft, N_POW2);
    // Calculate FFT magnitude in mV
    for (int j = 0; j < N_POW2; j++){
            fft[j] = 2*(sqrt(fft[j*2+0]*fft[j*2+0] + fft[j*2+1]*fft[j*2+1])) / (N_POW2/2);
    }
    fft[0] = fft[0] / 2;
    // Calculate FFT in mW
    for (int j = 0; j < N_POW2/2; j++){
            fft[j] = fft[j]*fft[j];
    }

    /* Detect maximum */
    float fft_max = fft[0];              // Signal maximum
    for(uint16_t i=0; i<N_POW2; i++){
        if(fft[i] > fft_max){
            fft_max = fft[i];
        }
    }

    /* Plot FFT */
    dsps_view(fft, N_POW2/2, PLOT_WIDTH, PLOT_HEIGHT, 0, fft_max, '*');
    ESP_LOGI("Plot", "Fs: %dHz", SAMPLE_FREQ);

}