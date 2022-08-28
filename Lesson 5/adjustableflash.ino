#include <TM1637Display.h>

// Seven segment pins

#define SEG_CLK		PIN6
#define SEG_DIO 	PIN5

// Rotary encoder pins

#define ENC_CLK 	PIN2
#define ENC_DT 		PIN3
#define ENC_SW 		PIN4

// Flash delay definitions

const int 	min			= 10;
const int 	max			= 200;
const int 	increment	= 10;
int 		flashDelay	= 100;

// Seven segment and rotary encoder definitions

TM1637Display 	sevenSegment	= TM1637Display(SEG_CLK, SEG_DIO);
int 			currentCLK 		= 0;
int 			previousCLK 	= 0;

// Light and switch definitions

enum LED 	: int {LED1 = 10, LED2 = 11, LED3 = 12};
enum Switch : int {SWITCH1 = 7, SWITCH2 = 8, SWITCH3 = 9};

LED 	leds[3] 	= {LED1, LED2, LED3};
Switch 	switches[3] = {SWITCH1, SWITCH2, SWITCH3};

// Called at startup, used to initialize program
void setup()
{
	// Configure encoder

	pinMode(ENC_CLK,	INPUT);
	pinMode(ENC_DT,		INPUT);
	pinMode(ENC_SW,		INPUT_PULLUP); // Using an internal resistor, force the button high to prevent floating from 0-5V

	// Note: interrupts only work on digital pins 2 and 3 

	attachInterrupt(digitalPinToInterrupt(ENC_CLK), updateDelay, CHANGE);
	attachInterrupt(digitalPinToInterrupt(ENC_DT), updateDelay, CHANGE);

	// Configure lights and switches

	for(int i = 0; i < 3; ++i)
	{
		pinMode(leds[i], OUTPUT);
		pinMode(switches[i], INPUT);
	}

	// Configure seven segment display

	sevenSegment.setBrightness(1);
	sevenSegment.showNumberDec(flashDelay);

	previousCLK = digitalRead(ENC_CLK);	// Initial encoder position

	Serial.begin(9600);
}

// Routine called at regular intervals
void loop()
{
	// Reset delay if the encoder dislay is pressed

	if (digitalRead(ENC_SW) == LOW)
	{
		flashDelay = 100;
	}

	// Flash the LEDs

	for(int i = 0; i < 3; ++i)
	{
		flashLED(leds[i], switches[i]);
	}

	// Update the display

	sevenSegment.showNumberDec(flashDelay);
}

// Flashes the led if the switch is set
void flashLED(LED led, Switch pin)
{
	if(digitalRead(pin))
	{
		digitalWrite(led, HIGH);
        delay(flashDelay);
        digitalWrite(led, LOW);
        delay(flashDelay);
	}
}

// Interrupt routine called when rotary encoder has pulsed
void updateDelay()
{
	currentCLK = digitalRead(ENC_CLK);

	Serial.print(">CLK:");
	Serial.println(currentCLK);

	if (currentCLK != previousCLK)
	{
		// Encoder has been rotated

		Serial.print(">DT:");
		Serial.println(digitalRead(ENC_DT));

		if (digitalRead(ENC_DT) != currentCLK)
		{
			// Different signals indicate clockwise rotation

			if(flashDelay < max)
			{
				flashDelay += increment;
			}
		}
		else
		{
			// Same signals indicate counter-clockwise rotation

			if(flashDelay > min)
			{
				flashDelay -= increment;
			}
		}
	}

	Serial.print(">Delay:");
	Serial.println(flashDelay);

	previousCLK = currentCLK;
}