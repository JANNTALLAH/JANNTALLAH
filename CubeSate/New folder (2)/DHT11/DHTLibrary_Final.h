

class DHTLib {
  private:
  unsigned char data[5],pulse[80];
  int pin=3;
  bool lvl;
  unsigned char lowcycle,highcycle;

  public:

  int expectpulse (bool lvl)
  {
      int count = 0;
      while(digitalRead(pin)==lvl) count++;
      return count;
  }

  char * read_data()
  {
        //Arduino sends out a start signal
        pinMode(pin,OUTPUT);

        digitalWrite(pin,HIGH);
         delay(1000);
        digitalWrite(pin,LOW);
          delay(18);
        digitalWrite(pin,HIGH);
          delayMicroseconds(40);

        //DHT sends out a responce signal
        pinMode(pin,INPUT);

        if(digitalRead(pin)==LOW)
        {
            while(digitalRead(pin)==LOW) {/*delayMicroseconds(80)*/};
            while(digitalRead(pin)==HIGH) {/*delayMicroseconds(80)*/};
        }

        //in case the if condition is false means the signal is high then it is an error .. so we use else to print error
        else
        {
          Serial.println("NOT RESPONDING!");
          return; //means when it is error, it will return us to the very start of void loop.
        }

        for(int i=0;i<80;i++)     pulse[i]= expectpulse(i%2);

        for(int i=0;i<40;i++)
        {
            lowcycle = pulse [i*2];
            highcycle = pulse [(i*2)+1];

            if(i<8)
            {
              data[0] <<=1;
              if(highcycle>lowcycle)   data[0] |=1;
            }
            if(i<16)
            {
              data[1] <<=1;
              if(highcycle>lowcycle)  data[1] |=1;
            }
            if(i<24)
            {
              data[2] <<=1;
              if(highcycle>lowcycle) data[2] |=1;
            }
            if(i<32)
            {
              data[3] <<=1;
              if(highcycle>lowcycle) data[3] |=1;
            }
            if(i<40)
            {
              data[4] <<=1;
              if(highcycle>lowcycle) data[4] |=1;
            }

        }

        if(data[4]!= data[0]+data[1]+data[2]+data[3])  Serial.println("ERROR");

        else
        {
          return data;
        }
  }

  void RelativeHumdity ()
  {
        read_data();
        //Serial.print("Relative Humidity: ");
        Serial.print("DHT:");
        Serial.print(data[0]); Serial.print(".");
        Serial.print(data[1]);
        Serial.print(",");
  }

  void Temperature ()
  {
        read_data();
        //Serial.print("Temperature by DHT: ");
        Serial.print(data[2]); Serial.print(".");
        Serial.print(data[3]);
  }



};
