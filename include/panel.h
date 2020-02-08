#include <FastLED.h>
#include <params.h>

CRGB panel[NUM_LEDS]; // Array of LEDs

/* Functions using 3D byte array 

void setPixel(byte x, byte y, byte r, byte g, byte b) {
    byte pixel = matrix2index(x, y);
    panel[pixel].setRGB(r, g, b);
}

void setImage(byte image[MATRIX_WIDTH][MATRIX_HEIGHT][3]) {
    for(byte x = 0; x < MATRIX_WIDTH; x++) {
        for(byte y = 0; y < MATRIX_HEIGHT; y++) {
            byte pixel = matrix2index(x, y);
            panel[pixel].setRGB(image[x][y][0], image[x][y][1], image[x][y][2]);
        }
    }
}
*/