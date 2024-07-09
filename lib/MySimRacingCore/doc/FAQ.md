# FAQ

---
# Please explain how you tell the pc which device are connected. Do I need a driver. I use windows 11

When connecting a custom device, like your ATmega32U4-based sim racing wheel base, to a PC running Windows 11, the communication and device recognition depend on how the device is configured to present itself to the computer. Here's how it works and what you need:

### USB Device Descriptor
The ATmega32U4 can be programmed to act as a Human Interface Device (HID) using the USB HID class. This class is natively supported by Windows, meaning you typically don't need to install a separate driver; Windows will automatically recognize the device and install a generic HID driver.

### Steps to Ensure Proper Recognition

1. **USB HID Configuration:**
   - Ensure your device's firmware configures the USB interface as an HID device. This is done using the USB descriptors which define the device's capabilities to the host system (Windows in this case).

2. **Device Descriptors:**
   - The `USB_VID` (Vendor ID) and `USB_PID` (Product ID) in your `platformio.ini` file are part of the device descriptors that tell the PC what kind of device it is. Windows uses these identifiers to recognize and load the appropriate driver.
   - For a custom device, you can use a unique VID and PID pair. If you don't have a unique VID, you can use the Arduino default or get one from the USB-IF organization.

3. **HID Report Descriptor:**
   - This descriptor defines the data format that your device will send and receive. For a sim racing wheel, you might need to define reports for various sensors and force feedback.

### Example Configuration

Here's an example of how you might set up the descriptors in the `platformio.ini` and firmware:

#### `platformio.ini`
```ini
[env:atmega32u4]
platform = atmelavr
board = sparkfun_promicro16
framework = cplusplus
lib_deps = 
    HID-Project
    adafruit/Adafruit SSD1306@^2.4.6
    adafruit/Adafruit GFX Library@^1.10.13
build_flags = 
    -D USB_VID=0x2341
    -D USB_PID=0x8036
    -D USB_MANUFACTURER="My Manufacturer"
    -D USB_PRODUCT="Sim Racing Wheel Base"
```

#### Example HID Report Descriptor
The HID report descriptor is a binary structure that defines the format of the data packets sent and received by your device. Here's a simplified example:

```cpp
#include <HID-Project.h>

// Define the HID report descriptor
const uint8_t HID_REPORT_DESCRIPTOR[] PROGMEM = {
    0x05, 0x01, // Usage Page (Generic Desktop)
    0x09, 0x04, // Usage (Joystick)
    0xa1, 0x01, // Collection (Application)
    0x15, 0x00, // Logical Minimum (0)
    0x26, 0xff, 0x03, // Logical Maximum (1023)
    0x75, 0x10, // Report Size (16)
    0x95, 0x01, // Report Count (1)
    0x09, 0x30, // Usage (X)
    0x81, 0x82, // Input (Data,Var,Abs,Vol)
    0x09, 0x31, // Usage (Y)
    0x81, 0x82, // Input (Data,Var,Abs,Vol)
    0x09, 0x32, // Usage (Z)
    0x81, 0x82, // Input (Data,Var,Abs,Vol)
    0x09, 0x33, // Usage (Rx)
    0x81, 0x82, // Input (Data,Var,Abs,Vol)
    0x09, 0x34, // Usage (Ry)
    0x81, 0x82, // Input (Data,Var,Abs,Vol)
    0x09, 0x35, // Usage (Rz)
    0x81, 0x82, // Input (Data,Var,Abs,Vol)
    0xc0 // End Collection
};

// Initialize HID device with the report descriptor
void setup() {
    HID.begin();
    HID.write(HID_REPORT_DESCRIPTOR, sizeof(HID_REPORT_DESCRIPTOR));
}

void loop() {
    // Send data to the PC according to the report descriptor
    uint16_t data[] = { steeringValue, throttleValue, brakeValue, clutchValue, button1State, button2State };
    HID.write(data, sizeof(data));
    delay(10);
}
```

### Windows Recognition

When you plug in your device:

1. **Windows Device Manager:**
   - Open Device Manager to verify if your device is recognized. It should appear under the "Human Interface Devices" section if configured correctly.

2. **No Additional Drivers Needed:**
   - Windows 11 will automatically install a generic HID driver, so you don't need any additional drivers. The HID class is built into Windows.

### Custom Software

If you need specific software to interact with the device (e.g., for additional features or more advanced interaction than the generic driver provides), you can develop it using libraries that support HID devices, such as:
- **hidapi** (for cross-platform support)
- **WinUSB** (for Windows-specific applications)

### Summary

- **HID Device:** Configure your ATmega32U4 as an HID device using USB descriptors.
- **Descriptors:** Use USB_VID, USB_PID, and HID report descriptors to define the device.
- **Windows 11 Compatibility:** Windows 11 will recognize the HID device and install a generic driver without needing additional drivers.
- **Device Manager:** Use Device Manager to verify recognition.
- **Custom Software:** Develop custom software if needed for advanced interaction.

With this setup, your device should be recognized by Windows 11 as an HID device, allowing for seamless communication between your sim racing wheel base and the PC.

---

# How many buttons can I connect to the device if I could connect an unlimited number of buttons. I want to know how many buttons the hid Oder windows can handle 

The number of buttons you can connect to an HID device, like your ATmega32U4-based sim racing wheel base, and how many buttons Windows can handle, depends on the HID report descriptor and the limitations of the HID class in the USB specification.

### HID Specification

The HID specification allows for a large number of inputs, but practical limits are defined by the report descriptor and how the data is structured. Here are some key points:

1. **Buttons in HID Report Descriptor:**
   - You can define multiple buttons in the HID report descriptor. Each button is typically represented by a single bit.
   - An HID report can support up to 8 bytes (64 bits) for a button array, meaning you could theoretically have up to 64 buttons in a single report if you use the standard 8-byte limit for a report descriptor.

2. **Windows Limitations:**
   - Windows can handle a large number of buttons through HID. The practical limit is more likely determined by how you implement the report descriptor and how you handle the data in your application.
   - In general, for gaming devices like joysticks, the DirectInput API can support up to 128 buttons, but the typical limit for HID reports is 64 buttons due to the 8-byte report descriptor limit.

### Example HID Report Descriptor with Buttons

Here's an example of an HID report descriptor that supports 32 buttons:

```cpp
#include <HID-Project.h>

// Define the HID report descriptor
const uint8_t HID_REPORT_DESCRIPTOR[] PROGMEM = {
    0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
    0x09, 0x04,       // USAGE (Joystick)
    0xa1, 0x01,       // COLLECTION (Application)
    0x15, 0x00,       //   LOGICAL_MINIMUM (0)
    0x25, 0x01,       //   LOGICAL_MAXIMUM (1)
    0x35, 0x00,       //   PHYSICAL_MINIMUM (0)
    0x45, 0x01,       //   PHYSICAL_MAXIMUM (1)
    0x75, 0x01,       //   REPORT_SIZE (1)
    0x95, 0x20,       //   REPORT_COUNT (32)
    0x05, 0x09,       //   USAGE_PAGE (Button)
    0x19, 0x01,       //   USAGE_MINIMUM (Button 1)
    0x29, 0x20,       //   USAGE_MAXIMUM (Button 32)
    0x81, 0x02,       //   INPUT (Data,Var,Abs)
    0xc0              // END_COLLECTION
};

// Initialize HID device with the report descriptor
void setup() {
    HID.begin();
    HID.write(HID_REPORT_DESCRIPTOR, sizeof(HID_REPORT_DESCRIPTOR));
}

void loop() {
    // Prepare button data (32 buttons)
    uint32_t buttonData = 0b10101010101010101010101010101010; // Example button states
    HID.write(&buttonData, sizeof(buttonData));
    delay(10);
}
```

### Increasing the Number of Buttons

If you need more than 32 buttons, you can extend the HID report descriptor. Here's an example for 64 buttons:

```cpp
const uint8_t HID_REPORT_DESCRIPTOR[] PROGMEM = {
    0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
    0x09, 0x04,       // USAGE (Joystick)
    0xa1, 0x01,       // COLLECTION (Application)
    0x15, 0x00,       //   LOGICAL_MINIMUM (0)
    0x25, 0x01,       //   LOGICAL_MAXIMUM (1)
    0x35, 0x00,       //   PHYSICAL_MINIMUM (0)
    0x45, 0x01,       //   PHYSICAL_MAXIMUM (1)
    0x75, 0x01,       //   REPORT_SIZE (1)
    0x95, 0x40,       //   REPORT_COUNT (64)
    0x05, 0x09,       //   USAGE_PAGE (Button)
    0x19, 0x01,       //   USAGE_MINIMUM (Button 1)
    0x29, 0x40,       //   USAGE_MAXIMUM (Button 64)
    0x81, 0x02,       //   INPUT (Data,Var,Abs)
    0xc0              // END_COLLECTION
};

// Initialize HID device with the report descriptor
void setup() {
    HID.begin();
    HID.write(HID_REPORT_DESCRIPTOR, sizeof(HID_REPORT_DESCRIPTOR));
}

void loop() {
    // Prepare button data (64 buttons)
    uint8_t buttonData[8] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA}; // Example button states
    HID.write(buttonData, sizeof(buttonData));
    delay(10);
}
```

### Summary

- **HID Report Descriptor:** Defines the number of buttons.
- **Windows Support:** Can handle a large number of buttons through the HID class, with practical limits typically around 64 buttons per HID report.
- **DirectInput API:** Supports up to 128 buttons, but HID descriptors typically limit to 64 buttons for practical purposes.
- **Custom Descriptor:** Modify the HID report descriptor to support the number of buttons you need.

Using these configurations, you can create an HID device that supports a large number of buttons and is recognized by Windows without needing additional drivers.

---

# How to use the oled display without Arduino lib

To use the OLED display without relying on the `Arduino.h` library, we need to directly interact with the I2C interface and manage the SSD1306 OLED display's initialization and data transfer. This can be done using low-level register manipulations.

Below is an example that demonstrates how to interface with the SSD1306 OLED display using direct register manipulations for I2C communication with the ATmega32U4.

### Example Code

#### `platformio.ini`
```ini
[env:atmega32u4]
platform = atmelavr
board = sparkfun_promicro16
framework = cplusplus
lib_deps = 
    adafruit/Adafruit SSD1306@^2.4.6
    adafruit/Adafruit GFX Library@^1.10.13
build_flags = 
    -D USB_VID=0x2341
    -D USB_PID=0x8036
    -D USB_MANUFACTURER="My Manufacturer"
    -D USB_PRODUCT="Sim Racing Wheel Base"
```

#### I2C and OLED Handling without `Arduino.h`

### `include/i2c.h`
```cpp
#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

void i2c_init() {
    TWSR = 0x00; // Set prescaler to 1
    TWBR = 0x0C; // SCL frequency is 400KHz (16MHz CPU clock)
    TWCR = (1 << TWEN); // Enable TWI
}

void i2c_start() {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // Send START condition
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set
}

void i2c_stop() {
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT); // Send STOP condition
    while (TWCR & (1 << TWSTO)); // Wait for STOP condition to be executed
}

void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT); // Clear TWINT to start transmission
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set
}

uint8_t i2c_read_ack() {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // Enable ACK generation
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set
    return TWDR;
}

uint8_t i2c_read_nack() {
    TWCR = (1 << TWEN) | (1 << TWINT); // Enable NACK generation
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set
    return TWDR;
}

#endif // I2C_H
```

### `include/ssd1306.h`
```cpp
#ifndef SSD1306_H
#define SSD1306_H

#include "i2c.h"

#define SSD1306_ADDR 0x3C
#define SSD1306_COMMAND 0x00
#define SSD1306_DATA 0x40

void ssd1306_command(uint8_t cmd) {
    i2c_start();
    i2c_write(SSD1306_ADDR << 1);
    i2c_write(SSD1306_COMMAND);
    i2c_write(cmd);
    i2c_stop();
}

void ssd1306_data(uint8_t data) {
    i2c_start();
    i2c_write(SSD1306_ADDR << 1);
    i2c_write(SSD1306_DATA);
    i2c_write(data);
    i2c_stop();
}

void ssd1306_init() {
    ssd1306_command(0xAE); // Display off
    ssd1306_command(0xD5); // Set display clock divide ratio/oscillator frequency
    ssd1306_command(0x80); // Default setting for display clock divide ratio/oscillator frequency
    ssd1306_command(0xA8); // Set multiplex ratio
    ssd1306_command(0x3F); // 1/64 duty
    ssd1306_command(0xD3); // Set display offset
    ssd1306_command(0x00); // No offset
    ssd1306_command(0x40); // Set start line address
    ssd1306_command(0x8D); // Enable charge pump regulator
    ssd1306_command(0x14); // Enable charge pump
    ssd1306_command(0x20); // Set memory addressing mode
    ssd1306_command(0x00); // Horizontal addressing mode
    ssd1306_command(0xA1); // Set segment re-map (A0/A1)
    ssd1306_command(0xC8); // Set COM output scan direction (C0/C8)
    ssd1306_command(0xDA); // Set COM pins hardware


---

# I need to display text. Please add some easy methods to set the cursor and the text height and print the string


To display text on the OLED display, we need to implement basic functions for setting the cursor position, setting text height, and printing strings. We'll create a minimal text handling system for the SSD1306 OLED display, which doesn't rely on `Arduino.h`. We'll also use the existing I2C functions for communication.

Here's the complete implementation with methods for setting the cursor position, text height, and printing strings:

### `include/i2c.h`
```cpp
#ifndef I2C_H
#define I2C_H

#include <avr/io.h>

void i2c_init() {
    TWSR = 0x00; // Set prescaler to 1
    TWBR = 0x0C; // SCL frequency is 400KHz (16MHz CPU clock)
    TWCR = (1 << TWEN); // Enable TWI
}

void i2c_start() {
    TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // Send START condition
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set
}

void i2c_stop() {
    TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT); // Send STOP condition
    while (TWCR & (1 << TWSTO)); // Wait for STOP condition to be executed
}

void i2c_write(uint8_t data) {
    TWDR = data;
    TWCR = (1 << TWEN) | (1 << TWINT); // Clear TWINT to start transmission
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set
}

uint8_t i2c_read_ack() {
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // Enable ACK generation
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set
    return TWDR;
}

uint8_t i2c_read_nack() {
    TWCR = (1 << TWEN) | (1 << TWINT); // Enable NACK generation
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set
    return TWDR;
}

#endif // I2C_H
```

### `include/ssd1306.h`
```cpp
#ifndef SSD1306_H
#define SSD1306_H

#include "i2c.h"
#include <avr/pgmspace.h>
#include "font8x8_basic.h"  // Include the basic 8x8 font

#define SSD1306_ADDR 0x3C
#define SSD1306_COMMAND 0x00
#define SSD1306_DATA 0x40

class SSD1306 {
public:
    SSD1306();
    void init();
    void clear();
    void setCursor(uint8_t x, uint8_t y);
    void setTextSize(uint8_t size);
    void print(const char *str);

private:
    uint8_t cursorX, cursorY, textSize;

    void sendCommand(uint8_t cmd);
    void sendData(uint8_t data);
};

#endif // SSD1306_H
```

### `lib/SSD1306/SSD1306.cpp`
```cpp
#include "ssd1306.h"

SSD1306::SSD1306() : cursorX(0), cursorY(0), textSize(1) {}

void SSD1306::init() {
    i2c_init();
    sendCommand(0xAE); // Display off
    sendCommand(0xD5); // Set display clock divide ratio/oscillator frequency
    sendCommand(0x80); // Default setting for display clock divide ratio/oscillator frequency
    sendCommand(0xA8); // Set multiplex ratio
    sendCommand(0x3F); // 1/64 duty
    sendCommand(0xD3); // Set display offset
    sendCommand(0x00); // No offset
    sendCommand(0x40); // Set start line address
    sendCommand(0x8D); // Enable charge pump regulator
    sendCommand(0x14); // Enable charge pump
    sendCommand(0x20); // Set memory addressing mode
    sendCommand(0x00); // Horizontal addressing mode
    sendCommand(0xA1); // Set segment re-map (A0/A1)
    sendCommand(0xC8); // Set COM output scan direction (C0/C8)
    sendCommand(0xDA); // Set COM pins hardware configuration
    sendCommand(0x12); // Alternative COM pin configuration, disable COM left/right remap
    sendCommand(0x81); // Set contrast control
    sendCommand(0xCF); // Set SEG output current brightness
    sendCommand(0xD9); // Set pre-charge period
    sendCommand(0xF1); // Set pre-charge period (External VCC / Internal VCC)
    sendCommand(0xDB); // Set VCOMH deselect level
    sendCommand(0x40); // Set VCOMH deselect level
    sendCommand(0xA4); // Entire display on (resume)
    sendCommand(0xA6); // Set normal display (not inverted)
    sendCommand(0xAF); // Display on
    clear();
}

void SSD1306::sendCommand(uint8_t cmd) {
    i2c_start();
    i2c_write(SSD1306_ADDR << 1);
    i2c_write(SSD1306_COMMAND);
    i2c_write(cmd);
    i2c_stop();
}

void SSD1306::sendData(uint8_t data) {
    i2c_start();
    i2c_write(SSD1306_ADDR << 1);
    i2c_write(SSD1306_DATA);
    i2c_write(data);
    i2c_stop();
}

void SSD1306::clear() {
    for (uint16_t i = 0; i < 1024; i++) {
        sendData(0x00);
    }
    setCursor(0, 0);
}

void SSD1306::setCursor(uint8_t x, uint8_t y) {
    cursorX = x;
    cursorY = y;
}

void SSD1306::setTextSize(uint8_t size) {
    textSize = size;
}

void SSD1306::print(const char *str) {
    while (*str) {
        for (uint8_t i = 0; i < 8; i++) {
            uint8_t line = pgm_read_byte(&font8x8_basic[(uint8_t)*str][i]);
            for (uint8_t j = 0; j < textSize; j++) {
                sendData(line);
            }
        }
        cursorX += 8 * textSize;
        if (cursorX >= 128) {
            cursorX = 0;
            cursorY += 8 * textSize;
            if (cursorY >= 64) {
                cursorY = 0;
            }
        }
        str++;
    }
}
```

### `include/font8x8_basic.h`
```cpp
#ifndef FONT8X8_BASIC_H
#define FONT8X8_BASIC_H

#include <avr/pgmspace.h>

const uint8_t font8x8_basic[128][8] PROGMEM = {
    // Add the 8x8 font data here, for example:
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 0x00
    // ... (other characters)
    {0x7E,0x81,0xA5,0x81,0xBD,0x99,0x81,0x7E}  // 0x7F
};

#endif // FONT8X8_BASIC_H
```

### `src/main.cpp`
```cpp
#include "i2c.h"
#include "ssd1306.h"

SSD1306 display;

int main(void) {
    display.init();
    display.clear();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.print("Hello, World!");

    while (1) {
        // Main loop
    }

    return 0;
}
```

### Summary
1. **I2C Communication:** Implemented basic I2C communication functions in `i2c.h`.
2. **SSD1306 Initialization:** Added SSD1306 initialization and command functions in `ssd1306.h` and `SSD1306.cpp`.
3. **Text Display:** Added functions to set cursor position, text size, and print strings on the OLED display.
4. **Font Data:** Included a basic 8x8 font in `font8x8_basic.h`.
5. **Example Usage:** Demonstrated usage in `main.cpp`.

With this setup, you can control the SSD1306 OLED display using direct register manipulations without relying on the `Arduino.h` library, and you have basic methods to display text on the screen.

---

# How did you receive the force feedback data? Which commands/data came from the game like assetto Corsa. Please explain how it works 

Force feedback data for games like Assetto Corsa typically comes through protocols like DirectInput or the more modern XInput, which are interfaces provided by Microsoft for gaming peripherals. These APIs allow the game to send force feedback commands to the hardware, which the firmware on the device interprets and uses to control the motors for the force feedback effect.

### Receiving Force Feedback Data

To receive force feedback data, your device needs to:

1. **Identify as a Force Feedback Device:** Your device must be recognized by the system as a force feedback device, which usually means it must conform to certain HID specifications.
2. **Handle Force Feedback Commands:** The firmware must be able to interpret the force feedback commands sent by the game.

### How Force Feedback Works

1. **Initialization:**
   - The game detects connected gaming devices and queries their capabilities.
   - Devices like steering wheels will report their ability to handle force feedback effects.

2. **Force Feedback Effects:**
   - Common effects include constant force, ramp force, periodic force (sine, square, triangle), and custom effects.
   - The game sends these effects to the device with parameters such as magnitude, duration, direction, etc.

3. **USB HID Report for Force Feedback:**
   - The device firmware receives these commands via USB HID reports.
   - The HID report descriptor must be designed to handle these reports.

### Example HID Report Descriptor for Force Feedback

Here is an example HID report descriptor that includes both input (buttons, axes) and output (force feedback) capabilities. This is a simplified example and may need adjustments for your specific needs:

```cpp
const uint8_t HID_REPORT_DESCRIPTOR[] PROGMEM = {
    0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
    0x09, 0x04,       // USAGE (Joystick)
    0xa1, 0x01,       // COLLECTION (Application)
    // Axes
    0x15, 0x00,       //   LOGICAL_MINIMUM (0)
    0x26, 0xFF, 0x03, //   LOGICAL_MAXIMUM (1023)
    0x75, 0x10,       //   REPORT_SIZE (16)
    0x95, 0x04,       //   REPORT_COUNT (4)
    0x09, 0x30,       //   USAGE (X)
    0x09, 0x31,       //   USAGE (Y)
    0x09, 0x32,       //   USAGE (Z)
    0x09, 0x35,       //   USAGE (Rz)
    0x81, 0x02,       //   INPUT (Data,Var,Abs)
    // Buttons
    0x15, 0x00,       //   LOGICAL_MINIMUM (0)
    0x25, 0x01,       //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,       //   REPORT_SIZE (1)
    0x95, 0x20,       //   REPORT_COUNT (32)
    0x05, 0x09,       //   USAGE_PAGE (Button)
    0x19, 0x01,       //   USAGE_MINIMUM (Button 1)
    0x29, 0x20,       //   USAGE_MAXIMUM (Button 32)
    0x81, 0x02,       //   INPUT (Data,Var,Abs)
    // Force Feedback
    0x09, 0x5A,       //   USAGE (PID State Report)
    0xA1, 0x02,       //   COLLECTION (Logical)
    0x85, 0x02,       //     REPORT_ID (2)
    0x09, 0x5B,       //     USAGE (PID State)
    0x75, 0x08,       //     REPORT_SIZE (8)
    0x95, 0x01,       //     REPORT_COUNT (1)
    0x91, 0x02,       //     OUTPUT (Data,Var,Abs)
    0xC0,             //   END_COLLECTION
    0xC0              // END_COLLECTION
};
```

### Handling Force Feedback in Firmware

In the firmware, you would set up an endpoint to handle HID OUT reports. This is where the force feedback data will be sent from the game. You need to parse these reports and apply the force feedback to the motors.

#### Example Firmware Snippet

Here's a simplified example of how you might handle receiving force feedback commands:

```cpp
#include <HID-Project.h>

// Assume motor control functions are implemented elsewhere
void setMotorForce(int force);

void receiveForceFeedback() {
    if (HID_ReceiveReport()) {
        uint8_t reportId;
        uint8_t data[8]; // Size depends on the report descriptor
        HID_ReadReport(&reportId, sizeof(reportId));
        
        if (reportId == 2) { // Assuming 2 is the report ID for force feedback
            HID_ReadReport(data, sizeof(data));
            // Parse data to determine the force
            int force = data[1]; // Simplified example, actual parsing will depend on descriptor
            setMotorForce(force);
        }
    }
}
```

### How the Data is Sent by the Game

1. **Game Initialization:**
   - The game queries the device capabilities.
   - The game identifies the device as a force feedback device via its HID report descriptor.

2. **Force Feedback Commands:**
   - The game sends commands to create, start, stop, and modify force feedback effects.
   - These commands are sent as HID OUT reports to the device.

3. **Firmware Processing:**
   - The device firmware receives these reports, interprets them, and controls the motors to apply the effects.

### Practical Implementation

To fully implement this, you would need:

1. **Complete HID Report Descriptor:**
   - Define all the necessary input and output reports for your device.

2. **USB HID Handling in Firmware:**
   - Set up endpoints to handle HID IN and OUT reports.
   - Implement logic to interpret the force feedback commands.

3. **Motor Control:**
   - Implement the actual motor control logic to apply the force feedback effects.

4. **Testing and Tuning:**
   - Test with games like Assetto Corsa to ensure the force feedback works correctly and fine-tune the responses.

By following these steps and understanding the flow of data, you can create a device that properly handles force feedback commands from games like Assetto Corsa.

---

# Does this mean I get only the int value named “force” ? What does it mean if this is under zero and over zero? How should I interpret this?

To interpret the force feedback commands from games like Assetto Corsa, it's important to understand that the actual data sent from the game will be more complex than a simple integer value. The force feedback data typically includes information about the type of force feedback effect, its duration, magnitude, direction, and other parameters.

### Force Feedback Data Structure

In the context of HID (Human Interface Device) reports, force feedback data is usually encoded in a structured way. The specific interpretation depends on the HID report descriptor you define and the HID class driver's implementation on the game side. Here’s a simplified explanation:

1. **Report ID:** Identifies the type of report (e.g., a force feedback report).
2. **Effect Type:** Specifies the type of force feedback effect (constant force, ramp, periodic, etc.).
3. **Magnitude:** The strength of the force.
4. **Direction:** The direction of the force (can be 0-360 degrees for angular force).
5. **Duration:** How long the force should be applied.

### Example HID Report Descriptor for Force Feedback

Here’s a more detailed HID report descriptor example that includes force feedback effects:

```cpp
const uint8_t HID_REPORT_DESCRIPTOR[] PROGMEM = {
    0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
    0x09, 0x04,       // USAGE (Joystick)
    0xa1, 0x01,       // COLLECTION (Application)
    // Axes
    0x15, 0x00,       //   LOGICAL_MINIMUM (0)
    0x26, 0xFF, 0x03, //   LOGICAL_MAXIMUM (1023)
    0x75, 0x10,       //   REPORT_SIZE (16)
    0x95, 0x04,       //   REPORT_COUNT (4)
    0x09, 0x30,       //   USAGE (X)
    0x09, 0x31,       //   USAGE (Y)
    0x09, 0x32,       //   USAGE (Z)
    0x09, 0x35,       //   USAGE (Rz)
    0x81, 0x02,       //   INPUT (Data,Var,Abs)
    // Buttons
    0x15, 0x00,       //   LOGICAL_MINIMUM (0)
    0x25, 0x01,       //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,       //   REPORT_SIZE (1)
    0x95, 0x20,       //   REPORT_COUNT (32)
    0x05, 0x09,       //   USAGE_PAGE (Button)
    0x19, 0x01,       //   USAGE_MINIMUM (Button 1)
    0x29, 0x20,       //   USAGE_MAXIMUM (Button 32)
    0x81, 0x02,       //   INPUT (Data,Var,Abs)
    // Force Feedback
    0x05, 0x0F,       //   USAGE_PAGE (Physical Interface)
    0x09, 0x92,       //   USAGE (PID State Report)
    0xA1, 0x02,       //   COLLECTION (Logical)
    0x85, 0x02,       //     REPORT_ID (2)
    0x09, 0x9F,       //     USAGE (Device Paused)
    0x75, 0x01,       //     REPORT_SIZE (1)
    0x95, 0x01,       //     REPORT_COUNT (1)
    0x81, 0x02,       //     INPUT (Data,Var,Abs)
    0x75, 0x07,       //     REPORT_SIZE (7)
    0x95, 0x01,       //     REPORT_COUNT (1)
    0x81, 0x03,       //     INPUT (Cnst,Var,Abs)
    0x09, 0xA0,       //     USAGE (Actuators Enabled)
    0x75, 0x01,       //     REPORT_SIZE (1)
    0x95, 0x01,       //     REPORT_COUNT (1)
    0x81, 0x02,       //     INPUT (Data,Var,Abs)
    0xC0,             //   END_COLLECTION
    0xC0              // END_COLLECTION
};
```

### Firmware Example to Interpret Force Feedback

Here’s a simplified example to demonstrate how you might interpret and handle a constant force effect. The actual parsing logic would depend on your HID descriptor and the specific format of the reports.

```cpp
#include <HID-Project.h>

// Assume motor control functions are implemented elsewhere
void setMotorForce(int force);

void receiveForceFeedback() {
    if (HID_ReceiveReport()) {
        uint8_t reportId;
        uint8_t data[8]; // Size depends on the report descriptor
        HID_ReadReport(&reportId, sizeof(reportId));
        
        if (reportId == 2) { // Assuming 2 is the report ID for force feedback
            HID_ReadReport(data, sizeof(data));
            // Parse data to determine the force
            int force = data[1]; // Simplified example, actual parsing will depend on descriptor
            setMotorForce(force);
        }
    }
}

void setMotorForce(int force) {
    if (force > 0) {
        // Apply positive force (e.g., clockwise rotation)
        analogWrite(MOTOR_PIN1, force);
        analogWrite(MOTOR_PIN2, 0);
    } else if (force < 0) {
        // Apply negative force (e.g., counterclockwise rotation)
        analogWrite(MOTOR_PIN1, 0);
        analogWrite(MOTOR_PIN2, -force);
    } else {
        // Stop motors
        analogWrite(MOTOR_PIN1, 0);
        analogWrite(MOTOR_PIN2, 0);
    }
}
```

### Understanding Force Values

- **Positive Force Values:** These might indicate a force in one direction (e.g., clockwise rotation for a steering wheel).
- **Negative Force Values:** These might indicate a force in the opposite direction (e.g., counterclockwise rotation for a steering wheel).
- **Zero Force Value:** This would typically indicate no force being applied.

### How the Data is Sent by the Game

1. **Game Initialization:**
   - The game queries the device capabilities.
   - The game identifies the device as a force feedback device via its HID report descriptor.

2. **Force Feedback Commands:**
   - The game sends commands to create, start, stop, and modify force feedback effects.
   - These commands are sent as HID OUT reports to the device.

3. **Firmware Processing:**
   - The device firmware receives these reports, interprets them, and controls the motors to apply the effects.

### Practical Implementation

To fully implement this, you would need:

1. **Complete HID Report Descriptor:**
   - Define all the necessary input and output reports for your device.

2. **USB HID Handling in Firmware:**
   - Set up endpoints to handle HID IN and OUT reports.
   - Implement logic to interpret the force feedback commands.

3. **Motor Control:**
   - Implement the actual motor control logic to apply the force feedback effects.

4. **Testing and Tuning:**
   - Test with games like Assetto Corsa to ensure the force feedback works correctly and fine-tune the responses.

By following these steps and understanding the flow of data, you can create a device that properly handles force feedback commands from games like Assetto Corsa.