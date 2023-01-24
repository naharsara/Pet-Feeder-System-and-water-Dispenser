 #include <Servo.h>
#define BLYNK_PRINT Serial
#include <Blynk.h>
#include <LiquidCrystal_I2C.h> 
#include <Wire.h>
#include <ESP8266WiFi.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <BlynkSimpleEsp8266.h>
const int TRIG_PIN = D6;//D6
const int ECHO_PIN = D5; //D5
//show display
WidgetLCD lcdd(V3);
BlynkTimer timer;
bool pinValue = 0;
const int TRIG_PIN2 = D2;
const int ECHO_PIN2 = D1; 

const int length=15;


const int DISTANCE_THRESHOLD = 50; 
const int DISTANCE_THRESHOLD2=30;
// variables will change:
float duration_us, distance_cm;


Servo servo;
Servo servo2;
char auth[] = "R6jeoc2cn4TeJZ2zWBqd7IrTL2q5kGwm";//Enter your Blynk auth token

char ssid[] = "OnePlus 9R";//Enter your WIFI name

char pass[] = "kishor1234";//Enter your WIFI password


BLYNK_WRITE(V1){

  servo.write(param.asInt());

  }
 
BLYNK_WRITE(V2) {
  
  pinValue = param.asInt();
}

  void setup() {

    Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mode

  //lcd 
  lcdd.clear();
  lcdd.print(1, 0, "Welcome");
  lcdd.print(4, 0, "To pet feeder ");
  delay(4000);
  lcdd.clear();
      
      servo.attach(D8);
        
      servo2.attach(D7);
     
    servo2.write(0);
   delay(2000);
   
   pinMode(TRIG_PIN2, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN2, INPUT);


  
        Blynk.begin(auth, ssid, pass);
        timer.setInterval(3L,foodlevel);

        }

void loop() {
  
 
 

  Blynk.run();
  timer.run();
  
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
//      servo.write(90);
//    delay(300);
//     servo.write(0);
//     delay(600); 

  
  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);
  // calculate the distance
  distance_cm = 0.017 * duration_us;
  int dist=(int)distance_cm;
  
  if((dist < DISTANCE_THRESHOLD)&& (dist > DISTANCE_THRESHOLD2)){
    if((dist<=50)&& (dist>=40))
    {
      Blynk.notify("your pet is nearby! Give him a food");
      
    }

  else
  {
    //digitalWrite(BUZZER_PIN, LOW);
  }

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(dist);
  Serial.println(" cm");

  delay(500);

  }
  if(dist>50){
     lcdd.print(1, 0, "Welcome To         pet feeder");
    delay(1000);
    lcdd.clear();
     
  }
  if(dist<=10){
    lcdd.print(1,0,"  pet Hungry");
    lcdd.print(6, 1, dist);
    lcdd.print(9, 1, "cm");

  }
    if((dist<=50)&&(dist>10)){
    lcdd.print(1,0,"  Pet Nearby");
   lcdd.print(6, 1, dist);
   lcdd.print(9, 1, "cm");
    
  }
  
}

  void foodlevel() {
//  if (pinValue == 1) {
//   // digitalWrite(B, LOW);
//
//  } else if (pinValue == 0) {
//   // digitalWrite(B, LOW);
//
//  }
 
  digitalWrite(TRIG_PIN2, LOW);
  delayMicroseconds(4);
  digitalWrite(TRIG_PIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN2, LOW);
  long t = pulseIn(ECHO_PIN2, HIGH);
  long distance = t / 29 / 2;
  float percent=5-(distance/3);
  int percent2=(int)percent;  

  if (percent<1)
  {
    Blynk.notify("Food run out");
   //for secondary servo
 
    servo2.write(120);
    delay(3000);
     servo2.write(0);
     delay(1000);  
  }
  Blynk.virtualWrite(V2, percent);
  //Serial.println(percent);

  }
