#include "U8glib.h"
U8GLIB_ST7920_128X64 u8g(13,11,10,U8G_PIN_NONE);
char Current_string[5];
char Total_string[5];

int count=0;
void draw(void) {
  int x=10;
  int Current =x;
  // graphic commands to redraw the complete screen should be placed here  
  
  // assign default font
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
   u8g.drawStr(0,50, F("T.F.="));
   u8g.drawStr(0,63, F("Limit.="));
   dtostrf(Current, 3, 0, Current_string);
  u8g.drawStr(22,50, Current_string);
  
  // of course, the F() macro can be used directly
  u8g.undoScale();  
}
void setup(void) {
}

void loop(void) {
  
    u8g.firstPage();  
    do {
      draw();
    } while( u8g.nextPage() );
  // rebuild the picture after some delay
  delay(500);
}

