/*
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
|                                                               getAddressEx.ino                                                                |
|                                                               SPIFRAM library                                                                 |
|                                                                   v 1.0.0                                                                     |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
|                                                                    Marzogh                                                                    |
|                                                                  16.11.2016                                                                   |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
|                                                                                                                                               |
|                                  This program shows the method to use the getAddress() function to automate                                   |
|                                the process of address allocation when using a fram memory module. Please note                                |
|                                         the special function used to get the size of the String object.                                       |
|                                                                                                                                               |
|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
*/
#include<SPIFRAM.h>
#define CHIPSIZE KB64

#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
// Required for Serial on Zero based boards
#define Serial SERIAL_PORT_USBVIRTUAL
#endif

#if defined (SIMBLEE)
#define BAUD_RATE 250000
#else
#define BAUD_RATE 115200
#endif

#define arrayLen(x) sizeof(x)/sizeof(x[0])
uint32_t strAddr[3], floatAddr[2], byteAddr[4];
String testStr[] = {
  "Test String 0",
  "Test String 1",
  "Test String 2"
};
float testFloat[] = {
  3.1415, 6.283
};
byte testByte[] = {
  3, 245, 84, 100
};

SPIFRAM fram;

void getAddresses();
void writeData();

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.print(F("Initialising fram memory"));
  for (int i = 0; i < 10; ++i)
  {
    Serial.print(F("."));
  }
  Serial.println();
  fram.begin(CHIPSIZE);
  Serial.println();
  Serial.println();

  getAddresses();
  writeData();
  fram.eraseChip();
}

void loop() {

}

// Function to get adresses for various variables
void getAddresses() {
  for (uint8_t i = 0; i < arrayLen(byteAddr); i++) {
    byteAddr[i] = fram.getAddress(sizeof(byte));
    Serial.print("Byte Address ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(byteAddr[i]);
  }

  for (uint8_t i = 0; i < arrayLen(floatAddr); i++) {
    floatAddr[i] = fram.getAddress(sizeof(float));
    Serial.print("Float Address ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(floatAddr[i]);
  }

  for (uint8_t i = 0; i < arrayLen(strAddr); i++) {
    strAddr[i] = fram.getAddress(fram.sizeofStr(testStr[i]));
    Serial.print("String Address ");
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(strAddr[i]);
  }
}

// Function to write data
void writeData() {
  for (uint8_t i = 0; i < arrayLen(byteAddr); i++) {
    if (fram.writeByte(byteAddr[i], testByte[i])) {
      Serial.print(testByte[i]);
      Serial.print(" written to ");
      Serial.println(byteAddr[i]);
    }
  }

  for (uint8_t i = 0; i < arrayLen(floatAddr); i++) {
    if (fram.writeFloat(floatAddr[i], testFloat[i])) {
      Serial.print(testFloat[i]);
      Serial.print(" written to ");
      Serial.println(floatAddr[i]);
    }
  }

  for (uint8_t i = 0; i < arrayLen(strAddr); i++) {
    if (fram.writeStr(strAddr[i], testStr[i])) {
      Serial.print(testStr[i]);
      Serial.print(" written to ");
      Serial.println(strAddr[i]);
    }
  }
}
