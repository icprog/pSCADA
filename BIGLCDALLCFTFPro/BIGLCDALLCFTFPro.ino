#include "U8glib.h"
U8GLIB_ST7920_128X64 u8g(13,11,10,U8G_PIN_NONE);
char Current_string[5];
char Total_string[5];
char Limit_string[5];

int count=0;
void draw(int l) {
  
  float Current =l;
  float Total = l;
  float Limit = l;

  //u8g.setFont(u8g_font_unifont);
  u8g.setFont (u8g_font_6x12);
  // pointer to strings in flash memory can be stored in a special type
  const __FlashStringHelper *flash_ptr;
  
  // the result of the F() macro can be assigned to this pointer
  flash_ptr = F("VISION WORLD TECH");
  
  
  // this pointer can be used as argument to the draw procedures
 // u8g.drawStr( 0+1, 20+1, flash_ptr);
  u8g.drawStr( 0, 10, flash_ptr);
  
  u8g.drawStr( 20, 25, F("PVT.LTD.(JAIPUR)"));
   u8g.drawHLine(0, 25, 140);
   
   
   u8g.drawStr(0,37, F("C.F.="));
   dtostrf(Current, 3, 0, Current_string);
   u8g.drawStr(30,37, Current_string);
   
   u8g.drawStr(0,50, F("T.F.="));
   dtostrf(Total, 3, 0, Total_string);
   u8g.drawStr(30,50, Total_string);

   
   u8g.drawStr(0,63, F("Limit.="));
   dtostrf(Limit, 3, 0, Limit_string);
   u8g.drawStr(40,63, Limit_string);
   
   
  
  // of course, the F() macro can be used directly
  u8g.undoScale();  
}
void setup(void) {
}

void loop(void) {
  float x =10000;
    u8g.firstPage();  
    do {
      draw(x);
    } while( u8g.nextPage() );
  // rebuild the picture after some delay
  delay(500);
}

