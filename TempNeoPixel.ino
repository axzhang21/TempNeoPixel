#include <Adafruit_NeoPixel.h>
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
#define LED_PIN 9
#define LED_COUNT 10

DHT dht(DHTPIN, DHTTYPE);

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int r=0, g=0, b=255; 

/*int r(int t) //red function
{
  if(t < 70) return 0;
  if(t>30) return 255;

  return map(t, 70, 80, 0, 255);
}

int g(int t) //green function
{
  if(t < 70
}*/

void setup() 
{
  Serial.begin(9600);
  dht.begin();
  strip.begin();
  strip.show();
  strip.setBrightness(50);
}

void loop() 
{
  //Temp Reading
  delay(2000);
  float t = dht.readTemperature(true); // in fahrenheit

  if (isnan(t)) 
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  Serial.print(F("%  Temperature: "));
  Serial.print(t);

  int tValue = digitalRead(2);

  Serial.print("2 => ");
  Serial.println(t);
  
//notes
//use <= so values inclusive?
  
  for(int i=0; i<LED_COUNT; i++)
  {
    if(t<75) //r(t)
    {
      r = 0;
    }
    if(t>75 && t<90)
    {
      //r = ((51/6)t-510);
      r = map(t, 75, 90, 0, 255);
    }
    else(t>90);
    {
      r = 255;
    }

    if(t<60) //g(t)
    {
      g = 0;
    }
    if(t>60 && t<75)
    {
      g = map(t, 60, 75, 0, 255);
    }
    if(t>75 && t<90);
    {
      g = map(t, 75, 90, 255, 0);
    }
    if(t>80)
    {
      g = 0;
    }

    if(t<60) //b(t)
    {
      b = 255;
    }
    else if(t>60 && t<75)
    {
      b = map(t, 60, 75, 255, 0); //inverted
    }
    else(t>90);
    {
      b = 0;
    }

    strip.setPixelColor(i, strip.Color(r, g, b));
    strip.show();
    delay(500);
    //strip.clear();
   }
   strip.clear();
}
