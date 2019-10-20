#ifndef SENSOR_AG_H
#define SENSOR_AG_H
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// UMSATS 2018-2020
//
// Repository:
//  ?Not this:UMSATS Google Drive: UMSATS/Guides and HowTos.../Command and Data Handling (CDH)/Coding Standards
//
// File Description:
//  Reads sensor data for accelerometer and gyroscope from the BMI088
//
// History
// 2019-03-29 by Benjamin Zacharias
// - Created.
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#include "bmi08x.h"
#include <inttypes.h>
#include "forward_declarations.h"
#include "cmsis_os.h"

#define	ACC_LENGTH	6		//Length of a accelerometer measurement in bytes.
#define	GYRO_LENGTH	6		//Length of a gyroscope measurement in bytes.

//Groups both sensor readings and a time stamp.
typedef struct imu_sensor_data{

	struct bmi08x_sensor_data	data_acc;
	struct bmi08x_sensor_data	data_gyro;
	uint32_t time_ticks;	//time of sensor reading in ticks.
}imu_sensor_data;

//Parameters for thread_imu_start.
typedef struct{
	UART_HandleTypeDef * huart;
	QueueHandle_t imu_queue;
	configuration_data_t *flightCompConfig;
} thread_imu_parameters;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------
// Description:
//  Enter description for public function here.
//
// Returns:
//  Enter description of return values (if any).
//-------------------------------------------------------------------------------------------------------------------------------------------------------------

//Wrapper functions for read and write
int8_t user_spi_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);
int8_t user_spi_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint16_t len);

void delay(uint32_t period);

void thread_imu_start(void *param);

//configuration functions for accelerometer and gyroscope
int8_t accel_config(struct bmi08x_dev *bmi088dev, configuration_data_t * configParams, int8_t rslt);
int8_t gyro_config(struct bmi08x_dev *bmi088dev, configuration_data_t * configParams, int8_t rslt);

#endif // SENSOR_AG_H