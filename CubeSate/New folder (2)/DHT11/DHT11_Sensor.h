class DHT11_Sensor{
private:
#define DHT_pin 3

public:

unsigned char expectPulse(bool level)
{
  unsigned char count = 0;
  while (digitalRead(DHT_pin) == level)
  {
    count++;
  }
  return count;
}

void calculate_parameters()
{
  unsigned char Pulse[80];
  unsigned char RH_int=0,RH_dec=0,Temp_int=0,Temp_dec=0,checksum=0;
  pinMode(DHT_pin,OUTPUT);
  digitalWrite(DHT_pin,HIGH);
  delay(300);
  digitalWrite(DHT_pin,LOW);
  delay(18);
  digitalWrite(DHT_pin,HIGH);
  delayMicroseconds(40);
  pinMode(DHT_pin,INPUT);
  while(digitalRead(DHT_pin) == LOW)
  {

  }
  while(digitalRead(DHT_pin) == HIGH)
  {

  }

  for (int i=0;i<40;i++)
  {
    Pulse[2*i]=expectPulse(LOW);
    Pulse[2*i+1]=expectPulse(HIGH);
  }
  for (int i=0; i<40; i++)
  {
    unsigned char lowCycles  = Pulse[2*i];
    unsigned char highCycles = Pulse[2*i+1];
    if (i<8)
    {
      RH_int <<= 1;
      if (highCycles > lowCycles)
      {
        RH_int|=1;
      }
    }
    else if (i<16)
    {
      RH_dec<<=1;
      if (highCycles > lowCycles)
      {
        RH_dec |= 1;
      }
    }
    else if (i<24)
    {Temp_int<<=1;
    if (highCycles > lowCycles)
          {Temp_int|=1;

    }
    }
    else if (i<32)
    {Temp_dec<<=1;
    if (highCycles > lowCycles)
          {Temp_dec|=1;

    }
    else
    {
      checksum<<=1;
    if (highCycles > lowCycles)
          {checksum|=1;
          }
    }

   }
 }


Serial.print(RH_int); Serial.write(".");Serial.print(RH_dec); Serial.print(',');
Serial.print(Temp_int); Serial.write(".");Serial.print(Temp_dec);
//Serial.print(checksum);

pinMode(DHT_pin,OUTPUT);
digitalWrite(DHT_pin,HIGH);
}

};
