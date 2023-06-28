/*  FFT plot

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
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "soc/uart_struct.h"
#include <math.h>
#include "esp_adc/adc_continuous.h"
#include "esp_dsp.h"
#include "rtc_wdt.h"
#include "Classifier.h"

/*==================[MACROS AND DEFINITIONS]=================================*/

/* Do not modify */
#define FS_1K           1000                    // Sample frequency: 1kHz
#define FS_2K           2000                    // Sample frequency: 2kHz
#define FS_4K           4000                    // Sample frequency: 4kHz
#define FS_8K           8000                    // Sample frequency: 8kHz
#define FS_16K          16000                   // Sample frequency: 16kHz
#define FS_32K          32000                   // Sample frequency: 32kHz   
#define FS_CAL          1.22                    // 
#define BUFFER_SIZE     1024                    // Buffer for continuous ADC
#define MAX_ADC         4095                    // ADC 12 bit
#define VDD             3300                    // VDD is 3.3V, 3300mV


/* User modificable Macros */
#define SAMPLE_FREQ     FS_8K                   // Sample frequency (select one of defined frequencies: FS_1K, FS_2K, ...)
#define N_SAMPLES       4096                    // Number of samples to plot (needs to be multiple of 1024)
#define ADC_CHANNEL     ADC_CHANNEL_6           // ADC channel 
#define PLOT_WIDTH      128                     // Plot width in characters
#define PLOT_HEIGHT     20                      // Plot height in characters
#define TAG             "FFT plot"              // Tag for LOG

/*==================[INTERNAL DATA DEFINITION]===============================*/

/* FreeRTOS variables */
TaskHandle_t fftTaskHandle = NULL;
TaskHandle_t plotTaskHandle = NULL;

adc_continuous_handle_t adc_handle = NULL;

// Input signal
__attribute__((aligned(16)))
float signal[N_SAMPLES];
// Window coefficients
__attribute__((aligned(16)))
float wind[N_SAMPLES];
// working complex array
__attribute__((aligned(16)))
float fft[N_SAMPLES*2];

float pcp[12];
float pcp_norm[12];
float pcp_norm_disp[12];
float pcp_sum = 0;
#define fref 130.81

bool pcp_send = false;
enum{FFT, PCP, LOGGING, PREDICTION};
enum{MV, DB};
uint8_t fft_unit = MV; 
uint8_t plot_config = LOGGING;
/*==================[INTERNAL FUNCTIONS DEFINITION]==========================*/



int M(uint16_t l, uint16_t p){
	if (l == 0){return -1;}
	float fs = SAMPLE_FREQ;
	float num = fs* l;
	float den = N_SAMPLES * fref;
	float div = num/den;
	float lg = log2f(div);
	lg = round(12*lg);
    return ((int)lg%12);
}

void pcdComputing(float* data, uint16_t N){
pcp_sum=0;
for (int p = 0 ; p < 12 ; p++){
	pcp[p]=0;
}
for (int p = 0 ; p < 12 ; p++) {
	for (int l = 0 ; l < N/2 ; l++) {
        if (p == M(l, p)){
            pcp[p] += labs((int)data[l])*labs((int)data[l]);         
        	}
		}
        pcp_sum += pcp[p];
	}
for (int p = 0 ; p < 12 ; p++) {
	pcp_norm[p] = (pcp[p]/pcp_sum);
    pcp_norm_disp[p] = (pcp[p]/pcp_sum)*100.0;
    if(pcp_norm[p]>0.25){
        pcp_send = true;
        }
	}
}


void fftTask(void *arg){
    esp_err_t ret;
    uint32_t ret_num = 0;
    uint8_t data[BUFFER_SIZE*SOC_ADC_DIGI_RESULT_BYTES];
    static uint16_t index = 0;
    const uint8_t STEP = FS_32K/SAMPLE_FREQ;
    // Holds the value of the computed coefficient
	
    ESP_LOGI(TAG, "*** Start FFT Task ***");
    
    while(1){  
        /* Wait untill next convertion done event*/
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        
        /* Read ADC buffer and format data */
        ret = adc_continuous_read(adc_handle, data, BUFFER_SIZE*SOC_ADC_DIGI_RESULT_BYTES, &ret_num, 0);
        if (ret == ESP_OK) {
            for (int i = 0; i < BUFFER_SIZE/STEP; i++) {
                adc_digi_output_data_t *p = (void*)&data[i*SOC_ADC_DIGI_RESULT_BYTES*STEP];  
                signal[index+i] = (float)(p->type1.data) * (float)VDD / (float)MAX_ADC;
            }
        } else if (ret == ESP_ERR_TIMEOUT) {
                //We try to read until API returns timeout, which means there's no available data
                break;
            }
        index += (BUFFER_SIZE/STEP);
        if (index >= N_SAMPLES){
            // Clear imaginary part of the complex signal
            memset(fft, 0, N_SAMPLES*SOC_ADC_DIGI_RESULT_BYTES*sizeof(float));
            // Multiply input array with window and store as real part
            dsps_mul_f32(signal, wind, fft, N_SAMPLES, 1, 1, 2);    
            // Calculate FFT  
            dsps_fft2r_fc32(fft, N_SAMPLES);
            // Bit reverse
            dsps_bit_rev_fc32(fft, N_SAMPLES);
            // Convert one complex vector to two complex vectors
            dsps_cplx2reC_fc32(fft, N_SAMPLES);
            switch(fft_unit){
                case MV:
                    // Calculate FFT magnitude in mV
                    for (int j = 0; j < N_SAMPLES; j++){
                        fft[j] = 2*(sqrt(fft[j*2+0]*fft[j*2+0] + fft[j*2+1]*fft[j*2+1])) / (N_SAMPLES/2);
                    }
                    fft[0] = fft[0] / 2;
                    break;
                case DB:
                    // Calculate FFT magnitude in dB
                    for (int i = 0 ; i < N_SAMPLES ; i++) {
    	                fft[i] = 10 * log10f((fft[i * 2 + 0] * fft[i * 2 + 0] + fft[i * 2 + 1] * fft[i * 2 + 1])/N_SAMPLES);
                    }
                    break;
            }
            pcdComputing(fft, N_SAMPLES/2);
            /* Notify to plot task */
            xTaskNotifyGive(plotTaskHandle);
            index = 0;
        }
    }
}

void plotTask(void *arg){
    
    ESP_LOGI(TAG, "*** Start plot Task ***");
    while(1){
        /* Wait untill next fft is ready to plot */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);  
        switch(plot_config){
        case FFT:
            /* Plot FFT */
            dsps_view(fft, N_SAMPLES/2, PLOT_WIDTH, PLOT_HEIGHT,-20, 100, '*');
            ESP_LOGI("Plot", "Fs: %dHz", SAMPLE_FREQ);
            break;
        case PCP:
            /* Plot PCP */
             dsps_view(pcp_norm_disp, 12, PLOT_WIDTH, PLOT_HEIGHT,  0, 100, '_');
             ESP_LOGI("Plot", "Fs: %dHz", SAMPLE_FREQ);
             break;
        case LOGGING:
            if(pcp_send){
                for (int j = 0; j < 11; j++){
                    printf("%.2f,", pcp_norm[j]);
                }
                printf("%.2f\r\n", pcp_norm[11]);
                pcp_send = false;
            }
            break;
        case PREDICTION:
            /* Model infering */
            if(pcp_send){
                 printf("%s\r\n", predictLabel(pcp_norm));
                 pcp_send = false;
            }
            break;
        }
    }
}

static bool IRAM_ATTR ConvDoneCallback(adc_continuous_handle_t handle, const adc_continuous_evt_data_t *edata, void *user_data){
    BaseType_t mustYield = pdFALSE;
    //Notify that ADC continuous driver has done enough number of conversions
    vTaskNotifyGiveFromISR(fftTaskHandle, &mustYield);

    return (mustYield == pdTRUE);
}

void app_main(void){
    /* GPIO14 used to check sample frequency */    
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;      // disable interrupt
    io_conf.mode = GPIO_MODE_OUTPUT;            // set as output mode   
    io_conf.pin_bit_mask = 1ULL << GPIO_NUM_14; // bit mask of the pins that you want to set,e.g.GPIO18/19  
    io_conf.pull_down_en = 0;                   // disable pull-down mode
    io_conf.pull_up_en = 0;                     // disable pull-up mode
    gpio_config(&io_conf);                      // configure GPIO with the given settings
    ESP_LOGI(TAG, "GPIO Configured");
    
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

    /* ADC configuration */
    adc_continuous_handle_cfg_t adc_config = {
        .max_store_buf_size = 2*BUFFER_SIZE*SOC_ADC_DIGI_RESULT_BYTES,      // Max length of the conversion Results that driver can store, in bytes.
        .conv_frame_size = BUFFER_SIZE*SOC_ADC_DIGI_RESULT_BYTES,           // Conversion frame size, in bytes.
    };
    ESP_ERROR_CHECK(adc_continuous_new_handle(&adc_config, &adc_handle));
    adc_continuous_config_t dig_cfg = {
        .pattern_num = 1,                       // Number of ADC channels that will be used 
        .sample_freq_hz = (int)(FS_32K*FS_CAL), // Expected ADC sampling frequency in Hz
        .conv_mode = ADC_CONV_SINGLE_UNIT_1,    // Only use ADC1 for conversion
        .format = ADC_DIGI_OUTPUT_FORMAT_TYPE1, // Conversion output format
    };
    adc_digi_pattern_config_t adc_pattern = {
        .atten = ADC_ATTEN_DB_2_5,               // ADC attenuation
        .channel = ADC_CHANNEL,                 // The IO corresponding ADC channel number
        .unit = ADC_UNIT_1,                     // The ADC that the IO is subordinate to
        .bit_width = SOC_ADC_DIGI_MAX_BITWIDTH, // The bitwidth of the raw conversion result
    };
    dig_cfg.adc_pattern = &adc_pattern;
    ESP_ERROR_CHECK(adc_continuous_config(adc_handle, &dig_cfg));
    adc_continuous_evt_cbs_t adc_cb = {
        .on_conv_done = ConvDoneCallback,       // Configure callback function for convertion done event
    };
    ESP_ERROR_CHECK(adc_continuous_register_event_callbacks(adc_handle, &adc_cb, NULL));
    ESP_LOGI(TAG, "ADC Configured");

    /* Initialize FFT */
    esp_err_t ret = dsps_fft2r_init_fc32(NULL, CONFIG_DSP_MAX_FFT_SIZE);
    if (ret != ESP_OK){
        ESP_LOGE(TAG, "Not possible to initialize FFT. Error = %i", ret);
        return;
    }
    // Generate Hann window
    dsps_wind_hann_f32(wind, N_SAMPLES);

    ESP_LOGI(TAG, "*** Start Example. ***");

    /* Create task */
    xTaskCreatePinnedToCore(fftTask, "fftTask", 8192, NULL, 10, &fftTaskHandle, 0);
    xTaskCreatePinnedToCore(plotTask, "plotTask", 2048, NULL, 8, &plotTaskHandle, 1);

    /* Start ADC*/
    ESP_ERROR_CHECK(adc_continuous_start(adc_handle));
}