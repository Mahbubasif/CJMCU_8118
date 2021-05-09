#include <Wire.h>
#include <ClosedCube_HDC1080.h>
#include <Adafruit_CCS811.h>

Adafruit_CCS811 ccs;
ClosedCube_HDC1080 hdc1080;

void setup() {
Serial.begin(9600);
hdc1080.begin(0x40);
Serial.println("Sensor test");
if(!ccs.begin()){
Serial.println("Failed to start sensors! Please check your wiring.");
while(1);
}
//calibrate temperature sensor
while(!ccs.available());
float ccstemp = ccs.calculateTemperature();
ccs.setTempOffset(ccstemp - 25.0);
}

void loop() {
  if(ccs.available()){
  float ccstemp = ccs.calculateTemperature();
  float hdctemp = hdc1080.readTemperature();
  float temp = (ccstemp+hdctemp)/2; //mean value of temperature
  if(!ccs.readData()){
    Serial.print("Humidity=");
    Serial.print(hdc1080.readHumidity()); //prints hdc1080 humidity
    Serial.println("%");
    Serial.print("CO2: "); 
    Serial.print(ccs.geteCO2());//prints ccs811 Co2
    Serial.print("ppm, TVOC: ");
    Serial.print(ccs.getTVOC());
    Serial.println("ppb");
    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.println("   ");
}
else{
Serial.println("ERROR!");
while(1);
}
}
delay(1000);
}
 
