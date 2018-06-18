#include <SD.h>
int chipSelect = 53;
File file;
int count1,count3;
int count2 = 0;
String x[8];
int i =0;
float sendTot;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
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

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()==1)
  {
   Serial.println("*****SD Value Add Start Value of Last ToT=********");
      SD.remove("file.txt");
      file = SD.open("file.txt", FILE_WRITE); // open "file.txt" to write data
      if (file) 
      {
        float number = 0; // generate random number between 0 and 9
        file.println(number); // write number to file
        file.close(); // close file
        Serial.print("Wrote number: "); // debug output: show written number in serial monitor
        Serial.println(number);
        Serial.println("Value Reset");
      }
      delay(1000);
  }
  else 
  {
    Serial.println("Enter Value in Serial Monitor");
    delay(1000);
  }
}
