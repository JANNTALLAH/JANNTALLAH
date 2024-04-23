#include "GPS_Sensor.h"

//convert1 function:converts Latitude into degrees
double GPS::convert1(char LT[])
{
  for(int i=0; i<=8; i++)
  {
    array1[i]=(LT[i])-'0';
  }
  double x=(array1[0]*10+array1[1]+((array1[2]*10+array1[3]+array1[5]*0.1+array1[6]*0.01+array1[7]*0.001+array1[8]*0.0001)*(1.0/60)));
  return x;
}

//convert2 function:converts Longitude into degrees
double GPS::convert2(char LOT[])
{
  for(int n=0;n<=9;n++)
  {
    array2[n]=(LOT[n])-'0';
  }
  double  y=(array2[0]*100+array2[1]*10+array2[2]+(array2[3]*10+array2[4]+array2[6]*0.1+array2[7]*0.01+array2[8]*0.001+array2[9]*0.0001)*(1.0/60));
  return y;
}

//read function:to read data efficiently
void GPS::print_readings(char arr[],int len)
{
  for(int i=0; i<len; i++)
  {
    Serial.print(arr[i]);
  }
  Serial.print(' ');
}

void GPS::Run()
{
  while(Serial.available()>0)
  {
    if(Serial.read()=='$')
    {
      Serial.readBytesUntil(',',Message_ID,7);
      if(Message_ID[2]=='G' && Message_ID[3]=='G' && Message_ID[4]=='A')
      {
        Serial.readBytesUntil(',',UTC_TIME,12);
        Serial.readBytesUntil(',',Latitude,11);
        Serial.readBytesUntil(',',NorS,3);
        Serial.readBytesUntil(',',Longitude,12);
        Serial.readBytesUntil(',',EorW,3);
        Serial.readBytesUntil(',',Fix_Quality,3);
        Serial.readBytesUntil(',',Satellites_USED,4);
        Serial.readBytesUntil(',',HDOP,5);
        Serial.readBytesUntil(',',Altitude,8);

        Serial.print("GPS:");
        print_readings(Message_ID,5);
        Serial.print(",");
        print_readings(UTC_TIME,10);
        Serial.print(",");
        Serial.print(convert1(Latitude),9);
        Serial.print(",");
        print_readings(NorS,1);
        Serial.print(",");
        Serial.print(convert2(Longitude),10);
        Serial.print(",");
        print_readings(EorW,1);
        Serial.print(",");
        print_readings(Fix_Quality,1);
        Serial.print(",");
        print_readings(Satellites_USED,3);
        Serial.print(",");
        print_readings(HDOP,4);
        Serial.print(",");
        print_readings(Altitude,7);
      }
    }
   break;
  }
}
