#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <stdio.h>

void debug_delay(uint32_t n) {
	for (volatile unsigned int i = 0; i < n; i++)
		__asm__("nop");
}



int print_each_digit(int x)
{
    if(x >= 10)
       print_each_digit(x / 10);

    int digit = x % 10;

    gpio_set(GPIOC, GPIO13);
    debug_delay(10);
    gpio_clear(GPIOC, GPIO13);

    for(int a = 0; a < digit ; a++)
    {
        gpio_set(GPIOC, GPIO13);
        // debug_delay(1);
        gpio_clear(GPIOC, GPIO13);
    }
}



void print_int(int i)
{ 
    print_each_digit(i);

    gpio_set(GPIOC, GPIO13);
    debug_delay(10);
    gpio_clear(GPIOC, GPIO13);
}