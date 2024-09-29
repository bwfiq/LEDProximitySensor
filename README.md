# LEDProximitySensor

A simple project to control an LED strip that reacts to the proximity of objects using an ultrasonic sensor. The LED strip changes colors when an object is detected and smoothly returns to the default color when the object moves away.

Used in and developed for SG Night Fest 2024's Delulu High.

## Features
- **Proximity Detection:** Changes LED color based on object distance.
- **Smooth Transitions:** LED colors fade smoothly between states.
- **Pulsing Brightness:** LED brightness gently pulses in a sine wave.

## Hardware Requirements
- **Microcontroller:** NodeMCU ESP8266
- **LED Strip:** WS2812B (can be changed to any [compatible with FastLED](https://github.com/FastLED/FastLED/wiki/Chipset-reference))
- **Ultrasonic Sensor:** HC-SR04
- **Power Supply:** Adequate power for both the microcontroller and LED strip

## NodeMCU ESP8266 Specific Set-up Instructions

1. **Pin Configuration:**
   - **LED Strip Data Pin:** Connect to D0 (GPIO16)
   - **Ultrasonic Trigger Pin:** Connect to D1 (GPIO5)
   - **Ultrasonic Echo Pin:** Connect to D2 (GPIO4)

2. **Power Supply:**
   - **LED Strip:** Ensure the LED strip has a stable 5V power supply. The NodeMCU's 3.3V pin is not sufficient for the LEDs.
   - **Microcontroller:** Power the NodeMCU via USB or a 5V source connected to Vin.
   - **Ultrasonic Sensor:** Power the HC-SR04 via a 5V source connected to VCC.

3. **Library Installation:**
   - Install the [FastLED library](https://github.com/FastLED/FastLED) using the Arduino IDE Library Manager.

4. **ESP8266 Setup in Arduino IDE:**
   - In the Arduino IDE, go to `File > Preferences`.
   - Add this URL to the "Additional Board Manager URLs" field: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
   - Go to `Tools > Board > Boards Manager`, search for "ESP8266", and install it.
   - Select `NodeMCU 1.0 (ESP-12E Module)` under `Tools > Board`.

5. **CH340C Driver Installation:**
   - If your NodeMCU board uses the CH340C USB-to-serial chip, you may need to install the appropriate driver to ensure your computer can communicate with the board.
   - **Download Driver:**
     - For Windows: [Download CH340C Driver](https://drive.google.com/file/d/1kk0b2HTYLKBXxS4TNNlC_neef6iE94sV/view)
     - For Mac: [Download CH340C Driver](https://drive.google.com/file/d/1iZ4fO-eAttw0ztlWVN_VTPB9cVSOu3CX/view)
     - For Linux: [Download CH340C Driver](https://drive.google.com/file/d/1iZ4fO-eAttw0ztlWVN_VTPB9cVSOu3CX/view)
     - Or: [Get the latest driver from factory](http://www.wch.cn/downloads/CH341SER_ZIP.html)
   - **Verify Installation:**
     - After installation, connect your NodeMCU to your computer via USB. The board should now appear under `Tools > Port` in the Arduino IDE.

6. **Uploading Code:**
   - Clone or download this repository.
   - Open the `LEDProximitySensor.ino` file in the Arduino IDE.
   - Select the correct port under `Tools > Port`.
   - Upload the code to your NodeMCU.

## Usage
1. Wire the components as described in the pin configuration.
2. Power on the setup; the LED strip will start pulsing in the default green color.
3. The color changes when an object is detected within 10 cm. The LEDs return to green when the object is removed.

## Customization
- **Set default color:** Change `DEFAULT_COLOR` in the code.
  - CRGB::Black represents a turned off state. A list of colours can be found [here](https://fastled.io/docs/struct_c_r_g_b.html).
- **Modify detection distance:** Change `DETECTION_DISTANCE`.
- **Adjust transition speed:** Modify `TRANSITION_DURATION`.
