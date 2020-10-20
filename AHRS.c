/*
 * AHRS.c
 *
 *  Created on: 19 oct. 2020
 *      Author: etera
 */


#include "AHRS.h"
#include "BMI160.h"
#include <math.h>

#define PYTHON 1
#define AHRS_SENDUART 1

// Float conversion variables
Accel_data_t RawAccel_data; /*  Raw accelerometer value*/
Gyro_data_t RawGyro_data; /* Raw gyroscope value*/
fAccel_data_t conv_Accel; /* Converted Accelerometer value*/
fGyro_data_t conv_Gyro;  /* Converted Gyroscope value */

void get_BMI160_data(void * args)
{
	uint32_t task = 0;
	TickType_t xLastWakeTime = xTaskGetTickCount();

	vTaskDelay(pdMS_TO_TICKS(1000));


	while (1) {
		task++;

		RawAccel_data = BMI160_ACCEL_Read(); // Read accelerometer
		RawGyro_data = BMI160_GRYO_Read();	// Read gyroscope

		Accel_conversion();	// Call accelerometer conversion function
		Gyroscope_conversion();	//  Call gyroscope conversion function

		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(AHRS_IMU_TIME)); // Delay task until  10ms

	}
}

void Accel_conversion(void) {
	/*Calculate conversion factor*/
	const float convAccel_factor = (float) Accelerometer_range / (float) MAX_VAL;
	/*Get Accelerometer values converted*/
	conv_Accel.x = (float) RawAccel_data.x * convAccel_factor;
	conv_Accel.y = (float) RawAccel_data.y * convAccel_factor;
	conv_Accel.z = (float) RawAccel_data.z * convAccel_factor;
//	PRINTF("Ax: %f  Ay: %f  Az: %f    |    ", float_A.x, float_A.y, float_A.z);

}

void Gyroscope_conversion(void) {
	/*Calculate conversion factor*/
	const float convGyro_factor = (float) Gyroscope_range / (float) MAX_VAL;
	/*Get Gyroscope values converted*/
	conv_Gyro.x = (float) RawGyro_data.x * convGyro_factor;
	conv_Gyro.y = (float) RawGyro_data.y * convGyro_factor;
	conv_Gyro.z = (float) RawGyro_data.z * convGyro_factor;
//	PRINTF("Gx: %f  Gy: %f  Gz: %f\n\r", float_G.x, float_G.y, float_G.z);

}
