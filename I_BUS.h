#ifndef I_BUS_H
#define I_BUS_H

#include "main.h"

/* --------
	
	Defines
	
-------- */

#define CH_NUM						6



/* --------

	Typedefs

-------- */

typedef struct {
	uint8_t ch_raw[32];
	uint16_t ch_proc[14];
	uint8_t flag;
	UART_HandleTypeDef *uart_Handle;
} I_BUS;



/* --------
	
	Function prototypes
	
-------- */

void I_BUS_initialize(I_BUS *input, UART_HandleTypeDef *huart);

void I_BUS_process(I_BUS *input);

void I_BUS_data_receive(I_BUS *input);




#endif

