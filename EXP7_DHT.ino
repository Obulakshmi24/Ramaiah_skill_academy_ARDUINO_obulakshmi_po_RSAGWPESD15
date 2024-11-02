#define DHTPIN 2
const float TEMP_THRESHOLD = 30.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(2000);
  
  // Simulate temperature reading (replace with your logic or sensor reading)
  float temperature = random(20, 40);  // Generates a random temperature between 20 and 40

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  if (temperature > TEMP_THRESHOLD) {
    Serial.println("Warning: Temperature exceeds threshold!");
  }

  delay(2000);
}
