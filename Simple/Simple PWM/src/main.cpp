#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

static void clock_setup(void)
{
    rcc_clock_setup_in_hse_8mhz_out_72mhz();

    rcc_periph_clock_enable(RCC_TIM1);
    rcc_periph_clock_enable(RCC_GPIOA);
	
}

static void gpio_setup(void)
{
    rcc_periph_clock_enable(RCC_AFIO);
    gpio_set_mode(
        GPIOA, 
        GPIO_MODE_OUTPUT_50_MHZ, 
        GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, 
        GPIO8);
}

static void timer_setup(void)
{
    timer_set_mode(TIM1, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_CENTER_1, TIM_CR1_DIR_UP);
    timer_set_oc_mode(TIM1, TIM_OC1, TIM_OCM_PWM2);
    timer_enable_oc_output(TIM1, TIM_OC1);
    timer_enable_break_main_output(TIM1);
    timer_set_period(TIM1, 256);
    timer_set_oc_value(TIM1, TIM_OC1, 100);
    timer_enable_counter(TIM1);
}

int main()
{
    clock_setup();
    gpio_setup();
    timer_setup();

    while(true){
        timer_set_oc_value(TIM1, TIM_OC1, 50);
        for(int i = 0; i < 10000000; i++){
            __asm__("nop");
        }
        timer_set_oc_value(TIM1, TIM_OC1, 150);
        for(int i = 0; i < 10000000; i++){
            __asm__("nop");
        }
    }
}