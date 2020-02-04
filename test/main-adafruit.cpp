#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN 14                           // Pin on the ESP32 is connected to the NeoPixels
#define NUMPIXELS 256                   // How many NeoPixels LEDs are attached to the ESP32
#define BRIGHTNESS 20                   // We define brightness of NeoPixel LEDs

// LED Matrix
Adafruit_NeoPixel matrix = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    matrix.setBrightness(BRIGHTNESS);   // Set NeoPixel configuration 
    matrix.begin();                     // Start NeoPixel library with all LEDs off
    matrix.show();                      // Show settings of LEDs in NeoPixel array
}

void colorWipe(uint32_t c, uint8_t wait) {
    for(uint16_t i = 0; i < matrix.numPixels(); i++) {
        matrix.setPixelColor(i, c);
        matrix.show();
        delay(wait);
    }
}

void loop() {
    colorWipe(matrix.Color(255, 0, 0), 40);         // Red
    colorWipe(matrix.Color(0, 255, 0), 40);         // Green
    colorWipe(matrix.Color(0, 0, 255), 40);         // Blue
    colorWipe(matrix.Color(255, 255, 255), 40);     // White
    colorWipe(matrix.Color(0, 0, 0), 40);           // Black
}