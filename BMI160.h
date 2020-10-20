/*
 * BMI160.h
 *
 *  Created on: 15 oct. 2020
 *      Author: etera
 */

#ifndef BMI160_H_
#define BMI160_H_

/* TODO: insert other include files here. */
#include <stdint.h>
/*RTOS Includes*/
#include "rtos_i2c.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "semphr.h"
#include "task.h"
/*DRIVERS includes*/
#include "fsl_i2c.h"
#include "fsl_debug_console.h"
#include "fsl_port.h"

/*Register definitions for Accelerometer & Gyroscope*/
#define BMI160_ACCEL 0x11
#define Ax_L 0x12
#define Ax_H 0x13
#define Ay_L 0x14
#define Ay_H 0x15
#define Az_L 0x16
#define Az_H 0x17

#define BMI160_GYRO 0x15
#define Gx_L 0x0C
#define Gx_H 0x0D
#define Gy_L 0x0E
#define Gy_H 0x0F
#define Gz_L 0x10
#define Gz_H 0x11

/* Config Defines for BMI */
#define BMI160_ADDR 0x68 // Default I2C 7-bit address of device
#define BMI160_SUBADDR (2U)	// Size of registers
#define BMI160_DATA_SIZE (2U)
#define BMI160_BAUDRATE (100000U)
#define BMI160_CONFIG 0x7E	// Register for configuration
#define BMI160_ID 0x00
#define BMI160_CHIP_ID 0xD1
#define EMPTY 1u
#define SHIFT 8

/*Pins */
#define PTC10 (10U)
#define PTC11 (11U)

/*Accelerometer structure data*/
typedef struct {
	int16_t x;
	int16_t y;
	int16_t z;
}Accel_data_t;

/*Gyroscope structure data*/
typedef struct {
	int16_t x;
	int16_t y;
	int16_t z;
}Gyro_data_t;


/*Initialization function*/
void BMI160_Initalization(void);
/*Accelerometer read function*/
Accel_data_t BMI160_ACCEL_Read(void);
/*Gyroscope read function*/
Gyro_data_t BMI160_GRYO_Read(void);


#endif /* BMI160_H_ */
