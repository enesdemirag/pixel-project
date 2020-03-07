#include <main.h>

std::string raw_data;

void setup() {
    Serial.begin(115200);
	InitializeLEDPanel();
	InitializeBluetooth("Pixel-Project");
}

void loop() {
    if(isConnected) {
        // characteristicTX->setValue("Hello World");
        // characteristicTX->notify();
        std::string msg = recv();
        if(msg != raw_data) {
            raw_data = msg;
            for (int i = 0; raw_data[i] != '\0'; i++) {
                Serial.print(raw_data[i]);
            }
            if(raw_data[0] == '1') {
                blink(255, 255, 255);
                blink(0, 0, 0);
            }
            else if(raw_data[0] == '2') {
                goCrazy();
                FastLED.clear();
                FastLED.show();
            }
            else if(raw_data[0] == '3') {
                Fire();
                FastLED.clear();
                FastLED.show();
            }
            else if(raw_data[0] == 'r') {
                fill_solid(panel, NUM_LEDS, CRGB::Red);
                FastLED.show();
            }
            else if(raw_data[0] == 'g') {
                fill_solid(panel, NUM_LEDS, CRGB::Green);
                FastLED.show();
            }
            else if(raw_data[0] == 'b') {
                fill_solid(panel, NUM_LEDS, CRGB::Blue);
                FastLED.show();
            }
            else if(raw_data[0] == '0') {
                FastLED.clear();
                FastLED.show();
            }
        }
    }
    else {
        Serial.print('NO');
    }
    // if(isImage) {
    //     setImage(parseImg(raw_data));
    // }
    // else if(isAnimation) {
    //     setAnimation(parseAni(raw_data));
    // }
    // setImage(parseImg(raw_data));
    delay(DELAY_TIME * 100);
}