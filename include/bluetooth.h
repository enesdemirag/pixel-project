#include <stdlib.h>
#include <params.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

// Definitions
// BLECharacteristic *pCharacteristic;
BLECharacteristic *characteristicTX;
bool isConnected = false;
bool isAnimation = false;
bool isImage = false;
std::string msg = "";
// uint8_t* recv_byte;
std::string recv();

// Classes
class ServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
        isConnected = true;
        Serial.print('1');
        Serial.print('\0');
        // TODO: Connecting LED Show
    };

    void onDisconnect(BLEServer* pServer) {
        isConnected = false;
        Serial.print('0');
        Serial.print('\0');
    };
};

class CharacteristicCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string rx_data = pCharacteristic->getValue();
        // recv_byte = pCharacteristic->getData();
        if(rx_data.length() > 0) {
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
        }
    };
};

std::string recv() {
    return msg;
}

// uint8_t* recvByte() {
//     return recv_byte;
// }
