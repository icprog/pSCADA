#include <SoftwareSerial.h>
SoftwareSerial SIM900(12, 13);
#include "U8glib.h"
U8GLIB_ST7920_128X64 u8g(8,7,6,U8G_PIN_NONE);
#include <EEPROM.h>
//-------------SD Card Header(50,51,52,53(CS))---------------
#include <SD.h>
int chipSelect = 53;
File file;
int i =0;
String x[8];
int count1,count3;
int count2 = 0;
float newOut=0;
float cumm03;
int l_scada;
//------------------------------------------
#include<Wire.h>
//----------------------RTC Header-------------------------------
#include "RTClib.h"
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
//-------------------------LCD Header ------------------------

//----------------------------------------------------------
int mains = 2;
int door = 3;
float count;
float outputValue;        // value of Flow Meter
float tsec;
float test;
float ltSec;
float cumm3;
float countMin = 1;
float countHr = 0;
float countDay = 0;
int sw = 48;
int SecEEP = 2;
int MinEEP = 8;
int HrEEP = 7;
int FlowEEP = 4;
int sdStart =0;
int SDwrite=0;
float sendTot;

int gsmCount = 0; 
float cumm12,cumm9;
float cf=0;
int gsmboot=1;
float testcumm;
//********************
  
  //String stringone = "AT+HTTPPARA=\"URL\",\"http://visionworldtech.com/Video/select.php?";
  //String paliString = "AT+HTTPPARA=\"URL\",\"http://tele.responseinfoway.com/daserver.ASPX?mid=3&";
  
  // String d = "director=";
  //String nu = "num=";
  //String tm = "time=";
  
//********************BIG LCD Char****************
char Current_string[5];
char Total_string[5];
char Limit_string[5];
///*************************************************
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void draw(float c,float t, float l) {
  
  float Current =c;
  float Total = t;
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
   dtostrf(Total, 3, 3, Total_string);
   u8g.drawStr(30,50, Total_string);

   
   u8g.drawStr(0,63, F("Limit.="));
   dtostrf(Limit, 3, 0, Limit_string);
   u8g.drawStr(40,63, Limit_string);
   u8g.undoScale();  
}

void setup() {
  gsmCount=0;
  pinMode(sw, INPUT);
  pinMode(mains, INPUT);
  pinMode(door, INPUT);
  pinMode(chipSelect,OUTPUT);
  SIM900.begin(9600);
  Serial.begin(9600);
  countMin = EEPROM.read(MinEEP);
  count = EEPROM.read(SecEEP);
  countHr = EEPROM.read(HrEEP);
 
  float sec = EEPROM.read(SecEEP);
  float minut = EEPROM.read(MinEEP);
  float cflow = EEPROM.read(FlowEEP);
  float hr = EEPROM.read(HrEEP);
  tsec = (sec + minut * 60 + hr * 60 * 60) * cflow;
  Serial.print("Tsec Value = ");
  Serial.println(tsec);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  if (!SD.begin(chipSelect)) { // Initialize SD card
    Serial.println("Could not initialize SD card."); // if return value is false, something went wrong.
  }
  //=================================Extracting Value from SD Card================================
    Serial.println("*****SD Value Extracting Start********");
    file = SD.open("file.txt", FILE_READ); // open "file.txt" to read data
    if (file) {
    Serial.println("--- Reading start ---");
    char character;
    while ((character = file.read()) != -1 ) 
    { // this while loop reads data stored in "file.txt" and prints it to serial monitor
      Serial.print ("Character Value= ");
      Serial.println(character-'0');
      count1 = count1 +1;
      if(character-'0' == -2)
      { 
          count2 = 1;
          count3 = count1;
          count1 =0;
          Serial.println("Else Loop");  
      }
      else if(count2 != 1 )
      {
        x[i] = character-'0';
        i++;  
        Serial.println("Program Run");
      }           
    }    
    count1=0;
    
    Serial.print("Total Digit");
    Serial.println(count3);
    if(count3 == 1)
    {
      String t = x[0];
      Serial.println(t);
      float s= t.toFloat();
      Serial.print("Totalizer1 Value is :");
      
      sendTot= s ;
      Serial.println(sendTot);
      count3=0;
    }
    else if(count3==2)
    {
      String t = x[0]+x[1];
      Serial.println(t);
      float s= t.toFloat();
      Serial.print("Totalizer2 Value is :");
      
      sendTot= s ;
      Serial.println(sendTot);
      count3=0;
    }
    else if(count3==3)
    {
      String t = x[0]+x[1]+x[2];
      Serial.println(t);
      float s= t.toFloat();
      Serial.print("Totalizer3 Value is :");
      
      sendTot= s ;
      Serial.println(sendTot);
      count3=0;
    }
    else if(count3==4)
    {
      String t = x[0]+x[1]+x[2]+x[3];
      Serial.println(t);
      float s= t.toFloat();
      Serial.print("Totalizer4 Value is :");
      
      sendTot= s ;
      Serial.println(sendTot);
      count3=0;
    }
    else if(count3==5)
    {
      String t = x[0]+x[1]+x[2]+x[3]+x[4];
      Serial.println(t);
      float s= t.toFloat();
      Serial.print("Totalizer5 Value is :");
      
      sendTot= s ;
      Serial.println(sendTot);
      count3=0;
    }
    else if(count3==6)
    {
      String t = x[0]+x[1]+x[2]+x[3]+x[4]+x[5];
      Serial.println(t);
      float s= t.toFloat();
      Serial.print("Totalizer6 Value is :");
      
      sendTot= s ;
      Serial.println(sendTot);
      count3=0;
    }
     else if(count3==7)
    {
      String t = x[0]+x[1]+x[2]+x[3]+x[4]+x[5]+x[6];
      Serial.println(t);
      float s= t.toFloat();
      Serial.print("Totalizer7 Value is :");
      
      sendTot =s;
      Serial.println(sendTot);
      count3=0;
    }
    else if(count3==8)
    {
      String t = x[0]+x[1]+x[2]+x[3]+x[4]+x[5]+x[6]+x[7];
      Serial.println(t);
      float s= t.toFloat();
      Serial.print("Totalizer8 Value is :");
      
      sendTot =s;
      Serial.println(sendTot);
      count3=0;
    }   
    count2= 0;  
    //SD.remove("file.txt");
    file.close();
    Serial.println("*****SD Value Extracting END********");
    }
    
    u8g.firstPage();  
    do {
      draw(outputValue,tsec,l_scada);
    } while( u8g.nextPage() );
    delay(10);
    
    outputValue=0;
    
 }
void loop()
{  
  gsmCount++;  
  gsmboot++;
  int rst = 0;
  //-------------------------------- Calculations SCADA -----------------------
  DateTime now = rtc.now();
  float sensorValue = analogRead(A1);
  outputValue = mapfloat(sensorValue,220,1056, 0,21); // 21
  Serial.print("SensorValue ");
  Serial.println(sensorValue);
  Serial.print("OutputValue ");
  Serial.println(outputValue);
  Serial.print("Tsec ");
  Serial.println(tsec);
  Serial.print("SendToto ");
  Serial.println(sendTot); 
  if (now.hour() == 23 && now.minute() == 59  && now.second() == 59)
  {
    Serial.println("Reset");
    tsec = 0;
    EEPROM.write(SecEEP, 0); //Reset Sec
    EEPROM.write(FlowEEP, 0); // Reset Flow
    EEPROM.write(MinEEP, 0); //Reset min
    EEPROM.write(HrEEP, 0); // Reset hour
  }   
  if(gsmCount==1)
  {
     SIM900.println("AT+CSQ");  
     ShowSerialData();
     delay(1000);
  }
  if(gsmCount==2)
  {
    SIM900.println("AT+CGATT?");
    ShowSerialData();
     delay(1000);
  }
  if(gsmCount==3)
  {
    SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
    ShowSerialData();
    delay(1000);
  }
  if(gsmCount==4)
  {
    SIM900.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");
    ShowSerialData();  
    delay(1000);            
  }
  if(gsmCount==5)
  {
     SIM900.println("AT+SAPBR=1,1");
     ShowSerialData();
     delay(1000);                
  }
  if(gsmCount==6)
  {
    SIM900.println("AT+HTTPINIT");
    ShowSerialData(); 
    delay(1000);
  }
  if(gsmCount==7)
  {
    
    int id_panel = 889;      
    int ups = 1;
    int door = 1;
    int current_flow ;
    if(outputValue>0)
    {
      current_flow= outputValue;
      
    }
    if(outputValue<0)
    {
      current_flow= 0;      
    }
    
    int total_flow = cumm12 * 100;
    int panel_lock = 0;
    int main = 1;
    int pump = 1 ;
    int auto_main = 1;
    int fc = 1;
    int water_level = 0;
    int water_level2 = 0 ;
    
    String paliString = "AT+HTTPPARA=\"URL\",\"http://59.90.174.164/MICROSCADA/DASERVER.ASPX?";

    String ID = "ID=";
    String A = "A=";
    String B = "B=";
    String C = "C=";
    String D = "D=";
    String E = "E=";
    String F = "F=";
    String G = "G=";
    String H = "H=";
    String I = "I=";
    String J = "J=";
    String K = "K=";
    String s = "&";
    String slash = " \0";
    String stringPali = paliString + ID + id_panel + s + A + ups + s + B + door + s + C + current_flow + s + D + total_flow + s + E + panel_lock + s + F + main + s + G + pump + s + H + auto_main + s + I + fc + s + J + water_level + s + K + water_level2 + slash;
    SIM900.println(stringPali);   
    delay(1000);
   }
   if(gsmCount==8)  
   {
    SIM900.println("AT+HTTPACTION=0");//submit the request
      delay(2000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
      //while(!SIM900.available());
      ShowSerialData();
      SIM900.println("AT+HTTPREAD");// read the data from the website you access
      delay(100);
      changeLed();//
      ShowSerialData();
      SIM900.println("");
      //delay(100);
      gsmCount=0;
     }
   
   if(gsmboot==600)  
   {
    SIM900.println("AT+CPOWD=0");//submit the request
    ShowSerialData(); 
    gsmboot=0;
    delay(1000);
   }    
   if (outputValue<=0)
   {
      cumm03 = (tsec * 0.0099999988)/10; 
      newOut=0;
          u8g.firstPage();  
        do {
          draw(0,cumm03,l_scada);
        } while( u8g.nextPage() );
        delay(10);
   }
   if(outputValue>0)
   {
      float testValue = outputValue * 100; // 5400
      float ltSec = testValue / 360; // 5.833 Curretn Flow 15
      tsec = ltSec + tsec; // tsec = 46.66+23.33
      sendTot = ltSec +sendTot;
      cumm3 = (tsec * 0.0099999988)/10;   
      // cumm03 = (tsec * 0.0099999988)/10;     
      cumm9 = sendTot * 0.0099999988;
      cumm12 = (cumm9/10);
      u8g.firstPage();  
        do {
          draw(outputValue,cumm3,l_scada);
        } while( u8g.nextPage() );
      
      //==================================Send Value in SD Card==============
      Serial.println("*****SD Value Add Start Value of Last ToT=********");
      SD.remove("file.txt");
      file = SD.open("file.txt", FILE_WRITE); // open "file.txt" to write data
      if (file) 
      {
        float number = sendTot; // generate random number between 0 and 9
        file.println(number); // write number to file
        file.close(); // close file
        Serial.print("Wrote number: "); // debug output: show written number in serial monitor
        Serial.println(number);
      }

        Serial.print("Cumm3 Value");
        Serial.println(cumm3*100);
      
      delay(10);
      Serial.println("Last LLOp");
      Serial.print("Tsec Value test = ");
      Serial.println(ltSec);
      if (ltSec > 1)
      {
        Serial.println("Testing 1");
        sdStart = 1;
        count = count + 1;
        EEPROM.write(SecEEP, count);
      }
      if (count == 60 && ltSec > 0)
      {
        count = 0;
        EEPROM.write(SecEEP, count);
        countMin = countMin + 1;
        Serial.print("Count Min= ");
        Serial.println(countMin);
        if (countMin == 60)
        {
          countMin = 0;
          countHr = countHr + 1;
          EEPROM.write(HrEEP, countHr);

          if (countHr == 24)
          {
            countDay = countDay + 1;

          }
          Serial.print("Count hr= ");
          Serial.println(countHr);
        }
        EEPROM.write(MinEEP, countMin);
      }
      if (count == 10 && ltSec > 0)
      { 
        EEPROM.write(FlowEEP, ltSec);
      }
        
     }
  Serial.print("Timing : ");      
  Serial.print(now.hour());
  Serial.println("");
  Serial.println(now.minute());
  //*********************************************************************************************************************
}


//void SubmitHttpRequest(float st)
//{   
//  //cumm9 = st * 0.0099999988;
//  //cumm12 = (cumm9 / 10);
//  int m = digitalRead(mains);
//  int d = digitalRead(door);
//  
//  //String stringthree = stringone+n+nam+a+t+txt+a+d+dr+a+nu+num+a+tm+tme+slash;
//  //String stringPali = paliString + ID + id_panel + s + A + ups + s + B + door + s + C + 0 + s + D + total_flow + s + E + panel_lock + s + F + main + s + G + pump + s + H + auto_main + s + I + fc + s + J + water_level + s + K + water_level2 + slash;
//  //Serial.println(stringthree);
//  delay(500);
//  
//  SIM900.println("AT+CSQ"); // Signal quality check
//  delay(100);
//  ShowSerialData();// this code is to show the data from gprs shield, in order to easily see the process of how the gprs shield submit a http request, and the following is for this purpose too.
//  SIM900.println("AT+CGATT?"); //Attach or Detach from GPRS Support
//  delay(100);
//  ShowSerialData();
//  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");//setting the SAPBR, the connection type is using gprs
//  delay(1000);
//  ShowSerialData();
//  SIM900.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");//setting the APN, Access point name string
//  delay(1000);
//  ShowSerialData();
//  SIM900.println("AT+SAPBR=1,1");//setting the SAPBR
//  //delay(1000);
//  ShowSerialData();
//  SIM900.println("AT+HTTPINIT"); //init the HTTP request
//  delay(1000);
//  ShowSerialData();
//  
//  //"AT+HTTPPARA=\"URL\",\"http://visionworldtech.com/Video/select.php?name=i&text=Enjoy&director=12&num=56&time=3\""
// // SIM900.println(stringPali);// setting the httppara, the second parameter is the website you want to access
//  ShowSerialData();
//  
//  Serial.print("  T F= ");
//  Serial.println(total_flow);
//
//  delay(1000);
//  SIM900.println("AT+HTTPACTION=0");//submit the request
//  delay(3000);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
//  //while(!SIM900.available());
//  ShowSerialData();
//  SIM900.println("AT+HTTPREAD");// read the data from the website you access
//  delay(1000);
//  //changeLed();//
//  ShowSerialData();
//  SIM900.println("");
//  delay(100);
//
//}
void ShowSerialData()
{
  while (SIM900.available() != 0)
    Serial.write(char (SIM900.read()));
}
void changeLed()
{
  String content = "";
  while (SIM900.available() != 0)
  {
    content = content + String(char (SIM900.read()));
  }
  Serial.println("30 31 is");
  Serial.println(content.substring(32, 35));
  String pstr = content.substring(32,33)+content.substring(33,34)+content.substring(34,35);
  Serial.println(pstr);
  float k= pstr.toFloat();
  if(k>0)
  l_scada=k;
  
  content = "";
}
