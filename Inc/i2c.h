/*
 * i2c.h
 *
 *  Created on: Oct 14, 2025
 *      Author: Anthon Brown
 */

#ifndef I2C_H_
#define I2C_H_



void I2C1_init		(void												);
void I2C_byteRead	(uint8_t saddr, char* data							);
void I2C_byteWrite	(uint8_t saddr, char* data							);
void I2C_burstRead	(uint8_t saddr, uint8_t maddr, int n, char* data	);
void I2C_burstWrite	(uint8_t saddr, uint8_t maddr, int n, char* data	);

#endif /* I2C_H_ */
