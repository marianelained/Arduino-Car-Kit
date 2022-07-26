
int in1 = 2;
int in2 = 4;
int enA =3;

int in3 = 5;
int in4 = 7;
int enB =6;

int forward = 1700;
int turn1 = 750;
int tile = 950;

const int trigPin = 9;
const int echoPin = 8;

float duration;
float cm;
float distance;
float mm;

int left_dist;
int right_dist;
#include <Servo.h>
Servo myservo;
int pos = 0;    
long microsecondsTodistance(long microseconds)
{return microseconds / 74 / 2;}
long microsecondsToCentimeters(long microseconds)
{return microseconds / 29 / 2;}
long microsecondsToMillimeters(long microseconds)
{return microseconds / 2.9 / 2;}


void moveF_baby(){
  
  digitalWrite(in1, LOW);//move forward; clockwise right wheel
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enA, 100);
  digitalWrite(enB, 100);
}

void moveB_baby(){
  
  digitalWrite(in1, HIGH);//move forward; clockwise right wheel
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(enA, 100);
  digitalWrite(enB, 100);
}

void moveL_baby(){
    digitalWrite(in1, HIGH);//turnleft
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(enA, 100);
    digitalWrite(enB, 100);
    delay(turn1);
}

void moveR_baby(){
    digitalWrite(in1, LOW);//turnright
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(enA, 100);
    digitalWrite(enB, 100);
    delay(turn1);
}


void stop_baby(){
    digitalWrite(in1, LOW);//stop
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(enA, 100);
    digitalWrite(enB, 100);
    delay(1500);
}

void calc(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = microsecondsTodistance(duration);
  cm = microsecondsToCentimeters(duration);
  mm = microsecondsToMillimeters(duration);
  delay(100);
}
void setup() {
  // put your setup code here, to run once:
  

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  myservo.attach(10); 
  myservo.write(90);
  Serial.begin(9600);
}

void loop() {

int x = 0;
while(x==0){
  calc();
  Serial.println(distance);
  moveF_baby();
  
  if(distance<=10){  //distance to which the robot will act upon obatacle detection
    moveB_baby();
    delay(350);
    stop_baby();
    delay(350);
    
    myservo.write(160);
    delay(2000);
    //additional
    myservo.write(80);
    delay(500);
   myservo.write(300);
    delay(500);
    myservo.write(80);
    delay(500);

    //additional end

    calc();
    
    left_dist = distance;
    delay(1000);

    myservo.write(0);
    delay(2000);

    calc();
//..??????????    
    right_dist = distance;
    delay(1000);
//

    if(left_dist > right_dist){
        myservo.write(80);
        delay(1000);
        moveL_baby();       
        break;
      }

    if(right_dist > left_dist){
      myservo.write(80);
      delay(1000);
      moveR_baby();
      
      stop_baby();
      break;
      
      
    }

  }

 
   
 }



 
 }

   
 
