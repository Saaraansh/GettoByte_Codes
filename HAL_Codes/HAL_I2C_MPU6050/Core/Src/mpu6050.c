/*
 * mpu6050.c
 *
 *  Created on: Dec 21, 2022
 *      Author: saar
 */

#include <mpu6050.h>

/*
 * @breif
 * @param None
 * @return None
 */
void MPU6050_Init (void)
{
	uint8_t check;
	uint8_t Data;

	// check device ID WHO_AM_I

	HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, REG_WHO_AM_I, 1, &check, 1, 1000);

	if (check == 0x68)  // 0x68 will be returned by the sensor if everything goes well
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, REG_PWR_MGMT_1, 1,&Data, 1, 1000);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0x07;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, REG_SMPLRT_DIV, 1, &Data, 1, 1000);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ± 2g
		Data = 0x00;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, REG_ACCEL_CONFIG, 1, &Data, 1, 1000);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ± 250 °/s
		Data = 0x00;
		HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDR, REG_GYRO_CONFIG, 1, &Data, 1, 1000);
	}
}

/*
 * @breif
 * @param MPU6050_t: User defined structure to get the values of Accelerometer
 * @return Accel_X, Accel_Y, Accel_Z
 */
void MPU6050_Read_Accel(MPU6050_ACCEL_t *Mpu_Accel)
{
	uint8_t Rec_Data[6];

	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, REG_ACCEL_XOUT_H, 1, Rec_Data, 6, 1000);

	int16_t Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	int16_t Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	int16_t Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	/*** convert the RAW values into acceleration in 'g'
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 16384.0
	     for more details check ACCEL_CONFIG Register              ****/

	Mpu_Accel -> Accel_X = (Accel_X_RAW)/16384.0;
	Mpu_Accel -> Accel_Y = (Accel_Y_RAW)/16384.0;
	Mpu_Accel -> Accel_Z = (Accel_Z_RAW)/16384.0;
}

/*
 * @breif
 * @param MPU6050_t:User defined structure to get the values of Gyroscope
 * @return Gyro_X, Gyro_Y, Gyro_Z
 */
void MPU6050_Read_Gyro (MPU6050_GYRO_t *Mpu_Gyro)
{
	uint8_t Rec_Data[6];

	// Read 6 BYTES of data starting from GYRO_XOUT_H register

	HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR, REG_GYRO_XOUT_H, 1, Rec_Data, 6, 1000);

	int16_t Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	int16_t Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	int16_t Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

	/*** convert the RAW values into dps (°/s)
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 131.0
	     for more details check GYRO_CONFIG Register              ****/

	Mpu_Gyro -> Gyro_X = (Gyro_X_RAW)/131.0;
	Mpu_Gyro -> Gyro_Y = (Gyro_Y_RAW)/131.0;
	Mpu_Gyro -> Gyro_Z = (Gyro_Z_RAW)/131.0;
}
