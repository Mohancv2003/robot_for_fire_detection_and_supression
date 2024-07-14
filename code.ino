#include <Servo.h>            //include servo.h library
//#include <SoftwareSerial.h>  //include SoftwareSerial.h library

Servo myservo;
 
int pos = 0;    
boolean fire = false;


/*
const String PHONE = "+91****"; //use your number with country code

#define rxPin 2
#define txPin 3 
SoftwareSerial sim800L(rxPin,txPin);
*/
#define buzz 3          // buzzer
#define Left 4          // left sensor
#define Right 5         // right sensor
#define Forward 6       //front sensor
#define GAS_SENSOR 7    //Gas sensor
#define LM1 8           // left motor
#define LM2 9           // left motor
#define RM1 10          // right motor
#define RM2 11          // right motor
#define pump 12         //water pumb



void setup()
{
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Forward, INPUT);
  pinMode(GAS_SENSOR, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(buzz, OUTPUT);
 
  myservo.attach(13);
  myservo.write(90); 
  
//  while(sim800L.available()){
//  Serial.println(sim800L.readString());
//  }
  
}
 
void put_off_fire()
{
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    digitalWrite(pump,HIGH);
    digitalWrite(buzz,HIGH);
    delay(500);
 
 
    for (pos = 50; pos <= 110; pos += 1) { 
    myservo.write(pos); 
    delay(50);  
  }
  for (pos = 110; pos >= 50; pos -= 1) { 
    myservo.write(pos); 
    delay(50);
  }
  digitalWrite(buzz,LOW);
  digitalWrite(pump,LOW);
  myservo.write(90); 
  fire=false;
}
 
void loop()
{
  myservo.write(90); //Sweep_Servo();  
  if (digitalRead(Left) ==1 && digitalRead(Right)==1 && digitalRead(Forward) ==1) 
    {
    delay(90);
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    }
    else if (digitalRead(Forward) ==0) 
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    fire = true;
    
    }
    
    else if (digitalRead(Left) ==0)
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    }
    
    else if (digitalRead(Right) ==0) 
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    }
    delay(150);//change this value to change the distance
    
     if(digitalRead(GAS_SENSOR)== 0)
    {
     Serial.println("Gas is Detected.");
     digitalWrite(buzz,HIGH);
     delay(5000);
     digitalWrite(buzz,LOW);
    //send_sms(); 
    }
   
     while (fire == true)
     {
      put_off_fire();
/*      Serial.println("Fire Detected.");
      send_sms();*/
     }
}

/*void send_sms()
{
    Serial.println("sending sms....");
    delay(50);
    sim800L.print("AT+CMGF=1\r");
    delay(1000);
    sim800L.print("AT+CMGS=\""+PHONE+"\"\r");
    delay(1000);
    sim800L.print("Gas Detected");
    delay(100);
    sim800L.write(0x1A);
    delay(5000);
}*/