#include "PulseSensorPlayground.h"   // Include the PulseSensor library to interact with the pulse sensor
#include <SPI.h>                     // SPI library to communicate with devices
#include <Wire.h>                    // Wire library to communicate with I2C devices like the OLED display
#include <Adafruit_GFX.h>            // Include Adafruit GFX library for handling graphics on OLED
#include <Adafruit_SH110X.h>         // Include Adafruit SH110X library for using SH1106 OLED displays

#define i2c_Address 0x3c             // Define the I2C address for the OLED display (0x3C is common for 128x64 displays)

#define SCREEN_WIDTH 128             // Set the width of the OLED display in pixels
#define SCREEN_HEIGHT 64             // Set the height of the OLED display in pixels
#define OLED_RESET -1                // Define the reset pin for OLED (-1 if not using one)
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Create a display object using Adafruit_SH1106G class

#define NUMFLAKES 10              
#define XPOS 0                    
#define YPOS 1                    
#define DELTAY 2                  
const int threshold = 35;            // Sensitivity threshold for detecting steps via accelerometer readings
int stepCount = 0;                   // Variable to hold the number of detected steps
int lastReading = 0;                 // Variable to store the last accelerometer reading for comparison

// Constants
const int PULSE_SENSOR_PIN = D0;     // Define the digital pin where the PulseSensor is connected (D0 in this case)
const int ACCELEROMETER_PIN = A0;    // Define the analog pin where the accelerometer is connected (A0 for reading analog values)
const int LED_PIN = LED_BUILTIN;     // Use the onboard LED pin (built-in LED) to blink on heartbeat detection
const int THRESHOLD = 550;           // Define the threshold value for detecting a heartbeat pulse

// Create PulseSensorPlayground object to interact with the pulse sensor
PulseSensorPlayground pulseSensor;

unsigned long previousMillis = 0;    // Variable to store the last time the display was updated (for timing purposes)
const long interval = 3000;          // Set a 3-second delay interval for alternating between displaying steps and heart rate
bool displaySteps = true;            // Boolean variable to toggle between displaying steps and heart rate

void setup() {
  Serial.begin(115200);              // Start the serial communication at 115200 baud rate for debugging purposes

  delay(250);                        // Wait 250ms for the OLED display to initialize
  display.begin(i2c_Address, true);  // Initialize the OLED display with I2C address (0x3C) and reset
  display.display();                 // Show any initial content on the OLED (buffered)
  delay(2000);                       // Wait 2 seconds to allow any startup information to be visible

  display.clearDisplay();            // Clear the OLED display to remove any previous content
  display.setTextSize(2);            // Set text size to 2 for better visibility on the OLED screen
  display.setTextColor(SH110X_WHITE);// Set text color to white for the OLED display

  // Configure PulseSensor
  pulseSensor.analogInput(PULSE_SENSOR_PIN); // Assign the PulseSensor to read from the defined analog pin
  pulseSensor.blinkOnPulse(LED_PIN);         // Set up the onboard LED to blink on detecting a heartbeat
  pulseSensor.setThreshold(THRESHOLD);       // Set the threshold for heartbeat detection

  // Check if PulseSensor is initialized correctly
  if (pulseSensor.begin()) {
    Serial.println("PulseSensor object created successfully!");  // Output success message in the serial monitor
  }
}

void loop() {
  int sensorValue = analogRead(ACCELEROMETER_PIN); // Read the analog value from the accelerometer connected to A0

  // DEBUG: Print the raw accelerometer value to the serial monitor
  Serial.print("Accelerometer Value: ");
  Serial.println(sensorValue);      // Display the accelerometer's current value in the serial monitor for debugging

  // Step counting logic
  if (abs(sensorValue - lastReading) > threshold) {  // If the difference between the current and last accelerometer reading exceeds the threshold
    stepCount++;                                     // Increment the step count
    Serial.print("Step count: ");
    Serial.println(stepCount);                       // Output the updated step count to the serial monitor
  }

  lastReading = sensorValue;                         // Update lastReading with the current accelerometer value

  int currentBPM = pulseSensor.getBeatsPerMinute();  // Get the current Beats Per Minute (BPM) from the PulseSensor

  // Check if a heartbeat is detected
  if (pulseSensor.sawStartOfBeat()) {                // If the PulseSensor detected the start of a heartbeat
    Serial.println("♥ A HeartBeat Happened!");       // Output heartbeat message to the serial monitor
    Serial.print("BPM: ");
    Serial.println(currentBPM);                      // Display the current BPM in the serial monitor
  }

  // Switch between displaying steps and heart rate every 3 seconds
  unsigned long currentMillis = millis();            // Get the current time in milliseconds
  if (currentMillis - previousMillis >= interval) {  // If 3 seconds have passed since the last update
    previousMillis = currentMillis;                  // Update the previousMillis timestamp
    displaySteps = !displaySteps;                    // Toggle between displaying steps and heart rate
  }

  if (displaySteps) {                                // If it's time to display step count
    displayStepCount(stepCount);                     // Call the function to display the step count
  } else {                                           // Otherwise, display heart rate (BPM)
    displayBPM(currentBPM);                          // Call the function to display the BPM
  }

  delay(100);                                        // Introduce a short delay to avoid rapid execution and false triggers
}

// Function to display the step count on the OLED screen
void displayStepCount(int count) {
  display.clearDisplay();                            // Clear the OLED display
  display.setCursor(0, 0);                           // Set the cursor to the top-left corner of the OLED
  display.print("Steps: ");                          // Print the label "Steps:" on the screen
  display.println(count);                            // Print the current step count value
  display.display();                                 // Push the data to the OLED screen to make it visible
}

// Function to display the BPM (heart rate) on the OLED screen
void displayBPM(int bpm) {
  display.clearDisplay();                            // Clear the OLED display
  display.setCursor(0, 0);                           // Set the cursor to the top-left corner of the OLED
  display.print("BPM: ");                            // Print the label "BPM:" on the screen
  display.println(bpm);                              // Print the current BPM value
  display.display();                                 // Push the data to the OLED screen to make it visible
}
