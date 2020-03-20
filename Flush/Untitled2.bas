/*
 * Arduino IDE v1.8.12
 * Last modified: 8-3-2020
 * Theme: sensor based flush exit valve controler.
 * Motor type: Servo 9g or later 0-180 degrees
 * Sensor used: close proximity Hall-effect switch (magnetic based switch).
 */

#include<Servo.h>
#define sensor_pin 2     // sensor output pin connected to arduino
#define F_off_state 180  //angle for flush off position (0-180) degrees
#define F_on_state 0     //angle for flush on position (0-180) degrees
#define how_long 1000    // if flushed how long shoud the flush be on in ms
#define wait 2000        // how long should the sensor be pressed to trigger th motor in ms+1s
#define how_often 1000   //how often do you want to check the sensor and motor positon in ms
Servo motor;

void setup() {
  delay(10);
  pinMode(sensor_pin,INPUT);
  motor.attach(9);
  delay(10);
  motor.write(F_off_state); //on boot by default the motor is in off position 
  delay(100); 
  //soft start
}

void check(int hold,int curr_pos){
  delay(hold);
  if(digitalRead(2)==1){
    //long flush, flush on, open F_gate
    if(curr_pos=F_off_state){
      motor.write(F_on_state);
    }
  }
}
void loop() {  
  if(digitalRead(2)==1){
    check(wait,motor.read());
    delay(how_long); 
    // keep it short reccursion can cause longer delays
    // or make use of interupts with pulse based switch, to eliminate self looping
  }
  else{
    motor.write(F_off_state);
  }
  delay(how_often);
}