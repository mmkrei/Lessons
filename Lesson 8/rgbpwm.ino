#define RED 	11
#define GREEN	10
#define BLUE	9

void setup()
{
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
}

void loop()
{
	RGB_color(125, 0, 0); // Red
	delay(800);
	RGB_color(0, 125, 0); // Green
	delay(800);
	RGB_color(0, 0, 125); // Blue
	delay(800);
	RGB_color(64, 32, 0); // yellow
	delay(800);
	RGB_color(125, 0, 125); // purple
	delay(800);
	RGB_color(125, 125, 125); // white
	delay(2000);
}

void RGB_color(int redValue, int greenValue, int blueValue)
{
	analogWrite(RED,	redValue);
	analogWrite(GREEN,	greenValue);
	analogWrite(BLUE,	blueValue);
}