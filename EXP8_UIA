// 7-segment display pins
#define segA 6
#define segB 7
#define segC 8
#define segD 9
#define segE 10
#define segF 11
#define segG 12

// IR sensor pins
#define irSensorEntry 2
#define irSensorExit 3

// Ultrasonic sensor pins
#define trigPin 4
#define echoPin 5

// Variables for people count
int peopleCount = 0;
bool entryDetected = false;
bool exitDetected = false;

void setup() {
    // Set up segment pins
    pinMode(segA, OUTPUT);
    pinMode(segB, OUTPUT);
    pinMode(segC, OUTPUT);
    pinMode(segD, OUTPUT);
    pinMode(segE, OUTPUT);
    pinMode(segF, OUTPUT);
    pinMode(segG, OUTPUT);

    // Set up sensor pins
    pinMode(irSensorEntry, INPUT);
    pinMode(irSensorExit, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.begin(9600);
    displayDigit(peopleCount);  // Initialize display with 0
}

void loop() {
    // Read IR sensor states
    bool entryState = digitalRead(irSensorEntry);
    bool exitState = digitalRead(irSensorExit);

    // Detect entry
    if (entryState == LOW && !entryDetected) {
        entryDetected = true;
        if (measureDistance() < 100) {
            peopleCount = (peopleCount + 1) % 10;  // Reset to 0 if count reaches 10
            displayDigit(peopleCount);
            Serial.println("Person entered. Count: " + String(peopleCount));
        }
    }

    // Detect exit
    if (exitState == LOW && !exitDetected) {
        exitDetected = true;
        if (measureDistance() < 100 && peopleCount > 0) {
            peopleCount--;
            displayDigit(peopleCount);
            Serial.println("Person exited. Count: " + String(peopleCount));
        }
    }

    // Reset detection flags when sensors are clear
    if (entryState == HIGH) entryDetected = false;
    if (exitState == HIGH) exitDetected = false;

    delay(100);  // Debounce delay
}

// Function to measure distance using ultrasonic sensor
unsigned long measureDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    unsigned long duration = pulseIn(echoPin, HIGH);
    unsigned long distance = duration * 0.034 / 2;
    return distance;
}

// Function to display a digit on a 7-segment display
void displayDigit(int digit) {
    // Segment patterns for numbers 0-9 on a 7-segment display
    bool segments[10][7] = {
        {1, 1, 1, 1, 1, 1, 0},  // 0
        {0, 1, 1, 0, 0, 0, 0},  // 1
        {1, 1, 0, 1, 1, 0, 1},  // 2
        {1, 1, 1, 1, 0, 0, 1},  // 3
        {0, 1, 1, 0, 0, 1, 1},  // 4
        {1, 0, 1, 1, 0, 1, 1},  // 5
        {1, 0, 1, 1, 1, 1, 1},  // 6
        {1, 1, 1, 0, 0, 0, 0},  // 7
        {1, 1, 1, 1, 1, 1, 1},  // 8
        {1, 1, 1, 1, 0, 1, 1}   // 9
    };

    // Write segment states based on the digit to display
    digitalWrite(segA, segments[digit][0]);
    digitalWrite(segB, segments[digit][1]);
    digitalWrite(segC, segments[digit][2]);
    digitalWrite(segD, segments[digit][3]);
    digitalWrite(segE, segments[digit][4]);
    digitalWrite(segF, segments[digit][5]);
    digitalWrite(segG, segments[digit][6]);
}
