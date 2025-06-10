#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <queue.h>

#include "pico/stdlib.h"
#include <stdio.h>

#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "mpu6050.h"

const int MPU_ADDRESS = 0x68;
const int I2C_SDA_GPIO = 4;
const int I2C_SCL_GPIO = 5;

void mpu6050_task(void *p) {
    imu_c mpu;
    mpu.i2c = i2c_default;
    mpu.pin_scl = I2C_SCL_GPIO;
    mpu.pin_sda = I2C_SDA_GPIO;
    mpu.acc_scale = 0;

    mpu6050_init(mpu);

    int16_t acceleration[3];

    while(1) {
        mpu6050_read_acc(mpu, acceleration);
        printf("%d, %d, %d\n", acceleration[0], acceleration[1], acceleration[2]);

        vTaskDelay(pdMS_TO_TICKS(10));
    }


}

int main() {
    stdio_init_all();
    xTaskCreate(mpu6050_task, "mpu6050_Task 1", 8192, NULL, 1, NULL);

    vTaskStartScheduler();

    while (true)
        ;
}