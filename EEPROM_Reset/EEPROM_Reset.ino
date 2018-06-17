#include <EEPROM.h>
int SecEEP = 2;
int MinEEP = 8;
int HrEEP = 7;
int FlowEEP = 4;
void setup() {
  // put your setup code here, to run once:
     EEPROM.write(SecEEP, 0); //Reset Sec
     EEPROM.write(FlowEEP, 0); // Reset Flow
      EEPROM.write(MinEEP, 0); //Reset min
      EEPROM.write(HrEEP, 0); // Reset hour
}

void loop() {
  // put your main code here, to run repeatedly:

}
