#ifndef I_BUS_H
#define IBUS_H

#include "main.h"

/* --------
	
	Defines
	
-------- */

#define CH_NUM						6
#define STORAGE_SIZE				780



/* --------

	Typedefs

-------- */

typedef struct I_BUS_struct{
	uint16_t ch_proc[14];
} I_BUS;



/* --------
	
	Function prototypes
	
-------- */

void I_BUS_initialize(uint8_t *ibus, UART_HandleTypeDef *huart);

void I_BUS_process(I_BUS *ibus, uint8_t *uart_buf, uint8_t *ibus_flag);




#endif
