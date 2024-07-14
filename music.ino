#include <Servo.h>            //include servo.h library
//#include <SoftwareSerial.h>  //include SoftwareSerial.h library

Servo myservo;
 
int pos = 0;    
boolean fire = false;


/*
const String PHONE = "+91**********"; //use your number with country code

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
#define pump 12         //water pump

// defining notes frequency
#define hi1 580
#define hi2 610
#define hi3 640
#define hi4 670
#define hi5 700
#define hi6 730
#define hi7 760
#define hi8 790
#define hi9 820
#define hi10 850
#define hi11 880
#define hi12 910
#define hi13 940
#define hi14 970
#define hi15 1000

const float songSpeed = 2.0; // song speed


int notes[] = {
    hi1,hi2,hi3,hi4,hi5,hi6,hi7,hi8,hi9,hi10,hi11,hi12,hi13,hi14,hi15,hi15,hi14,hi13,hi12,hi11,hi10,hi9,hi8,hi7,hi6,hi5,hi4,hi3,hi2,hi1,
    hi1,hi2,hi3,hi4,hi5,hi6,hi7,hi8,hi9,hi10,hi11,hi12,hi13,hi14,hi15,hi15,hi14,hi13,hi12,hi11,hi10,hi9,hi8,hi7,hi6,hi5,hi4,hi3,hi2,hi1,
    hi1,hi2,hi3,hi4,hi5,hi6,hi7,hi8,hi9,hi10,hi11,hi12,hi13,hi14,hi15,hi15,hi14,hi13,hi12,hi11,hi10,hi9,hi8,hi7,hi6,hi5,hi4,hi3,hi2,hi1,
    hi1,hi2,hi3,hi4,hi5,hi6,hi7,hi8,hi9,hi10,hi11,hi12,hi13,hi14,hi15,hi15,hi14,hi13,hi12,hi11,hi10,hi9,hi8,hi7,hi6,hi5,hi4,hi3,hi2,hi1,
    hi1,hi2,hi3,hi4,hi5,hi6,hi7,hi8,hi9,hi10,hi11,hi12,hi13,hi14,hi15,hi15,hi14,hi13,hi12,hi11,hi10,hi9,hi8,hi7,hi6,hi5,hi4,hi3,hi2,hi1,
    hi1,hi2,hi3,hi4,hi5,hi6,hi7,hi8,hi9,hi10,hi11,hi12,hi13,hi14,hi15,hi15,hi14,hi13,hi12,hi11,hi10,hi9,hi8,hi7,hi6,hi5,hi4,hi3,hi2,hi1};

// Durations (in ms) of each music note of the song
// Quarter Note is 250 ms when songSpeed = 1.0
int durations[] = {
    90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,
    90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,
    90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,
    90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,
    90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,
    90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90,90};




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
  
}
 
void put_off_fire()
{
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);
  digitalWrite(pump,HIGH);
  delay(500);
 
 
  for (pos = 50; pos <= 110; pos += 1) { 
    myservo.write(pos); 
    delay(50);  
  }
  for (pos = 110; pos >= 50; pos -= 1) { 
    myservo.write(pos); 
    delay(50);
  }
  digitalWrite(pump,LOW);
  myservo.write(90); 
  fire=false;
}

void siren()
{
  const int totalNotes = sizeof(notes) / sizeof(int);
  // Loop through each note
  for (int i = 0; i < totalNotes; i++)
  {
    const int currentNote = notes[i];
    float wait = durations[i] / songSpeed;
    // Play tone if currentNote is not 0 frequency, otherwise pause (noTone)
    if (currentNote != 0)
    {
      tone(buzz, notes[i], wait); // tone(pin, frequency, duration)
    }
    else
    {
      noTone(buzz);
    }
    // delay is used to wait for tone to finish playing before moving to next loop
    delay(wait);
  }
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
      siren();
    }
   
    while (fire == true)
    {
      put_off_fire();
    }
}
