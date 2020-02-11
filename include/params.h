/* ******************* LED Settings ****************** */
#define LED_PIN                     14                  // SPI interface pin
#define DEFAULT_BRIGHTNESS_LEVEL    20                  // Default brightness level of the Panel
#define CHIP_TYPE                   WS2812B             // Model of the chip inside the Panel
#define MATRIX_WIDTH                16                  // Width of the Panel
#define MATRIX_HEIGHT               16                  // Height of the Panel      
#define NUM_LEDS                    256                 // Number of LEDs in the Panel
#define DELAY_TIME                  10                  // Period of the loop function

/* ******************* Bluetooth Settings ******************* */
#define SERVICE_UUID                "c76befcd-2077-4bca-a823-46077378784d"
#define CHARACTERISTIC_UUID_RX      "2a0e8457-0738-412c-b6c3-0c04c2b3372f"
#define CHARACTERISTIC_UUID_TX      "67f25d42-2093-4653-9cd0-773a7e65841c"