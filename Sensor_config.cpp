#include <Wire.h>
#include "Regs.h"
#include "Sensor_config.h"
#include <Arduino.h>

const int i2c_address = 0x21;

void Sensor_config(){
  
  Wire.begin();
  
  writeList(reset);
  
  writeList(qvga_rgb565);
  }
  
  
void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(i2c_address);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void writeList(const struct regval_list cmd[]) {
  for (int i = 0; cmd[i].reg <= REG_LAST; i++) {
    writeRegister(cmd[i].reg, cmd[i].value);
    delay(1);
  }
}
