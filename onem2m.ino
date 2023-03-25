#include <HTTPClient.h>
#include "constants.h"

long randNumber;
HTTPClient http;
String server;

void publish_Onem2m(unsigned long epochTime, float sensor_value){
  String data;
  if (HTTPS){
    server = "https://" + String() + CSE_IP + ":" + String() + CSE_PORT + String() + OM2M_MN;  
  }
  else{
    server = "http://" + String() + CSE_IP + ":" + String() + CSE_PORT + String() + OM2M_MN;
  }
  

  http.begin(server + String() + OM2M_AE + "/" + OM2M_DATA_CONT + "/");

  http.addHeader("X-M2M-Origin", OM2M_ORGIN);
  http.addHeader("Content-Type", "application/json;ty=4");
  http.addHeader("Content-Length", "100");

  data = "[" + String(epochTime) + ", " + String(sensor_value) +   + "]"; 
  String req_data = String() + "{\"m2m:cin\": {"

    +
    "\"con\": \"" + data + "\","

    +
    "\"lbl\": \"" + "V1.0.0" + "\","

    //+ "\"rn\": \"" + "cin_"+String(i++) + "\","

    +
    "\"cnf\": \"text\""

    +
    "}}";
  int code = http.POST(req_data);
  http.end();
  Serial.println(code);
  prev_millis = millis();
  delay(500);
}
