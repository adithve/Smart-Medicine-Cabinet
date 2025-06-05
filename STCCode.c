#include <DS3231.h>  
#include <LiquidCrystal.h>  
#include <LiquidCrystal_I2C.h>  
#include <Stepper.h> 
int styear; 
int stmon; 
int stdate; 
int sthour; 
int stsec; 
int buzzer = 3; 
DS3231 rtc(SDA, SCL); 
Time t; 
LiquidCrystal_I2C lcd(0x27, 16, 2); 
int motorSpeed =10; 
Stepper myStepper(2048, 8,10,9,11); 
void setup ()  
{ 
rtc.begin (); 
Serial.begin (9600); 
lcd.init(); 
//rtc.setDate(19, 7,2023); 
//rtc.setTime (14,14,00) ; 
//rtc.setDOW (WEDNESDAY) ; 
lcd.backlight(); 
pinMode(buzzer,OUTPUT); 
} 
void loop ()  
{ 
lcd.clear(); 
lcd.backlight(); 
t=rtc.getTime () ; 
lcd.setCursor(0, 0); 
lcd.print ("Date:"); 
lcd.print (t.date); 
lcd.print ("-"); 
lcd.print (t.mon);  
lcd.print ("-"); 
lcd.println (t.year); 
lcd.setCursor(0, 1); 
lcd.print ("Time:");   
lcd.print (t.hour); 
lcd.print (":"); 
lcd.print (t.min); 
lcd.print (":"); 
lcd.println (t.sec); 
delay (1000) ; 
if(t.hour==20 && t.min == 40 && t.sec==0) 
//if(t.sec%10==0)//(t.hour==19 && t.min == 11 && t.sec == 0)//t.hour == 7 && t.min == 30|| 
t.hour == 19 
//t.date == 20 && t.hour ==7 && t.min == 30  
{ 
digitalWrite(buzzer,HIGH); 
rotatStepper(); 
delay(1000); 
digitalWrite(buzzer,LOW); 
} 
} 
void rotatStepper() 
{ 
myStepper.setSpeed(motorSpeed); 
myStepper.step(256); 
delay(1000); 
myStepper.step(-256); 
delay(1000); 
}