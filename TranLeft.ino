const int LSonicEcho = 22;
const int LSonicTrig = 23;

const int MSonicEcho = 24;
const int MSonicTrig = 25;

const int RSonicEcho = 26;
const int RSonicTrig = 27;

const int Far1 = 91;

const int LClose1 = 11;
const int MClose1 = 21;
const int RClose1 = 31;
const int all1 = 41;
const int LM1= 71;
const int RM1 = 61;
const int RL1 = 51;

const int SWL1 = 37;
 
long Ldur1;
long Mdur1;
long Rdur1;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const uint64_t pipes[3] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL };
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipes[1]);
  
  pinMode(LSonicTrig,OUTPUT);
  pinMode(MSonicTrig,OUTPUT);
 
  pinMode(LSonicEcho,INPUT);
  pinMode(MSonicEcho,INPUT);
  
  pinMode(RSonicTrig,OUTPUT);
  pinMode(RSonicEcho,INPUT);

  pinMode(SWL1, INPUT);
 

}

void loop() {

  digitalWrite(LSonicTrig,LOW);
  delayMicroseconds(2);
  digitalWrite(LSonicTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(LSonicTrig,LOW);
  Ldur1 = pulseIn(LSonicEcho,HIGH);
  
  digitalWrite(MSonicTrig,LOW);
   delayMicroseconds(2);
  digitalWrite(MSonicTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(MSonicTrig,LOW);
  Mdur1 = pulseIn(MSonicEcho,HIGH);
  
  digitalWrite(RSonicTrig,LOW);  
  delayMicroseconds(2);
  digitalWrite(RSonicTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(RSonicTrig,LOW);
  Rdur1 = pulseIn(RSonicEcho,HIGH);


 if (digitalRead(SWL1) == LOW){


  if(Ldur1 < 500 && Mdur1 < 500 && Rdur1 < 500)
  {

    radio.write(&all1, sizeof(all1));
    delay(50);
  }

  else if(Ldur1 < 500 && Mdur1 < 500)
  {
    radio.write(&LM1, sizeof(LM1)); 
    delay(50);
    
  }
  

  else if(Ldur1 < 500 && Rdur1 < 500)
  {
    radio.write(&RL1, sizeof(RL1));
    delay(50);
  }

  else if(Mdur1 < 500 && Rdur1 < 500)
  {
    radio.write(&RM1, sizeof(RM1)); 
    delay(50);

  }
  
  else if(Ldur1 < 500){
     radio.write(&LClose1, sizeof(LClose1));
     delay(50);

  }
  else if(Mdur1 < 500){     
     radio.write(&MClose1, sizeof(MClose1));
     delay(50);

  }
  else if(Rdur1 < 500){
      radio.write(&RClose1, sizeof(RClose1));
      delay(50);

  }
  else{
      radio.write(&Far1, sizeof(Far1));
      delay(50);

  }
 }
  
 if (digitalRead(SWL1)  == HIGH){
  if(Ldur1 < 1000 && Mdur1 < 1000  && Rdur1 < 1000)
  {
    radio.write(&all1, sizeof(all1));
    delay(50);
  }

  else if(Ldur1 < 1000 && Mdur1 < 1000)
  {
    radio.write(&LM1, sizeof(LM1)); 
    delay(50);

  }
  

  else if(Ldur1 < 1000  && Rdur1 < 1000)
  {
    radio.write(&RL1, sizeof(RL1));
    delay(50);
  }

  else if(Mdur1 <1000 && Rdur1 <1000)
  {
    radio.write(&RM1, sizeof(RM1)); 
    delay(50);

  }
  
  else if(Ldur1 < 1000){
     radio.write(&LClose1, sizeof(LClose1));
     delay(50);

  }
  else if(Mdur1 < 1000){
     radio.write(&MClose1, sizeof(MClose1));
     delay(50);

  }
  else if(Rdur1 < 1000){
      radio.write(&RClose1, sizeof(RClose1));
      delay(50);

  }
  else{
      radio.write(&Far1, sizeof(Far1));
      delay(50);

  }
  }
}
