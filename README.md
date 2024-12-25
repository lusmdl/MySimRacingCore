# Sim Racing Core Controller

Welcome to the Sim Racing Core Controller repository!

This project focuses on programming the ATmega32u4 microcontroller to serve as the core of a high-performance sim racing setup. 
The controller independently handles all tasks, including steering, pedals, and accessory management, ensuring a streamlined and immersive racing experience—all without external setup software.

Other projects require PC-based software. 
This solution does everything directly on the microcontroller. 
Sensor calibration, configuration, and adjustments are all handled locally and stored in the microcontroller’s memory. 
The system can be operated intuitively via a simple interface.

This repository is designed to prioritize simplicity and reliability, with clean, maintainable code that’s easy to understand and adapt to your needs.

## Features

- 32 buttons (includes joystick button (1) for setup)
- Steering-Axis without FFB (Steering)
- Accelerate-Axis
- Brake-Axis
- X-Rotation-Axis (Joystick)
- Y-Rotation-Axis (Joystick)

## Getting Started

You can use the pre compiled hex file. 
Or you compile it yourself.

## Hardware Requirements

- **ATmega32u4 Microcontroller**: I use the original arduino micro board
- **Steering Wheel**: I use a cheap optical encoder with A and B line from china
- **Pedals**: I use a old xbox360 racing wheele pedal set. It only needs to work with potis.
- **Buttons**: The microcontroller get the 16 bit data from I2C Interface Adress 8 & 9 button data. You need a diffrent device for this. Look at my other project [here](https://github.com/lusmdl/MySimRacingButtonBox)!
- **Joystick**: I use a hall-effect sony dualshock joystick
- **LCD**: I use 1602 with an I2C module attached

> Example PCB for the project
![KiCad-PCB-Design](https://github.com/lusmdl/MySimRacingCore/blob/main/doc/hardware/Pictures/PCBA.png)

## Software Requirements

- [**Platform IO**](https://platformio.org/install/ide?install=vscode): Used for programming the ATmega32u4 microcontroller.
- [**AVR Lib**](https://github.com/avrdudes/avr-libc.git): standard lib for programming atmega microcontrollers with platformIO.
- [**Arduino AVR Core**](https://github.com/arduino/ArduinoCore-avr.git): used `Arduino.h`, `Wire.h` and `EEPROM.h`
- [**Arduino Joystick With Force Feedback Library**](https://github.com/YukMingLaw/ArduinoJoystickWithFFBLibrary.git): used for USB communication with the game

## Software Installation and Setup

1. **Install PlatformIO**:
- Follow the [installation guide](https://platformio.org/install) to set up PlatformIO in your preferred environment (VSCode, Atom, etc.).

2. **Clone the Repository**:

```sh
git clone https://github.com/lusmdl/MySimRacingCore.git
```

3. **Open the Project**:
- Open the cloned repository folder in your PlatformIO environment.

4. **Build and Upload**:
- Connect your Arduino Micro.
- Build and upload the code using PlatformIO:

```sh
pio run --target upload
```

### Hardware Setup


## Usage

1. **Connecting the Hardware**:
- Connect the accessorys to the Arduino Micro as per your configuration.
- Connect the Arduino Micro to the PC.

2. **Running the Code**:
- Power up your setup.
- The Arduino Micro will continuously push the accessorys states and update the Game data via USB.

## Documentation
- **Software**: [doc/software/html/index.html](doc/software/html/index.html)

## Contributing

We welcome contributions from the community!

First, read the [general contributing conventions for projects from me](CONTRIBUTING.md).

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a new Pull Request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
