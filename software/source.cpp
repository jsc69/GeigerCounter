volatile unsigned long counts = 0;
unsigned long lastMillis = 0;
const int pulsePin = 2;

void ISRcount() { counts++; }

void setup() {
  Serial.begin(115200);
  pinMode(pulsePin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pulsePin), ISRcount, RISING);
  lastMillis = millis();
}

void loop() {
  if (millis() - lastMillis >= 60000) {  // jede Minute
    unsigned long cpm = counts;
    counts = 0;
    float uSvh = cpm * 0.01;  // ⚠️ Näherungswert! Siehe unten
    Serial.print("CPM: ");
    Serial.print(cpm);
    Serial.print("   μSv/h (ungefähr): ");
    Serial.println(uSvh, 3);
    lastMillis = millis();
  }
}

