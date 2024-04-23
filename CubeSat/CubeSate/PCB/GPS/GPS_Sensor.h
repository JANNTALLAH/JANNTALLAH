#ifndef GPS_Sensor_H
#define GPS_Sensor_H

#include "Arduino.h"

class GPS
{
  public:
  void Run();

  private:
  char Message_ID[6];
  char UTC_TIME[11];
  char Latitude[10];
  char NorS[2];
  char Longitude[11];
  char EorW[2];
  char Fix_Quality[2];
  char Satellites_USED[3];
  char HDOP[4];
  char Altitude[7];
  int array1[10];
  int array2[11];
  double convert1(char LT[]);
  double convert2(char LOT[]);
  void print_readings(char arr[],int len);
};
#endif
