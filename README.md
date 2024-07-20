# Sim Racing Core Controller

Welcome to the Sim Racing Core Controller repository! This project focuses on programming an ATmega32u4 microcontroller to serve as the central processing unit for a high-performance sim racing setup. The controller is designed to manage steering, pedals, and other accessories, providing a seamless and immersive racing experience.

## Features

- 32 buttons (includes joystick button (1))
- X-Axis with FFB (Steering)
- Accelerate-Axis
- Brake-Axis
- Z-Axis (clutch/Handbrake)
- X-Rotation-Axis (Joystick)
- Y-Rotation-Axis (Joystick)



## Getting Started

You can use the pre compiled hex file. Or you use compile it [yourself](Installation and Setup).


## Hardware Requirements

- **ATmega32u4 Microcontroller**: I used the original arduino micro board
- **Steering Wheel**: I used a cheap optical encoder with A and B line from china
- **Pedals**: I used a old xbox360 racing wheele pedal set. It only needs to work with potis.
- **Buttons**: I used 4 2x2 matrixes
- **Joystick**: I used one joystick with a button
- **LCD**: I used 1602 with an I2C module attached

## Software Requirements

- [**Platform IO**](https://platformio.org/install/ide?install=vscode): Used for programming the ATmega32u4 microcontroller.
- [**AVR Lib**](https://github.com/avrdudes/avr-libc.git): standard lib with platformIO.
- [**Arduino AVR Core**](https://github.com/arduino/ArduinoCore-avr.git): used `Arduino.h`, `Wire.h` and `EEPROM.h`
- [**Arduino Joystick With Force Feedback Library**](https://github.com/YukMingLaw/ArduinoJoystickWithFFBLibrary.git): used for USB communication with the game

## Installation and Setup

1. **Install PlatformIO**:
   - Follow the [installation guide](https://platformio.org/install) to set up PlatformIO in your preferred environment (VSCode, Atom, etc.).

2. **Clone the Repository**:

   ```sh
   git clone https://github.com/lusmdl/MySimRacingCor.git
   ```

3. **Open the Project**:
   - Open the cloned repository folder in your PlatformIO environment.

4. **Build and Upload**:
   - Connect your Arduino Micro.
   - Build and upload the code using PlatformIO:

   ```sh
   pio run --target upload
   ```

### Arduino Micro Setup


## Usage

1. **Connecting the Hardware**:
   - Connect the accessorys to the Arduino Micro as per your configuration.
   - Connect the Arduino Micro to the PC.

2. **Running the Code**:
   - Power up your setup.
   - The Arduino Micro will continuously push the accessorys states and update the Game data via USB.

## Contributing

We welcome contributions from the community!

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
