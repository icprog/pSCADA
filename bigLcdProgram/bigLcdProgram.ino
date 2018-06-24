#include <SoftwareSerial.h>
SoftwareSerial SIM900(8, 9);
#include "U8glib.h"
U8GLIB_ST7920_128X64 u8g(13,11,10,U8G_PIN_NONE);
 // configure software serial port
int mains = 2;
int door = 3;

int sw=7;
int sw1=A0;
int Current;
int Total=0;
int count=0;
char Current_string[5];
char Total_string[5];


void draw(int test){
  Current=analogRead(sw1);
  delay(300);
  //Serial.println(Current);
  Total=Current+Total;
  u8g.setFont (u8g_font_6x12);// Chagne Font size from change 12
  u8g.drawStr( 0,12,"Vision World Tech Pvt");
  u8g.drawStr( 40,24,"Ltd (PALI)");
  u8g.drawFrame(8,26,55,35);            // upper frame
  u8g.drawFrame(70,26,55,35);           // lower frame
 //==== fRO cT AND FT
  u8g.setFont (u8g_font_6x12);
  u8g.drawStr(17,37,"C.FLOW");
  u8g.drawStr(80,37,"T.FLOW");
  dtostrf(Current, 3, 0, Current_string);
  u8g.drawStr(20,50, Current_string);
  dtostrf(Total,13,0, Total_string);
  u8g.drawStr(40,50, test_string); 
}


void setup() {     
  
  
  pinMode(mains,INPUT);
  pinMode(door,INPUT);
  SIM900.begin(19200);
  Serial.begin(19200); 
  Serial.print("power up" );
  delay(3000); 
}

void loop()
{
  int x = 10;
  
  delay(1000);
  u8g.firstPage();  
  do {
    draw(x);
  } while( u8g.nextPage() );
   
    
}


