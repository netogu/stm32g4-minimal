#include "board/bsp.h"
#include "tusb.h"

//------------------------------------------------------+
// HRTIM Interrupt Handler
//------------------------------------------------------+

void HRTIM1_TIMA_IRQHandler(void) {

    /* REP Interrupt Routine */
    if (HRTIM1->sTimerxRegs[HRTIM_TIM_A].TIMxISR & HRTIM_TIMISR_REP) { 
        // Disable continuous mode
        HRTIM1->sTimerxRegs[HRTIM_TIM_A].TIMxCR &= ~(HRTIM_TIMCR_CONT);
        // Clear REP interrupt
        HRTIM1->sTimerxRegs[HRTIM_TIM_A].TIMxICR |= HRTIM_TIMICR_REPC;
    }

    
    /* RESET Roll-Over Interupt */
    if (HRTIM1->sTimerxRegs[HRTIM_TIM_A].TIMxISR & HRTIM_TIMISR_RST) { 
        // Togle test pin
        // gpio_pin_set(&io.test_pin1);
        // gpio_pin_clear(&io.test_pin1);
        // Clear RST interrupt
        HRTIM1->sTimerxRegs[HRTIM_TIM_A].TIMxICR |= HRTIM_TIMICR_RSTC;
    }
}

//------------------------------------------------------+
// ADC Interrupt Handler
//------------------------------------------------------+

// void ADC1_2_IRQHandler(void) {
//     // Clear the ADC interrupt
//     ADC1->ISR |= ADC_ISR_EOC;
//     // Read the ADC value
//     uint16_t adc_value = ADC1->DR;
//     // Togle test pin
//     gpio_pin_set(&io.test_pin1);
//     gpio_pin_clear(&io.test_pin1);
// }

//--------------------------------------------------------------------+
// USB interrupt Handler
//--------------------------------------------------------------------+

void USB_HP_IRQHandler(void) {
  tud_int_handler(0);
}

uint32_t usb_lp_irq_counter = 0;
void USB_LP_IRQHandler(void) {
  tud_int_handler(0);
  usb_lp_irq_counter++;
}

void USBWakeUp_IRQHandler(void) {
  tud_int_handler(0);
}
