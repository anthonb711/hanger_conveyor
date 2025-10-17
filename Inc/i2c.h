/*
 * i2c.h
 *
 *  Created on: Oct 14, 2025
 *      Author: Anthon Brown
 */

#ifndef I2C_H_
#define I2C_H_



void I2C1_init		(void												);
void I2C_byteRead	(uint8_t saddr, uint8_t maddr, char* data 			);
void I2C_byteWrite	(uint8_t saddr, uint8_t  data							);

void I2C_burstRead	(uint8_t saddr, uint8_t maddr, int n, char* dataS	);
void I2C_burstWrite	(uint8_t saddr, uint8_t maddr, int n, char* data	);

/* probe helper */
int  i2c_probe(uint8_t addr); // returns 1 if device ACKs, 0 otherwise

#endif /* I2C_H_ */
