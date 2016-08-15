#ifndef __MPU6050_DRIVER_H__
#define __MPU6050_DRIVER_H__

#include <stdint.h>

//定义MPU6050内部地址
#define	SMPLRT_DIV		          0x19	//陀螺仪采样率 典型值 0X07 125Hz
#define	CONFIG			            0x1A	//低通滤波频率 典型值 0x00 
#define	GYRO_CONFIG		          0x1B	//陀螺仪自检及测量范围                 典型值 0x18 不自检 2000deg/s
#define	ACCEL_CONFIG	          0x1C	//加速度计自检及测量范围及高通滤波频率 典型值 0x01 不自检 2G 5Hz
#define INT_PIN_CFG               0x37
#define INT_ENABLE                0x38
#define INT_STATUS                0x3A    //只读
#define	ACCEL_XOUT_H	          0x3B
#define	ACCEL_XOUT_L	          0x3C
#define	ACCEL_YOUT_H	          0x3D
#define	ACCEL_YOUT_L	          0x3E
#define	ACCEL_ZOUT_H	          0x3F
#define	ACCEL_ZOUT_L	          0x40
#define	TEMP_OUT_H		          0x41
#define	TEMP_OUT_L		          0x42
#define	GYRO_XOUT_H		          0x43
#define	GYRO_XOUT_L		          0x44	
#define	GYRO_YOUT_H		          0x45
#define	GYRO_YOUT_L		          0x46
#define	GYRO_ZOUT_H		          0x47
#define	GYRO_ZOUT_L		          0x48
#define	PWR_MGMT_1		          0x6B	//电源管理 典型值 0x00 正常启用
#define	WHO_AM_I		          0x75	//只读  默认读出应该是 MPU6050_ID = 0x70
#define MPU6050_ID                0x70
#define MPU6050_DEVICE_ADDRESS    0xD0


#define MPU6050_DATA_START        ACCEL_XOUT_H   //由于数据存放地址是连续的，所以一并读出
#define MPU6050_RA_SELF_TEST_X                  0x0D
#define MPU6050_RA_SLEF_TEST_Y                  0x0E
#define MPU6050_RA_SELF_TEST_Z                  0x0F
#define MPU6050_RA_SELF_TEST_A                  0x10
#define MPU6050_RA_SMPLRT_DIV                   0x19
#define MPU6050_RA_CONFIG                       0x1A
#define MPU6050_RA_GYRO_CONFIG                  0x1B
#define MPU6050_RA_ACCEL_CONFIG                 0x1C
#define MPU6050_RA_FIFO_EN                      0x23
#define MPU6050_RA_I2C_MST_CTRL                 0x24
#define MPU6050_RA_I2C_MST_STATUS               0x36
#define MPU6050_RA_INT_PIN_CFG                  0x37
#define MPU6050_RA_INT_ENABLE                   0x38
#define MPU6050_RA_INT_STATUS                   0x3A
#define MPU6050_RA_ACCEL_XOUT_H                 0x3B
#define MPU6050_RA_ACCEL_XOUT_L                 0x3C
#define MPU6050_RA_ACCEL_YOUT_H                 0x3D
#define MPU6050_RA_ACCEL_YOUT_L                 0x3E
#define MPU6050_RA_ACCEL_ZOUT_H                 0x3F
#define MPU6050_RA_ACCEL_ZOUT_L                 0x40
#define MPU6050_RA_TEMP_OUT_H                   0x41 
#define MPU6050_RA_TEMP_OUT_L                   0x42
#define MPU6050_RA_GYRO_XOUT_H                  0x43
#define MPU6050_RA_GYRO_XOUT_L                  0x44
#define MPU6050_RA_GYRO_YOUT_H                  0x45
#define MPU6050_RA_GYRO_YOUT_L                  0x46
#define MPU6050_RA_GYRO_ZOUT_H                  0x47
#define MPU6050_RA_GYRO_ZOUT_L                  0x48       
#define MPU6050_RA_I2C_MST_DELAY_CTRL           0x67
#define MPU6050_RA_SIGNAL_PATH_RESET            0x68
#define MPU6050_RA_USER_CTRL                    0x6A
#define MPU6050_RA_PWR_MGMT_1                   0x6B
#define MPU6050_RA_PWR_MGMT_2                   0x6C
#define MPU6050_RA_FIFO_COUNTH                  0x72
#define MPU6050_RA_FIFO_COUNTL                  0x73
#define MPU6050_RA_FIFO_R_W                     0x74
#define MPU6050_RA_WHO_AM_I                     0x75 
#define MPU6050_RA_SLV0_ADDR                    0x25
#define MPU6050_RA_SLV0_REG                     0x26
#define MPU6050_RA_SLV0_CTRL                    0x27 
#define MPU6050_RA_SLV0_DO                      0x63 
#define MPU6050_RA_SLV1_ADDR                    0x28
#define MPU6050_RA_SLV1_REG                     0x29
#define MPU6050_RA_SLV1_CTRL                    0x2A
#define MPU6050_RA_SLV1_DO                      0x64 
#define MPU6050_RA_SLV4_CTRL                    0x34 
#define MPU6050_RA_ES_DATA00                    0x49
#define MPU6050_RA_ES_DATA01                    0x4A
#define MPU6050_RA_ES_DATA02                    0x4B
#define MPU6050_RA_ES_DATA03                    0x4C
#define MPU6050_RA_ES_DATA04                    0x4D
#define MPU6050_RA_ES_DATA05                    0x4E
#define MPU6050_RA_ES_DATA06                    0x4F
#define MPU6050_RA_ES_DATA07                    0x50

typedef struct __MPU6050_RAW_Data__
{
    short Accel_X;  //寄存器原生X轴加速度表示值
    short Accel_Y;  //寄存器原生Y轴加速度表示值
    short Accel_Z;  //寄存器原生Z轴加速度表示值
    short Temp;     //寄存器原生温度表示值
    short Gyro_X;   //寄存器原生X轴陀螺仪表示值
    short Gyro_Y;   //寄存器原生Y轴陀螺仪表示值
    short Gyro_Z;   //寄存器原生Z轴陀螺仪表示值
	
}MPU6050_RAW_DATA;

typedef struct __MPU6050_REAL_Data__
{
    float Accel_X;  //转换成实际的X轴加速度，
    float Accel_Y;  //转换成实际的Y轴加速度，
    float Accel_Z;  //转换成实际的Z轴加速度，
    float Temp;     //转换成实际的温度，单位为摄氏度
    float Gyro_X;   //转换成实际的X轴角加速度，
    float Gyro_Y;   //转换成实际的Y轴角加速度，
    float Gyro_Z;   //转换成实际的Z轴角加速度
}MPU6050_REAL_DATA;

//define the eluer angle
typedef struct AHRS
{
	float pitch;
	float roll;
	float yaw;
	
}AHRS;
extern AHRS ahrs;

extern volatile MPU6050_RAW_DATA    MPU6050_Raw_Data; 
extern volatile MPU6050_REAL_DATA   MPU6050_Real_Data;
extern uint8_t mpu_buf[20];

int MPU6050_Init(void);
void MPU6050_Initialize(void);
void MPU6050_InitGyro_Offset_Start(void);
void MPU6050_InitGyro_Offset_Save(void);
int MPU6050_ReadData(uint8_t Slave_Addr, uint8_t Reg_Addr, uint8_t * Data, uint8_t Num);
int MPU6050_EnableInt(void);
void MPU6050_getMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
void MPU6050_getlastMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
void Reset_MAG_MinMaxVal(void);

#endif


