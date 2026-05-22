#pragma once 
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

bool i2c_hal_init(void);
bool i2c_hal_write_reg(uint8_t device_addr , uint8_t register_addr , uint8_t value  );
bool i2c_hal_read_reg(uint8_t device_addr , uint8_t register_addr , uint8_t *value ); 



