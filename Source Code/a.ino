#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
int lastx=0;
int lasty=0;
int x=0,y=0;
int in =8;
int ecg=0;
float gsr;
int lastrate=0;
int count=0,l=0,rate=0;
unsigned long time2,time1;
void setup() 
{
  Serial.begin(9600);
  pinMode(in, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13,1);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  //welcome display
  display.clearDisplay();
  display.drawFastHLine(0,1,127,WHITE);
  display.drawFastHLine(0,31,127,WHITE);
  display.drawFastVLine(0,1,31,WHITE);
  display.drawFastVLine(127,1,31,WHITE);
  display.setCursor(15,5);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("STRESS MANAGEMENT");
  display.setCursor(60,19);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("KIT");
  display.display();
  delay(3000);
  display.clearDisplay();
}


void loop() 
{ 
  if(x>127)  
  {
    display.clearDisplay();
    x=0;
    lastx=x;
  }
  gsr =analogRead(A0);
  gsr =(5.0*gsr)/1023.0;
  int value=analogRead(A1);
  ecg=map(value,0,1023,0,500);
  display.setTextColor(WHITE);
  y=map(value,1023,0,20,29);
  display.drawFastHLine(0,1,127,WHITE);
  display.drawFastHLine(0,31,127,WHITE);
  display.drawFastVLine(0,1,30,WHITE);
  display.drawFastVLine(127,1,30,WHITE);
  display.writeLine(lastx,lasty,x,y,WHITE);
  display.setCursor(70,5);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("GSR:");
  display.setCursor(95,5);
  display.setTextSize(1);
  display.setTextColor(WHITE,BLACK);
  display.print(gsr);
  if(lastrate > 100 && rate < 100)
  {
    display.writeFillRect(35,5,30,7,BLACK);
  }
  else
  {
  display.setCursor(10,5);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("BPM:");
  display.setCursor(35,5);
  display.setTextSize(1);
  display.setTextColor(WHITE,BLACK);
  display.print(rate);
  }
  display.display();
  lastrate=rate;
  lasty=y;
  lastx=x;
  x++;
  l=0;
    while(l<5)
    {
     if(digitalRead(in))
     {
      if(l==0)
      time1=millis();
      l++;
      while(digitalRead(in));
     }
    }
      time2=millis();
      rate=time2-time1;
      rate=rate/5;
      rate=60000/rate;
      if(rate > 200)
      {
      rate=0;
      }
      if(rate > 100 && gsr > 1 && gsr < 3)
       digitalWrite(13,0);
      else
       digitalWrite(13,1);
  String data ="hb="+String(rate)+ "&gsr=" + String(gsr)+ "&ecg=" + String(ecg);
  Serial.println(data);
}
