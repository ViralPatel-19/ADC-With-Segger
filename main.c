#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
//#include "ads8866.h"
#include "ads8860.h"
#include <stdio.h>
#include "SEGGER_RTT.h"


int main(void)
{
    cy_rslt_t result;
    uint16_t adc_result;
    cy_stc_scb_spi_context_t spiContext;
    /* Initialize the device and board peripherals */
    result = cybsp_init() ;

    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    //INITIALIZE ADC PIN
    Cy_GPIO_Pin_Init(CYBSP_A2_PORT, CYBSP_A2_PIN, &CYBSP_A2_config); //CLOCK PIN
    Cy_GPIO_Pin_Init(CYBSP_A0_PORT, CYBSP_A0_PIN, &CYBSP_A0_config); //MOSI
    Cy_GPIO_Pin_Init(CYBSP_A1_PORT, CYBSP_A1_PIN, &CYBSP_A1_config);//MISO
    Cy_GPIO_Pin_Init(CYBSP_A3_PORT, CYBSP_A3_PIN, &CYBSP_A3_config); //CS



    SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
	result = Cy_SCB_SPI_Init(SCB1, &scb_1_config, &spiContext);
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}
	Cy_SCB_SPI_Enable(SCB1);

    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    SEGGER_RTT_printf(0,"\x1b[2J\x1b[;H");

    SEGGER_RTT_printf(0,"****************** "
           "emUSB Device: CDC echo application "
           "****************** \r\n\n");


    SEGGER_RTT_printf(0,"mUSB Device: CDC echo application");
    ADS8866_Init();

    /* Enable global interrupts */
    __enable_irq();


    while (1) {
        uint16_t adc_value = ADS8866_ReadData();
        char float_str[80];
        double voltage = ((double)adc_value*5.0/65535)*1.04;
        sprintf(float_str, "Float value is %f\n", voltage);
        SEGGER_RTT_printf(0, "Voltage by sprintf : %0.3s V\r\n",float_str);
        Cy_SysLib_Delay(1.2);  // Delay as per your sampling requirement
    }

}
