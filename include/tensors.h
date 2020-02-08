#include <Arduino.h>
#include <params.h>

class Pixel {
    public:
        byte x;
        byte y;
        // byte color[3];
        byte r;
        byte g;
        byte b;
};

class Image {
    public:
        // std::array<std::array<std::array<byte, 3>, MATRIX_WIDTH>, MATRIX_HEIGHT> data;
        byte data[16][16][3];
};

class Animation {
    public:
        // Image *data;
        Image data[];
};