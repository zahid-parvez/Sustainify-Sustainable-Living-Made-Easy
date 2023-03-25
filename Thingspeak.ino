#include <ThingSpeak.h>
#include "constants.h"

WiFiClient  client;

void setup_thingspeak()
{
  ThingSpeak.begin(client);
}

void publish_thingspeak(unsigned long epochTime, float sensor_value)
{
  ThingSpeak.setField(1, sensor_value);
  ThingSpeak.setCreatedAt(String(epochTime));
  int x = ThingSpeak.writeFields(channel, writekey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
}
