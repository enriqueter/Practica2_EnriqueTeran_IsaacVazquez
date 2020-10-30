/*
 * AHRS.c
 *
 *  Created on: 19 oct. 2020
 *      Author: etera
 */


#include "AHRS.h"
#include "BMI160.h"
#include <math.h>


// Float conversion variables
Accel_data_t RawAccel_data; /*  Raw accelerometer value*/
Gyro_data_t RawGyro_data; /* Raw gyroscope value*/
fAccel_data_t conv_Accel; /* Converted Accelerometer value*/
fGyro_data_t conv_Gyro;  /* Converted Gyroscope value */

void get_BMI160_data(void * args)
{

	TickType_t xLastWakeTime = xTaskGetTickCount();
	vTaskDelay(pdMS_TO_TICKS(1000));

	while (1) {

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

void UART_SEND_DATA(void * args)
{
	uint32_t task = 0;
		TickType_t xLastWakeTime = xTaskGetTickCount();
	 	/*UART config*/
		freertos_uart_config_t config;
		config.baudrate = 115200;
		config.rx_pin = 16;
		config.tx_pin = 17;
		config.pin_mux = kPORT_MuxAlt3;
		config.uart_number = freertos_uart0;
		config.port = freertos_uart_portB;
		freertos_uart_init(config);

		vTaskDelay(pdMS_TO_TICKS(1000));// Delay task until  1s

		while (1) {
			task ++;
			MahonyAHRSEuler_t euler;
			/*Data return*/
			euler = MahonyAHRSupdateIMU(conv_Gyro.x, conv_Gyro.y, conv_Gyro.z,conv_Accel.x, conv_Accel.y, conv_Accel.z);
			//PRINTF("Roll: %f  Pitch: %f  Yaw: %f\n\r", euler.roll, euler.pitch, euler.yaw);

			comm_msg_t msg;
			msg.header = HEADER;
			msg.x = euler.yaw;
			msg.y = euler.pitch;
			msg.z = euler.roll;

			PRINTF("Yaw: %f	Pitch: %f	Roll: %f\n\r", msg.x, msg.y, msg.z);

			freertos_uart_send(freertos_uart0, (uint8_t*) &msg, sizeof(msg));

			vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(AHRS_UART_TIME));// Delay task until  5ms
		}
}
