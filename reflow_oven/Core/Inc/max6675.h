/*
 * max6675.h
 *
 *  Created on: Apr 22, 2025
 *      Author: anushmutyala
 */

#ifndef INC_MAX6675_H_
#define INC_MAX6675_H_
#include "main.h"

// ------------------------- Defines -------------------------
#define SSPORT GPIOA       // GPIO Port of Chip Select(Slave Select)
#define SSPIN  GPIO_PIN_4  // GPIO PIN of Chip Select(Slave Select)
// ------------------------- Functions  ----------------------
float Max6675_Read_Temp(void);
_Bool Max6675_Connection_Status(void);
#endif
