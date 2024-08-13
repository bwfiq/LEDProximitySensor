# LEDProximitySensor

A simple project to control an LED strip that reacts to the proximity of objects using an ultrasonic sensor. The LED strip changes colors when an object is detected and smoothly returns to the default color when the object moves away.

## Features
- **Proximity Detection:** Changes LED color based on object distance.
- **Smooth Transitions:** LED colors fade smoothly between states.
- **Pulsing Brightness:** LED brightness gently pulses for a dynamic effect.

## Hardware Requirements
- **Microcontroller:** Compatible with Arduino or ESP8266/ESP32.
- **LED Strip:** WS2812B.
- **Ultrasonic Sensor:** HC-SR04.
- **Power Supply:** Adequate power for both the microcontroller and LED strip.

## Pin Configuration
- **LED Strip Data Pin:** D0 (GPIO16)
- **Ultrasonic Trigger Pin:** D1 (GPIO5)
- **Ultrasonic Echo Pin:** D2 (GPIO4)

## Software Setup
1. Install the [FastLED library](https://github.com/FastLED/FastLED) via the Arduino IDE Library Manager.
2. Clone or download this repository.
3. Upload the `LEDProximitySensor.ino` file to your microcontroller.

## Usage
1. Wire the components as described in the pin configuration.
2. Power on the setup; the LED strip will start pulsing in the default green color.
3. The color changes when an object is detected within 10 cm. The LEDs return to green when the object is removed.

## Customization
- **Change the number of LEDs:** Adjust `NUM_LEDS` in the code. Default is set to 500 LEDs as setting more LEDs in the code than there are actual LEDs doesn't affect the functionality of the program.
- **Modify detection distance:** Change `DETECTION_DISTANCE`.
- **Adjust transition speed:** Modify `TRANSITION_DURATION`.
- **Set default color:** Change `DEFAULT_COLOR` in the code.

