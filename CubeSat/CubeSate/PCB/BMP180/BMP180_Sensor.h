#include <Wire.h>
class BMP180_Sensor
{
private:
#define BMP 0x77
#define AC1_REG 0xAA
#define AC2_REG 0xAC
#define AC3_REG 0xAE
#define AC4_REG 0xB0
#define AC5_REG 0xB2
#define AC6_REG 0xB4
#define BB1_REG 0xB6
#define BB2_REG 0xB8
#define MB_REG 0xBA
#define MC_REG 0xBC
#define MD_REG 0xBE
#define CONTROL 0xF4
#define TEMP 0x2E
#define PRESSURE 0x34
#define UT_REG 0xF6
short AC1;
short AC2;
short AC3;
unsigned short AC4;
unsigned short AC5;
unsigned short AC6;
short BB1;
short BB2;
short MB;
short MC;
short MD;
const unsigned char OSS=0;
long UT;
long UP;
long T;
long P;
const float PO=101392.0;
float A;

public:

int READ_REGISTER(unsigned char Register_Name)
{
  Wire.beginTransmission(BMP);
  Wire.write(Register_Name);
  Wire.endTransmission();
  Wire.requestFrom(BMP,2);
  if(Wire.available()==2)
  {
    short data_1=Wire.read();
    short data_2=Wire.read();
    short Convert=data_1<<8;
    short DATA_OUT=Convert|data_2;
    return DATA_OUT;
  }
}

void GET_DATA_FROM_REGISTERS()
{
  AC1=READ_REGISTER(AC1_REG);
  AC2=READ_REGISTER(AC2_REG);
  AC3=READ_REGISTER(AC3_REG);
  AC4=READ_REGISTER(AC4_REG);
  AC5=READ_REGISTER(AC5_REG);
  AC6=READ_REGISTER(AC6_REG);
  BB1=READ_REGISTER(BB1_REG);
  BB2=READ_REGISTER(BB2_REG);
  MB=READ_REGISTER(MB_REG);
  MC=READ_REGISTER(MC_REG);
  MD=READ_REGISTER(MD_REG);
}
void calculate_parameters()
{
  Wire.beginTransmission(BMP);
  Wire.write(CONTROL);
  Wire.write(TEMP);
  Wire.endTransmission();
  delay(5);
  UT=READ_REGISTER(UT_REG);
  Wire.beginTransmission(BMP);
  Wire.write(CONTROL);
  Wire.write(PRESSURE+(OSS<<6));
  Wire.endTransmission();
  delay(5);
  Wire.beginTransmission(BMP);
  Wire.write(UT_REG);
  Wire.endTransmission();
  Wire.requestFrom(BMP,3);
  if(Wire.available()==3)
  {
    unsigned long UP1=Wire.read();
    unsigned long UP2=Wire.read();
    unsigned long UP3=Wire.read();
    UP=((UP1<<16) + (UP2<<8) | (UP3)) >> (8-OSS);
  }
  long X1 = (UT-AC6)*AC5/(pow(2,15));
  long X2 = MC* pow(2,11)/(X1+MD);
  long B5 = X1+X2;
  T = (long)(B5+8) /pow(2,4);
  long B6 = B5-4000;
  X1 = (BB2 * (B6 * B6/pow(2,12))/pow(2,11));
  X2 = AC2 * B6/pow(2,11);
  long X3 = X1 + X2;
  long B3 = (((AC1*4 + X3)<<OSS) + 2)/4;
  X1 = AC3 * B6/pow(2,13);
  X2 = BB1 * (B6 * B6/pow(2,12))/pow(2,16);
  X3 = ((X1 + X2) + 2)/pow(2,2);
  unsigned long B4 = AC4 * (unsigned long)(X3 + 32768)/pow(2,15);
  unsigned long B7 = (UP - (unsigned long) B3) * (50000>>OSS);
  if (B7 < 0x80000000)
  {
    P = (B7*2)/B4;
  }
  else
  {
    P = (B7/B4)*2;
  }
  X1 = (P/pow(2,8)) * (P/pow(2,8));
  X1= (X1 * 3038)/pow(2,16);
  X2 = (-7357 * P)/pow(2,16);
  P += (X1 + X2 + 3791)/pow(2,4);
  A=44330*(1-pow((P/PO),(1/5.255)));
  Serial.print(P); Serial.print(","); Serial.print(A);
}
};
