#include <WiFi.h>
#include <WiFiAP.h>

bool led_on = false;
String inputString = "";

const char *ssid = "RED-AP";
const char *password = "PASSWD-AP";

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configurando punto de acceso...");
  
  WiFi.softAP(ssid, password);
  
  IPAddress AP_IP = WiFi.softAPIP();
  Serial.print("Dirección IP del AP: ");
  Serial.println(AP_IP);
  Serial.println();
  Serial.println("Comandos disponibles:");
  Serial.println("  'ip'  - Muestra la IP del AP");
  Serial.println("  'sta' - Muestra número de clientes conectados");
  Serial.println("  'ver' - Muestra configuración actual");
}

void loop() {    
    // Verificar comandos por serial
    while (Serial.available()) {
        char inChar = (char)Serial.read();
        inputString += inChar;
        
        if (inChar == '\n') {
            inputString.trim();  // Eliminar espacios y saltos de línea
            
            if (inputString == "ip") {
                Serial.print("IP del AP: ");
                Serial.println(WiFi.softAPIP());
            }
            else if (inputString == "sta") {
                Serial.print("Clientes conectados: ");
                Serial.println(WiFi.softAPgetStationNum());
            }
            else if (inputString == "ver") {
                Serial.println("=== CONFIGURACIÓN AP ===");
                Serial.print("SSID: ");
                Serial.println(ssid);
                Serial.print("IP: ");
                Serial.println(WiFi.softAPIP());
                Serial.print("MAC: ");
                Serial.println(WiFi.softAPmacAddress());
                Serial.print("Canal: ");
                Serial.println(WiFi.channel());
                Serial.print("Clientes: ");
                Serial.println(WiFi.softAPgetStationNum());
            }
            else if (inputString.length() > 0) {
                Serial.println("Comando no reconocido. Usar: ip, sta, ver");
            }
            
            inputString = "";
        }
    }
    
    // Mostrar cambios en conexiones
    static int last_stations = -1;
    int current_stations = WiFi.softAPgetStationNum();
    
    if (current_stations != last_stations) {
        Serial.print("Conexiones: ");
        Serial.println(current_stations);
        if (current_stations > 0) {
            Serial.println("Usar 'ip' para ver la dirección del AP");
        }
        last_stations = current_stations;
    }
    
    // Parpadeo del LED (menos frecuente para no saturar)
    static unsigned long last_toggle = 0;
    if (millis() - last_toggle > 500) {
        digitalWrite(LED_BUILTIN, led_on ? HIGH : LOW);
        led_on = !led_on;
        last_toggle = millis();
    }
}