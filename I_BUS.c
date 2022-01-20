#include "I_BUS.h"
#include "main.h"

/* --------

	Functions

-------- */


void I_BUS_initialize(I_BUS *input, UART_HandleTypeDef *huart){
	
	// Init vars
	uint8_t f = 0;
	
	// fill struct
	input->uart_Handle = huart;
	
	// 	Start receiving data from DMA stream
	HAL_UART_Receive_DMA(input->uart_Handle, input->ch_raw, 32);
	
	// Delay to allow buffer to be filled
	HAL_Delay(6);

	// Since the stream is continous, the begining must be found
	// The first two byte are always 0x20 and 0x40
	// If this is not found, abort and try again with different delays
	// This ensures that no matter where we start the beginning in found in a few tries
	while(input->flag == 0){
		if( input->ch_raw[0] == 0x20 && input->ch_raw[1] == 0x40 ){
			// Set flag to indicate locating the stream correctly
			input->flag = 1;
		}
		else{
			// Stream is not located stop receiving
			HAL_UART_AbortReceive(input->uart_Handle);
			// Make a short delay
			// 7ms between msg-s
			// 3ms pause 4ms receiving
			f++;
			HAL_Delay(f);
			
			// No point in making too long delay
			if(f==3){f=0;}
			
			// Try receiving again
			HAL_UART_Receive_DMA(input->uart_Handle, input->ch_raw, 32);
			
			// Delay to allow buffer to be filled
			HAL_Delay(6);
		}
	}
}


void I_BUS_process(I_BUS *input){
	
	// Assemble the received ch info
	// ch1 info starts with raw[4]
	for( uint8_t i = 0; i < CH_NUM; i++ ){
		input->ch_proc[i] = (input->ch_raw[2*i+5] << 8) | input->ch_raw[2*i + 4];
	}
	
	// Reset ibus flag
	input->flag = 0;
	
}


void I_BUS_data_receive(I_BUS *input){
	// Set ibus flag
	input->flag = 1;
}
