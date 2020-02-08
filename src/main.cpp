#include <main.h>

std::string raw_data;

void setup() {
    Serial.begin(115200);
	InitializeLEDPanel();
	InitializeBluetooth("PixelProjectDemo");
}

void loop() { 
    if(isConnected) {
        std::string msg = recv();
        if(msg != raw_data) {
            raw_data = msg;
            for (int i = 0; i < raw_data.length(); i++) {
                Serial.print(raw_data[i]);
            }
        }
    }
    delay(DELAY_TIME * 100);
    // if(isImage) {
    //     setImage(parseImg(raw_data));
    // }
    // else if(isAnimation) {
    //     setAnimation(parseAni(raw_data));
    // }
}