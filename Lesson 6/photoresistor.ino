#include <TM1637Display.h>

// Seven segment

#define SEG_CLK	PIN6
#define SEG_DIO PIN5

// "Battery" level

unsigned int	batteryCapacity	= 50000;
unsigned int	batteryLevel 	= 0;
unsigned int	ticks 			= 0;
unsigned int	wait 			= 100;
double			percentage;

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
	// Get photosensor value and flash light

	sensorValue = analogRead(sensonPin);
	digitalWrite(onboardLED, HIGH);
	delay(sensorValue);
	digitalWrite(onboardLED, LOW);
	delay(sensorValue);
	
	// Adjust the battery level (based on input from the photosensor)

	batteryLevel	+= sensorValue;
  	ticks 			+= wait;
 
	if(batteryLevel >= batteryCapacity) 
	{
		// Battery level is full 
		
		Serial.print(ticks);
		Serial.print(">ms:");
		Serial.println("FULLY CHARGED");
	
		batteryLevel = batteryCapacity; // to prevent integer from continuing to increase
		
		ticks = 0;
		
		delay(20000);	// long pause
	}
	else 
	{
		PrintBatteryPercentage();
	}
 
 	delay(wait);
	sevenSegment.showNumberDecEx(percentage);
}

void PrintBatteryPercentage() 
{
	Serial.print(ticks);
	Serial.print(" ms    charge at ");

	percentage=100*((double)batteryLevel / (double)batteryCapacity);
	Serial.print(percentage);

	// print a percent character and line return...
	Serial.println("%");
}