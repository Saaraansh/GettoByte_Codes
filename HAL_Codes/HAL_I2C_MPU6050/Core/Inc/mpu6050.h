/*
 * mpu6050.h
 *
 *  Created on: Dec 21, 2022
 *      Author: saar
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_
/******************************************************************************************************************
 	 	 	 	 	 	 	 	 	 	 	 	 Required Header Files
******************************************************************************************************************/
#include <stdint.h>
#include <i2c.h>
/******************************************************************************************************************
 	 	 	 	 	 	 	 	 	 	 	 Register and Address Definitions
******************************************************************************************************************/
#define MPU6050_ADDR 		0xD0

#define REG_SMPLRT_DIV 		0x19
#define REG_GYRO_CONFIG 	0x1B
#define REG_ACCEL_CONFIG 	0x1C
#define REG_ACCEL_XOUT_H 	0x3B
#define REG_TEMP_OUT_H 		0x41
#define REG_GYRO_XOUT_H 	0x43
#define REG_PWR_MGMT_1 		0x6B
#define REG_WHO_AM_I 		0x75

/******************************************************************************************************************
 	 	 	 	 	 	 	 	 	 	 	 	 	 	Structure Definition
******************************************************************************************************************/
typedef struct
{
	float Accel_X;
	float Accel_Y;
	float Accel_Z;
}MPU6050_ACCEL_t;

typedef struct
{
	float Gyro_X;
	float Gyro_Y;
	float Gyro_Z;
}MPU6050_GYRO_t;;

/******************************************************************************************************************
														Driver APIs
******************************************************************************************************************/
/*
 * @breif
 * @param None
 * @return None
 */
void MPU6050_Init (void);

/*
 * @breif
 * @param MPU6050_t: User defined structure to get the values of Accelerometer
 * @return Accel_X, Accel_Y, Accel_Z
 */
void MPU6050_Read_Accel(MPU6050_ACCEL_t *Mpu_Accel);

/*
 * @breif
 * @param MPU6050_t:User defined structure to get the values of Gyroscope
 * @return Gyro_X, Gyro_Y, Gyro_Z
 */
void MPU6050_Read_Gyro (MPU6050_GYRO_t *Mpu_Gyro);

#endif /* INC_MPU6050_H_ */
