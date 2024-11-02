#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

double startTime = 0;
double elapsedTime = 0;
bool running = false;
bool button1Pressed = false;
bool button2Pressed = false;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  Serial.begin(9600);

  pinMode(8, INPUT_PULLUP); // Button 1 for start/stop
  pinMode(9, INPUT_PULLUP); // Button 2 for reset
}

void loop() {
  // Display prompt to press start if not running
  if (!running && elapsedTime == 0) {
    lcd.clear();
    lcd.print("Press Start");
    //delay(1000);
  }

  // Check Button 1 for Start/Stop functionality
  if (digitalRead(8) == LOW && !button1Pressed) {
    //delay(10000);
    button1Pressed = true; // Mark button as pressed
	//delay(100);
    if (!running) {
      // Start timer
      running = true;
      startTime = millis();
      //delay(100);
    } else {
      // Stop timer
      running = false;
      elapsedTime = (millis() - startTime) / 1000.0;
      //delay(100);
    }
  } else if (digitalRead(8) == HIGH) {
    button1Pressed = false; // Reset button state when released
    //delay(100);
  }

  // Check Button 2 for Reset functionality
  if (digitalRead(9) == LOW && !button2Pressed) {
    //delay(10000);
    button2Pressed = true; // Mark button as pressed
    running = false;
    elapsedTime = 0;
    lcd.clear();
    lcd.print("Press Start");
  } else if (digitalRead(9) == HIGH) {
    button2Pressed = false; // Reset button state when released
  }

  // Update display based on running state
  lcd.setCursor(0, 0);
  if (running) {
    //delay(10000);
    double currentTime = (millis() - startTime) / 1000.0;
    lcd.print(currentTime);
  } else {
    lcd.print(elapsedTime);
  }

  lcd.setCursor(7, 0);
  lcd.print(" Sec's");

  delay(100);
}
