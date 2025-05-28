#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// WiFi Access Point
const char* ssid = "ASTRO-Control";
const char* password = "12345678";

ESP8266WebServer server(80);

// Página HTML embebida
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>ASTRO Robot</title>
  <style>
    body { font-family: sans-serif; text-align: center; margin-top: 50px; background: #f0f0f0; }
    h1 { color: #333; }
    button {
      font-size: 20px; padding: 15px 30px; margin: 10px;
      background-color: #2196F3; color: white; border: none;
      border-radius: 8px; cursor: pointer;
    }
    button:hover { background-color: #0b7dda; }
  </style>
</head>
<body>
  <h1>Control de Astro</h1>
  <div>
    <button onclick="sendCommand('adelante')">Adelante</button><br>
    <button onclick="sendCommand('izquierda')">Izquierda</button>
    <button onclick="sendCommand('detener')">Detener</button>
    <button onclick="sendCommand('derecha')">Derecha</button><br>
    <button onclick="sendCommand('atras')">Atrás</button>
  </div>

  <h2>Dar la patita</h2>
  <div>
    <button onclick="sendCommand('patita_derecha')">Derecha</button>
    <button onclick="sendCommand('patita_izquierda')">Izquierda</button>
  </div>

  <h2>Mover cabeza</h2>
  <div>
    <button onclick="sendCommand('cabeza_izquierda')">Izquierda</button>
    <button onclick="sendCommand('cabeza_derecha')">Derecha</button>
  </div>

  <script>
    function sendCommand(cmd) {
      fetch("/" + cmd).then(response => {
        console.log("Comando enviado:", cmd);
      });
    }
  </script>
</body>
</html>
)=====";


void setup() {
  Serial.begin(9600);  // Comunicación con el Arduino UNO

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  Serial.println("WiFi listo. Conectate a:");
  Serial.println(WiFi.softAPIP());

  // Servir HTML
  server.on("/", []() {
    server.send_P(200, "text/html", MAIN_page);
  });

  // Comandos que se envían al Arduino por Serial
  server.on("/adelante", []() {
    Serial.println("adelante");
    server.send(200, "text/plain", "OK");
  });

  server.on("/atras", []() {
    Serial.println("atras");
    server.send(200, "text/plain", "OK");
  });

  server.on("/izquierda", []() {
    Serial.println("izquierda");
    server.send(200, "text/plain", "OK");
  });

  server.on("/derecha", []() {
    Serial.println("derecha");
    server.send(200, "text/plain", "OK");
  });

  server.on("/detener", []() {
    Serial.println("detener");
    server.send(200, "text/plain", "OK");
  });

server.on("/patita_derecha", []() {
  Serial.println("patita_derecha");
  server.send(200, "text/plain", "OK");
});

server.on("/patita_izquierda", []() {
  Serial.println("patita_izquierda");
  server.send(200, "text/plain", "OK");
});

server.on("/cabeza_izquierda", []() {
  Serial.println("cabeza_izquierda");
  server.send(200, "text/plain", "OK");
});

server.on("/cabeza_derecha", []() {
  Serial.println("cabeza_derecha");
  server.send(200, "text/plain", "OK");
});

  server.begin();
}

void loop() {
  server.handleClient();
}
