#ifndef __AINS_H
#define __AINS_H

#include <stdbool.h>
#include <stdint.h>
#include "nrf.h"
#include "nrf_gpiote.h"
#include "nrf_gpio.h"
//#include "boards.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_timer.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "nrf_adc.h"

#define AIN_0_PIN    27
#define AIN_0_CHN    NRF_ADC_CONFIG_INPUT_1

void AINS_Init(void);

#endif //__AINS_H
