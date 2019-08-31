
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#include <Servo.h>

#define FIREBASE_HOST "nodemcu-d8b18.firebaseio.com"
#define FIREBASE_AUTH "7ZacqPc5zeXic7WcQ6itqqvhgZuef8ugqUAcFo4m"
#define WIFI_SSID "ks"
#define WIFI_PASSWORD "ks1052000"

Servo myservo;
const int T1= D1;
 const int E1= D2;
 const int T2= D6;
 const int E2= D7;
 
 long duration1, distance1,duration2, distance2,duration3, distance3;
 
 int pirpin=D5;
void setup() 
{
    
    Serial.begin(9600);
    pinMode(pirpin,INPUT);
    pinMode (T1,OUTPUT);
    pinMode (E1,INPUT);
    pinMode (T2,OUTPUT);
    pinMode (E2,INPUT);
    myservo.attach(D4);
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop()
{
  us1();
  us2();
  int pirValue=digitalRead(pirpin);
  Serial.println(pirValue);
  if(pirValue==1)
  {
  Serial.println("motion detecteed");
  servofn();
  delay(1000);
  }
  else
  {
  Serial.println("motion not detecteed");
  delay(1000);
  }
}
void servofn()
{
  int pos;
  for (pos = 0; pos <= 180; pos += 1) 
  {
    myservo.write(pos);        
    delay(15);
  }
  delay(1000);
  for (pos = 180; pos >= 0; pos -= 1) 
  {
    myservo.write(pos);              
    delay(15);                       
  }
}
void us1()
{
  
  digitalWrite (T1,LOW);
  delayMicroseconds(2);
  digitalWrite (T1,HIGH);
  delayMicroseconds(10);
  digitalWrite(T1,LOW);
  duration1= pulseIn(E1,HIGH);
  distance1= (duration1/2)/29.1;
  Serial.print("distance1=");
  Serial.println(distance1);
  delay (1000);
  Firebase.set("Bin 1",distance);
  checkfill();
}
void us2()
{
  digitalWrite (T2,LOW);
  delayMicroseconds(2);
  digitalWrite (T2,HIGH);
  delayMicroseconds(10);
  digitalWrite(T2,LOW);
  duration2= pulseIn(E2,HIGH);
  distance2= (duration2/2)/29.1;
  Serial.print("distance2=");
  Serial.println(distance2);
  delay (2000);
  Firebase.set("Bin 2",distance2);
  checkfill();
}
void checkfill()
{
  if(distance1<=5||distance2<=5)
  {
    Serial.println("Bin is full");
  }
  else
  {
    Serial.println("Bin is not full");
  }
}
    
