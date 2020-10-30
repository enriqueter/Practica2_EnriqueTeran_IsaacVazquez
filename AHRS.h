/*
 * AHRS.h
 *
 *  Created on: 19 oct. 2020
 *      Author: etera
 */

#ifndef AHRS_H_
#define AHRS_H_

#include "BMI160.h"
#include "rtos_uart.h"
#include "Mahony.h"

#define Accelerometer_range 2 /*Accelerometer data range*/
#define Gyroscope_range 360/*Gryoscope data range*/
#define MAX_VAL 327680 /*BMI160 MAX VALUE*/
#define AHRS_IMU_TIME 	10 /* Delay time for IMU read data*/
#define AHRS_UART_TIME 	5
#define SAMPLES 10
#define HEADER 0xAAAAAAAA /* header to uart message*/


typedef struct {
	float x;
	float y;
	float z;
}fAccel_data_t;

typedef struct {
	float x;
	float y;
	float z;
}fGyro_data_t;


typedef struct {
	uint32_t header;
	float x;
	float y;
	float z;
} comm_msg_t;


/*Function to get raw data from BMI160*/
void get_BMI160_data(void * args);
/*Function to make conversion of the raw data from the accelerometer*/
void Accel_conversion(void);
/*Function to make conversion of the raw data from the gryoscope*/
void Gyroscope_conversion(void);
/*Function that sends data through UART to PC*/
void UART_SEND_DATA(void * args);

#endif /* AHRS_H_ */
