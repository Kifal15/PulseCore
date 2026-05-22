#include <stdio.h>
#include "i2c_hal.h"
#include "driver/i2c.h"

#define I2C_SCL_IO 22 
#define I2C_SDA_IO 21 
#define I2C_MASTER_FREQ_HZ 100000

bool i2c_hal_init(void){


i2c_config_t conf = {

.mode = I2C_MODE_MASTER, 
.sda_io_num = I2C_SDA_IO ,
.sda_pullup_en = GPIO_PULLUP_ENABLE,
.scl_io_num = I2C_SCL_IO , 
.scl_pullup_en = GPIO_PULLUP_ENABLE,
.master.clk_speed = I2C_MASTER_FREQ_HZ

};


esp_err_t err = i2c_param_config(I2C_NUM_0 , &conf);







}