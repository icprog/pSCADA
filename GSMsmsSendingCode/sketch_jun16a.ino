#include <SoftwareSerial.h>
SoftwareSerial SIM900(12, 13);
float outputValue = 12;
int gsmCount;  
int newOut;
float cumm12;
int gsmboot;
void setup() {
  // put your setup code here, to run once:
  SIM900.begin(9600);
  Serial.begin(9600);
}

void loop() {
  gsmCount++;
  // put your main code here, to run repeatedly:
if(gsmCount==1)
             {
                 SIM900.println("AT+CSQ");  
                 ShowSerialData();
                  delay(1000);
             }
             if(gsmCount==2){
              SIM900.println("AT+CGATT?");
              ShowSerialData();
               delay(1000);
             }
             if(gsmCount==3){
              SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
              ShowSerialData();
               delay(1000);
             }
             if(gsmCount==4){
              SIM900.println("AT+SAPBR=3,1,\"APN\",\"airtelgprs.com\"");
              ShowSerialData();  
               delay(1000);            
              }
             if(gsmCount==5){
               SIM900.println("AT+SAPBR=1,1");
               ShowSerialData();
                delay(1000);                
              }
             if(gsmCount==6){
              SIM900.println("AT+HTTPINIT");
              ShowSerialData(); 
               delay(1000);
              }
             if(gsmCount==7 ){
                if(outputValue>0)
                {
                  
                  outputValue= newOut;
                  }
                int id_panel = 8890;
                
                int ups = 1;
                int door = 1;
                int current_flow = newOut;
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
                ShowSerialData(); 
                gsmCount=0;
                delay(1000);
              }
               if(gsmboot==600)  
              {
                SIM900.println("AT+CPOWD=0");//submit the request
                ShowSerialData(); 
                gsmboot=0;
                delay(1000);
              }
}
void ShowSerialData()
{
  while (SIM900.available() != 0)
    Serial.write(char (SIM900.read()));
}
