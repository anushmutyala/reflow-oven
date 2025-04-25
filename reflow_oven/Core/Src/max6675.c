/*
 * max6675.c
 *
 *  Created on: Apr 22, 2025
 *      Author: anushmutyala
 */


#include"max6675.h"
#include <math.h>

extern SPI_HandleTypeDef hspi1;

// ------------------- Variables ----------------
_Bool TCF=0;                                          // Thermocouple Connection acknowledge Flag
uint8_t DATARX[2];                                    // Raw Data from MAX6675

// ------------------- Functions ----------------
//float Max6675_Read_Temp(void){
//	HAL_Delay(400);                                       // Waits for Chip Ready(according to Datasheet, the max time for conversion is 220ms)
//	float Temp=0;                                         // Temperature Variable
//	HAL_GPIO_WritePin(SSPORT,SSPIN,GPIO_PIN_RESET);       // Low State for SPI Communication
//	HAL_SPI_Receive(&hspi1,DATARX,1,HAL_MAX_DELAY);                  // DATA Transfer
//	HAL_GPIO_WritePin(SSPORT,SSPIN,GPIO_PIN_SET);         // High State for SPI Communication
//	//TCF=(((DATARX[0]|(DATARX[1]<<8))>>2)& 0x0001);        // State of Connecting
//	Temp=((((DATARX[0]|DATARX[1]<<8)))>>3);               // Temperature Data Extraction
//	Temp*=0.25;                                           // Data to Centigrade Conversation
//return Temp;
//}

float Max6675_Read_Temp(void) {
    uint16_t raw;

    // Ensure the previous conversion (triggered by the last CS↑) has finished:
    HAL_Delay(250);

    // Pull CS low to start the read:
    HAL_GPIO_WritePin(SSPORT, SSPIN, GPIO_PIN_RESET);

    // Full-duplex: clock out 0x0000 while you clock in the 16-bit result
    HAL_SPI_TransmitReceive(
      &hspi1,
      (uint8_t *)&raw,   // TX buffer (dummy)
      (uint8_t *)&raw,   // RX buffer (where the MAX6675 data lands)
      1,                 // transfer 1 word of 16 bits
      HAL_MAX_DELAY
    );

    // De-select the chip (and start the next conversion)
    HAL_GPIO_WritePin(SSPORT, SSPIN, GPIO_PIN_SET);

    // Check for open-thermocouple fault (bit D2):
    if (raw & 0x0004) return NAN;

    // Strip off the 3 status bits and convert to °C
    raw >>= 3;
    return raw * 0.25f;  // each LSB = 0.25 °C :contentReference[oaicite:0]{index=0}&#8203;:contentReference[oaicite:1]{index=1}
}


_Bool Max6675_Connection_Status(void){
	HAL_GPIO_WritePin(SSPORT,SSPIN,GPIO_PIN_RESET);       // Low State for SPI Communication
	HAL_SPI_Receive(&hspi1,DATARX,1,50);                  // DATA Transfer
	HAL_GPIO_WritePin(SSPORT,SSPIN,GPIO_PIN_SET);         // High State for SPI Communication
	TCF=(((DATARX[0]|(DATARX[1]<<8))>>2)& 0x0001);        // State of Connecting
	HAL_Delay(250);
	return TCF;
}
