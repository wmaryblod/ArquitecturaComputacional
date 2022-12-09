//
//    FILE: dht11_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 1.0.0
// PURPOSE: DHT library test sketch for DHT11 && Arduino
//     URL: https://github.com/RobTillaart/DHTstable
//
//  HISTORY:
//  1.0.0   2021-05-26  class name changed to DHTStable  (breaking change)
//
//  0.2.0   use getHumidity() and getTemperature()
//  0.1.2   add URL in header


#include "DHTStable.h"
#include <LiquidCrystal.h>

DHTStable DHT;

#define DHT11_PIN 22

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  lcd.begin(16, 2);
  
  lcd.print("HUME:");
  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHTSTABLE_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperatura (%), \tLED ");
}


void loop()
{
  // READ DATA
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
      Serial.print("OK,\t"); 
      break;
    case DHTLIB_ERROR_CHECKSUM: 
      Serial.print("Checksum error,\t"); 
      break;
    case DHTLIB_ERROR_TIMEOUT: 
      Serial.print("Time out error,\t"); 
      break;
    default: 
      Serial.print("Unknown error,\t"); 
      break;
  }
  // DISPLAY DATA
  Serial.print(DHT.getHumidity(), 1);
  Serial.print(", \t\t");
  Serial.print(DHT.getTemperature(), 1);
  Serial.print(", \t\t\t");
  if(DHT.getTemperature()>29){
    Serial.print("RED");
  }else if (DHT.getTemperature()<26){
    Serial.print("BLUE");
  }else{
    Serial.print("GREEN");
  }
  Serial.println("");
  lcd.setCursor(0, 0);
  lcd.print("TEMP:");
  lcd.print(DHT.getTemperature(),1);
  lcd.setCursor(0, 1);
  lcd.print("HUME:");
  lcd.print(DHT.getHumidity(),1);
  delay(2000);
}

