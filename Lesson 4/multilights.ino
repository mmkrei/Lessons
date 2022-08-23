enum LED : int {LED1 = 10, LED2 = 11, LED3 = 12};
enum Switch : int {SWITCH1 = 2, SWITCH2 = 3, SWITCH3 = 4};

LED leds[3] = {LED1, LED2, LED3};
Switch switches[3] = {SWITCH1, SWITCH2, SWITCH3};

void setup() {
	for(int i = 0; i < 3; ++i)
	{
		pinMode(leds[i], OUTPUT);
		pinMode(switches[i], INPUT);
	}
}

void loop() {
	for(int i = 0; i < 3; ++i)
	{
		flashLED(leds[i], switches[i]);
	}
}

void flashLED(LED led, Switch pin)
{
	if(digitalRead(pin))
	{
		digitalWrite(led, LOW);
        delay(1000);
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        delay(100);
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
	}
	else
	{
		digitalWrite(led, LOW);
	}
}