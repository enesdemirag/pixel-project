#include <stdlib.h>
#include <params.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// Definitions
BLECharacteristic *pCharacteristic;
bool isConnected = false;
bool isAnimation = false;
bool isImage = false;
std::string msg = "";
std::string recv();

// Classes
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        isConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
        isConnected = false;
    };
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string rx_data = pCharacteristic->getValue();
        // Message received !
        msg = rx_data;
        if(msg.find("animation") != -1) {
            isImage = false;
            isAnimation = true;
        }
        else if(msg.find("image") != -1) {
            isAnimation = false;
            isImage = true;
        }
    };
};

std::string recv() {
    return msg;
}