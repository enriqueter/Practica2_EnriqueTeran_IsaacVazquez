/*
 * BMI160.c
 *
 *  Created on: 15 oct. 2020
 *      Author: etera
 */

#include "BMI160.h"

/* Conversion variables for unified data */
uint8_t X_L;
uint8_t X_H;
uint8_t Y_L;
uint8_t Y_H;
uint8_t Z_L;
uint8_t Z_H;

void BMI160_Initalization(void) {
	/* variable for writing and reading  */
	uint8_t dWrite;
	uint8_t dRead;
	/*Define i2c config variable for initialization*/
	rtos_i2c_config_t i2c_config;
	/* i2c config values for BMI160 */
    i2c_config.baudrate = BMI160_BAUDRATE;/*I2C Baud rate*/
    i2c_config.i2c_number = rtos_i2c_1;	/*I2C to use*/
    i2c_config.port = rtos_i2c_portC;	/*Port*/
	i2c_config.SCL_pin = PTC10;	/*Pin SCL*/
	i2c_config.SDA_pin = PTC11;	/*Pin SDA*/
	i2c_config.pin_mux = kPORT_MuxAlt2;	/*Pin Configuration*/
	rtos_i2c_init(i2c_config);
	dRead = NULL;
	/**/
	rtos_i2c_receive(rtos_i2c_1, &dRead, EMPTY, BMI160_SUBADDR, BMI160_ID, EMPTY);
	dWrite = BMI160_ACCEL;
	rtos_i2c_transfer(rtos_i2c_1, &dWrite, EMPTY, BMI160_SUBADDR, BMI160_CONFIG, EMPTY);
	dWrite = BMI160_GYRO;
	rtos_i2c_transfer(rtos_i2c_1, &dWrite, EMPTY, BMI160_SUBADDR, BMI160_CONFIG, EMPTY);

	if (dRead == BMI160_CHIP_ID) {
		PRINTF("ID = 0x%x \n", dRead);
	}
	vTaskDelay(portMAX_DELAY);
}


Accel_data_t BMI160_ACCEL_Read(void) {
	/* variable for sending data out */
	Accel_data_t Accel_data;

	/*Receive data from IMU */
	rtos_i2c_receive(rtos_i2c_1, &X_L, EMPTY, BMI160_SUBADDR, Ax_L, EMPTY);
	rtos_i2c_receive(rtos_i2c_1, &X_H, EMPTY, BMI160_SUBADDR, Ax_H, EMPTY);
	rtos_i2c_receive(rtos_i2c_1, &Y_L, EMPTY, BMI160_SUBADDR, Ay_L, EMPTY);
	rtos_i2c_receive(rtos_i2c_1, &Y_H, EMPTY, BMI160_SUBADDR, Ay_H, EMPTY);
	rtos_i2c_receive(rtos_i2c_1, &Z_L, EMPTY, BMI160_SUBADDR, Az_L, EMPTY);
	rtos_i2c_receive(rtos_i2c_1, &Z_H, EMPTY, BMI160_SUBADDR, Az_H, EMPTY);

	/*Data unification High and Low */
	Accel_data.x = (X_H << SHIFT) + X_L;
	Accel_data.y = (Y_H << SHIFT) + Y_L;
	Accel_data.z = (Z_H << SHIFT) + Z_L;
	/*Read data return*/
	return Accel_data;
}


Gyro_data_t BMI160_GRYO_Read(void) {
	/* variable for sending data out*/
	Gyro_data_t Gyro_data;

	/*Receive data from IMU */
	rtos_i2c_receive(rtos_i2c_1, &X_L, EMPTY, BMI160_SUBADDR, Gx_L, EMPTY);
	rtos_i2c_receive(rtos_i2c_1, &X_H, EMPTY, BMI160_SUBADDR, Gx_H, EMPTY);
	rtos_i2c_receive(rtos_i2c_1, &Y_L, EMPTY, BMI160_SUBADDR, Gy_L, EMPTY);
	rtos_i2c_receive(rtos_i2c_1, &Y_H, EMPTY, BMI160_SUBADDR, Gy_H, EMPTY);
	rtos_i2c_receive(rtos_i2c_1, &Z_L, EMPTY, BMI160_SUBADDR, Gz_L, EMPTY);
	rtos_i2c_receive(rtos_i2c_1, &Z_H, EMPTY, BMI160_SUBADDR, Gz_H, EMPTY);

	/*Data unification High and Low */
	Gyro_data.x = (X_H << SHIFT) + X_L;
	Gyro_data.y = (Y_H << SHIFT) + Y_L;
	Gyro_data.z = (Z_H << SHIFT) + Z_L;
	/*Read data return*/
	return Gyro_data;
}
