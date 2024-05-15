##NOTE : I HAVE USED TWO ESP 32 ONE FOR DS18B20 AND ANOTHER FOR REST OF THE THE SENSORS. 

##THIS CODE IS DS18B20

#include <HTTPClient.h>
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6Uu6v4lVP"
#define BLYNK_TEMPLATE_NAME "temp"
#define BLYNK_AUTH_TOKEN "Kq0uqLq49WxfXcknBTCfP3UywJCeOahD"

#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <ThingSpeak.h> // Include ThingSpeak library

#define DS18B20 4    // Connect to GPIO2 pin
OneWire ourWire(DS18B20);
DallasTemperature sensor(&ourWire);

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "*****";  // Enter your WiFi name
char pass[] = "*****";  // Enter your WiFi password

#define THINGSPEAK_CHANNEL_ID 2473605
#define THINGSPEAK_API_KEY "9AFVTGX7AJ13YB0A"

BlynkTimer timer;

void sendToThingSpeak(float tempC, float tempF) {
  WiFiClient client;
  HTTPClient http;

  String url = "http://api.thingspeak.com/update";
  url += "?api_key=";
  url += THINGSPEAK_API_KEY;
  url += "&field2=";
  url += String(tempC);
  url += "&field3=";
  url += String(tempF);

  Serial.print("Sending data to ThingSpeak: ");
  Serial.println(url);

  http.begin(client, url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.printf("HTTP GET request sent, response code: %d\n", httpCode);
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.printf("Error sending HTTP GET request, error code: %d\n", httpCode);
  }

  http.end();
}

void sendSensor() {
  // Request temperature to all devices on the data line
  sensor.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // We can connect more than one IC on the same data wire. 0 refers to the first IC on the wire
  Serial.print(sensor.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensor.getTempFByIndex(0));
  float tempC = sensor.getTempCByIndex(0);
  float tempF = sensor.getTempFByIndex(0);
  
  // Send data to Blynk
  Blynk.virtualWrite(V0, tempC);
  Blynk.virtualWrite(V1, tempF);
  
  // Send data to ThingSpeak
  sendToThingSpeak(tempC, tempF);
}

void setup() {
  Serial.begin(9600);
  sensor.begin();
  
  Blynk.begin(auth, ssid, pass);
  
  timer.setInterval(100L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}


THIS CODE IS FOR REST OF THE THE SENSORS. 

#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6Uu6v4lVP"
#define BLYNK_TEMPLATE_NAME "temp"
#define BLYNK_AUTH_TOKEN "Kq0uqLq49WxfXcknBTCfP3UywJCeOahD"

#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define trig 5
#define echo 4
#define PIR_SENSOR  21
#define MQ_PIN 34
#define DIGITAL_PIN 2
#define BUZZER_PIN 18   


char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "*****";
char pass[] = "*****";

BlynkTimer timer;
unsigned long lastConnectionTime = 0;
const char* thingSpeakAddress = "api.thingspeak.com";
const unsigned long postingInterval = 10 * 1000; // Interval to post data to ThingSpeak (in milliseconds)

void waterLevel() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long t = pulseIn(echo, HIGH);
  long cm = t / 29 / 2;
  Serial.println(cm);
  double level = 16 - cm;  // Assuming tankDepth is 16
  if (level > 0) {
    long percentage = ((level / 16)) * 100;
    Blynk.virtualWrite(V2, percentage);
  } else {
    Blynk.virtualWrite(V2, 0);
  }

  // Send data to ThingSpeak
  if (millis() - lastConnectionTime > postingInterval) {
    sendToThingSpeak(cm);
    lastConnectionTime = millis();
  }
}

void notifyOnTheft() {
  int isTheftAlert = digitalRead(PIR_SENSOR);
  Serial.println(isTheftAlert);
  if (isTheftAlert == 1) {
    Serial.println("Theft Alert in Home");
    Blynk.logEvent("theft_alert", "Theft Alert in Home");
  }
}

void smokeDetection() {
  float airQuality = analogRead(MQ_PIN);

  Serial.print("Air Quality: ");
  Serial.println(airQuality);

  if (airQuality > 500) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void setup() {
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(PIR_SENSOR, INPUT);
  pinMode(DIGITAL_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.begin(115200);
  delay(100);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(10L, waterLevel);  // Interval for ultrasonic sensor
  timer.setInterval(5000L, notifyOnTheft);  // Interval for motion sensor
  timer.setInterval(2000L, smokeDetection); // Interval for smoke sensor
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendToThingSpeak(long cm) {
  WiFiClient client;
  HTTPClient http;
  
  String url = "http://";
  url += thingSpeakAddress;
  url += "/update";
  url += "?api_key=";
  url += "9AFVTGX7AJ13YB0A";
  url += "&field1=";
  url += String(cm);


  Serial.print("Sending data to ThingSpeak: ");
  Serial.println(url);
  
  http.begin(client, url);
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.printf("HTTP GET request sent, response code: %d\n", httpCode);
    String payload = http.getString();
    Serial.println(payload);
  } else {
    Serial.printf("Error sending HTTP GET request, error code: %d\n", httpCode);
  }

  http.end();
}
