#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "helpers.c"

#define I2CDEV_M LPC_I2C1
//#define CHAR buffer = 0

int main(void)
{
	serial_init(); // Configures serial port for reading and writing messages
	PINSEL_CFG_Type PinCfg;				// Pin configuration for I2C
	/*
	 * Initialize I2C pin connect
	 */
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Funcnum = 3;
	PinCfg.Pinnum = 0;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 1;
	PINSEL_ConfigPin(&PinCfg);
	
	I2C_Init(I2CDEV_M, 100000);

	I2C_Cmd(I2CDEV_M, ENABLE);

	char master_buf[1];
	master_buf[0] = 0;

	char response[1];
	
	I2C_M_SETUP_Type transferMCfg;
	
	transferMCfg.sl_addr7bit = 59;
        transferMCfg.tx_data = master_buf;
        transferMCfg.tx_length = sizeof(master_buf);
        transferMCfg.rx_data = response;
        transferMCfg.rx_length = sizeof(response);
        transferMCfg.retransmissions_max = 3;
	
	
	//I2C_MasterTransferData(I2CDEV_M, &transferMCfg, 0);
	
	/*if(I2C_MasterTransferData(I2CDEV_M, &transferMCfg, 0) == SUCCESS)
	{
		write_usb_serial_blocking("Got here\n\r",11);
	}*/
	int i = 0; // Addresses
	int succ = 0; // No. of Successes
	char str[37];
	while(i < 128)
	{
		transferMCfg.sl_addr7bit = i;
		if(I2C_MasterTransferData(I2CDEV_M, &transferMCfg, 0) == SUCCESS)
		{
			
			succ++;
			sprintf(str, "Device connected at i2c address: %d\n\r", i);
			write_usb_serial_blocking(str, 37);
			
		}
		i++;
	}
	char str1[32];
	sprintf(str1, "%d devices connected to i2c bus\n\r", succ);
	write_usb_serial_blocking(str1,32);
			

	
	



}
