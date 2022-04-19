#include "em_device.h"
#include "em_chip.h"
#include "em_core.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_iadc.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

// Set CLK_ADC to 10 MHz
#define CLK_SRC_ADC_FREQ 20000000 // CLK_SRC_ADC
#define CLK_ADC_FREQ 100000       // CLK_ADC - 10 MHz max in normal mode
#define EM2DEBUG 1

static void readBatteryVoltage()
{

  uint32_t adc_Value;

  IADC_Init_t init = IADC_INIT_DEFAULT;
  IADC_AllConfigs_t initAllConfigs = IADC_ALLCONFIGS_DEFAULT;
  IADC_InitSingle_t initSingle = IADC_INITSINGLE_DEFAULT;
  IADC_SingleInput_t initSingleInput = IADC_SINGLEINPUT_DEFAULT;

  CMU_ClockEnable(cmuClock_IADC0, true);

  IADC_reset(IADC0);

  CMU_ClockSelectSet(cmuClock_IADCCLK, cmuSelect_FSRCO);

  init.warmup = iadcWarmupNormal;
  init.timerCycles = 200;
  init.srcClkPrescale = IADC_calcSrcClkPrescale(IADC0, CLK_SRC_ADC_FREQ, 0);

  // Internal Ref
  initAllConfigs.configs[0].reference = iadcCfgReferenceInt1V2;
  initAllConfigs.configs[0].adcClkPrescale = IADC_calcAdcClkPrescale(IADC0,
                                                                     CLK_ADC_FREQ,
                                                                     0,
                                                                     iadcCfgModeNormal,
                                                                     init.srcClkPrescale);
  /*
   * Specify the input channel.  When negInput = iadcNegInputGnd, the
   * conversion is single-ended.
   */
  initSingleInput.posInput = iadcPosInputAvdd | 1;
  initSingleInput.negInput = iadcNegInputGnd;

  initSingle.triggerAction = iadcTriggerActionOnce;

  IADC_init(IADC0, &init, &initAllConfigs);
  IADC_initSingle(IADC0, &initSingle, &initSingleInput);
  IADC_command(IADC0, iadcCmdStartSingle);

  while ((IADC0->STATUS & (_IADC_STATUS_CONVERTING_MASK | _IADC_STATUS_SINGLEFIFODV_MASK)) != IADC_STATUS_SINGLEFIFODV)
    ;

  adc_Value = IADC_pullSingleFifoResult(IADC0).data;
  double result = ((adc_Value * 4 * 1.21) / (0xFFF));
  IADC_reset(IADC0);
  CMU_ClockEnable(cmuClock_FSRCO, false);
  CMU_ClockEnable(cmuClock_IADC0, false);
  // for Vref = AVDD = 3.30V, 12 bits represents 6.60V full scale IADC range.
}

/*****************************************************************************
 * @brief GPIO Interrupt handler for even pins.
 *****************************************************************************/
void GPIO_EVEN_IRQHandler(void)
{
  // Get and clear all pending GPIO interrupts
  uint32_t interruptMask = GPIO_IntGet();
  GPIO_IntClear(interruptMask);

  // Check if button 0 was pressed
  if (interruptMask & (1 << 0))
  {
    readBatteryVoltage();
  }
}

/*****************************************************************************
 * @brief  IADC IRQ Handler
 *****************************************************************************/
// void
// IADC_IRQHandler (void)
//{
//  sample = IADC_pullSingleFifoResult (IADC0);
//  singleResult = 4 * sample.data * 1.21 / 0xFFF;
//
//  IADC_clearInt (IADC0, IADC_IF_SINGLEDONE);
//}

static void gpioSetup(void)
{
  // Configure GPIO Clock. Note this is not required for EFR32xG21
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Configure Button PB0 as input and enable interrupt
  GPIO_PinModeSet(gpioPortB, 0, gpioModeInputPull, 1);
  GPIO_ExtIntConfig(gpioPortB, 0, 0, false, true, true);

  // Enable EVEN interrupt to catch button press that changes slew rate
  NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);
}

/*****************************************************************************
 * @brief  Main function
 *****************************************************************************/
int main(void)
{
  CHIP_Init();
  gpioSetup();

#ifdef EM2DEBUG
#if (EM2DEBUG == 1)
  // Enable debug connectivity in EM2
  EMU->CTRL_SET = EMU_CTRL_EM2DBGEN;
#endif
#endif

  while (1)
  {
    // Enter EM2 sleep, wait for IADC interrupt
    EMU_EnterEM2(false);
  }
}
