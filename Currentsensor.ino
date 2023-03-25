#define CURRENT_PIN 34
#define SENSITIVITY 0.045

float setup_sensor(){
  pinMode(CURRENT_PIN, INPUT);
  analogReadResolution(12);
  delay(1000);
  zeroValue = 0;
  // Read current sensor when there is no load
  for(int i=0; i<500;i++){
  sensorValue = analogRead(CURRENT_PIN);
  Serial.print("Analog reading:");
  Serial.println(sensorValue);
  zeroValue = (sensorValue *(3.27/4095)) + (zeroValue);
  delay(2);
  }

  zeroValue = zeroValue /500;
  Serial.println("**************************************");
     
  Serial.print("Zero Value when no Load condition =: ");
  Serial.println(zeroValue);
  return zeroValue;
}

float read_sensor(float zeroValue){
  double sumValue = 0.0;
// capturing sensor voltage rms and current

  for(int i=0; i<1000;i++){

  sensorValue = analogRead(CURRENT_PIN);
  outputValue = (sensorValue *(3.27/4095)) - ( zeroValue);

  sumValue = (outputValue * outputValue) + (sumValue);
  delay(2);

  }
  sumValue = (sumValue / 1000);
  sumValue = sqrt(sumValue);
  outputValue = sumValue /SENSITIVITY;

  Serial.print("Processed Sensor Voltage Value in Volts =:   ");
  Serial.println(sumValue);
  Serial.print("Current  Value in Amp =: ");
  Serial.println(outputValue);
  Serial.println("____________________________________");
  return outputValue;
}
