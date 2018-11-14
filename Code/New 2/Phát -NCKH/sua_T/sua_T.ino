
#include <SPI.h>
#include "RF24.h"

// Xac dinh radio la radio phat
//bool radioNumber = 1;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);

byte addresses[][6] = {"1Node","2Node"};

// Used to control whether this node is sending or receiving
//bool role = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("CAM BIEN DO AM + RADIO PHAT"));
  //Serial.println(F("*** AN 'T' DE BAT DAU QUA TRINH CHUYEN GIU LIEU *** "));
  pinMode (2, INPUT);
  pinMode(A0, INPUT);
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  /*if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }*/
  
  // Start the radio listening for data
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  //radio.startListening();
  Serial.println(F("Bat dau gui"));
}

void loop() {
  radio.stopListening();                                    // First, stop listening so we can talk.
  long value = analogRead(A0);     // Ta sẽ đọc giá trị hiệu điện thế của cảm biến
                                      // Giá trị được số hóa thành 1 số nguyên có giá trị
                                      // trong khoảng từ 0 đến 1023
  Serial.print("Do am do duoc tren cay la: ");
  Serial.println(value);//Xuất ra serial Monitor                   
  delay(10);
  
  long start_time = value;                             // Take the time, and send it.  This will block until complete
  if (!radio.write( &start_time, sizeof(long) )){
    Serial.println(F("LOI"));
  }
  else{
     Serial.println(F("OK"));
  }
  
  //radio.startListening();                                    // Now, continue listening
  
  /*unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
  boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
  
  while ( ! radio.available() ){                             // While nothing is received
      if (micros() - started_waiting_at > 200000 ){            // If waited longer than 200ms, indicate timeout and exit while loop
          timeout = true;
          break;
      }      
  }
  
  if ( timeout ){
    Serial.println(F("LOI , KHONG KET NOI DUOC VOI RADIO THU."));
    } else {
        unsigned long got_time;                                 // Grab the response, compare, and send to debugging spew
        radio.read( &got_time, sizeof(unsigned long) );
        unsigned long end_time = micros();
      }*/
   // Try again 1s later
   delay(1000);
} 


  /*if ( Serial.available() )
  {
    char c = toupper(Serial.read());
    if ( c == 'T' && role == 0 ){      
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      role = 1;                  // Become the primary transmitter (ping out)
    
   }else
    if ( c == 'R' && role == 1 ){
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));      
       role = 0;                // Become the primary receiver (pong back)
       radio.startListening();
       
    }
  }*/
 


 
