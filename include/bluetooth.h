#include <stdlib.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// Function Declarations
bool InitializeBluetooth();
Image getImage();
Animation getAnimation();

// Functions
bool InitializeBluetooth(std::string device_name) {
    BLEDevice::init(device_name);
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                         );

    pCharacteristic->setValue("characteristic");
    pService->start();
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    // Functions that help with iPhone connections issue
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    return true;
}

Image getImage() {
    // TODO: Implement bluetooth
    Image dummy;
    return dummy; 
}

Animation getAnimation() {
    // TODO: Implement bluetooth
    Animation dummy;
    return dummy;
}