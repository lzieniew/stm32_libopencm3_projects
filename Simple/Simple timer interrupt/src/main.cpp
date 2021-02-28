#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/stm32/flash.h>

#include <overclocking.hpp>

#define LED1_PORT GPIOC
#define LED1_PIN GPIO13

constexpr int PWM_RESOLUTION_BITS = 8;
constexpr int PWM_RESOLUTION = 2 << PWM_RESOLUTION_BITS;

bool state = false;

static void clock_setup(void)
{
	// rcc_clock_setup_in_hse_8mhz_out_72mhz();
    rcc_clock_setup_in_hse_8mhz_out_128mhz();
    rcc_periph_clock_enable(RCC_TIM1);
    rcc_periph_clock_enable(RCC_GPIOA);
}

static void gpio_setup(void)
{
	/* Enable GPIO clock for leds. */
	rcc_periph_clock_enable(RCC_GPIOC);
    rcc_periph_clock_enable(RCC_AFIO);

	/* Enable led as output */
	gpio_set_mode(LED1_PORT, GPIO_MODE_OUTPUT_50_MHZ,
		GPIO_CNF_OUTPUT_PUSHPULL, LED1_PIN);
	gpio_set(LED1_PORT, LED1_PIN);

    gpio_set_mode(
        GPIOA, 
        GPIO_MODE_OUTPUT_50_MHZ, 
        GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, 
        GPIO8);
}

static void interrupt_tim_setup(void)
{
	/* Enable TIM2 clock. */
	rcc_periph_clock_enable(RCC_TIM2);

	/* Enable TIM2 interrupt. */
	nvic_enable_irq(NVIC_TIM2_IRQ);

	/* Reset TIM2 peripheral to defaults. */
	rcc_periph_reset_pulse(RST_TIM2);

	/* Timer global mode:
	 * - No divider
	 * - Alignment edge
	 * - Direction up
	 * (These are actually default values after reset above, so this call
	 * is strictly unnecessary, but demos the api for alternative settings)
	 */
	timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT,
		TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

	/*
	 * Please take note that the clock source for STM32 timers
	 * might not be the raw APB1/APB2 clocks.  In various conditions they
	 * are doubled.  See the Reference Manual for full details!
	 * In our case, TIM2 on APB1 is running at double frequency, so this
	 * sets the prescaler to have the timer run at 5kHz
	 */
	timer_set_prescaler(TIM2, 1);

	/* Disable preload. */
	timer_disable_preload(TIM2);
	timer_continuous_mode(TIM2);

	/* count full range, as we'll update compare value continuously */
	timer_set_period(TIM2, 128);

	// /* Set the initual output compare value for OC1. */
	// timer_set_oc_value(TIM2, TIM_OC1, 3);

	/* Counter enable. */
	timer_enable_counter(TIM2);

	/* Enable Channel 1 compare interrupt to recalculate compare values */
	timer_enable_irq(TIM2, TIM_DIER_CC1IE);
}

static void pwm_timer_setup(void)
{
    timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_CENTER_1, TIM_CR1_DIR_UP);
    timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM2);
    timer_enable_oc_output(TIM1, TIM_OC1);
    timer_enable_break_main_output(TIM1);
    timer_set_period(TIM1, PWM_RESOLUTION);
    timer_set_oc_value(TIM1, TIM_OC1, 100);
    timer_enable_counter(TIM1);
}

void tim2_isr(void)
{
	if (timer_get_flag(TIM2, TIM_SR_CC1IF)) {

		/* Clear compare interrupt flag. */
		timer_clear_flag(TIM2, TIM_SR_CC1IF);

		/* Toggle LED to indicate compare event. */
		// gpio_toggle(LED1_PORT, LED1_PIN);
        if(state){
            timer_set_oc_value(TIM1, TIM_OC1, 50);
        } else {
            timer_set_oc_value(TIM1, TIM_OC1, 75);
        }
        state = !state;
	}
}

int main(void)
{
	clock_setup();
	gpio_setup();
	interrupt_tim_setup();
    pwm_timer_setup();

	while (true) {
		// timer_set_period(TIM2, 128);
        // for(int i = 0; i < 10000000; i++){
        //     __asm__("nop");
        // }
        // timer_set_period(TIM2, 256);
        // for(int i = 0; i < 10000000; i++){
        //     __asm__("nop");
        // }
	}

	return 0;
}