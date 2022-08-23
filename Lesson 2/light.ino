int Light = 12; //HERO board pin 12

void setup () {
    pinMode(Light, OUTPUT);
    digitalWrite(Light, LOW);
}


void loop() {
    digitalWrite(Light, HIGH);
    delay(1000);
    digitalWrite(Light, LOW);
    delay(1000);
}