/*
 E *SP32 como emisor BLE
 */

#include <BLEBeacon.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

// Configuración
#define UUID "12345678-1234-5678-1234-56789abcdef0"
#define MAJOR 1
#define MINOR 1

// Pines (opcional para LED indicador)
const int led = 4;

void setup()
{
    Serial.begin(115200);
    Serial.println("Iniciando ESP32 como emisor BLE...");

    // Opcional: configurar LED indicador
    pinMode(led, OUTPUT);
    digitalWrite(led, HIGH); // LED encendido mientras anuncia

    // Inicializar dispositivo BLE
    BLEDevice::init("MiEmisorESP32"); // Nombre visible en escaneos

    // Crear el beacon
    BLEBeacon oBeacon;
    oBeacon.setManufacturerId(0x004C); // Apple Inc. (para iBeacon)
    oBeacon.setProximityUUID(BLEUUID(UUID));
    oBeacon.setMajor(MAJOR);
    oBeacon.setMinor(MINOR);
    oBeacon.setSignalPower(-59); // Potencia de la señal a 1 metro

    // Configurar advertising con los datos del beacon
    BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
    BLEAdvertisementData oAdvertisementData = BLEAdvertisementData();
    oAdvertisementData.setFlags(0x04); // BR_EDR not supported

    // Establecer los datos del beacon
    std::string strPayload = std::string((char*)oBeacon.getData(), sizeof(oBeacon.getData()));
    oAdvertisementData.setManufacturerData(strPayload);

    pAdvertising->setAdvertisementData(oAdvertisementData);

    // Iniciar advertising continuo
    pAdvertising->start();

    Serial.println("Beacon BLE activo. UUID: " + String(UUID));
    Serial.println("Usa nRF Connect o LightBlue para detectarlo");
}

void loop()
{
    // El beacon se anuncia automáticamente
    // Opcional: parpadeo del LED como indicador de actividad
    digitalWrite(led, !digitalRead(led));
    delay(1000);
}
