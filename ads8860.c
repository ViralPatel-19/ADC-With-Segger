
#include "ads8860.h"
#include "cybsp.h"
#include "cy_syslib.h"
#include "SEGGER_RTT.h"
cy_rslt_t result;

static void DOUT_Reset(void) {
    Cy_GPIO_Write(CYBSP_A1_PORT, CYBSP_A1_PIN ,0);
    SEGGER_RTT_printf(0, "DOUT Reset\r\n");
}

static void DOUT_Set(void) {
    Cy_GPIO_Write(CYBSP_A1_PORT, CYBSP_A1_PIN ,1);
    SEGGER_RTT_printf(0, "DOUT Set\r\n");
}

static void DIN_Reset(void) {
    Cy_GPIO_Write(CYBSP_A0_PORT, CYBSP_A0_PIN, 0);
    SEGGER_RTT_printf(0, "DIN Reset\r\n");
}

static void DIN_Set(void) {
    Cy_GPIO_Write(CYBSP_A0_PORT, CYBSP_A0_PIN, 1);
    SEGGER_RTT_printf(0, "DIN Set\r\n");
}

static void CONVST_Reset(void) {
    Cy_GPIO_Write(CYBSP_A3_PORT, CYBSP_A3_PIN, 0);
    SEGGER_RTT_printf(0, "CONVST Reset - Conversion Started\r\n");
}

static void CONVST_Set(void) {
    Cy_GPIO_Write(CYBSP_A3_PORT, CYBSP_A3_PIN, 1);
    SEGGER_RTT_printf(0, "CONVST Set - Conversion Ended\r\n");
}

uint16_t ADS8866_ReadData(void)
{

    uint8_t rxBuffer[2];  // Buffer to store the 16-bit ADC result
    uint16_t adcReadValue = 0;
    uint8_t tx_data[2] = {0xff, 0xff};
    SEGGER_RTT_printf(0, "Initializing ADC read sequence...\r\n");

    // Set up DIN and initiate conversion
    DIN_Set();

    Cy_SysLib_Delay(1);
    CONVST_Set();
    Cy_SysLib_DelayUs(8.8);  // Short delay for the ADC to stabilize
//
    CONVST_Reset(); // Start conversion
    Cy_SysLib_DelayUs(1.2);  // Allow time for conversion based on ADC specs



    SEGGER_RTT_printf(0, "Starting SPI transfer...\r\n");
    Cy_SCB_SPI_WriteArray(SCB1, tx_data, 2);
    // Check if SPI is ready to transfer data
    while (Cy_SCB_SPI_GetNumInRxFifo(SCB1) < 2) {
        SEGGER_RTT_printf(0, "Waiting for data in RX FIFO...\r\n");
    }

    // Read 2 bytes of data from ADS8866 (16-bit result)
    Cy_SCB_SPI_ReadArray(SCB1, rxBuffer, 2);  // Blocking read
//    rxBuffer[0]= Cy_SCB_SPI_Read(SCB1);
    Cy_SCB_SPI_ClearRxFifoStatus(SCB1, CY_SCB_SPI_RX_INTR_MASK);

    SEGGER_RTT_printf(0, "SPI transfer complete.\r\n");

    // Combine the two received bytes into a single 16-bit value
    adcReadValue = (rxBuffer[0] << 8) | rxBuffer[1];  // MSB first

    // Debug print the received bytes and the combined 16-bit value
    SEGGER_RTT_printf(0, "RX Byte 1: 0x%02X, RX Byte 2: 0x%02X\n", rxBuffer[0], rxBuffer[1]);
    SEGGER_RTT_printf(0, "Combined ADC Value: 0x%04X\n", adcReadValue);

    DOUT_Reset();
    Cy_GPIO_Write(CYBSP_A2_PORT, CYBSP_A2_PIN ,0);

    //  Clear the RX FIFO
    Cy_SCB_SPI_ClearRxFifo(SCB1);
    return adcReadValue;


}

void ADS8866_Init(void)
{
	cy_stc_scb_spi_context_t spiContext;
    SEGGER_RTT_printf(0, "Initializing ADS8866...\r\n");
	result = Cy_SCB_SPI_Init(SCB1, &scb_1_config, &spiContext);
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}
	Cy_SCB_SPI_Enable(SCB1);

    DIN_Set();
    CONVST_Reset();
    SEGGER_RTT_printf(0, "ADS8866 initialized and ready.\r\n");
}
