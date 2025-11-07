#ifndef AD5611_H
#define AD5611_H

#include <Arduino.h>
#include <SPI.h> 

/**
 * @brief Class for controlling the AD5611 Digital-to-Analog Converter
 * 
 * The AD5611 is a 10-bit Digital-to-Analog Converter (DAC) with SPI interface.
 * This class provides methods to initialize and control the DAC.
 * 
 * @note Operating voltage range: 2.7V to 5.5V
 * @note Resolution: 10-bit
 * 
 * Power modes available:
 * - Normal operation
 * - Power-down with 1kΩ to GND
 * - Power-down with 100kΩ to GND
 * - Power-down in three-state
 */
class AD5611 {
public:
    
    AD5611(int syncPin);
    
    bool begin();

    int writeValue(uint16_t value);

private:
    int _csPin;

    const uint8_t _resolution = 10;
    const uint16_t DAC_AD56X1_MODE_NORMAL = 0x0000; 
    const uint16_t DAC_AD56X1_MODE_POWER_DOWN_1K = 0x4000;
    const uint16_t DAC_AD56X1_MODE_POWER_DOWN_100K = 0x8000;
    const uint16_t DAC_AD56X1_MODE_POWER_DOWN_THREE_STATE = 0xC000;
};

#endif