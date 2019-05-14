#include <Servo.h>   
Servo servo;

int servoPin = 9;

int trigPin = 6;    
int echoPin = 7;   
long duration, distance;   
long aver[3];   

void setup() {     
  servo.attach(servoPin);  
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT); 
  servo.write(0); 
  delay(1000);
  servo.detach();
} 

void measure() {  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  distance = duration *0.034 / 2;
}

void loop() { 
  for (int i=0;i<=2;i++) {   
    measure();               
    aver[i]=distance;            
    delay(50);           
  }
 
  distance=(aver[0]+aver[1]+aver[2])/3; 
  
  if (distance<40) {
    servo.attach(servoPin);
    delay(1);
    servo.write(90);  
    delay(5000);  
    servo.write(0);    
    delay(1000);
    servo.detach();      
  }
}
