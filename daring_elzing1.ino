#include <LiquidCrystal.h>

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

const int sosButton = 2;
const int resetButton = 3;
const int ledPin = 13;
const int buzzerPin = 8;

bool emergency = false;
int alertCount = 0;

void setup()
{
  pinMode(sosButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Women Safety");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");

  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Status: SAFE");
  lcd.setCursor(0, 1);
  lcd.print("Alerts: 0");
}

void loop()
{
  // SOS Button Pressed
  if (digitalRead(sosButton) == LOW)
  {
    if (!emergency)
    {
      emergency = true;
      alertCount++;

      Serial.print("EMERGENCY ALERT #");
      Serial.println(alertCount);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("!!! EMERGENCY");
      lcd.setCursor(0, 1);
      lcd.print("Alerts: ");
      lcd.print(alertCount);
    }

    delay(200);
  }

  // Emergency Mode
  if (emergency)
  {
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000);
  }

  // Reset Button Pressed
  if (digitalRead(resetButton) == LOW)
  {
    emergency = false;

    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status: SAFE");
    lcd.setCursor(0, 1);
    lcd.print("Alerts: ");
    lcd.print(alertCount);

    Serial.println("SYSTEM RESET");

    delay(300);
  }
}