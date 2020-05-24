/*
 * Verison 1.0 
 * Author: Umesh Kumar
 * Email : developer15109@gmail.com
 * Date: 11th May, 2020
 * Last update: 11th May, 2020
 * : apply best practice method and create two classes : Range.h and Timer.h
 */

 // Include the classes in our main file

 #include "Range.h"
 #include "Timer.h"

 int TRIG_PIN = 9;
 int ECHO_PIN = 8;

 int PUMP_PIN = 10;
 int led = 13;

 int count = 0;

 float distance;
  
 Range range(TRIG_PIN,ECHO_PIN);
 Timer timerLoop;

boolean flag = false;

 // For now I have set it as 50 miliseconds
 const int LOOP_TIME = 50;
 const int PUMP_ON_TIME = 250;
 const int CONSTANT_DISTANCE = 20;
 const int WAITING_TIME = 8000;

 void setup(){
  Serial.begin(9600);
  Serial.println("Welcome Umesh");
  pinMode(PUMP_PIN,OUTPUT);
  pinMode(led,OUTPUT);
  digitalWrite(PUMP_PIN, HIGH);
 }

 void loop(){
  
  // Loop for every 50 miliseconds and measure the distance using the sensor
  if(timerLoop.isTimeForLoop(LOOP_TIME)){
      Serial.print("Distance measured is: ");
      distance = range.sensorRange();
      Serial.print(distance);
      Serial.println(" cm");
      timerLoop.startTimer();
       
       // less than 10cm
      if(distance<=CONSTANT_DISTANCE && distance !=0){
          flag = true;
          count = count +1;
          Serial.println("Sensor ON ");
          digitalWrite(PUMP_PIN, LOW);   // turn the LED on (HIGH is the voltage level)
          digitalWrite(led, HIGH);

 
          while(timerLoop.isTimerReady(PUMP_ON_TIME));
         
          // turn off the motor now
          Serial.println("Sensor OFF");
          digitalWrite(PUMP_PIN, HIGH);    // turn the LED off by making the voltage LOW
          
//          Serial.println("Waiting Start"); 
//          timerLoop.startTimer();
//          while(timerLoop.isTimerReady(WAITING_TIME));
//          Serial.println("Waiting Stop"); 
          
      }else{
          Serial.println("LOW Value ");
          digitalWrite(PUMP_PIN, HIGH);    // turn the LED off by making the voltage LOW 
          digitalWrite(led, LOW);
          delayMicroseconds(2);
       }   
   }

   // if flag is true
    if(flag == true && count == 3){
      delay(WAITING_TIME);
      flag = false;
      count = 0;
    }
 
 }


// void stepper(){
//  
//  // Enable the motor to move in a particular direction
//  digitalWrite(dirPin, LOW); 
//
//  // make 200 pulses for making the one full cycle rotation
//  for (int x=0; x< step;x++){
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(Delay);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(Delay);
//  }
//
//  delay(50);
//
//  // change the rotation direction
//  digitalWrite(dirPin, HIGH); 
//  
//  // make 400 pulses for making two full cycle rotation
//  for(int x=0;x<step;x++){
//    digitalWrite(stepPin, HIGH);
//    delayMicroseconds(Delay);
//    digitalWrite(stepPin, LOW);
//    delayMicroseconds(Delay);
//  }
//}
