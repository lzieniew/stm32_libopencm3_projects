#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <wctype.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>

#include <overclocking.hpp>
#include <waveshapes/sinus.hpp>
#include <waveshapes/triangle.hpp>
#include <waveshapes/saw.hpp>
#include <waveshapes/square.hpp>

#define LED1_PORT GPIOC
#define LED1_PIN GPIO13

constexpr uint16_t adc_vals[4095]{};

constexpr int PWM_RESOLUTION_BITS = 8;
//2^8 = 256 values, from 0 to 255
constexpr int PWM_RESOLUTION = 2 << PWM_RESOLUTION_BITS;

const float *wave_table;

constexpr int wave_table_len = 512;
int wave_table_step = 10;

//adc value is from 0 to 4095
volatile uint16_t adc_res[3];
volatile uint16_t wave_counter{0};

void delay(uint32_t n) {
	for (volatile unsigned int i = 0; i < n; i++)
		__asm__("nop");
}

inline void chooseWave(){
	uint16_t wave_select = adc_res[2];
	if(wave_select < 900){
		wave_table = sinus_tab;
	} else if(wave_select > 1024 && wave_select < 1900){
		wave_table = triangle_tab;
	} else if(wave_select > 2048 && wave_select < 3072){
		wave_table = saw_tab;
	} else if(wave_select > 2900){
		wave_table = square_tab;
	}
}

inline void chooseStep(){
	uint16_t step_select = adc_res[1];
	wave_table_step = step_select / 256;
}

static void clock_setup(void)
{
	rcc_clock_setup_in_hse_8mhz_out_72mhz();
    // rcc_clock_setup_in_hse_8mhz_out_128mhz();
    rcc_periph_clock_enable(RCC_TIM1);
    rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_GPIOC);
	rcc_periph_clock_enable(RCC_AFIO);
	rcc_periph_clock_enable(RCC_USART1);
	rcc_periph_clock_enable(RCC_DMA1);
	rcc_periph_clock_enable(RCC_ADC1);
}

void adc_setup(void) {
	uint8_t channel_seq[16];

	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO0);
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO1);
	gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_ANALOG, GPIO2);
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
	channel_seq[2] = 2;
	
	adc_set_regular_sequence(ADC1, 3, channel_seq);
	
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
	dma_set_number_of_data(DMA1, DMA_CHANNEL1, 3);
	
	dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL1);
	dma_enable_channel(DMA1, DMA_CHANNEL1);
}

static void gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_AFIO);

	gpio_set_mode(LED1_PORT, GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL, LED1_PIN);
	gpio_set(LED1_PORT, LED1_PIN);

    gpio_set_mode(
        GPIOA, 
        GPIO_MODE_OUTPUT_50_MHZ, 
        GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, 
        GPIO8);
}

void dma1_channel1_isr(void) {
    dma_clear_interrupt_flags(DMA1, DMA_CHANNEL1, DMA_IFCR_CGIF1);
}

static void interrupt_tim_setup(void)
{
	rcc_periph_clock_enable(RCC_TIM2);
	nvic_enable_irq(NVIC_TIM2_IRQ);
	/* Reset TIM2 peripheral to defaults. */
	rcc_periph_reset_pulse(RST_TIM2);
	timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT,
		TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	timer_set_prescaler(TIM2, 1);
	timer_disable_preload(TIM2);
	timer_continuous_mode(TIM2);

	timer_set_period(TIM2, 2004);

	// /* Set the initual output compare value for OC1. */
	timer_set_oc_value(TIM2, TIM_OC1, 0);

	timer_enable_counter(TIM2);
	timer_enable_irq(TIM2, TIM_DIER_CC1IE);
}

static void pwm_timer_setup(void)
{
    timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_CENTER_1, TIM_CR1_DIR_UP);
    timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM2);
    timer_enable_oc_output(TIM1, TIM_OC1);
    timer_enable_break_main_output(TIM1);
    timer_set_period(TIM1, PWM_RESOLUTION);
    // timer_set_oc_value(TIM1, TIM_OC1, 100);
    timer_enable_counter(TIM1);
}

void tim2_isr(void)
{
	if (timer_get_flag(TIM2, TIM_SR_CC1IF)) {
		timer_clear_flag(TIM2, TIM_SR_CC1IF);
		chooseWave();
		chooseStep();
        timer_set_oc_value(TIM1, TIM_OC1, wave_table[wave_counter]);
		wave_counter = wave_counter >= (wave_table_len-wave_table_step) ? 0 : wave_counter + wave_table_step;
		// int i = adc_res[0];
		// timer_set_period(TIM2, adc_res[0]);
		// timer_set_period(TIM2, 600);
		timer_set_period(TIM2, (adc_res[0] + 1) * 2);
	}
}

int main(void)
{ 
	clock_setup();
	gpio_setup();
	interrupt_tim_setup();
    pwm_timer_setup();

	dma_setup();
    adc_setup();
    
    while(1) {
        if(adc_res[2] > 2000){
            gpio_set(GPIOC, GPIO13);
        } else {
            gpio_clear(GPIOC, GPIO13);
        }
        // delay(80000);
    }

	while(1){
		gpio_set(GPIOC, GPIO13);
		delay(100000);
		gpio_clear(GPIOC, GPIO13);
		delay(100000);
	}

	return 0;
}