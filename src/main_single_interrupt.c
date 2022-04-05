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
#define CLK_SRC_ADC_FREQ        20000000  // CLK_SRC_ADC
#define CLK_ADC_FREQ            100000  // CLK_ADC - 10 MHz max in normal mode
#define EM2DEBUG                  1

/*******************************************************************************
 ***************************   GLOBAL VARIABLES   ******************************
 ******************************************************************************/

static volatile IADC_Result_t sample;
static volatile double singleResult;

/**************************************************************************//**
 * @brief  IADC initialization
 *****************************************************************************/
void
initIADC (void)
{
  // Declare initialization structures
  IADC_Init_t init = IADC_INIT_DEFAULT;
  IADC_AllConfigs_t initAllConfigs = IADC_ALLCONFIGS_DEFAULT;
  IADC_InitSingle_t initSingle = IADC_INITSINGLE_DEFAULT;

  // Single input structure
  IADC_SingleInput_t singleInput = IADC_SINGLEINPUT_DEFAULT;

  /*
   * Enable IADC0 and GPIO register clock.
   *
   * Note: On EFR32xG21 devices, CMU_ClockEnable() calls have no effect
   * as clocks are enabled/disabled on-demand in response to peripheral
   * requests.  Deleting such lines is safe on xG21 devices and will
   * reduce provide a small reduction in code size.
   */
  CMU_ClockEnable (cmuClock_IADC0, true);

  // Use the FSRC0 as the IADC clock so it can run in EM2
  CMU_ClockSelectSet (cmuClock_IADCCLK, cmuSelect_FSRCO);

  // Set the prescaler needed for the intended IADC clock frequency
  init.srcClkPrescale = IADC_calcSrcClkPrescale (IADC0, CLK_SRC_ADC_FREQ, 0);

  // Shutdown between conversions to reduce current
  init.warmup = iadcWarmupNormal;

  /*
   * Configuration 0 is used by both scan and single conversions by
   * default.  Use unbuffered AVDD as reference and specify the
   * AVDD supply voltage in mV.
   *
   * Resolution is not configurable directly but is based on the
   * selected oversampling ratio (osrHighSpeed), which defaults to
   * 2x and generates 12-bit results.
   */
  initAllConfigs.configs[0].reference = iadcCfgReferenceInt1V2;
  initAllConfigs.configs[0].vRef = 1210;
  initAllConfigs.configs[0].osrHighSpeed = iadcCfgOsrHighSpeed2x;

  initAllConfigs.configs[0].adcClkPrescale = IADC_calcAdcClkPrescale (
      IADC0,
      CLK_ADC_FREQ,
      0, iadcCfgModeNormal, init.srcClkPrescale);

  /*
   * Specify the input channel.  When negInput = iadcNegInputGnd, the
   * conversion is single-ended.
   */
  singleInput.posInput = iadcPosInputAvdd | 1;
  singleInput.negInput = iadcNegInputGnd;

  // Initialize IADC
  IADC_init (IADC0, &init, &initAllConfigs);

  // Initialize a single-channel conversion
  IADC_initSingle (IADC0, &initSingle, &singleInput);

  // Clear any previous interrupt flags
  IADC_clearInt (IADC0, _IADC_IF_MASK);

  // Enable single-channel done interrupts
  IADC_enableInt (IADC0, IADC_IEN_SINGLEDONE);

  // Enable IADC interrupts
  NVIC_ClearPendingIRQ (IADC_IRQn);
  NVIC_EnableIRQ (IADC_IRQn);
}

int32_t someDummyFunction ()
{

  uint32_t adc_Value;

  IADC_Init_t init = IADC_INIT_DEFAULT;

  IADC_AllConfigs_t initAllConfigs = IADC_ALLCONFIGS_DEFAULT;

  IADC_InitSingle_t initSingle = IADC_INITSINGLE_DEFAULT;

  IADC_SingleInput_t initSingleInput = IADC_SINGLEINPUT_DEFAULT;

  CMU_ClockEnable (cmuClock_IADC0, true);

  IADC_reset (IADC0);

  CMU_ClockSelectSet (cmuClock_IADCCLK, cmuSelect_FSRCO);

  init.warmup = iadcWarmupNormal;
  init.timerCycles = 200;
  init.srcClkPrescale = IADC_calcSrcClkPrescale (IADC0, CLK_SRC_ADC_FREQ, 0);

  // Internal Ref
  initAllConfigs.configs[0].reference = iadcCfgReferenceInt1V2;
  initAllConfigs.configs[0].adcClkPrescale = IADC_calcAdcClkPrescale ( IADC0,
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

  IADC_init (IADC0, &init, &initAllConfigs);
  IADC_initSingle (IADC0, &initSingle, &initSingleInput);
  IADC_command (IADC0, iadcCmdStartSingle);

  while ((IADC0->STATUS
      & (_IADC_STATUS_CONVERTING_MASK | _IADC_STATUS_SINGLEFIFODV_MASK))
      != IADC_STATUS_SINGLEFIFODV)
    ;

  adc_Value = IADC_pullSingleFifoResult (IADC0).data;
  double result = ((adc_Value * 4 * 1.21) / (0xFFF)) ;
  IADC_reset (IADC0);
  CMU_ClockEnable (cmuClock_FSRCO, false);
  CMU_ClockEnable (cmuClock_IADC0, false);
  // for Vref = AVDD = 3.30V, 12 bits represents 6.60V full scale IADC range.

  return (((int32_t) adc_Value * 4 * 1.21) / 0xFFF) + 500;

}

/**************************************************************************//**
 * @brief GPIO Interrupt handler for even pins.
 *****************************************************************************/
void GPIO_EVEN_IRQHandler (void)
{
  // Get and clear all pending GPIO interrupts
  uint32_t interruptMask = GPIO_IntGet ();
  GPIO_IntClear (interruptMask);
  int32_t temp;
  // Check if button 0 was pressed
  if (interruptMask & (1 << 0))
    {
      temp = someDummyFunction();
    }

}

///**************************************************************************//**
// * @brief  IADC IRQ Handler
// *****************************************************************************/
//void
//IADC_IRQHandler (void)
//{
//  sample = IADC_pullSingleFifoResult (IADC0);
//  singleResult = 4 * sample.data * 1.21 / 0xFFF;
//
//  IADC_clearInt (IADC0, IADC_IF_SINGLEDONE);
//}

static void gpioSetup (void)
{
  // Configure GPIO Clock. Note this is not required for EFR32xG21
  CMU_ClockEnable (cmuClock_GPIO, true);

  // Configure Button PB0 as input and enable interrupt
  GPIO_PinModeSet (gpioPortB, 0, gpioModeInputPull, 1);
  GPIO_ExtIntConfig (gpioPortB, 0, 0, false, true, true);

  // Enable EVEN interrupt to catch button press that changes slew rate
  NVIC_ClearPendingIRQ (GPIO_EVEN_IRQn);
  NVIC_EnableIRQ (GPIO_EVEN_IRQn);
}

/**************************************************************************//**
 * @brief  Main function
 *****************************************************************************/
int
main (void)
{
  CHIP_Init ();
//  initIADC ();
  gpioSetup ();


#ifdef EM2DEBUG
#if (EM2DEBUG == 1)
  // Enable debug connectivity in EM2
  EMU->CTRL_SET = EMU_CTRL_EM2DBGEN;
#endif
#endif

  while (1)
    {
      /*
       * Care must be taken when using the SINGLEDONE interrupt as a way
       * to exit low-energy modes, especially EM2/3.  Because the IADC
       * is has its own clock  (it runs from the IADC_CLK vs. the PCLK as
       * is the case for most other peripherals), register accesses
       * must be synchronized and require additional clock cycles.
       *
       * This matters because if the ADC_CLK is fast enough, it is
       * possible to start a single conversion, have it finish, and
       * request an interrupt before the device can enter EM2/3.
       *
       * ADC_CLK = 1 MHz (minimum conversion time = 10 microseconds) in
       * this example allows sufficient time to start the conversion
       * and enter EM2 so that the SINGLEDONE interrupt wakes the
       * device.  However, if ADC_CLK is sufficiently fast relative to
       * the CPU clock frequency, this may not be possible.
       */

      // Enter EM2 sleep, wait for IADC interrupt
      EMU_EnterEM2 (false);
    }
}