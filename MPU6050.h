#ifndef MPU6050_H_
#define MPU6050_H_

#include "stm32f1xx_hal.h"  // Thay đổi nếu bạn dùng dòng STM32 khác
#include <stdint.h>

// Địa chỉ I2C mặc định của MPU6050
#define MPU6050_ADDR 0x68 << 1  // Dịch trái 1 bit vì HAL dùng 8-bit địa chỉ

// Các thanh ghi quan trọng
#define MPU6050_REG_PWR_MGMT_1     0x6B
#define MPU6050_REG_ACCEL_XOUT_H   0x3B
#define MPU6050_REG_WHO_AM_I       0x75
#define ACCEL_CONFIG_REG       0x1C
#define GYRO_CONFIG_REG        0x1B

// Cấu trúc lưu giá trị cảm biến
typedef struct {
    int16_t Accel_X;
    int16_t Accel_Y;
    int16_t Accel_Z;
    int16_t Temp;
    int16_t Gyro_X;
    int16_t Gyro_Y;
    int16_t Gyro_Z;
    float   Accel_Total;
} MPU6050_Data;

// Các hàm giao tiếp với MPU6050
uint8_t MPU6050_Init(I2C_HandleTypeDef *hi2c);
void MPU6050_Read_All(I2C_HandleTypeDef *hi2c, MPU6050_Data *data);

#endif /* MPU6050_H_ */
