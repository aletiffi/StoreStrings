#include "Arduino.h"
#include "StoreStrings.h"
#include "EEPROM.h"

StoreStrings::StoreStrings(int size)
{
  _eepromSize = size;
  EEPROM.begin(_eepromSize);
}

String StoreStrings::read(int start_addr, int end_addr)
{

  if (start_addr >= 0 && start_addr < _eepromSize){
    _ReadAddress = start_addr;
    String value = "";

    while (_ReadAddress < start_addr + end_addr && _ReadAddress < _eepromSize && char(EEPROM.read(_ReadAddress)) != _null) {
      value += char(EEPROM.read(_ReadAddress));
      _ReadAddress++;
    }
    _ReadAddress++;
    _ReadAddressPre = _ReadAddress;
    return value;

  } else {
    Serial.println("Start address must be >= 0 and <" + String(_eepromSize));
    _ReadAddress = _ReadAddressPre;
    return String(_null);
  }
}

void StoreStrings::resetReadCounter()
{
  _ReadAddress = 0;
  _ReadAddressPre = 0;
}

bool StoreStrings::write(int start_addr, String val)
{
  if (start_addr >= 0 && start_addr < _eepromSize){
    _WriteAddress = start_addr;
    val += _null;

    for (int i=0; i<val.length(); i++){
      if(_WriteAddress < _eepromSize){
        if(char(EEPROM.read(_WriteAddress)) != val.charAt(i)){
          EEPROM.write(_WriteAddress, val.charAt(i));
          EEPROM.commit();
        }
        _WriteAddress ++;
      } else {
        Serial.println("EEPROM Full");
        _WriteAddress = _WriteAddressPre;
        return false;
      }
    }
    _WriteAddressPre = _WriteAddress;
    return true;

  } else {
    Serial.println("Start address must be >= 0 and <" + String(_eepromSize));
    _WriteAddress = _WriteAddressPre;
    return false;
  }
}

void StoreStrings::resetWriteCounter()
{
  _WriteAddress = 0;
  _WriteAddressPre = 0;
}

int StoreStrings::getEepromSize()
{
  return _eepromSize;
}

int StoreStrings::getLastReadedByte()
{
  return _ReadAddress;
}

int StoreStrings::getLastWrittenByte()
{
  return _WriteAddress;
}
