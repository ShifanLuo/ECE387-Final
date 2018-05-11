const int LSonicEcho = 22;
const int LSonicTrig = 23;
int SWR1 = 34;
const int MSonicEcho = 24;
const int MSonicTrig = 25;

const int RSonicEcho = 26;
const int RSonicTrig = 27;

const int Far2 = 92;

const int LClose2 = 12;
const int MClose2 = 22;
const int RClose2 = 32;
const int all2 = 42;
const int LM2 = 72;
const int RM2 = 62;
const int RL2 = 52;
 
long Ldur2;
long Mdur2;
long Rdur2;

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
const uint64_t pipes[3] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL };
void setup() {
  radio.begin();
  radio.openWritingPipe(pipes[2]);
  
  pinMode(LSonicTrig,OUTPUT);
  pinMode(MSonicTrig,OUTPUT);
 
  pinMode(LSonicEcho,INPUT);
  pinMode(MSonicEcho,INPUT);
  
  pinMode(RSonicTrig,OUTPUT);
  pinMode(RSonicEcho,INPUT);
  pinMode(SWR1, INPUT);

}

void loop() {
  digitalWrite(LSonicTrig,LOW);
  delayMicroseconds(2);
  digitalWrite(LSonicTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(LSonicTrig,LOW);
  Ldur2 = pulseIn(LSonicEcho,HIGH);
  
  digitalWrite(MSonicTrig,LOW);
   delayMicroseconds(2);
  digitalWrite(MSonicTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(MSonicTrig,LOW);
  Mdur2 = pulseIn(MSonicEcho,HIGH);
  
  digitalWrite(RSonicTrig,LOW);  
  delayMicroseconds(2);
  digitalWrite(RSonicTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(RSonicTrig,LOW);
  Rdur2 = pulseIn(RSonicEcho,HIGH);
  
  if(digitalRead(SWR1) == LOW){
  if(Ldur2 <500 && Mdur2 <500 && Rdur2 <500)
  {
    radio.write(&all2, sizeof(all2));
    delay(50);
  }

  else if(Ldur2 <500 && Mdur2 <500)
  {
    radio.write(&LM2, sizeof(LM2)); 
    delay(50);

  }

  else if(Ldur2 <500 && Rdur2 <500)
  {
    radio.write(&RL2, sizeof(RL2));
    delay(50);
  }

  else if(Mdur2 <500 && Rdur2 <500)
  {
    radio.write(&RM2, sizeof(RM2)); 
    delay(50);

  }
  
  else if(Ldur2 < 500){
     radio.write(&LClose2, sizeof(LClose2));
     delay(50);

  }
  else if(Mdur2 < 500){
     radio.write(&MClose2, sizeof(MClose2));
     delay(50);

  }
  else if(Rdur2 < 500){
      radio.write(&RClose2, sizeof(RClose2));
      delay(50);

  }
  else{
      radio.write(&Far2, sizeof(Far2));
      delay(50);

  }
  }
  if(digitalRead(SWR1) == HIGH){
  if(Ldur2 <1000 && Mdur2 <1000 && Rdur2 <1000)
  {
    radio.write(&all2, sizeof(all2));
    delay(50);
  }

  else if(Ldur2 <1000 && Mdur2 <1000)
  {
    radio.write(&LM2, sizeof(LM2)); 
    delay(50);

  }

  else if(Ldur2 <1000 && Rdur2 <1000)
  {
    radio.write(&RL2, sizeof(RL2));
    delay(50);
  }

  else if(Mdur2 <1000 && Rdur2 <1000)
  {
    radio.write(&RM2, sizeof(RM2)); 
    delay(50);

  }
  
  else if(Ldur2 < 1000){
     radio.write(&LClose2, sizeof(LClose2));
     delay(50);

  }
  else if(Mdur2 < 1000){
     radio.write(&MClose2, sizeof(MClose2));
     delay(50);

  }
  else if(Rdur2 < 1000){
      radio.write(&RClose2, sizeof(RClose2));
      delay(50);

  }
  else{
      radio.write(&Far2, sizeof(Far2));
      delay(50);

  }
  }
}
