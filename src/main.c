#include <stdio.h>
#include <stdbool.h>
#include "nrf_delay.h"
#include "s25fl.h"
#include "pcf85.h"
#include "ains.h"

/*
 * This example uses only one instance of the SPI master.
 * Please make sure that only one instance of the SPI master is enabled in config file.
 */

static uint8_t WrBuf[1024];
static uint8_t RdBuf[1024];


static bool CompareBuffers(uint8_t * pBufA, uint8_t * pBufB, uint32_t len)
{
  uint32_t i;

  for(i = 0; i < len; i++)
  {
    if(pBufA[i] != pBufB[i]) return false;
  }

  return true;
}


static void InitBuffers(uint8_t * pBufA, uint8_t * pBufB, uint32_t len)
{
  uint32_t i;

  for(i = 0; i < len; i++)
  {
    pBufA[i] = i & 0xFF;
    pBufB[i] = 0;
  }
}


/**@brief Function for initializing bsp module.
 */
//void bsp_configuration()
//{
//    uint32_t err_code = NRF_SUCCESS;

//    NRF_CLOCK->LFCLKSRC            = (CLOCK_LFCLKSRC_SRC_Xtal << CLOCK_LFCLKSRC_SRC_Pos);
//    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
//    NRF_CLOCK->TASKS_LFCLKSTART    = 1;

//    while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0)
//    {
        // Do nothing.
//    }

//    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_MAX_TIMERS, APP_TIMER_OP_QUEUE_SIZE, NULL);
        
//    err_code = bsp_init(BSP_INIT_LED, APP_TIMER_TICKS(100, APP_TIMER_PRESCALER), NULL);
//    APP_ERROR_CHECK(err_code);
//}


int main(void)
{
  volatile bool S25FL_WriteComplete = false;
  volatile uint32_t S25FL_ReadedID = 0;
  volatile bool PCF85_Present = false;

  
//  if(S25FL_Init())
//  {
//    S25FL_ReadBuffer(0x00000000, RdBuf, 512);
//    S25FL_ReadBuffer(0x00010000, RdBuf, 512);
//    
//    //WARNING! Sector Address MUST be aligned to Sector Size
//    if(S25FL_SectorErase(0x00000000))
//    {
//      S25FL_ReadBuffer(0x00000000, RdBuf, 1024);
//      
//      InitBuffers(WrBuf, RdBuf, 1024);
//      
//      //WARNING! Address MUST be aligned to Page Size
//      // Random Writing Memory Driver is difficult and It requires a large RAM for Full Sector Saving
//      // And thats why the Flash MUST be written Page by Page
//      // In addition Page Write Command gives the highest Write Speed
//      if(S25FL_WriteBuffer(0x00000000, WrBuf, 753) == 753)
//      {
//        if(S25FL_ReadBuffer(0x00000000, RdBuf, 1024) == 1024)
//        {
//          S25FL_WriteComplete = CompareBuffers(WrBuf, RdBuf, 753);
//        }
//      }
//    }
//  }
//  //APP_ERROR_CHECK(err_code);
  
  
//  PCF85_Present = PCF85_Init();
//
//  pcf85time_t Time;
//  
//  Time.Seconds = 13;
//  Time.Minutes = 36;
//  Time.Hours = 23;
//  Time.Days = 10;
//  Time.WeekDays = 4;
//  Time.Months = 7;
//  Time.Years = 2015;
//  PCF85_SetTime(&Time);
  
  AINS_Init();
  
  while(1)
  {
    //PCF85_GetTime(&Time);
    //PCF85_SetTime(&Time);
    nrf_delay_ms(10);
  }
  
  //while(1);
}


/** @} */
