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
    pServer->setCallbacks(new ServerCallbacks());
    // pServer->setCallbacks(new MyServerCallbacks());
    // Create the BLE Service
    BLEService *pService = pServer->createService(SERVICE_UUID);
    // Create a BLE Characteristic
    characteristicTX = pService->createCharacteristic(
                    CHARACTERISTIC_UUID_TX,
                    BLECharacteristic::PROPERTY_NOTIFY
                    );
    characteristicTX->addDescriptor(new BLE2902());
    BLECharacteristic *characteristic = pService->createCharacteristic(
                                        CHARACTERISTIC_UUID_RX,
                                        BLECharacteristic::PROPERTY_WRITE
                                        );
    characteristic->setCallbacks(new CharacteristicCallbacks());

    // BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    //                                    SERVICE_UUID,
    //                                    BLECharacteristic::PROPERTY_READ |
    //                                    BLECharacteristic::PROPERTY_WRITE
    //                                  );
    // // pCharacteristic = pService->createCharacteristic(
    //                   CHARACTERISTIC_UUID_RX,
    //                   BLECharacteristic::PROPERTY_READ
    //                   );
                      
    // pCharacteristic->addDescriptor(new BLE2902());

    // BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    //                                      CHARACTERISTIC_UUID_RX,
    //                                      BLECharacteristic::PROPERTY_READ
    //                                      );

    // pCharacteristic->setCallbacks(new MyCallbacks());

    // Start the service
    pService->start();
    // BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    // pAdvertising->addServiceUUID(SERVICE_UUID);
    // pAdvertising->setScanResponse(true);
    // pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
    // pAdvertising->setMinPreferred(0x12);
    // BLEDevice::startAdvertising();
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
    for(int i = 0; i < NUM_LEDS; i++) {
        panel[i].setRGB(r, g, b);
        FastLED.show();
        delay(DELAY_TIME);
    }
}

/* Crazy Part Begin */
static uint16_t x = random16();
static uint16_t y = random16();
static uint16_t z = random16();
uint16_t speed = 20;
uint16_t scale = 311;
uint8_t noise[16][16];

uint16_t XY( uint8_t x, uint8_t y) {
    uint16_t i;
    if(y & 0x01) {
        uint8_t reverseX = (16 - 1) - x;
        i = (y * 16) + reverseX;
    }
    else {
        i = (y * 16) + x;
    }
    return i;
}

void fillnoise8() {
    for(int i = 0; i < 16; i++) {
        int ioffset = 311 * i;
        for(int j = 0; j < 16; j++) {
        int joffset = 311 * j;
        noise[i][j] = inoise8(x + ioffset,y + joffset,z);
        }
    }
    z += speed;
}

void goCrazy() {
    for(int i = 0; i < 1000; i++) {
        static uint8_t ihue=0;
        fillnoise8();
        for(int i = 0; i < 16; i++) {
            for(int j = 0; j < 16; j++) {
                panel[XY(i,j)] = CHSV(noise[j][i],255,noise[i][j]);
            }
        }
        ihue+=1;
        LEDS.show();
    }
    LEDS.clear();
}
/* Crazy Part End */

/* Fire Part Begin */
void Fire() {
    for(int i = 0; i < 1000; i++) {
        static byte heat[NUM_LEDS];
        for( int i = 0; i < NUM_LEDS; i++) {
            heat[i] = qsub8( heat[i],  random8(0, ((55 * 10) / NUM_LEDS) + 2));
        }
        for( int k= NUM_LEDS - 1; k >= 2; k--) {
            heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
        }
        if( random8() < 120 ) {
            int y = random8(7);
            heat[y] = qadd8( heat[y], random8(160,255) );
        }
        for( int j = 0; j < NUM_LEDS; j++) {
            CRGB color = HeatColor( heat[j]);
            int pixelnumber;
            pixelnumber = j;
            panel[pixelnumber] = color;
        }
        FastLED.show();
        FastLED.delay(DELAY_TIME);
    }
}
/* Fire Part End */
