/*  
# Ejemplo IIR plot

Este ejemplo muestra como cargar un filtro IIR generado utilizando la aplicación online [Micromodeler DSP](https://micromodeler.com/dsp/), graficando luego su respuesta al impulso y respuesta en frecuencia.

## Cómo usar el ejemplo

### Hardware requerido

Este ejemplo no requiere ningún elemento de Hardware adicional.

### Configurar el proyecto

En este ejemplo se prueban dos filtros precargados (un Butterworth y un Chebyshev). Si se desea probar un filtro distinto generado con [Micromodeler DSP](https://micromodeler.com/dsp/), se deben copiar los coeficientes generados en forma de secciones de orden 2 (SOS), en el siguiente orden: b0, b1, b2, a0, a1. Nota: los signos de a0 y a1 se deben invertir respecto a los devueltos por Micromodeler.
```
float sos_1_but[5] = {0.07718949372345962, 0.15437898744691925, 0.07718949372345962, -1.0485995763626117, 0.2961403575616696};
```
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
#include <math.h>
#include "esp_dsp.h"

/*==================[MACROS AND DEFINITIONS]=================================*/

/* User modificable Macros */
#define N_SAMPLES       1024                    // Number of samples to plot (needs to be multiple of 1024)
#define PLOT_WIDTH      128                     // Plot width in characters
#define PLOT_HEIGHT     20                      // Plot height in characters
#define TAG             "IIR plot"              // Tag for LOG

/*==================[INTERNAL DATA DEFINITION]===============================*/

/* Butterworth Band-pass filter order: 8*/
float sos_1_but[5] = {0.023879506018041567, 0.04775901203608313, 0.023879506018041567, -1.782312015127054, 0.8169043136006663};  // Array of coeficients of SOS: b0, b1, b2, a1, a2
float w_1_but[2] = {0, 0};  // delay
float sos_2_but[5] = {0.5, -1, 0.5, -1.8727120022494252, 0.8856363861548432}; // Array of coeficients of SOS: b0, b1, b2, a1, a2
float w_2_but[2] = {0, 0};  // delay
float sos_3_but[5] = {0.0078125, 0.015625, 0.0078125, -1.8452018524584375, 0.9065304015992756};  // Array of coeficients of SOS: b0, b1, b2, a1, a2
float w_3_but[2] = {0, 0};  // delay
float sos_4_but[5] = {0.5, -1, 0.5, -1.9576917383162364, 0.96562417674302}; // Array of coeficients of SOS: b0, b1, b2, a1, a2
float w_4_but[2] = {0, 0};  // delay

/* Chebyshev Band-pass filter order: 4*/
float sos_1_cheb[5] = {0.00680972, 0.01361943, 0.00680972, -1.80936695, 0.86890704};  // Array of coeficients of SOS: b0, b1, b2, a1, a2
float w_1_cheb[2] = {0, 0};  // delay
float sos_2_cheb[5] = {1.0, -2.0, 1.0, -1.94277705, 0.95072435};  // Array of coeficients of SOS: b0, b1, b2, a1, a2
float w_2_cheb[2] = {0, 0};  // delay

// Input signal
__attribute__((aligned(16)))
float input[N_SAMPLES];
// Output signal
__attribute__((aligned(16)))
float output[N_SAMPLES];
// FFT complex array
__attribute__((aligned(16)))
float fft[N_SAMPLES*2];

/*==================[INTERNAL FUNCTIONS DEFINITION]==========================*/

void plotIir(float *impulse_response){

    /* Plot impulse response */
    ESP_LOGI(TAG, "Impulse response");
    dsps_view(impulse_response, N_SAMPLES/8, PLOT_WIDTH, PLOT_HEIGHT, -0.3, 0.3, 'o');

    /* Calculate frequency response */
    for (int i=0 ; i< N_SAMPLES ; i++){
        fft[i*2 + 0] = impulse_response[i];
        fft[i*2 + 1] = 0;
    } 
    // Calculate FFT  
    dsps_fft2r_fc32(fft, N_SAMPLES);
    // Bit reverse
    dsps_bit_rev_fc32(fft, N_SAMPLES);
    // Calculate FFT magnitude 
    float max = 0;
    for (int j = 0; j < N_SAMPLES; j++){
            fft[j] = ((fft[j*2+0]*fft[j*2+0] + fft[j*2+1]*fft[j*2+1]) / (N_SAMPLES));
            if(fft[j] > max) {
                max = fft[j];
            }
    }

    ESP_LOGI(TAG, "Frequency response");
    /* Plot frequency response */          
    dsps_view(fft, N_SAMPLES/8, PLOT_WIDTH, PLOT_HEIGHT,  0, max, '*');
}

void app_main(void){
    esp_err_t ret = ESP_OK;
    uint32_t start_t;
    uint32_t end_t;
    
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
    ret = dsps_fft2r_init_fc32(NULL, CONFIG_DSP_MAX_FFT_SIZE);
    if (ret != ESP_OK){
        ESP_LOGE(TAG, "Not possible to initialize FFT. Error = %i", ret);
        return;
    }

    ESP_LOGI(TAG, "*** Start Example. ***");

    // Initialize input signal
    // Generate d function as input signal
    dsps_d_gen_f32(input, N_SAMPLES, 0);

    // filter input signal with Butterworth filter
    ESP_LOGI(TAG, "Butterworth order 8");
    start_t = dsp_get_cpu_cycle_count();
    dsps_biquad_f32(input, output, N_SAMPLES, sos_1_but, w_1_but);
    dsps_biquad_f32(output, output, N_SAMPLES, sos_2_but, w_2_but);
    dsps_biquad_f32(output, output, N_SAMPLES, sos_3_but, w_3_but);
    dsps_biquad_f32(output, output, N_SAMPLES, sos_4_but, w_4_but);
    end_t = dsp_get_cpu_cycle_count();
    ESP_LOGI(TAG, "IIR for %d samples take %ld cycles", N_SAMPLES, (end_t - start_t));
    plotIir(output);

    ESP_LOGW("", "");
    ESP_LOGW("", "*******************************************************************************************************");
    ESP_LOGW("", "");
    
    // filter input signal with Butterworth filter
    ESP_LOGI(TAG, "Chebyshev order 4");
    start_t = dsp_get_cpu_cycle_count();
    dsps_biquad_f32(input, output, N_SAMPLES, sos_1_cheb, w_1_cheb);
    dsps_biquad_f32(output, output, N_SAMPLES, sos_2_cheb, w_2_cheb);
    end_t = dsp_get_cpu_cycle_count();
    ESP_LOGI(TAG, "IIR for %d samples take %ld cycles", N_SAMPLES, (end_t - start_t));
    plotIir(output);

    ESP_LOGI(TAG, "*** End Example. ***");
}