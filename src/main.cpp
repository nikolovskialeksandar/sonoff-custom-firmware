#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>
#include <config.h>

const char WIFI_SSID[] =  SSID;
const char WIFI_PASSWORD[]  = PASSWORD;
const char FIREBASE_HOST[]  = FIREBASE_PROJECT_ID;
const char FIREBASE_AUTH[]  = FIREBASE_DATABASE_SECRET;

int LED_PIN = 13;
int RELAY_PIN = 12;
int BTN_PIN = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BTN_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  bool relayState = Firebase.getBool("sonoff/sonoffSwitch");
  Serial.println(relayState);
  if(relayState == true) {
    digitalWrite(RELAY_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
  }
  else {
    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }
}
