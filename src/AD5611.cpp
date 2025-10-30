#include "AD5611.h"

#define DAC_SPI_FREQUENCY 10000000 
/**
 * @brief AD5611 DAC driver class.
 *
 * This class provides an interface for controlling the AD5611 Digital-to-Analog Converter
 * via SPI. It supports writing 10-bit values to the DAC.
 */
AD5611::AD5611(int syncPin) {
    _csPin = syncPin;
}

/**
 * @brief Initializes the AD5611 Digital-to-Analog Converter (DAC).
 *
 * This function sets up the necessary pins and communication protocols for the AD5611.
 * It configures the Chip Select (CS) pin as an output and sets it to a HIGH state
 * (inactive) to prepare for SPI communication. It then initializes the SPI bus.
 * This function should be called once in the `setup()` routine of an Arduino sketch.
 */
void AD5611::begin() {
    pinMode(_csPin, OUTPUT);
    digitalWrite(_csPin, HIGH); 

    SPI.begin(); 
}

/**
 * @brief Writes a digital value to the AD5611 Digital-to-Analog Converter (DAC).
 *
 * This function takes a 10-bit digital value and sends it to the AD5611 DAC
 * via SPI. It first checks if the provided value is within the DAC's
 * configured resolution. If valid, it constructs the command byte by
 * combining the DAC's normal operating mode with the input value,
 * then transfers the high and low bytes over the SPI bus.
 *
 * @param value The 10-bit digital value to be written to the DAC.
 *              This value should be less than (1 << _resolution).
 * @return int Returns 0 on successful write, or -1 if the provided value
 *             exceeds the DAC's configured resolution.
 */
int AD5611::writeValue(uint16_t value) {
    if (value >= (1 << _resolution)) {
        return -1; 
    }

    uint16_t command = DAC_AD56X1_MODE_NORMAL; 
    
    command |= value << 4; 
    uint8_t highByte = (uint8_t)(command >> 8);
    uint8_t lowByte = (uint8_t)(command & 0xFF);

    SPI.beginTransaction(SPISettings(DAC_SPI_FREQUENCY, MSBFIRST, SPI_MODE1));

    digitalWrite(_csPin, LOW);

    SPI.transfer(highByte);
    SPI.transfer(lowByte);

    digitalWrite(_csPin, HIGH);
    SPI.endTransaction();

    return 0;
}