// Define pin connections
#define PIRPIN 4   // PIR sensor output pin
#define BUZZER_PIN 5 // Buzzer pin

void setup() {
  Serial.begin(9600); 
  pinMode(PIRPIN, INPUT); // Set PIR pin as input
  pinMode(BUZZER_PIN, OUTPUT); // Set buzzer pin as output
}

void loop() {
  int motionDetected = digitalRead(PIRPIN); // Read PIR sensor state

  // Check if motion is detected
  if (motionDetected == HIGH) {
    // Motion detected, sound the buzzer
    digitalWrite(BUZZER_PIN, HIGH); // Activate buzzer
    Serial.print("Motion detected at: ");
    Serial.println(millis() / 1000); // Log the timestamp in seconds
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW); 
    delay(2000);
  } else {
    // No motion detected
    digitalWrite(BUZZER_PIN, LOW); 
  }

  delay(100);
}
