#define BLYNK_PRINT Serial

#include <SPI.h>
#include <WiFi101.h>
#include <BlynkSimpleMKR1000.h>
#include <Wire.h>
#include <SimpleTimer.h>
#include <Servo.h> 

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "fe06855ba6cc424a9516b270be7d0a7b";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "RedRover";
char pass[] = "";

const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

int x = 127;
int y = 127;
int left = 5;
int right = 3;
int up = 2;
int down = 4;
int autopin = 0;

int autoflag = 0;

int sensor = 1;

int xx = 0;
int yy = 0;
int zz = 0;

int xx_p = 0;
int yy_p = 0;
int zz_p = 0;


WidgetLED Up(V1);
WidgetLED Right(V2);
WidgetLED Down(V3);
WidgetLED Left(V4);
WidgetLED autoLED(V8);
BlynkTimer timer;

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  timer.setInterval(500L, main_loop);
  pinMode(sensor, INPUT);
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);
  pinMode(autopin, OUTPUT);

  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);

  int xx_p = analogRead(xpin);
  int yy_p = analogRead(ypin);
  int zz_p = analogRead(zpin);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}


BLYNK_WRITE(V9) {
  autoflag = param.asInt(); 
  Serial.print("autoflag = ");
  Serial.println(autoflag);
}

BLYNK_WRITE(V0) {
  x = param[0].asInt();
  y = param[1].asInt();

  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);
  //joy_send(x, y);
}

void main_loop(){
  Serial.println("LEDing");
  if(y < 50) {
    Blynk.virtualWrite(V1, 0);
    digitalWrite(up, LOW);
    Up.off();
    Blynk.virtualWrite(V3, 1);
    digitalWrite(down, HIGH);
    Down.on();
  }
  if(y > 200){
    Blynk.virtualWrite(V1, 1);
    digitalWrite(up, HIGH);
    Up.on();
    Blynk.virtualWrite(V3, 0);
    digitalWrite(down, LOW);
    Down.off();
  }

  if(x < 57){
    Blynk.virtualWrite(V2, 0);
    digitalWrite(right, LOW);
    Left.on();
    Blynk.virtualWrite(V4, 1);
    digitalWrite(left, HIGH);
    Right.off();
  }
  if(x > 200){
    Blynk.virtualWrite(V2, 1);
    digitalWrite(left, LOW);
    Left.off();
    Blynk.virtualWrite(V4, 0);
    digitalWrite(right, HIGH);
    Right.on();
  }

  if(x >= 57 && x <= 200 && y >= 57 && y <= 200){
    Blynk.virtualWrite(V1, 0);
    digitalWrite(up, LOW);
    Up.off();
    Blynk.virtualWrite(V3, 0);
    digitalWrite(down, LOW);
    Down.off();
    Blynk.virtualWrite(V2, 0);
    digitalWrite(left, LOW);
    Left.off();
    Blynk.virtualWrite(V4, 0);
    digitalWrite(right, LOW);
    Right.off();
  }
  if(autoflag) {autoLED.on();digitalWrite(autopin, HIGH);}
  else {autoLED.off();digitalWrite(autopin, LOW);}

  int cat = digitalRead(sensor);
  Serial.print("cat = ");
  Serial.println(cat);

  int xx = analogRead(xpin);
  int yy = analogRead(ypin);
  int zz = analogRead(zpin);
  
  Serial.println(xx);
  Serial.println(yy);
  Serial.println(zz);
  Blynk.virtualWrite(V13, xx);
  Blynk.virtualWrite(V14, yy);
  Blynk.virtualWrite(V12, zz);

  int diff = (xx - xx_p) * (xx - xx_p) + (yy - yy_p) * (yy - yy_p) + (zz- zz_p) * (zz - zz_p);
  Serial.println(diff);

  if (!cat || diff > 1000){
    Serial.println("Notification");
    Blynk.notify("Cat is near! Enter to tease him/her!");
  }

  xx_p = xx;
  yy_p = yy;
  zz_p = zz;
}

