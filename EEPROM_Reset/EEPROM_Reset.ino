#include <EEPROM.h>
int SecEEP = 2;
int MinEEP = 8;
int HrEEP = 7;
int FlowEEP = 4;
void setup() {
    Serial.begin(9600);
  // put your setup code here, to run once:
     EEPROM.write(SecEEP, 0); //Reset Sec
     EEPROM.write(FlowEEP, 0); // Reset Flow
     EEPROM.write(MinEEP, 0); //Reset min
     EEPROM.write(HrEEP, 0); // Reset hour
}

void loop() {
  // put your main code here, to run repeatedly:
  int secE = EEPROM.read(SecEEP);
  int minE = EEPROM.read(MinEEP);
  int hrE = EEPROM.read(HrEEP);
  int flowE = EEPROM.read(FlowEEP);


  Serial.print("Seconds :");
  Serial.println(secE);
  Serial.print("Minute :");
  Serial.println(minE);
  Serial.print("Hour :");
  Serial.println(hrE);
  Serial.print("Flow :");
  Serial.println(flowE);
  delay(1000);
  
}
