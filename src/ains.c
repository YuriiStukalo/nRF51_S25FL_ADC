#include "ains.h"

static nrf_drv_timer_t Timer = NRF_DRV_TIMER_INSTANCE(0);

#ifndef NRF_APP_PRIORITY_HIGH
#define NRF_APP_PRIORITY_HIGH 1
#endif




void Timer_EventHandler(nrf_timer_event_t event_type, void * p_context)
{
  return;
}


void AINS_Init(void)
{
  uint32_t                      pCompareEvent;
  //uint32_t                      pGPIOTETask;
  uint32_t                      pADCTask;
  nrf_ppi_channel_t             PPIChannel;
  ret_code_t                    error;
  //nrf_drv_gpiote_out_config_t   GPIOTEConfig = GPIOTE_CONFIG_OUT_TASK_TOGGLE(false);
  uint32_t                      TimerTicks;
  nrf_adc_config_t              ADCConfig = NRF_ADC_CONFIG_DEFAULT;
  
  
  //Initialize PPI
  error = nrf_drv_ppi_init();
  APP_ERROR_CHECK(error);

  //Initialize GPIOTE
  //error = nrf_drv_gpiote_init();
  //APP_ERROR_CHECK(error);

  //Initialize Timer
  error = nrf_drv_timer_init(&Timer, NULL, Timer_EventHandler);
  APP_ERROR_CHECK(error);
  *(uint32_t *)0x40008C0C = 1;
  
  // Initialize ADC
  ADCConfig.scaling    = NRF_ADC_CONFIG_SCALING_INPUT_ONE_THIRD;
  ADCConfig.resolution = NRF_ADC_CONFIG_RES_10BIT;
  ADCConfig.reference  = NRF_ADC_CONFIG_REF_VBG;
  nrf_adc_configure(&ADCConfig);
  nrf_adc_input_select(AIN_0_CHN);
  nrf_adc_int_enable(ADC_INTENSET_END_Enabled << ADC_INTENSET_END_Pos);
  NVIC_SetPriority(ADC_IRQn, NRF_APP_PRIORITY_HIGH);
  NVIC_EnableIRQ(ADC_IRQn);

  // Setup PPI channel with event from TIMER compare and task GPIOTE pin toggle.
  //error = nrf_drv_gpiote_out_init(AIN_0_PIN, &GPIOTEConfig);
  //APP_ERROR_CHECK(error);

  //Configure Timer to generate an event every 1000 us
  TimerTicks = nrf_drv_timer_us_to_ticks(&Timer, 1000);
  nrf_drv_timer_extended_compare(&Timer, NRF_TIMER_CC_CHANNEL0, TimerTicks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, false);
  
  
  
  
  
  //Allocate PPI Channel
  error = nrf_drv_ppi_channel_alloc(&PPIChannel);
  APP_ERROR_CHECK(error);

  pCompareEvent = nrf_drv_timer_event_address_get(&Timer, NRF_TIMER_EVENT_COMPARE0);
  //pGPIOTETask = nrf_drv_gpiote_out_task_addr_get(AIN_0_PIN);
  pADCTask = (uint32_t)nrf_adc_task_address_get(NRF_ADC_TASK_START);

  error = nrf_drv_ppi_channel_assign(PPIChannel, pCompareEvent, pADCTask); //pGPIOTETask);
  APP_ERROR_CHECK(error);

  error = nrf_drv_ppi_channel_enable(PPIChannel);
  APP_ERROR_CHECK(error);

  //nrf_drv_gpiote_out_task_enable(AIN_0_PIN);


  // Enable timer
  nrf_drv_timer_enable(&Timer);
}



///**
// * @brief ADC interrupt handler.
// */
void ADC_IRQHandler(void)
{
  volatile int32_t adc_sample;

  nrf_adc_conversion_event_clean();

  adc_sample = nrf_adc_result_get();
  
  if(adc_sample > 938)
  {
    adc_sample = 0;
  }

  // trigger next ADC conversion
  //nrf_adc_start();
}





