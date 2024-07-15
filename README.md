# Sim Racing Core Controller

Welcome to the Sim Racing Core Controller repository! This project focuses on programming an ATmega32u4 microcontroller to serve as the central processing unit for a high-performance sim racing setup. The controller is designed to manage steering, pedals, and other accessories, providing a seamless and immersive racing experience.

## Features

- 32 buttons
- X-Axis with FFB
- Accelerate-Axis
- Brake-Axis
- Z-Axis (clutch/Handbrake)
- X-Rotation-Axis (Joystick)
- Y-Rotation-Axis (Joystick)



## Getting Started



## Hardware Requirements

- **ATmega32u4 Microcontroller**: I used the original arduino micro board
- **Steering Wheel**: I used a cheap optical encoder with A and B line from china
- **Pedals**: I used a old xbox360 racing wheele pedal set. It only needs to work with potis.
- **Buttons**: I used 4 2x2 matrixes
- **Joystick**: I used one joystick with an button
- **LCD**: I used 1602 with an I2C module attached

## Software Requirements

- [**Platform IO**](https://platformio.org/install/ide?install=vscode): Used for programming the ATmega32u4 microcontroller.
- [**AVR Lib**](https://github.com/avrdudes/avr-libc.git): standard lib with platformIO.
- [**Arduino Joystick With Force Feedback Library**](https://github.com/YukMingLaw/ArduinoJoystickWithFFBLibrary.git)
- [**Keypad Library**](https://github.com/Chris--A/Keypad.git): Used for the 4x4 Matrix

## Contributing

We welcome contributions from the community! Please read our [CONTRIBUTING.md](CONTRIBUTING.md) to learn how you can help improve this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
