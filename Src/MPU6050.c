#include "mpu6050.h"
#include "math.h"

uint8_t MPU6050_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t check;
    uint8_t Data;

    // Ki?m tra thi?t b?
    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_REG_WHO_AM_I, 1, &check, 1, 1000);

    if (check == 104) // 0x68
    {
        // Wake up MPU6050 (PWR_MGMT_1 register = 0)
        Data = 0;
        HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, MPU6050_REG_PWR_MGMT_1, 1, &Data, 1, 1000);

        // Thi?t l?p t?c d? gyroscope = � 250 �/s
        Data = 0x00;
        HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 1000);

        // Thi?t l?p d? nh?y accelerometer = � 2g
        Data = 0x00;
        HAL_I2C_Mem_Write(hi2c, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 1000);

        return 1;
    }

    return 0;
}

void MPU6050_Read_All(I2C_HandleTypeDef *hi2c, MPU6050_Data *dataStruct) {
    uint8_t Rec_Data[14];

    HAL_I2C_Mem_Read(hi2c, MPU6050_ADDR, MPU6050_REG_ACCEL_XOUT_H, 1, Rec_Data, 14, 1000);

    dataStruct->Accel_X = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
    dataStruct->Accel_Y = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
    dataStruct->Accel_Z = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);

    dataStruct->Temp = (int16_t)(Rec_Data[6] << 8 | Rec_Data[7]);

    dataStruct->Gyro_X = (int16_t)(Rec_Data[8] << 8 | Rec_Data[9]);
    dataStruct->Gyro_Y = (int16_t)(Rec_Data[10] << 8 | Rec_Data[11]);
    dataStruct->Gyro_Z = (int16_t)(Rec_Data[12] << 8 | Rec_Data[13]);
}
