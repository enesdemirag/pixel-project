#include <Arduino.h>
#include <FastLED.h>
#include <params.h>

CRGB panel[NUM_LEDS]; // Array of LEDs

// Function Definitions
byte matrix2index(byte x, byte y);
void setPixel(byte x, byte y, byte r, byte g, byte b);
void setImage(byte image[16][16][3]);

byte matrix2index(byte x, byte y) {
    if(y % 2 == 0) {
        return (MATRIX_WIDTH * y) + x;
    }
    else {
        return (MATRIX_WIDTH * y) + (MATRIX_WIDTH - x);
    }
}

void setPixel(byte x, byte y, byte r, byte g, byte b) {
    byte pixel = matrix2index(x, y);
    panel[pixel].setRGB(r, g, b);
}

void setImage(byte image[16][16][3]) {
    for(byte x = 0; x < 16; x++) {
        for(byte y = 0; y < 16; y++) {
            byte pixel = matrix2index(x, y);
            panel[pixel].setRGB(image[x][y][0], image[x][y][1], image[x][y][2]);
        }
    }
}