/* Arduino ide version-1.8.12
 *writen by:Arvindne555 
 * Aduino code to measure the analog voltage of the mic and covert to sound levels
 * using linear/recurresive curve fitting
 * Last modified: 1-3-2020
 
  The circuit:
   LCD RS pin to digital pin 12
   LCD Enable pin to digital pin 11
   LCD D4 pin to digital pin 5
   LCD D5 pin to digital pin 4
   LCD D6 pin to digital pin 3
   LCD D7 pin to digital pin 2
   LCD R/W pin to ground
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)
   mic pin to analog pin 0
   
   sound levels and their cause:
 
  120DB Threshold of pain, Thunder,above this can damage ear
  110dB - Concerts, Screaming child
  100dB - Motorcycle, Blow dryer
  90dB - Diesel truck, Power mower
  BODB - Loud music, Alarm clocks
  70dB - Busy traffic, Vacuum cleaner
  60dB - Normal conversation at 3 ft.
  50DB - Quiet office. Moderate rainfall
  40DB Quiet library. Bird calls
  30dB - Whisper. Quiet rural area
  20dB - Rustling leaves. Ticking watch
  10dB - Almost quiet, Breathing
  
*/

#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface LCD pins
//LiquidCrystal lcd(9);// use this for 74hc595 shifted lcd module
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int mic = A0;//output of sound/microphone module goes to analog pin A0

void setup() {
  //begin Serial interface to debugg and test
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(" NOISE LEVEL");
  lcd.setCursor(8, 1);
  lcd.print("METER!");
  delay(2000);
  lcd.clear();
}

int process(int adc_value) {
  int dB = (adc_value + 83.2073) / 11.003; //Convert ADC value to dB using Regression values
  //calibrate your mic for diffrent sounds and put up the Regression coefficents
  return dB;
}

void lcd_update(int dB) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Noise= ");
  lcd.print(dB);
  lcd.setCursor(10, 0);
  lcd.print("dB");
  lcd.setCursor(0, 1);

  if (dB <= 10) {
    lcd.print("Almost Quiet");
    Serial.println("Almost Quiet");
  }

  if (dB > 10 && dB <= 20) {
    lcd.print("Ticking Watch");
    Serial.println("Ticking Watch");
  }
  if (dB > 20 && dB <= 30) {
    lcd.print("A Quiet Place");
    Serial.println("A Quiet Place");
  }
  if (dB > 30 && dB <= 40) {
    lcd.print("Moderate Rainfall");
    Serial.println("Moderate Rainfall");
  }
  if (dB > 40 && dB <= 50) {
    lcd.print("A Conversation");
    Serial.println("A Conversation");
  }
  if (dB > 50 && dB <= 60) {
    lcd.print("Vaccum Cleaner");
    Serial.println("Vaccum Cleaner");
  }
  if (dB > 60 && dB <= 70) {
    lcd.print("Loud Music");
    Serial.println("Loud Music");
  }
  if (dB > 70 && dB <= 80) {
    lcd.print("Motorcycle");
    Serial.println("Motorcycle");
  }
  if (dB > 80 && dB <= 90) {
    lcd.print("Diesel Truck");
    Serial.println("Diesel Truck");
  }
  if (dB > 90 && dB <= 100) {
    lcd.print("Concerts");
    Serial.println("Concerts");
  }
  if (dB > 100 && dB <= 110) {
    lcd.print("Threshold of Pain");
    Serial.println("Threshold of Pain");
  }
  if (dB > 120) {
    lcd.print("ROCKET Launch!");
    Serial.println("ROCKET Launch!");
  }
}
void loop() {

  //read the voltage changes
  int value = analogRead(mic);
  //convert the voltages to dB using curve fitting
  int dB = process(value);
  //send to lcd
  lcd_update(dB);

  // print data on to serial moniter
  Serial.print("analouge value: ");
  Serial.print(value);
  Serial.println("");
  Serial.print("noise in dB: ");
  Serial.print(dB);
  Serial.println("             ");
  Serial.println("             ");

  //wait for 2 seconds to aviod random voltage spikes at A0
  delay(2000);

}
