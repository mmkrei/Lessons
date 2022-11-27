#include <TM1637Display.h>

// Battery percent macro

#define BATTERY_PERCENT 100*((double)batteryLevel / (double)batteryCapacity)

// Seven segment

#define SEG_CLK	PIN6
#define SEG_DIO PIN5

// "Battery" level

unsigned int	batteryCapacity	= 50000;
unsigned int	batteryLevel 	= 0;
unsigned int	ticks 			= 0;
unsigned int	wait 			= 100;

TM1637Display 	sevenSegment	= TM1637Display(SEG_CLK, SEG_DIO);

// Photosensor

int 		sensorPin 	= A0;
int 		onboardLED	= 13;
int 		sensorValue = 0;
const int	sensorMax	= 500; // Determined empirically to be ~500 at maximum brightness

void setup()
{
	pinMode(onboardLED, OUTPUT);
	sevenSegment.setBrightness(1);
	Serial.begin(9600);
}

void loop()
{
	// Get photosensor value and flash onboard LED

	sensorValue = analogRead(sensorPin);
	flashOnboardLED(((double)(sensorMax - sensorValue)/sensorMax) * 100); // Flash faster with increased brightness

	// Calculate battery level (prevent calculation that exceeds capacity)

	batteryLevel += (batteryLevel >= batteryCapacity) ? 0 : sensorValue;

	// Print to serial and seven segment

	printToSerial(true);
 	sevenSegment.showNumberDecEx(BATTERY_PERCENT);

	// Delay and add to tick count used for serial output

	delay(wait);
	ticks += wait;
}

// Flashes the onboard LED, using "flashDelay" parameter as a delay
void flashOnboardLED(int flashDelay)
{
	digitalWrite(onboardLED, HIGH);
	delay(flashDelay);
	digitalWrite(onboardLED, LOW);
	delay(flashDelay);
}

// Prints to serial or VS Code's teleplot extension when "printPlot" is set to 'true'
void printToSerial(bool printPlot) 
{
	if(printPlot)
	{
		Serial.print(">Level:");
		Serial.println(batteryLevel);
		Serial.print(">Percent:");
		Serial.println(BATTERY_PERCENT);
		Serial.print(">Sensor:");
		Serial.println(sensorValue);
	}
	else
	{
		Serial.print(ticks);
		Serial.print(" ms    charge at ");
		Serial.print(BATTERY_PERCENT);
		Serial.println("%");
	}
}