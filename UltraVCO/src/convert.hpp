#include "adc_to_dac_and_step.hpp"

//for step 1
//timer_set_period(TIM2, 600); = 117Hz
// timer_set_period(TIM2, 1200); = 58Hz
// 100 = 498,3 Hz
// 103 = 497,9 Hz
// 140 = 492,9Hz
// 165 = 423,6Hz
// 160 = 436,7Hz
// 157 = 445 Hz
// 158 = 442,25Hz
// 159 = 439,5Hz

//for step 2
// 300 = 467,2Hz
// 310 = 452,2
// 320 = 438,1 Hz
// 318 = 440,8 Hz
// 319 = 439,4Hz


//for step 4
// 319 = 879,0 Hz
//1519 = 185 Hz
//2149 = 130,0 Hz
//1807 = 155,6 Hz

//adc_value: 0-4095
//PWM value: 0 to 255

const std::pair<int, int> convert_adc_value_to_PWM_value(uint16_t adc_value){
    return dac_values_and_steps[adc_value];
}