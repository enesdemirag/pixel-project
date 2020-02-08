/* ******************* LED Settings ****************** */
#define LED_PIN                     14                  // SPI interface pin
#define DEFAULT_BRIGHTNESS_LEVEL    100                 // Default brightness level of the Panel
#define CHIP_TYPE                   WS2812B             // Model of the chip inside the Panel
#define MATRIX_WIDTH                16                  // Width of the Panel
#define MATRIX_HEIGHT               16                  // Height of the Panel      
#define NUM_LEDS                    256                 // Number of LEDs in the Panel
#define DELAY_TIME                  10                  // Period of the loop function

/* ******************* Bluetooth Settings ******************* */
#define SERVICE_UUID                "0769ef76-b358-4b20-9d85-c78ca50fb085"
#define CHARACTERISTIC_UUID_RX      "2d704545-2eb7-451e-95bd-91ea6f0427b7"
#define CHARACTERISTIC_UUID_TX      "2d704545-2eb7-451e-95bd-91ea6f0427b7"