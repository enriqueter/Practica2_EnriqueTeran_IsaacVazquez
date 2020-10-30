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

#define I2C_BR			115200U
#define	I2C				freertos_i2c_0
#define I2C_PORT		freertos_i2c_portB
#define I2C_SCL_PIN		2U
#define I2C_SDA_PIN		3U
#define I2C_PIN_MUX		2U
#define SOFTRESET_BMI   0xB6
void BMI160_Initalization(void *args) {
	/* variable for writing and reading  */
	uint8_t dWrite;
	uint8_t dRead;
	/*Define i2c config variable for initialization*/
	rtos_i2c_config_t i2c_config;
	/* i2c config values for BMI160 */
    i2c_config.baudrate = BMI160_BAUDRATE;/*I2C Baud rate*/
    i2c_config.i2c_number = rtos_i2c_0;	/*I2C to use*/
    i2c_config.port = rtos_i2c_portB;	/*Port*/
	i2c_config.SCL_pin = I2C_PIN_MUX;	/*Pin SCL*/
	i2c_config.SDA_pin = I2C_SDA_PIN;	/*Pin SDA*/
	i2c_config.pin_mux = kPORT_MuxAlt2;	/*Pin Configuration*/
	rtos_i2c_init(i2c_config);
	dRead = 0;
	rtos_i2c_receive(rtos_i2c_0, &dRead, BMI160_DATA_SIZE, BMI160_ADDR, BMI160_ID, EMPTY);
	dWrite = SOFTRESET_BMI;
	rtos_i2c_transfer(rtos_i2c_0, &dWrite, EMPTY, BMI160_ADDR, BMI160_CONFIG, EMPTY);
	vTaskDelay(pdMS_TO_TICKS(10));
	dWrite = BMI160_ACCEL;
	rtos_i2c_transfer(rtos_i2c_0, &dWrite, EMPTY, BMI160_ADDR, BMI160_CONFIG, EMPTY);
	vTaskDelay(pdMS_TO_TICKS(10));
	dWrite = BMI160_GYRO;
	rtos_i2c_transfer(rtos_i2c_0, &dWrite, EMPTY, BMI160_ADDR, BMI160_CONFIG, EMPTY);
	vTaskDelay(pdMS_TO_TICKS(10));

	vTaskDelete(NULL);
}


Accel_data_t BMI160_ACCEL_Read(void) {
	/* variable for sending data out */
	Accel_data_t Accel_data;

	/*Receive data from IMU */
	rtos_i2c_receive(rtos_i2c_0, &X_L, EMPTY, BMI160_ADDR, Ax_L, EMPTY);
	rtos_i2c_receive(rtos_i2c_0, &X_H, EMPTY, BMI160_ADDR, Ax_H, EMPTY);
	rtos_i2c_receive(rtos_i2c_0, &Y_L, EMPTY, BMI160_ADDR, Ay_L, EMPTY);
	rtos_i2c_receive(rtos_i2c_0, &Y_H, EMPTY, BMI160_ADDR, Ay_H, EMPTY);
	rtos_i2c_receive(rtos_i2c_0, &Z_L, EMPTY, BMI160_ADDR, Az_L, EMPTY);
	rtos_i2c_receive(rtos_i2c_0, &Z_H, EMPTY, BMI160_ADDR, Az_H, EMPTY);

	/*Data unification High and Low */
	Accel_data.x = (X_H << SHIFT) + X_L;
	Accel_data.y = (Y_H << SHIFT) + Y_L;
	Accel_data.z = (Z_H << SHIFT) + Z_L;
	PRINTF("Accelerometer values x:%d y:%d z:%d \n", Accel_data.x, Accel_data.y, Accel_data.z);
	/*Read data return*/
	return Accel_data;
}


Gyro_data_t BMI160_GRYO_Read(void) {
	/* variable for sending data out*/
	Gyro_data_t Gyro_data;

	/*Receive data from IMU */
	rtos_i2c_receive(rtos_i2c_0, &X_L, EMPTY, BMI160_ADDR, Gx_L, EMPTY);
	rtos_i2c_receive(rtos_i2c_0, &X_H, EMPTY, BMI160_ADDR, Gx_H, EMPTY);
	rtos_i2c_receive(rtos_i2c_0, &Y_L, EMPTY, BMI160_ADDR, Gy_L, EMPTY);
	rtos_i2c_receive(rtos_i2c_0, &Y_H, EMPTY, BMI160_ADDR, Gy_H, EMPTY);
	rtos_i2c_receive(rtos_i2c_0, &Z_L, EMPTY, BMI160_ADDR, Gz_L, EMPTY);
	rtos_i2c_receive(rtos_i2c_0, &Z_H, EMPTY, BMI160_ADDR, Gz_H, EMPTY);

	/*Data unification High and Low */
	Gyro_data.x = (X_H << SHIFT) + X_L;
	Gyro_data.y = (Y_H << SHIFT) + Y_L;
	Gyro_data.z = (Z_H << SHIFT) + Z_L;
	PRINTF("Accelerometer values x:%d y:%d z:%d \n", Gyro_data.x, Gyro_data.y, Gyro_data.z);
	/*Read data return*/
	return Gyro_data;
}
