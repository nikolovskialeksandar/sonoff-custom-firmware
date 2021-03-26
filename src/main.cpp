#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>
#include <config.h>

const char WIFI_SSID[] =  SSID;
const char WIFI_PASSWORD[]  = PASSWORD;
const char URL[] = SERVER_URL;
const int PORT = SERVER_PORT;

WebSocketsClient webSocket;

int LED_PIN = 13;
int RELAY_PIN = 12;
int BTN_PIN = 0;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
	switch(type) {
		case WStype_DISCONNECTED:
			Serial.printf("[WSc] Disconnected!\n");
			break;
		case WStype_CONNECTED: 
      Serial.printf("[WSc] Connected to url: %s\n", payload);
			break;
		case WStype_TEXT:
      // Change state when WebSocket message is received (using led pin for testing purposes)
      String message = (char*)payload;
      if (message == String("true")) {
        digitalWrite(LED_PIN, LOW);
      } else if (message == String("false")) {
        digitalWrite(LED_PIN, HIGH);
      }
      break;
  }
}

void setup() {  
	Serial.begin(115200);

  // Set pins, initalize relay state
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);
  digitalWrite(RELAY_PIN, LOW);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  // Connect to WebSocket server, handle WebSocket events
  webSocket.begin(URL, PORT);
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
}
