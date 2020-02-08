#include <Arduino.h>
#include <params.h>
#include <tensors.h>
#include <panel.h>
#include <bluetooth.h>

// Bluetooth Declarations
bool InitializeBluetooth(std::string device_name);
Image getImage();
Animation getAnimation();
void blink(byte r, byte g, byte b);

// LED Panel Declarations
bool InitializeLEDPanel();
byte matrix2index(byte x, byte y);
void setPixel(Pixel p);
void setImage(Image img);

bool InitializeBluetooth(std::string device_name) {
    // Create the BLE Device
    BLEDevice::init(device_name);
    // Create the BLE Server
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());
    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);
    // Create a BLE Characteristic
    pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID_TX,
                      BLECharacteristic::PROPERTY_NOTIFY
                      );
                      
    pCharacteristic->addDescriptor(new BLE2902());

    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_RX,
                                         BLECharacteristic::PROPERTY_WRITE
                                         );

    pCharacteristic->setCallbacks(new MyCallbacks());

    // Start the service
    pService->start();
    // Start advertising
    pServer->getAdvertising()->start();
    return true;
}

Image parseImg(std::string raw) {
    Image parsed_img;
    return parsed_img;
}

Animation parseAni(std::string raw) {
    Animation parsed_ani;
    return parsed_ani;
}

bool InitializeLEDPanel() {
    FastLED.addLeds<CHIP_TYPE, LED_PIN, RGB>(panel, NUM_LEDS);
    FastLED.setBrightness(DEFAULT_BRIGHTNESS_LEVEL);
    return true;
}

byte matrix2index(byte x, byte y) { // Serialize the matrix
    if(y % 2 == 0) {
        return (MATRIX_WIDTH * y) + x;
    }
    else {
        return (MATRIX_WIDTH * y) + (MATRIX_WIDTH - x);
    }
}

void setPixel(Pixel p) {
    byte pixel = matrix2index(p.x, p.y);
    panel[pixel].setRGB(p.r, p.g, p.b);
    // panel[pixel].setRGB(p.color[0], p.color[1], p.color[1]);
    FastLED.show();
}

// TODO: Remove delays from here and use Timer to simultaniously recv() while showing an Animation
// https://github.com/espressif/arduino-esp32/blob/master/libraries/ESP32/examples/Timer/RepeatTimer/RepeatTimer.ino
// TODO: Instead of two different functions, reduce to one (Image is just a Animation with 1 frame)

void setImage(Image img) {
    for(byte x = 0; x < MATRIX_WIDTH; x++) {
        for(byte y = 0; y < MATRIX_HEIGHT; y++) {
            byte pixel = matrix2index(x, y);
            panel[pixel].setRGB(img.data[x][y][0], img.data[x][y][1], img.data[x][y][2]);
        }
    }
    FastLED.show();
    delay(DELAY_TIME);
}

void setAnimation(Animation ani) {
    for(byte frame = 0; frame < ani.len; frame++) {
        for(byte x = 0; x < MATRIX_WIDTH; x++) {
            for(byte y = 0; y < MATRIX_HEIGHT; y++) {
                byte pixel = matrix2index(x, y);
                panel[pixel].setRGB(ani.data[frame].data[x][y][0],
                                    ani.data[frame].data[x][y][1],
                                    ani.data[frame].data[x][y][2]);
            }
        }
        FastLED.show();
        delay(DELAY_TIME);
    }
}

void blink(byte r, byte g, byte b) {
    for(byte i = 0; i < NUM_LEDS; i++) {
        panel[i].setRGB(r, g, b);
        FastLED.show();
        delay(DELAY_TIME);
    }
}