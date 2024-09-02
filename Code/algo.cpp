const int photodiodePin = A0; // Photodiode connected to analog pin A0
const int ledPin = 8; // LED connected to digital pin 8
const int buzzerPin = 9; // Buzzer connected to digital pin 9

const int threshold = 100; // Threshold value for the photodiode signal
const unsigned long alarmDelay = 5000; // 5 seconds delay

unsigned long lastSignalTime = 0;

void setup() {
    pinMode(ledPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(ledPin, LOW); // Turn off LED
    digitalWrite(buzzerPin, LOW); // Turn off buzzer
    Serial.begin(9600);
}

void loop() {
    int photodiodeValue = analogRead(photodiodePin);

    if (photodiodeValue > threshold) {
        // Photodiode is receiving signal from the laser
        digitalWrite(ledPin, HIGH); // Turn on LED
        lastSignalTime = millis(); // Update the last signal time
        digitalWrite(buzzerPin, LOW); // Turn off the buzzer if it was on
    } else {
        // Photodiode is not receiving signal from the laser
        digitalWrite(ledPin, LOW); // Turn off LED

        if (millis() - lastSignalTime > alarmDelay) {
            // More than 5 seconds have passed without signal
            digitalWrite(buzzerPin, HIGH); // Turn on buzzer
        }
    }

    Serial.print("Photodiode Value: ");
    Serial.println(photodiodeValue);
    delay(100); // Short delay to avoid spamming the Serial Monitor
}