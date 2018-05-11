const int LRed = 27;
const int LYellow = 25;
const int LGreen = 23;

const int RRed = 26;
const int RYellow = 24;
const int RGreen = 22;

long xAccelRaw, yAccelRaw, zAccelRaw;
float xAccelNormal, yAccelNormal, zAccelNormal;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
RF24 radio(7, 8); // CE, CSN
const uint64_t pipes[3] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL };

int text1, text2; 

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
//  Wire.beginTransmission(0b1101000);
//  Wire.write(107);
//  Wire.write(0b10000000);
//  Wire.endTransmission();
//  delay(100);
//  
//  Wire.beginTransmission(0b1101000);
//  Wire.write(104);
//  Wire.write(0b00000111);
//  Wire.endTransmission();
//  delay(100);
  
  //Let's set up the MPU to wake up
  Wire.beginTransmission(0b1101000); //Slave address. LSB 0 because AD0 pulled to ground.
  Wire.write(107); //Access Power Management register because device automatically comes in sleep mode
  Wire.write(0b00000000); //Turn off sleep mode and sets internal oscillator as clock source.
  Wire.endTransmission();

  //Configure sensitivity of Gyroscope
  Wire.beginTransmission(0b1101000); //Slave address
  Wire.write(27); //Gyrscope configuration register
  Wire.write(0b00000000); //Range of +- 250 degrees per second.
  Wire.endTransmission();
  
  //Configure sensitivity for Accelerometer
  Wire.beginTransmission(0b1101000); //Slave address
  Wire.write(28); //Accelerometer configuration register
  Wire.write(0b00000000); //Range of +-2g
  Wire.endTransmission();


  
  radio.begin();
  radio.openReadingPipe(1, pipes[1]);
  radio.openReadingPipe(2, pipes[2]);  
  radio.startListening();
  
  pinMode(LRed, OUTPUT);
  pinMode(LYellow, OUTPUT);
  pinMode(LGreen, OUTPUT);
  
  pinMode(RRed, OUTPUT);
  pinMode(RYellow, OUTPUT);
  pinMode(RGreen, OUTPUT);

  
}
void loop() 
{
  delay(150);
  getAcceleration();
  normalizeValues();
  
  
  if (radio.available()) {
    
    
    radio.read(&text1, sizeof(text1));
    radio.read(&text2, sizeof(text2));
      
      digitalWrite(LRed, LOW); 
      digitalWrite(LYellow, LOW); 
      digitalWrite(LGreen, LOW); 
      digitalWrite(RRed, LOW); 
      digitalWrite(RYellow, LOW); 
      digitalWrite(RGreen, LOW); 

    if(abs(zAccelNormal) >.5 || abs(yAccelNormal) > .5)
    {
      

    //Tran1 All
    if(text1 == 41){
      digitalWrite(LGreen, HIGH);
      digitalWrite(LYellow, HIGH);
      digitalWrite(LRed, HIGH);
      Serial.print("l");
      delay(300); 

    }
    // Tran2 All
    else if(text2 == 42){
      digitalWrite(RGreen, HIGH);
      digitalWrite(RYellow, HIGH);
      digitalWrite(RRed, HIGH);
      Serial.print("r");
      delay(300); 

    }
    
    // Tran1 RL
    else if(text1 == 51){
      digitalWrite(LRed, HIGH);
      digitalWrite(LGreen, HIGH);
      Serial.print("l");
      delay(300); 

    }
    
    // Tran2 RL
    else if(text2 == 52){
      digitalWrite(RRed, HIGH);
      digitalWrite(RGreen, HIGH);
      Serial.print("r");
      delay(300); 

    }
    
    // Tran1 RM
    else if(text1 == 61){
      digitalWrite(LGreen, HIGH);
      digitalWrite(LYellow, HIGH);
      Serial.print("l");
      delay(300); 

    }
    
    // Tran2 RM
    else if(text2 == 62){
      digitalWrite(RGreen, HIGH);
      digitalWrite(RYellow, HIGH);
      Serial.print("r");
      delay(300); 

    }
    // Tran1 LM
    else if(text1 == 71){
      digitalWrite(LRed, HIGH);
      digitalWrite(LYellow,HIGH);
      Serial.print("l");
      delay(300); 

    }
    
    // Tran2 LM
    else if(text2 == 72){
      digitalWrite(RRed, HIGH);
      digitalWrite(RYellow,HIGH);
      Serial.print("r");
      delay(300); 

    }
    
    // Tran1 L
    else if(text1 == 11){
      digitalWrite(LRed, HIGH); 
      Serial.print("l");
      delay(300); 

    }

    // Tran2 L
    else if(text2 == 12){
      digitalWrite(RRed, HIGH); 
      Serial.print("r");
      delay(300); 

    }

    // Tran1 M
    else if(text1 == 21){
      digitalWrite(LYellow, HIGH);
      Serial.print("l");
      delay(300); 

    }
    
    // Tran2 M
    else if(text2 == 22){
      digitalWrite(RYellow, HIGH);
      Serial.print("r");
      delay(300); 

    }
    // Tran1 R
    else if(text1 == 31){
      digitalWrite(LGreen, HIGH);
      Serial.print("l");
      delay(300);   
    }

    // Tran2 R
    else if(text2 == 32){
      digitalWrite(RGreen, HIGH);
          Serial.print("r");
        delay(300); 

    }
    // Tran Nothing
    else{
      digitalWrite(LRed, LOW); 
      digitalWrite(LYellow, LOW); 
      digitalWrite(LGreen, LOW); 
      digitalWrite(RRed, LOW); 
      digitalWrite(RYellow, LOW); 
      digitalWrite(RGreen, LOW); 
      Serial.print("n");
    }
  }

  }
}


void getAcceleration()
{
  Wire.beginTransmission(0b1101000); //Begin I2C communication
  Wire.write(59); //Begin communication with accelerometer values register
  Wire.endTransmission();
  Wire.requestFrom(0b1101000, 6); // Requesting accelerometer data from registers 59-64
  while(Wire.available() < 6)    //Wait until all 6 registers have transmitted the data
  {
        Serial.println(Wire.available());
  }

  xAccelRaw = Wire.read() <<8 | Wire.read(); //Put x axis accelerometer value back together (16 bits)
  yAccelRaw = Wire.read() <<8 | Wire.read();// Put y accelerometer value back together
  zAccelRaw = Wire.read() <<8 | Wire.read(); //Z accelerometer value

}

void normalizeValues()
{
  xAccelNormal = (xAccelRaw / 16384.0); //Converts it to G's. The divisor depends on the range of the measurements selected (+-2g)
  yAccelNormal = (yAccelRaw / 16384.0);
  zAccelNormal = (zAccelRaw / 16384.0);
}



