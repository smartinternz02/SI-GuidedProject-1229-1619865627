// analogWrite() for esp32:
#include <analogWrite.h>

//DHT:
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>
#include <Wire.h>
#define DHTTYPE DHT11
#define DHTPIN 22
#define led2 35 //This LED acts as a Fan
float t,h;
void Dht();
DHT dht(DHTTYPE,DHTPIN);

//OLED:
#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
Adafruit_SSD1306 display =Adafruit_SSD1306(128, 64, &Wire);

//LDR:
#define led1 23 //This LED acts as a light
#define LDR 15
int a;
void ldr();

void setup() 
{
   pinMode(led1,OUTPUT);
   pinMode(led2,OUTPUT);
   pinMode(LDR,INPUT);
   dht.begin();
   display.display();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
   display.clearDisplay();
   display.setCursor(0,0);
}

void loop() 
{
  ldr();                   // Calls LDR and  
  Dht();                   // DHT11 Sensors.
  display.print("temp");  
  display.setCursor(0,5);
  display.print("humi");
  display.setCursor(0,10);               
  display.print("LDR");                     // Displaying temperature,humidity,LDR values.
  display.setCursor(1,0);
  display.println(t);
  display.setCursor(1,5);
  display.println(h);
  display.setCursor(1,10);
  display.println(a); 
  display.clearDisplay();
}

void ldr()
{
  a= analogRead(LDR);
  analogWrite(led1,a);
}

void Dht()
{ 
  t= dht.readTemperature();
  h= dht.readHumidity();
  int avg = (t+h);
  analogWrite(led2,avg);
}
