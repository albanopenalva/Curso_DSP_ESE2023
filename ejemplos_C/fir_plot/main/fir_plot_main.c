/*  
# Ejemplo IIR plot

Este ejemplo muestra como cargar un filtro FIR generado utilizando la aplicación online [Micromodeler DSP](https://micromodeler.com/dsp/), graficando luego su respuesta al impulso y respuesta en frecuencia.

## Cómo usar el ejemplo

### Hardware requerido

Este ejemplo no requiere ningún elemento de Hardware adicional.

### Configurar el proyecto

En este ejemplo se prueban un filtro precargados (pasabanda Equiripple). Si se desea probar un filtro distinto generado con [Micromodeler DSP](https://micromodeler.com/dsp/), se deben copiar los coeficientes generados tal y como los devuelve la aplicación.
```
float equiripple_coefs[FIR_ORDER] = {
    -0.047206800, 0.0028018166, -0.0053542622, -0.00030879196, 0.088077221, -0.00080543163, 0.0076126216, 
	0.00097891198, -0.31190470, -0.00042065941, 0.49147537, -0.00042065941, -0.31190470, 0.00097891198,
	0.0076126216, -0.00080543163, 0.088077221, -0.00030879196, -0.0053542622, 0.0028018166, -0.047206800	
}; 
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
#define TAG             "FIR plot"              // Tag for LOG

/*==================[INTERNAL DATA DEFINITION]===============================*/

/* Window Band-pass filter order: 19*/
#define FIR1_ORDER       19
float window_coefs[FIR1_ORDER] = {
    -0.071488410, -0.072959286, -0.071854345, -0.062158068, 
    -0.039125342, -0.0022398888, 0.043459476, 0.088364179, 
    0.12130080, 0.13340178, 0.12130080, 0.088364179,
    0.043459476, -0.0022398888, -0.039125342, -0.062158068, 
    -0.071854345, -0.072959286, -0.071488410	
};  
fir_f32_t window;

/* Equirriple Band-pass filter order: 328*/
#define FIR2_ORDER       328
float equiripple_coefs[FIR2_ORDER] = {
    -0.02950435, 0.02824013,  0.01621326,  0.00838789,  0.00362666,  0.00111867,
    0.00024981,  0.00053086,  0.00155244,  0.00296906,  0.00448867,  0.00587536,
    0.00695151,  0.00759998,  0.0077646,   0.00744647,  0.00669834,  0.00561472,
    0.00431901,  0.00295101,  0.00165143,  0.00055011,  -0.00024564, -0.00066227,
    -0.00066493, -0.00025958, 0.0005076,   0.00155562,  0.00277384,  0.00403162,
    0.00519196,  0.00612178,  0.00670225,  0.00684029,  0.00647693,  0.00559306,
    0.00421164,  0.00239662,  0.00025011,  -0.00209436, -0.00448343, -0.00675553,
    -0.00875128, -0.01032738, -0.01137112, -0.01180936, -0.01161552, -0.01081549,
    -0.00948815, -0.00776166, -0.0058059,  -0.00382196, -0.0020289,  -0.00064552,
    0.00012721,  0.00012089,  -0.00078289, -0.00263818, -0.00542802, -0.00905964,
    -0.01336257, -0.01809643, -0.0229645,  -0.02762729, -0.03172311, -0.0348943,
    -0.0368077,  -0.03717946, -0.03580039, -0.03254839, -0.02740331, -0.02045835,
    -0.01191274, -0.00206913, 0.00867826,  0.01986977,  0.03099863,  0.041542,
    0.05099451,  0.05888709,  0.06482996,  0.06851929,  0.06977162,  0.06851929,
    0.06482996,  0.05888709,  0.05099451,  0.041542,    0.03099863,  0.01986977,
    0.00867826,  -0.00206913, -0.01191274, -0.02045835, -0.02740331, -0.03254839,
    -0.03580039, -0.03717946, -0.0368077,  -0.0348943,  -0.03172311, -0.02762729,
    -0.0229645,  -0.01809643, -0.01336257, -0.00905964, -0.00542802, -0.00263818,
    -0.00078289, 0.00012089,  0.00012721,  -0.00064552, -0.0020289,  -0.00382196,
    -0.0058059,  -0.00776166, -0.00948815, -0.01081549, -0.01161552, -0.01180936,
    -0.01137112, -0.01032738, -0.00875128, -0.00675553, -0.00448343, -0.00209436,
    0.00025011,  0.00239662,  0.00421164,  0.00559306,  0.00647693,  0.00684029,
    0.00670225,  0.00612178,  0.00519196,  0.00403162,  0.00277384,  0.00155562,
    0.0005076,   -0.00025958, -0.00066493, -0.00066227, -0.00024564, 0.00055011,
    0.00165143,  0.00295101,  0.00431901,  0.00561472,  0.00669834,  0.00744647,
    0.0077646,   0.00759998,  0.00695151,  0.00587536,  0.00448867,  0.00296906,
    0.00155244,  0.00053086,  0.00024981,  0.00111867,  0.00362666,  0.00838789,
    0.01621326,  0.02824013,  -0.02950435	
};  
fir_f32_t equiripple;

// Input signal
__attribute__((aligned(16))) float input[N_SAMPLES];
// Output signal
__attribute__((aligned(16))) float output[N_SAMPLES];
// Delay line
__attribute__((aligned(16))) float delay1[FIR1_ORDER + 4];
__attribute__((aligned(16))) float delay2[FIR2_ORDER + 4];
// FFT complex array
__attribute__((aligned(16))) float fft[N_SAMPLES*2];

/*==================[INTERNAL FUNCTIONS DEFINITION]==========================*/

void plotFir(float *impulse_response){

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

    // Initialize fir filters
    dsps_fir_init_f32(&window, window_coefs, delay1, FIR1_ORDER);
    dsps_fir_init_f32(&equiripple, equiripple_coefs, delay2, FIR2_ORDER);

    // filter input signal with window filter
    ESP_LOGI(TAG, "Window");
    start_t = dsp_get_cpu_cycle_count();
    dsps_fir_f32_ae32(&window, input, output, N_SAMPLES);
    end_t = dsp_get_cpu_cycle_count();
    ESP_LOGI(TAG, "FIR of %d coeficients take %ld cycles for %d samples", FIR1_ORDER, (end_t - start_t), N_SAMPLES);
    plotFir(output);

    ESP_LOGW("", "");
    ESP_LOGW("", "*******************************************************************************************************");
    ESP_LOGW("", "");

    // filter input signal with equiripple filter
    ESP_LOGI(TAG, "Equiripple");
    start_t = dsp_get_cpu_cycle_count();
    dsps_fir_f32_ae32(&equiripple, input, output, N_SAMPLES);
    end_t = dsp_get_cpu_cycle_count();
    ESP_LOGI(TAG, "FIR of %d coeficients take %ld cycles for %d samples", FIR2_ORDER, (end_t - start_t), N_SAMPLES);
    plotFir(output);

    ESP_LOGI(TAG, "*** End Example. ***");
}