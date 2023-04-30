#include <SPI.h>
#include <SD.h>

File myFile;

bool playing = true;
unsigned char data;

void setup()
{
  pinMode(6, OUTPUT);
  TCCR0B = 0x01; // Sets the PWM frequency to 64KHz in pins 5 and 6.

  SD.begin(10);
  myFile = SD.open("doong.wav", FILE_READ);

  for (int count = 0; count < 128; count++) data = myFile.read();
}

void loop()
{
  data = myFile.read();
  analogWrite(6, data);

  delay(3);
}
