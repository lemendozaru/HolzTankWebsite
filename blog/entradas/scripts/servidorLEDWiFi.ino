/*
  Servidor web en ESP32 conectado a una red WiFi existente.
  Permite controlar el LED mediante peticiones HTTP.

  Pasos:
  1. Conectar la ESP32 a la red WiFi domestica
  2. Averiguar la IP que el router le asigna a la ESP32 (por el monitor serie)
  3. En cualquier dispositivo de la misma red, abrir el navegador y acceder a:
     - http://IP_ESP32/H  -> Enciende el LED
     - http://IP_ESP32/L  -> Apaga el LED
*/

#include <WiFi.h>
#include <WiFiClient.h>

// === CONFIGURACION DE LA RED EXISTENTE ===
// Cambiar estos valores por los de la red WiFi domestica
const char *ssid = "ranchitomiado";      // Ejemplo: "MiFibra-2F4G"
const char *password = "Xochiquetzalli9424";   // Ejemplo: "ClaveWifi123"

// Puerto del servidor web (80 es el estandar HTTP)
WiFiServer server(80);

// Declarando el led
const int led = 16;

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("=== SERVIDOR ESP32 ===");
  
  // Intentar conectar a la red WiFi existente
  Serial.print("Conectando a la red WiFi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  // Esperar hasta 10 segundos para conectarse
  int intentos = 0;
  while (WiFi.status() != WL_CONNECTED && intentos < 20) {
    delay(500);
    Serial.print(".");
    intentos++;
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.println("Conectado a la red WiFi exitosamente");
    Serial.print("Direccion IP asignada por el router: ");
    Serial.println(WiFi.localIP());
    Serial.print("Puerta de enlace (router): ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Intensidad de señal (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    
    server.begin();
    Serial.println("Servidor HTTP iniciado en puerto 80");
    Serial.println("------------------------------------");
    Serial.println("Para controlar el LED, acceder a:");
    Serial.print("   - http://");
    Serial.print(WiFi.localIP());
    Serial.println("/H  -> ENCENDER");
    Serial.print("   - http://");
    Serial.print(WiFi.localIP());
    Serial.println("/L  -> APAGAR");
    Serial.println("------------------------------------");
  } else {
    Serial.println();
    Serial.println("No se pudo conectar a la red WiFi");
    Serial.println("Verifica que:");
    Serial.println("   - El nombre de la red (SSID) sea correcto");
    Serial.println("   - La contrasena sea correcta");
    Serial.println("   - El router este encendido y dentro del alcance");
  }
}

void loop() {
  // Si la conexion WiFi se pierde, intentar reconectar automaticamente
  if (WiFi.status() != WL_CONNECTED) {
    static unsigned long ultimoIntento = 0;
    if (millis() - ultimoIntento > 10000) {  // Intentar cada 10 segundos
      Serial.println("Conexion WiFi perdida. Reconectando...");
      WiFi.reconnect();
      ultimoIntento = millis();
    }
    return;
  }
  
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("Nuevo cliente conectado");
    String currentLine = "";
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);  // Mostrar la peticion HTTP (opcional)
        
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Enviar respuesta HTTP
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            
            // Pagina web de control
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<title>Control LED ESP32</title>");
            client.println("<meta charset='UTF-8'>");
            client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
            client.println("<style>");
            client.println("body { font-family: Arial; text-align: center; margin-top: 50px; background: #1a1a2e; color: white; }");
            client.println("button { padding: 15px 30px; margin: 10px; font-size: 18px; cursor: pointer; border: none; border-radius: 8px; }");
            client.println(".btn-on { background-color: #4CAF50; color: white; }");
            client.println(".btn-off { background-color: #f44336; color: white; }");
            client.println(".status { font-size: 20px; margin: 20px; }");
            client.println("</style>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1>Control de LED ESP32</h1>");
            client.println("<div class='status'>");
            client.print("<p>Conectado a la red: <strong>");
            client.print(ssid);
            client.println("</strong></p>");
            client.println("</div>");
            client.println("<button class='btn-on' onclick='location.href=\"/H\"'>ENCENDER</button>");
            client.println("<button class='btn-off' onclick='location.href=\"/L\"'>APAGAR</button>");
            client.println("<p><small>Servidor ESP32</small></p>");
            client.println("</body>");
            client.println("</html>");
            
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        
        // Procesar comandos HTTP
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(led, HIGH);
          Serial.println("LED ENCENDIDO");
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(led, LOW);
          Serial.println("LED APAGADO");
        }
      }
    }
    
    client.stop();
    Serial.println("Cliente desconectado");
  }
  
  delay(10);
}