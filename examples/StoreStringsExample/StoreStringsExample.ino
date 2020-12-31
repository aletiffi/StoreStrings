#include <StoreStrings.h>

#define EEPROM_SIZE   256


String words[] = {
  "Store",
  "Strings",
  "Example", 
  "Sketch"
  };

void setup()
{
  StoreStrings mem(EEPROM_SIZE);
  Serial.begin(115200);
  delay(500);
  print("\nDemo Started");
  print("EEPROM initialized with " + String(mem.getEepromSize()) + " bytes");

  for (int i = 0; i < 4; i++) {
    if(mem.write(mem.getLastWrittenByte(), words[i])){
      print(mem.read(mem.getLastReadedByte(), EEPROM_SIZE));
    } else {
      print("Writing failed!");
    }
  }
}

void loop()
{

}

void print(String val) {
  Serial.println(val);
}