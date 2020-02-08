#include <FastLED.h>

CRGB panel[NUM_LEDS]; // Array of LEDs

// Function Declarations
byte matrix2index(byte x, byte y);
// void setPixel(byte x, byte y, byte r, byte g, byte b);
// void setImage(byte image[16][16][3]);
void setPixel(Pixel p);
void setImage(Image img);


// Functions
bool InitializeLEDPanel() {
	LEDS.addLeds<CHIP_TYPE, DATA_PIN, RGB>(panel, NUM_LEDS);
	LEDS.setBrightness(DEFAULT_BRIGHTNESS_LEVEL);
}

byte matrix2index(byte x, byte y) { // Serialize the matrix
    if(y % 2 == 0) {
        return (MATRIX_WIDTH * y) + x;
    }
    else {
        return (MATRIX_WIDTH * y) + (MATRIX_WIDTH - x);
    }
}

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

// Functions using custom Image class
 
void setPixel(Pixel p) {
    byte pixel = matrix2index(p.x, p.y);
    panel[pixel].setRGB(p.r, p.g, p.b);
    // panel[pixel].setRGB(p.color[0], p.color[1], p.color[1]);
}

void setImage(Image img) {
    for(byte x = 0; x < MATRIX_WIDTH; x++) {
        for(byte y = 0; y < MATRIX_HEIGHT; y++) {
            byte pixel = matrix2index(x, y);
            panel[pixel].setRGB(img.data[x][y][0], img.data[x][y][1], img.data[x][y][2]);
        }
    }
}