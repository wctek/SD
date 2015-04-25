/*
  SD card basic file example
 
 This example shows how to create and destroy an SD card file 	
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 5
 
 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified for Piccolino by Alex Sardo 19 Mar 2015
 
 This example code is in the public domain.
 	 
 */
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Piccolino_RAM.h>
#include <Piccolino_OLED_SRAM.h>

File root;
Piccolino_OLED_SRAM display;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  display.begin();
  display.clear();
  display.setCursor(0,0);
    

  Serial.print(F("Initializing SD card..."));

  if (!SD.begin(5)) {
    Serial.println(F("initialization failed!"));
    return;
  }
  Serial.println(F("initialization done."));

  root = SD.open("/");
  
  printDirectory(root, 0);
  
  Serial.println(F("done!"));
}

void loop()
{
  // nothing happens after setup finishes.
}

void printDirectory(File dir, int numTabs) {  

    while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
       display.print(" ");
     }
     Serial.print(entry.name());
     display.print(entry.name());
     
     if (entry.isDirectory()) {
       Serial.println("/");       
       display.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       display.print("  ");
       Serial.println(entry.size(), DEC);
       display.println(entry.size(), DEC);
     }
     entry.close();
     
     display.update();
   }
}



