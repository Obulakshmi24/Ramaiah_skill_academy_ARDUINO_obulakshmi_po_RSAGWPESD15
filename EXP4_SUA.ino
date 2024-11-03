// Define pins for ultrasonic sensor
#define trigPin A0   // Trig pin for ultrasonic sensor
#define echoPin A1   // Echo pin for ultrasonic sensor

// Touch sensor pin
#define touchPin 2   // Touch sensor pin

// 7-segment display segment and power pins
#define SEGMENT_A 9
#define SEGMENT_B 8
#define SEGMENT_C 7
#define SEGMENT_D 6
#define SEGMENT_E 3
#define SEGMENT_F 4
#define SEGMENT_G 5

#define POWER_PIN_1 10
#define POWER_PIN_2 11
#define POWER_PIN_3 12
#define POWER_PIN_4 13

const byte SEGMENT_PINS[8] = {SEGMENT_A, SEGMENT_B, SEGMENT_C, SEGMENT_D, SEGMENT_E, SEGMENT_F, SEGMENT_G, 2}; // Adjusted to reflect actual pins
const byte POWER_PINS[4] = {POWER_PIN_1, POWER_PIN_2, POWER_PIN_3, POWER_PIN_4};
const byte SEGMENT_LENGTH = sizeof(SEGMENT_PINS) / sizeof(byte);
const byte POWER_LENGTH = sizeof(POWER_PINS) / sizeof(byte);

// Segment bitwise patterns for each LED segment
const unsigned int SEGMENTS[8] = {
    1 << 0, // middle
    1 << 1, // top left
    1 << 2, // top
    1 << 3, // top right
    1 << 4, // dot
    1 << 5, // bottom right
    1 << 6, // bottom
    1 << 7  // bottom left
};

// Digit patterns for numbers 0-9 and "E" error indicator
const unsigned int DIGITS[11] = {
    (SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5] | SEGMENTS[6] | SEGMENTS[7]), // 0
    (SEGMENTS[3] | SEGMENTS[5]), // 1
    (SEGMENTS[0] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[6] | SEGMENTS[7]), // 2
    (SEGMENTS[0] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5] | SEGMENTS[6]), // 3
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[3] | SEGMENTS[5]), // 4
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[5] | SEGMENTS[6]), // 5
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[5] | SEGMENTS[6] | SEGMENTS[7]), // 6
    (SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5]), // 7
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5] | SEGMENTS[6] | SEGMENTS[7]), // 8
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[3] | SEGMENTS[5] | SEGMENTS[6]), // 9
    (SEGMENTS[0] | SEGMENTS[1] | SEGMENTS[2] | SEGMENTS[6] | SEGMENTS[7]) // "E"
};

// Threshold distance in cm to reset the timer
const int thresholdDistance = 10;

void setup() {
    // Set up serial monitor
    Serial.begin(9600);

    // Set up the ultrasonic sensor pins
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Set up the touch sensor pin
    pinMode(touchPin, INPUT_PULLUP);

    // Set up 7-segment display pins
    for (byte i = 0; i < POWER_LENGTH; i++) {
        pinMode(POWER_PINS[i], OUTPUT);
        digitalWrite(POWER_PINS[i], LOW);
    }
    for (byte i = 0; i < SEGMENT_LENGTH; i++) {
        pinMode(SEGMENT_PINS[i], OUTPUT);
        digitalWrite(SEGMENT_PINS[i], HIGH);
    }
}

void loop() {
    // Wait for the touch sensor to be pressed
    if (digitalRead(touchPin) == LOW) {
        startCountdown();
    }
}

void startCountdown() {
    for (int count = 9; count >= 0; count--) {
        displayNumber(count);
        Serial.print("Countdown: ");
        Serial.println(count); // Display countdown value on Serial Monitor

        delay(1000); // 1-second delay for countdown

        // Check if obstacle is detected
        unsigned int distance = measureDistance();
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm"); // Display distance on Serial Monitor

        if (distance < thresholdDistance) {
            Serial.println("Obstacle detected! Resetting countdown.");
            count = 9; // Reset the countdown if an object is detected
        }
    }
    displayError(); // Display "E" if countdown completes without interruption
    Serial.println("Countdown completed without interruption. Displaying 'E'.");
}

unsigned int measureDistance() {
    // Clear the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    // Set the trigPin high for 10us to send pulse
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Read echoPin, get duration
    long duration = pulseIn(echoPin, HIGH);
    
    // Calculate the distance in cm
    return duration * 0.034 / 2;
}

// Function to display a number on the 7-segment display
void displayNumber(int number) {
    int thousands = number / 1000;
    int hundreds = (number / 100) % 10;
    int tens = (number / 10) % 10;
    int units = number % 10;

    displayDigit(thousands, 0);
    delay(5);
    displayDigit(hundreds, 1);
    delay(5);
    displayDigit(tens, 2);
    delay(5);
    displayDigit(units, 3);
    delay(5);
}

// Function to display a single digit on a specific position
void displayDigit(int digit, int position) {
    // Activate only the specified digit (position)
    for (int i = 0; i < 4; i++) digitalWrite(POWER_PINS[i], LOW); // Turn off all digits
    digitalWrite(POWER_PINS[position], HIGH); // Turn on the specified digit

    // Set segments for the desired digit
    for (int i = 0; i < 8; i++) {
        if (DIGITS[digit] & SEGMENTS[i]) {
            digitalWrite(SEGMENT_PINS[i], LOW);
        } else {
            digitalWrite(SEGMENT_PINS[i], HIGH);
        }
    }
}

// Function to display an error ("E") on the 7-segment display
void displayError() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(POWER_PINS[i], LOW); // Turn off all digits
    }
    digitalWrite(POWER_PINS[3], HIGH); // Use the last digit position for "E"

    // Set segments to display "E"
    for (int i = 0; i < 8; i++) {
        if (DIGITS[10] & SEGMENTS[i]) {
            digitalWrite(SEGMENT_PINS[i], LOW);
        } else {
            digitalWrite(SEGMENT_PINS[i], HIGH);
        }
    }
}
