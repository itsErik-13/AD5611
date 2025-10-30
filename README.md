# AD5611 DAC Driver for Arduino (and ESP32)

## 💡 Overview

This library provides a simple interface to control the single-channel Digital-to-Analog Converter (DAC) **Analog Devices AD5611 (10-bit)** via the **Serial Peripheral Interface (SPI)** bus.

The driver is optimized to work on Arduino and ESP32 platforms, assuming 16-bit communication (2 bytes) in normal mode.

## 🛠️ Hardware Requirements

* **Microcontroller:** ESP32.
* **DAC Chip:** AD5611.
* **Required Libraries:**
    * **SPI.h** (Included in the Arduino/ESP32 core).

## 🔌 Pin Connection (ESP32 Example)

The driver uses your board's main SPI bus and requires an independent Chip Select (CS) pin.

| Pin Function | DAC Pin | ESP32 Pins (e.g., VSPI) | Notes |
| :--- | :--- | :--- | :--- |
| Clock | SCL | **GPIO18** | Shared bus |
| Master Out, Slave In | DIN (Data In) | **GPIO23** | Shared bus |
| **Chip Select** | **SYNC (Frame Sync)** | **-** | User-defined GPIO pin (exclusive for this DAC) |
| Power Supply | VDD | 3.3V or 5V | Depends on the chip and microcontroller |
| Reference | VREF | VDD or external source | Crucial for output accuracy |

## 🚀 Installation

1.  Download the ZIP file from this repository.
2.  In the Arduino IDE, go to **Sketch** $\rightarrow$ **Include Library** $\rightarrow$ **Add .ZIP Library...**
3.  Select the downloaded ZIP file.

## ✍️ Basic Usage Example

The following code shows how to initialize the DAC and write a ramp value between 0 and 1023 (for the 10-bit AD5611).

```cpp
#include <SPI.h>
#include "AD5611.h"

// Define the GPIO pin to be used for SYNC (Chip Select)
#define DAC_SYNC_PIN 13 

// Initialize the library (the constructor requires the SYNC pin)
AD5611 myDAC(DAC_SYNC_PIN);

void setup() {
  Serial.begin(115200);
  myDAC.begin(); // Initializes the CS pin and the SPI bus
  Serial.println("DAC AD5611 - Ready.");
}

void loop() {
  // The AD5611 is 10-bit, so the range is 0 to 1023.
  static uint16_t analogValue = 0;
  
  // Write the value. The DAC converts it to the corresponding voltage.
  if (myDAC.writeValue(analogValue) == 0) {
      Serial.print("Written: ");
      Serial.println(analogValue);
  }

  // Increment the value and reset upon reaching the maximum
  analogValue += 50;
  if (analogValue >= 1024) {
    analogValue = 0;
  }
  
  delay(500);
}
