#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>
/*int BUTTON =2;
boolean current_Button = LOW;
boolean last_Button = LOW;
*/
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
#define microphone_pin A0
TMRpcm audio;   // create an object for use in this sketch 

void setup() {

  //pinMode(BUTTON, INPUT);
  pinMode(12,OUTPUT);  //Pin pairs: 9,10 Mega: 5-2,6-7,11-12,46-45
  
  Serial.begin(9600);
  
  if (!SD.begin(SD_ChipSelectPin)) {  
    Serial.println("sd 연결에 실패하였습니다."); 
    return;
  }else{
    Serial.println("SD 연결에 성공하였습니다."); 
  }
  
  audio.CSPin = SD_ChipSelectPin;
}


void loop() {
    //current_Button =  digitalRead(BUTTON);
    if(Serial.available()){                          //Send commands over serial to play
      switch(Serial.read()){
        case 'r': audio.startRecording("doong.wav",16000,microphone_pin); Serial.println("녹음을 시작합니다."); break;    //Record at 16khz sample rate on pin A0
        case 's': audio.stopRecording("doong.wav"); Serial.println("녹음을 종료합니다."); break;              //Stop recording
      }
    }
}
