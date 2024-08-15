#define TRIG_PIN D1  // Trigger pin connected to D1 (GPIO5)
#define ECHO_PIN D2  // Echo pin connected to D2 (GPIO4)
#define LED_PIN LED_BUILTIN // Built-in LED pin on NodeMCU

#define DETECTION_DISTANCE 10 // Distance threshold in cm

void setup() {
  pinMode(TRIG_PIN, OUTPUT); // Set the trigger pin as output
  pinMode(ECHO_PIN, INPUT);  // Set the echo pin as input
  pinMode(LED_PIN, OUTPUT);   // Set the built-in LED pin as output
}

void loop() {
  long duration, distance;

  // Clear the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Set the trigger pin high for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pin and calculate the duration of the pulse
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in cm (duration * 0.034 / 2)
  distance = duration * 0.034 / 2;

  // Check if the distance is within the detection threshold
  if (distance > 0 && distance < DETECTION_DISTANCE) {
    // Object detected within the threshold
    blinkLED(100); // Blink fast
  } else {
    // No object detected or out of range
    blinkLED(500); // Blink slow
  }

  delay(100); // Short delay before the next measurement
}

// Function to blink the LED
void blinkLED(int delayTime) {
  digitalWrite(LED_PIN, HIGH); // Turn the LED on
  delay(delayTime);            // Wait for the specified time
  digitalWrite(LED_PIN, LOW);  // Turn the LED off
  delay(delayTime);            // Wait for the specified time
}
