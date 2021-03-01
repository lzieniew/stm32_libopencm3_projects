// #include <libopencm3/stm32/rcc.h>
// #include <libopencm3/stm32/gpio.h>
// #include <libopencm3/stm32/adc.h>
// #include <libopencm3/stm32/dma.h>
// #include <libopencm3/stm32/usart.h>

// #define RCCLEDPORT (RCC_GPIOC)
// #define LEDPORT (GPIOC)
// #define LEDPIN (GPIO13)
// #define GPIO_MODE_OUTPUT GPIO_MODE_OUTPUT_2_MHZ
// #define GPIO_PUPD_NONE GPIO_CNF_OUTPUT_PUSHPULL

// volatile uint32_t adc_value;

// void gpio_init()
// {
//     rcc_periph_clock_enable(RCC_GPIOC);
//     gpio_set_mode(LEDPORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LEDPIN);
//     gpio_set(LEDPORT, LEDPIN);

//     rcc_periph_clock_enable(RCC_GPIOA);
//     gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO6);
// }

// void adc_init()
// {
//     rcc_periph_clock_enable(RCC_ADC1);
// 	adc_power_off(ADC1);
// 	rcc_periph_reset_pulse(RST_ADC1);
// 	rcc_set_adcpre(RCC_CFGR_ADCPRE_PCLK2_DIV2);
// 	adc_set_dual_mode(ADC_CR1_DUALMOD_IND);
// 	adc_disable_scan_mode(ADC1);
// 	adc_set_single_conversion_mode(ADC1);
// 	adc_set_sample_time(ADC1, ADC_CHANNEL0, ADC_SMPR_SMP_1DOT5CYC);
// 	adc_enable_external_trigger_regular(ADC1, ADC_CR2_EXTSEL_SWSTART);
// 	adc_power_on(ADC1);
// 	adc_reset_calibration(ADC1);
// 	adc_calibrate(ADC1);
// }

// void adc_init_dma()
// {
//     // dma
//     gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO0);
//     gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO1);
//     rcc_periph_clock_enable(RCC_DMA1);
//     dma_disable_channel(DMA1, DMA_CHANNEL1);
//     dma_enable_circular_mode(DMA1, DMA_CHANNEL1);
//     dma_disable_memory_increment_mode(DMA1, DMA_CHANNEL1);
//     dma_disable_peripheral_increment_mode(DMA1, DMA_CHANNEL1);
//     dma_disable_transfer_complete_interrupt(DMA1, DMA_CHANNEL1);
//     dma_set_memory_address(DMA1, DMA_CHANNEL1, (uint32_t)&adc_value);
//     dma_set_number_of_data(DMA1, DMA_CHANNEL1, 1);
//     dma_set_peripheral_address(DMA1, DMA_CHANNEL1, (uint32_t) &ADC_DR(ADC1));
//     dma_set_priority(DMA1, DMA_CHANNEL1, DMA_CCR_PL_MEDIUM);
//     dma_set_read_from_peripheral(DMA1, DMA_CHANNEL1);
//     dma_set_memory_size(DMA1, DMA_CHANNEL1, DMA_CCR_MSIZE_32BIT);
// 	dma_set_peripheral_size(DMA1, DMA_CHANNEL1, DMA_CCR_PSIZE_32BIT);
//     dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL1);
//     // ADC_CR2(adc) |= ADC_CR2_DDS;

//     dma_enable_channel(DMA1, DMA_CHANNEL1);

//     //adc
//     rcc_periph_clock_enable(RCC_ADC1);
// 	adc_power_off(ADC1);
// 	rcc_periph_reset_pulse(RST_ADC1);
// 	rcc_set_adcpre(RCC_CFGR_ADCPRE_PCLK2_DIV2);
// 	// adc_set_dual_mode(ADC_CR1_DUALMOD_IND);
//     adc_set_continuous_conversion_mode (ADC1);
// 	adc_enable_scan_mode(ADC1);

// 	// adc_set_single_conversion_mode(ADC1);
// 	adc_set_sample_time(ADC1, ADC_CHANNEL0, ADC_SMPR_SMP_1DOT5CYC);
//     adc_enable_dma(ADC1);
// 	// adc_enable_external_trigger_regular(ADC1, ADC_CR2_EXTSEL_SWSTART);
// 	adc_power_on(ADC1);
// 	adc_reset_calibration(ADC1);
// 	adc_calibrate(ADC1);
//     adc_start_conversion_regular(ADC1);
    
// }

// uint32_t adc_read()
// {
//     adc_start_conversion_regular(ADC1);
// 	while (! adc_eoc(ADC1));
// 	return adc_read_regular(ADC1);
// }

// void dma1_channel1_isr(void) {
//     dma_clear_interrupt_flags(DMA1, DMA_CHANNEL1, DMA_IFCR_CGIF1);
//     gpio_clear(LEDPORT, LEDPIN);
// }

// int main(void)
// {   
//     gpio_init();
//     // adc_init();
//     adc_init_dma();

//     while(1){
//         uint32_t val = adc_value;
//         // uint32_t val = adc_read();
//         // if(val > 2000){
//         //     gpio_set(GPIOC, GPIO13);
//         // } else {
//         //     gpio_clear(GPIOC, GPIO13);
//         // }
//         gpio_toggle(GPIOA, GPIO6);
//         // for(int i =0; i<1000; i++){
//         //     __asm__("nop");
//         // }
//     }
// }

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <wctype.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
     
void delay(uint32_t n) {
    for (volatile int i = 0; i < n; i++)
        __asm__("nop");
}
    
static void clock_setup(void) {
    rcc_clock_setup_in_hse_8mhz_out_72mhz();
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_AFIO);
    rcc_periph_clock_enable(RCC_USART1);
    rcc_periph_clock_enable(RCC_DMA1);
    rcc_periph_clock_enable(RCC_ADC1);
}
    
volatile uint16_t adc_res[2];
    
void adc_setup(void) {
    uint8_t channel_seq[16];

    gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO0);
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO1);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);
    adc_power_off(ADC1);
    
    adc_enable_scan_mode(ADC1);
    adc_set_continuous_conversion_mode(ADC1);
    adc_disable_discontinuous_mode_regular(ADC1);
    
    adc_enable_external_trigger_regular(ADC1, ADC_CR2_EXTSEL_SWSTART);
    adc_set_right_aligned(ADC1);
    adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_7DOT5CYC);
    
    adc_power_on(ADC1);
    
    delay(10);
    
    adc_reset_calibration(ADC1);
    adc_calibrate(ADC1);
    
    channel_seq[0] = 0;
    channel_seq[1] = 1;
    
    adc_set_regular_sequence(ADC1, 2, channel_seq);
    
    adc_enable_dma(ADC1);
    delay(100);
    adc_start_conversion_regular(ADC1);
}
    
void dma_setup(void) {
    dma_disable_channel(DMA1, DMA_CHANNEL1);
    
    dma_enable_circular_mode(DMA1, DMA_CHANNEL1);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL1);
    
    dma_set_peripheral_size(DMA1, DMA_CHANNEL1, DMA_CCR_PSIZE_16BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL1, DMA_CCR_MSIZE_16BIT);
    
    dma_set_read_from_peripheral(DMA1, DMA_CHANNEL1);
    dma_set_peripheral_address(DMA1, DMA_CHANNEL1, (uint32_t) &ADC_DR(ADC1));
    
    dma_set_memory_address(DMA1, DMA_CHANNEL1, (uint32_t) &adc_res);
    dma_set_number_of_data(DMA1, DMA_CHANNEL1, 2);
    
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL1);
    dma_enable_channel(DMA1, DMA_CHANNEL1);
}
    
void dma1_channel1_isr(void) {
    dma_clear_interrupt_flags(DMA1, DMA_CHANNEL1, DMA_IFCR_CGIF1);
}
    
int main(void) {
    clock_setup();
    // uart_setup();
    dma_setup();
    adc_setup();
    
    while(1) {
        // printf("%6lu %6lu\r\n", adc_res[0], adc_res[1]);

        if(adc_res[0] > 2000){
            gpio_set(GPIOC, GPIO13);
        } else {
            gpio_clear(GPIOC, GPIO13);
        }
        // delay(80000);
    }
    return 0;
}

