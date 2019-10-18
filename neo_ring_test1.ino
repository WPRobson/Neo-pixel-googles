#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 12 // neoPixle ring pin

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      24 // 2*12 for having 2 rings connected
const int buttonPin1 = 9;
const int buttonPin2 = 10;

int buttonState1;
int buttonState2;

bool button1Enable = true;
bool button2Enable = true;

int red = 200;
int green = 0;
int blue = 0;
int colorMode = 1;

int brightness = 100;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup()
{
	pixels.begin(); // This initializes the NeoPixel library.
	pixels.show(); // This sends the updated pixel color to the hardware.

	pixels.setBrightness(brightness);
	pinMode(buttonPin1, INPUT);
	pinMode(buttonPin2, INPUT);
	turnOnLights(red, green, blue); //rgb

}

void loop()
{

	buttonState1 = digitalRead(buttonPin1);
	buttonState2 = digitalRead(buttonPin2);

	if (buttonState1 == 1 && button1Enable){
		button1Enable = false;
		switchColourMode();
	}
	else{
		button1Enable = true;
	}

	if (buttonState2 == 1 && button2Enable){
		brightness = brightness - 25;

		if (brightness <= 0)
		{
			brightness = 100;
		}
		pixels.setBrightness(brightness);
		turnOnLights(red, green, blue); //rgb
		delay(300);
	}
	else
	{
		button2Enable = true;
	}
	// For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

	//turnOnLights(red, green, blue); //rgb
    //delay(2000);
	//flikerLights();
	//flikerLights();

}

void flikerLights(){
	turnOffLights();
	delay(100); //100
	turnOnLights(red * 25, green * 25, blue * 25);
	delay(150); //150
	turnOffLights();
	delay(50); //50
	turnOnLights(red * 10, green * 10, blue * 10);
}

void turnOnLights(int r, int g, int b){
	for (int i = 0; i < NUMPIXELS; i++)
	{
		// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
		pixels.setPixelColor(i, pixels.Color(r, g, b)); // Moderately bright green color.
		pixels.show();
	}
}

void turnOffLights(){
	for (int i = 0; i < NUMPIXELS; i++)
	{
		pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
		pixels.show();
	}
}

void switchColourMode(){
	colorMode = colorMode + 1;

		switch (colorMode)
		{
		case 1: // Red
			red = 255;
			green = 0;
			blue = 0;
			break;
		case 2: // Green
			red = 0;
			green = 255;
			blue = 0;
			break;
		case 3: //Blue
			red = 0;
			green = 0;
			blue = 255;
			break;
		case 4: //Purple
			red = 50;
			green = 0;
			blue = 255;
			break;
		case 5: //Pink
			red = 255;
			green = 0;
			blue = 255;
			break;
		case 6: //Orange
			red = 255;
			green = 100;
			blue = 0;
			break;
		case 7: //Yellow
			red = 255;
			green = 255;
			blue = 0;
			break;
		case 8: //White
			red = 255;
			green = 255;
			blue = 255;
			colorMode = 0;
			break;
		}
		turnOnLights(red, green, blue); //rgb
		delay(300);
}