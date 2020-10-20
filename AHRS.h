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
#define Gyroscope_range 2000 /*Gryoscope data range*/
#define MAX_VAL 32768 /*BMI160 MAX VALUE*/
#define AHRS_IMU_TIME 	10 /* Delay time for IMU read data*/



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

/*Function to get raw data from BMI160*/
void get_BMI160_data(void * args);
/*Function to make conversion of the raw data from the accelerometer*/
void Accel_conversion(void);
/*Function to make conversion of the raw data from the gryoscope*/
void Gyroscope_conversion(void);


#endif /* AHRS_H_ */
