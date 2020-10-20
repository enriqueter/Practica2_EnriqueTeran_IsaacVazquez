#ifndef AHRS_H_
#define AHRS_H_
#include "BMI160.h"
#include "rtos_uart.h"
#include "mahony.h"

#define A_range 2 //2g 
#define G_range 2000	// 2000°/s 
#define MAX_VAL 32768 //INT16
#define HEADER 0xAAAAAAAA
#define AHRS_IMU_TIME 	10
#define AHRS_UART_TIME 	5
#define SAMPLES 10

typedef struct {
	uint32_t header;
	float x;
	float y;
	float z;
} comm_msg_t;

typedef struct {
	float x;
	float y;
	float z;
}BMI160_fA_data_t;

typedef struct {
	float x;
	float y;
	float z;
}BMI160_fG_data_t;

void AHRS_UART(void * args);
void get_data(void * args);
void A_conversion(void);	// Conversion
void G_conversion(void);	// Conversion

#endif /* AHRS_H_ */
