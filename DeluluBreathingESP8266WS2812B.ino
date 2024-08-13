#include <FastLED.h>

#define LED_PIN D0   // Data pin connected to D0 (GPIO16)
#define TRIG_PIN D1  // Trigger pin connected to D1 (GPIO5)
#define ECHO_PIN D2  // Echo pin connected to D2 (GPIO4)

#define NUM_LEDS 500         // Number of LEDs in the strip
#define MAX_BRIGHTNESS 255  // Maximum brightness level (0-255)
#define MIN_BRIGHTNESS 32   // Minimum brightness level (0-255)
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define DEFAULT_COLOR CRGB::Green
#define TRANSITION_DURATION 2000
#define DETECTION_DISTANCE 10
#define REFRESH_RATE 10

CRGB leds[NUM_LEDS];

struct LEDController {
  CRGB currentColor = DEFAULT_COLOR;
  CRGB targetColor = DEFAULT_COLOR;

  float fadeValue = 0.0;
  float fadeRate = 0.05;
  unsigned long fadeDuration = TRANSITION_DURATION;
  unsigned long fadeStartTime = 0;

  void setup() {
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(MIN_BRIGHTNESS);
  }

  void update() {
    updateBrightness();
    updateColor();
  }

  void updateBrightness() {
    fadeValue += fadeRate;
    if (fadeValue > TWO_PI) fadeValue -= TWO_PI;
    float brightness = (sin(fadeValue) + 1.0) / 2.0 * (MAX_BRIGHTNESS - MIN_BRIGHTNESS) + MIN_BRIGHTNESS;
    FastLED.setBrightness((uint8_t)brightness);
  }

  void setColor(CRGB color) {
      if (color != targetColor) {
          targetColor = color;
          fadeStartTime = millis();
      }
  }

  void updateColor() {
      unsigned long currentTime = millis();
      if (fadeStartTime > 0 && currentTime - fadeStartTime < fadeDuration) {
          float progress = (float)(currentTime - fadeStartTime) / fadeDuration;
          currentColor = blend(currentColor, targetColor, progress * 255);
      } else {
          currentColor = targetColor;
          fadeStartTime = 0;
      }
      fill_solid(leds, NUM_LEDS, currentColor);
      FastLED.show();
  }
};

struct UltrasonicSensor {
  bool detectionActive = false;

  void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
  }

  long getDistance() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // 30ms timeout to avoid blocking
    if (duration == 0 || duration > 30000) return -1; // Ensure out-of-range values are handled
    return duration * 0.034 / 2;
  }

  bool isObjectDetected() {
    long distance = getDistance();
    if (distance > 0 && distance < DETECTION_DISTANCE) {
      detectionActive = true;
    } else {
      detectionActive = false;
    }
    return detectionActive;
  }
};

LEDController ledController;
UltrasonicSensor ultrasonicSensor;
unsigned long lastUpdate = 0;

void setup() {
  ledController.setup();
  ultrasonicSensor.setup();
}

void loop() {
  unsigned long currentTime = millis();
  bool objectDetected = false;
  if (currentTime - lastUpdate > REFRESH_RATE) {
    lastUpdate = currentTime;

    objectDetected = ultrasonicSensor.isObjectDetected();
    if (objectDetected && ledController.targetColor == DEFAULT_COLOR) {
      byte hue = random(0, 255);
      byte saturation = random(180, 255);
      byte value = 255;
      ledController.setColor(CHSV(hue, saturation, value));
    } 
    else if (!objectDetected && ledController.targetColor != DEFAULT_COLOR) {
      ledController.setColor(DEFAULT_COLOR);
    }

    ledController.update();
  }
}
