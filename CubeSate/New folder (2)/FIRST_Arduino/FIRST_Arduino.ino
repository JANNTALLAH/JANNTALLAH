#include <Wire.h>

//BMP
#include <BMP180_Sensor.h>
BMP180_Sensor bmp;

//DHT
#include <DHT11_Sensor.h>
DHT11_Sensor dht;

//GPS
#include "GPS_Sensor.h"
GPS gps;

//MPU 
#include <MPU6050_Sensor.h>
MPU6050_Sensor mpu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  bmp.GET_DATA_FROM_REGISTERS();
  Serial.print('*'); 
  
  //GPS
  gps.Run();

  //MPU6050
  mpu.start_communication();
  
}

void loop() {

//DHT 
dht.calculate_parameters();
Serial.print(';');

//BMP
bmp.calculate_parameters();
Serial.print(';');

//MPU
mpu.calculate_parameters();
Serial.print(';');

}
