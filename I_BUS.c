#include "I_BUS.h"
#include "main.h"

/* --------

	Functions

-------- */

void I_BUS_initialize(uint8_t *ibus, UART_HandleTypeDef *huart){
	
	uint8_t i_bus_flag = 0;
	uint8_t f = 0;
	
	HAL_UART_Receive_DMA(huart, (uint8_t *)ibus, 32);

	while(i_bus_flag == 0){
		if( ibus[0] == 0x20 && ibus[1] == 0x40 ){
			i_bus_flag = 1;
			break;
		}
		else{
			HAL_UART_AbortReceive(huart);
			if(f==3){f=0;}
			HAL_UART_Receive_DMA(huart, (uint8_t *)ibus, 32);

			HAL_Delay(f);
			f++;
		}
	}
}

void I_BUS_process(I_BUS *ibus, uint8_t *uart_buf, uint8_t *ibus_flag){
	for( uint8_t i = 0; i < CH_NUM; i++ ){
		ibus->ch_proc[i] = (uart_buf[2*i+1] << 8) + uart_buf[2];
	}
	*ibus_flag = 0;
	
}
