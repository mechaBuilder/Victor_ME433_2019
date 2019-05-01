#ifndef IMU_H__
#define IMU_H__
// Header file for imu.c
// IMU LSM6DS33 initialization & helper function

#define WHO_AM_I 0x0F
#define SLAVE_ADDR 0b1101010 //SDO/SAO pin unconnect, so LSbit is 0 (note: 7 bits total)
#define CTRL1_XL 0x10
#define CTRL2_G 0x11
#define CTRL3_C 0x12
#define CTRL1_XL_config 0b10000010
#define CTRL2_G_config 0b10001000
#define CTRL3_C_config 0b00000100

int whoAmI(void);
void imu_init();

#endif