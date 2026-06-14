/*
 Usar una esp32 como emisor BLE
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

const char* UUID = "2d214dcf-bc32-45bc-b825-6f7f8e6566f8";
const uint16_t MAJOR = 1;
const uint16_t MINOR = 1;
const int led = 16;

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando ESP32 con BLE...");

    pinMode(led, OUTPUT);
    digitalWrite(led, HIGH);

    // Renombrar dispositivo BLE (cambiarlo por equipo)
    BLEDevice::init("ESP32_BLE");

    // Construir payload iBeacon (estructura para Apple)

    // Estructura:
    // Apple ID (2) + iBeacon type (2) + UUID (16) + Major (2) + Minor (2) +
    // TX Power (1)
    uint8_t payload[25];

    // Apple Manufacturer ID (0x004C) - Little Endian
    payload[0] = 0x4C;
    payload[1] = 0x00;

    // iBeacon type (0x0215)
    payload[2] = 0x02;
    payload[3] = 0x15;

    // UUID (16 bytes)
    String uuidStr = UUID;
    uuidStr.replace("-", "");
    for(int i = 0; i < 16; i++) {
        String byteStr = uuidStr.substring(i*2, i*2+2);
        payload[4 + i] = (uint8_t) strtol(byteStr.c_str(), NULL, 16);
    }

    // Major (2 bytes) - Big Endian
    payload[20] = (MAJOR >> 8) & 0xFF;
    payload[21] = MAJOR & 0xFF;

    // Minor (2 bytes) - Big Endian
    payload[22] = (MINOR >> 8) & 0xFF;
    payload[23] = MINOR & 0xFF;

    // TX Power (RSSI a 1 metro)
    payload[24] = -59;

    // Esta línea solo funciona en librerías más recientes que la 3.0.0
    String payloadString = "";
    for(int i = 0; i < 25; i++) {
        payloadString += (char)payload[i];
    }

    // Configurar advertising con los datos
    BLEAdvertisementData advData;
    advData.setFlags(0x04);
    advData.setManufacturerData(payloadString);

    // Iniciar advertising
    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->setAdvertisementData(advData);
    pAdvertising->start();

    Serial.println("BLE activo");
    Serial.print("   UUID: ");
    Serial.println(UUID);
    Serial.print("   Major: ");
    Serial.println(MAJOR);
    Serial.print("   Minor: ");
    Serial.println(MINOR);
    Serial.println("\n  Escanear con nRF Connect o LightBlue");
}

void loop() {
    static unsigned long lastBlink = 0;
    if (millis() - lastBlink > 2000) {
        lastBlink = millis();
        digitalWrite(led, !digitalRead(led));
        Serial.print(".");
    }
    delay(100);
}
