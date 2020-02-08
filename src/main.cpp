#include <Arduino.h>
#include <FastLED.h>
#include <params.h>
#include <image.h>
#include <panel.h>
#include <bluetooth.h>

void setup() { 
	LEDS.addLeds<CHIP_TYPE, DATA_PIN, RGB>(panel, NUM_LEDS);
	LEDS.setBrightness(DEFAULT_BRIGHTNESS_LEVEL);
}

void loop() { 
	setImage(getImage());
	LEDS.show(); 
}