/*
 WiFiAccessPoint.ino crea un punto de acceso WiFi y proporciona un servidor web en él.

  Pasos:
  1. Conectarse al punto de acceso "RED-AP"
  2. Apuntar el navegador web a http://IP_ESP32/H para encender el LED o a http://IP_ESP32/L para apagarlo
     O
     Ejecutar TCP raw "GET /H" y "GET /L" en la terminal PuTTY con 192.168.4.1 como dirección IP y 80 como puerto
*/

#include <WiFi.h>
#include <WiFiClient.h>

// Establecer las credenciales deseadas.
const char *ssid = "RED-AP";
const char *password = "PASSWD-AP";

// Establecer el puerto del servidor web a 80
WiFiServer server(80);

// Declarar pin del led
const int led = 16;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Conectando a ");

  // Conectarse a la red WiFi con SSID y contraseña
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  IPAddress myIP = WiFi.localIP();
  Serial.print("Conectado con la dirección IP asignada: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Servidor iniciado en puerto 80");
  Serial.print("Accede desde el navegador en: http://");
  Serial.println(myIP);
}

void loop() {
  WiFiClient client = server.available();   // Escuchar clientes entrantes

  if (client) {                             // Si se recibe un cliente,
    Serial.println("Nuevo Cliente.");       // Imprimir un mensaje en el puerto serie
    String currentLine = "";                // Crear un String para almacenar datos entrantes del cliente
    while (client.connected()) {            // Bucle mientras el cliente esté conectado
      if (client.available()) {             // Si hay bytes para leer del cliente,
        char c = client.read();             // Leer un byte
        Serial.write(c);                    // Imprimirlo en el monitor serie
        if (c == '\n') {                    // Si el byte es un carácter de nueva línea

          // Si la línea actual está vacía, se obtuvieron dos caracteres de nueva línea consecutivos.
          // Ese es el final de la petición HTTP del cliente, por lo que se envía una respuesta:
          if (currentLine.length() == 0) {
            // Las cabeceras HTTP siempre comienzan con un código de respuesta (ej. HTTP/1.1 200 OK)
            // y un tipo de contenido para que el cliente sepa lo que viene, luego una línea en blanco:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // El contenido de la respuesta HTTP sigue a la cabecera:
            client.print("Hacer <a href=\"/H\">clic</a> para encender el LED.<br>");
            client.print("Hacer <a href=\"/L\">clic</a> para apagar el LED.<br>");

            // La respuesta HTTP termina con otra línea en blanco:
            client.println();
            // Salir del bucle while:
            break;
          } else {    // Si se recibió una nueva línea, entonces limpiar currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // Si se recibió cualquier cosa excepto un retorno de carro,
          currentLine += c;      // Añadirlo al final de currentLine
        }

        // Verificar si la petición del cliente fue "GET /H" o "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(led, HIGH);               // GET /H enciende el LED
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(led, LOW);                // GET /L apaga el LED
        }
      }
    }
    // Cerrar la conexión:
    client.stop();
    Serial.println("Cliente desconectado.");
  }
}