#include <stdio.h>
#include "i2c_hal.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
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

if (err != ESP_OK)
    {
        return false ;
    }   


err = i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER , 0 ,0,0 );

if(err != ESP_OK)
    {
        return false ;
    }


return true ;


}



bool i2c_hal_write_reg( uint8_t device_addr , uint8_t register_addr , uint8_t value )
    {

        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        if(cmd == NULL ){

            return false ; 

        }

        i2c_master_start(cmd);

        i2c_master_write_byte(cmd, (device_addr << 1 ) | I2C_MASTER_WRITE , true);

        i2c_master_write_byte(cmd , register_addr , true);

        i2c_master_write_byte(cmd , value , true) ;
        
        i2c_master_stop(cmd);

       esp_err_t err = i2c_master_cmd_begin(
        I2C_NUM_0 , 
        cmd , 
        pdMS_TO_TICKS(1000)
       );
        i2c_cmd_link_delete(cmd);

       if (err != ESP_OK){

        return false ; 

           }
        
        return true ;

    }   



    bool i2c_hal_read_reg ( uint8_t device_addr , uint8_t register_addr , uint8_t *value)
    {

        i2c_cmd_handle_t cmd = i2c_cmd_link_create();

        if (cmd == NULL ){

            return false ;

        }

        i2c_master_start(cmd);

        i2c_master_write_byte(cmd, (device_addr<<1) | I2C_MASTER_WRITE , true);
        i2c_master_write_byte(cmd , register_addr , true );


        i2c_master_start(cmd);
        i2c_master_write_byte(cmd , (device_addr << 1) | I2C_MASTER_READ , true );
        i2c_master_read_byte(cmd , value , I2C_MASTER_NACK );
        
        i2c_master_stop(cmd);

        esp_err_t err = i2c_master_cmd_begin(
            I2C_NUM_0 ,
            cmd, 
            pdMS_TO_TICKS(1000)
        );

        if (err != ESP_OK){

            i2c_cmd_link_delete(cmd);
            return false;

        }

        i2c_cmd_link_delete(cmd);

        return true ; 


    }