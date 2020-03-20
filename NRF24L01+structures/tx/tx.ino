/*
  Arduino IDE:1.8.12
  last modified:20-3-2020
  code by:ArvindNE555

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
//================================TRANSMITTER(00001)================================
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//MAX PAYLOAD SIZE 32BYTES PER LAUNCH
RF24 radio(7, 8); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};//40-BIT ADDRESS
struct dumpster {// data recived is stored here
  char re[32];
} rec;
struct dumpster_1{// data recived is stored here
   byte mag;
  byte mag2;
  byte ax;
  byte ay;
  byte az;
  byte gx;
  byte gx2;
  byte gy;
  byte gy2;
  byte gz;
  byte gz2;
  byte s;
  byte m;
  byte h;
  byte d; 
}rec_1;
struct payload {// data to be transmited
  char se[32];
} sen = {"hello,reciver"};
struct payload_1{// data to be transmited 
  byte mag;
  byte mag2;
  byte ax;
  byte ay;
  byte az;
  byte gx;
  byte gx2;
  byte gy;
  byte gy2;
  byte gz;
  byte gz2;
  byte s;
  byte m;
  byte h;
  byte d;
}sen_1 = {68, 1, 16, 16, 16, 208, 7, 208, 7, 208, 7, 60, 60, 24, 31};
void printDumpster_1() {
  Serial.print(rec_1.mag);
  Serial.print(",");
  Serial.print(rec_1.mag2);
  Serial.print(",");
  Serial.print(rec_1.ax);
  Serial.print(",");
  Serial.print(rec_1.ay);
  Serial.print(",");
  Serial.print(rec_1.az);
  Serial.print(",");
  Serial.print(rec_1.gx);
  Serial.print(",");
  Serial.print(rec_1.gx2);
  Serial.print(",");
  Serial.print(rec_1.gy);
  Serial.print(",");
  Serial.print(rec_1.gy2);
  Serial.print(",");
  Serial.print(rec_1.gz);
  Serial.print(",");
  Serial.print(rec_1.gz2);
  Serial.print(",");
  Serial.print(rec_1.s);
  Serial.print(",");
  Serial.print(rec_1.m);
  Serial.print(",");
  Serial.print(rec_1.h);
  Serial.print(",");
  Serial.print(rec_1.d);
  Serial.println(",");
}
void setup() {
  Serial.begin(115200);// for faster printing 
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
}
void recive() {
  radio.startListening();
  if (radio.available()) {
    radio.read(&rec_1, sizeof(dumpster_1));
    printDumpster_1();
  }
}
void transmit() {
  radio.stopListening();
  radio.write(&sen_1, sizeof(payload_1));
  Serial.println("sent");
}
void loop() {// maintain minimum 4ms at sucessive launch
  delay(5);
  transmit();
  delay(10);
  recive();
  delay(10);
}
