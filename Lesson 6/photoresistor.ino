#include <TM1637Display.h>

// Seven segment

#define SEG_CLK	PIN6
#define SEG_DIO PIN5

TM1637Display 	sevenSegment	= TM1637Display(SEG_CLK, SEG_DIO);

// Photosensor

int sensonPin 	= A0;
int onboardLED	= 13;
int sensorValue = 0;

void setup()
{
	pinMode(onboardLED, OUTPUT);
	sevenSegment.setBrightness(1);
	Serial.begin(9600);
}

void loop()
{
	sensorValue = analogRead(sensonPin);
	digitalWrite(onboardLED, HIGH);
	delay(sensorValue);
	digitalWrite(onboardLED, LOW);
	delay(sensorValue);
	
	sevenSegment.showNumberDec(sensorValue);

	Serial.print(">sensorValue:");
	Serial.println(sensorValue);
}