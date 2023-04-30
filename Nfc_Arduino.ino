#include <AddicoreRFID.h>
#include <SPI.h>

#define	uchar	unsigned char
#define	uint	unsigned int

uchar fifobytes;
uchar fifoValue;

AddicoreRFID myRFID; //RFID 모듈 객체 생성

const int chipSelectPin = 10;
const int NRSTPD = 5;

//Maximum length of the array
#define MAX_LEN 16

void setup() {                
   Serial.begin(9600);                       
 
  //SPI library:
  SPI.begin();
  
  pinMode(chipSelectPin,OUTPUT);              // Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin 
    digitalWrite(chipSelectPin, LOW);         // 리더기 활성화: 둥이 몸에 들어갈 거
  pinMode(NRSTPD,OUTPUT);                     // Set digital pin 10 , Not Reset and Power-down
    digitalWrite(NRSTPD, HIGH);

  myRFID.AddicoreRFID_Init();  
}

void loop()
{
  	uchar i, tmp, checksum1;
	uchar status;
        uchar str[MAX_LEN];
        uchar RC_size;
        uchar blockAddr;	//Selection operation block address 0 to 63
        String mynum = "";

        str[1] = 0x4400;
	//Find tags, return tag type
	status = myRFID.AddicoreRFID_Request(PICC_REQIDL, str);	

	//Anti-collision, return tag serial number 4 bytes
	status = myRFID.AddicoreRFID_Anticoll(str);
	if (status == MI_OK)
	{         
            // Should really check all pairs, but for now we'll just use the first
            if(str[0] == 91)//흰색 카드                      
            {
                Serial.println("녹음을 시작합니다.\n");
                //audio.startRecording("test.wav",16000,microphone_pin); Serial.println("recording start");
                
            } else if(str[0] == 234) {//파란색 키             
                Serial.println("재생을 시작합니다.\n");


            }
            Serial.println();
            delay(1000);
	}
		
        myRFID.AddicoreRFID_Halt();		              

}
