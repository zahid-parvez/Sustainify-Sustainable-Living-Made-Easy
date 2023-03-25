#include <WiFi.h>
#include <time.h>
#include <HTTPClient.h>
#include "constants.h"

#define THINGSPEAK  true
#define ONEM2M true

void setup_Thingspeak();
void publish_Thingspeak(unsigned int , float );
void publish_Onem2m(unsigned int , float);

const char * ntpServer = "time.iiit.ac.in";

long int prev_millis = 0;
unsigned long epochTime;
float zeroValue = 0, sensorValue, outputValue;

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime( & timeinfo)) {
    //Serial.println("Failed to obtain time");
    return (0);
  }
  time( & now);
  return now;
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(MAIN_SSID, MAIN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println(WiFi.localIP());
  configTime(0, 0, ntpServer);
  zeroValue = setup_sensor();
  setup_thingspeak();
  
}

void loop() {
 float sensor_value = read_sensor(zeroValue);
 bool nw_status = WiFi.status()== WL_CONNECTED? true: false;
 if ((millis() - prev_millis) >= INTERVAL){
 epochTime = getTime();
 publish_Onem2m(epochTime, sensor_value); 
 publish_thingspeak(epochTime, sensor_value); 
 prev_millis = millis();
 }
 
}
