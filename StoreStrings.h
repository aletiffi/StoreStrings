#ifndef StoreStrings_h
#define StoreStrings_h

#include "Arduino.h"
#include "EEPROM.h"

class StoreStrings
{
  public:
    StoreStrings(int size);
    String read(int start_addr, int end_addr);
    bool write(int start_addr, String val);
    int getEepromSize();
    void resetReadCounter();
    void resetWriteCounter();
    int getLastReadedByte();
    int getLastWrittenByte();
    
  private:
    int _ReadAddress = 0;
    int _ReadAddressPre = 0;
    int _WriteAddress = 0;
    int _WriteAddressPre = 0;
    int _eepromSize = 0;
    char _null = '\0';
};

#endif
