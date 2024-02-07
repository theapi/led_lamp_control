

const int buttonPin = 7;
const int ledPin = LED_BUILTIN;
const int analogInPin = A0;
const int analogInPin2 = A1;
const int analogOutPin = 6;
const int analogOutPin2 = 5;

int ledState = LOW;
int buttonState;
int lastButtonState = LOW;
int sensorValue = 0;
int outputValue = 0;
int sensorValue2 = 0;
int outputValue2 = 0;
int outputState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long lastPotTime = 0;
unsigned long potDelay = 2;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        outputState = ledState;
      }

      digitalWrite(ledPin, ledState);
    }
  }

  lastButtonState = reading;

  // Process the pots
  if ((millis() - lastPotTime) > potDelay) {
    if (outputState) {
      sensorValue = analogRead(analogInPin);
      sensorValue2 = analogRead(analogInPin2);

      outputValue = map(sensorValue, 0, 1023, 0, 255);
      analogWrite(analogOutPin, outputValue);
      outputValue2 = map(sensorValue2, 0, 1023, 0, 255);
      analogWrite(analogOutPin2, outputValue2);
    } else {
      analogWrite(analogOutPin, 0);
      analogWrite(analogOutPin2, 0);
    }

    lastPotTime = millis();
  }
}

