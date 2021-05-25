#define _SENSOR_CONFIG_H

void Sensor_config();
void writeRegister(uint8_t reg, uint8_t value);
void writeList(const struct regval_list cmd[]);
