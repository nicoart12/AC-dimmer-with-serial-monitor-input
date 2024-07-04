#define triacPulse 10
#define SW 7
#define ZVC 2

int x = 0;

void setup() {
  Serial.begin(115200);
  pinMode(ZVC, INPUT_PULLUP);
  pinMode(triacPulse, OUTPUT);
  pinMode(SW, INPUT);
  digitalWrite(SW, INPUT_PULLUP);
}

void loop() {
  if (Serial.available() > 0) {
    // Membaca nilai dari serial monitor dan mengonversinya menjadi integer
    x = Serial.parseInt();
    Serial.print("Nilai x: ");
    Serial.println(x);
  }
  
  if (!digitalRead(SW)) { // Ketika tombol ditekan
    Serial.println(digitalRead(ZVC));
    attachInterrupt(digitalPinToInterrupt(ZVC), acon, FALLING); // Pasang interrupt di pin ZVC
  } else {
    detachInterrupt(digitalPinToInterrupt(ZVC)); // Lepaskan interrupt
  }
}

void acon() {
  delayMicroseconds(x); // Baca nilai x dari serial monitor
  digitalWrite(triacPulse, HIGH);
  delayMicroseconds(50); // Tunda 50 mikrodetik pada output pulse untuk menyalakan triac
  digitalWrite(triacPulse, LOW);
}
