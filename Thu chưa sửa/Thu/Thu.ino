
#include <SPI.h>
#include "RF24.h"

//set lam radio thu
bool radioNumber = 0;
RF24 radio(7,8);
byte addresses[][6] = {"1Node","2Node"};
//dia chi cho radio thuu
bool role = 0;
//set chuong trinh cho cam bien Hall
int pushButton = 2;
//cac tham so cua do am
const float a=200;
const float b=400;
const float c=600,d=800,e=1000;
//cac tham so cua luong nuoc
const float v=200,y=400,z=600,t=800,k=1000;
float luongnuoc;
int st;
int dem;
float tb;
int solanthaydoitrangthai=0;
int trangthaihientai;
int trangthaitruoc;
void setup() {
  Serial.begin(115200);
  Serial.println(F("CAM BIEN DO AM + RADIO THU"));
  pinMode(pushButton,INPUT);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  radio.startListening();
  st=0; //trang thai doi
  dem=0;
  tb=0;
  //van
  pinMode (2,OUTPUT);
  //cambienHALL
  pinMode (3,INPUT);
}
float ratcao(float x,float a, float b,float c,float d,float e){
	if(0<x && x<=a){
		return 1.0;
		} else if(a<x && x<b){
			return (b-x)/(b-a);
			} else {
				return 0.0;
				}
    }
float cao(float x,float a, float b,float c,float d,float e){
	if(x<=a){
		return 0.0;
		} else if(a<x && x<=b){
			return (x-a)/(b-a);
			}else if(b<x && x<c){
				return (c-x)/(c-b);
				}else {
					return 0.0;
				}
}
float trungbinh(float x,float a, float b,float c,float d,float e){
	if(x<=b){
		return 0.0;
		}else if(b<x && x<=c){
			return (x-b)/(c-b);
			}else if(c<x && x<d){
				return (d-x)/(d-c);
				}else {
					return 0.0;
					}
}
float thap(float x,float a, float b,float c,float d,float e){
	if(x<=c){
		return 0.0;
		}else if(c<x && x<=d){
			return (x-c)/(d-c);
			}else if(d<x && x<e){
				return (e-x)/(e-d);
				}else {
					return 0.0;
					}
}
float ratthap(float x,float a, float b,float c,float d,float e){
	if(x<=d){
		return 0.0;
		} else if(d<x && x<e){
			return (x-d)/(e-d);
			} else {
				return 1.0;
				}
}
void loop() {
  //kiem tra gio de chuyen st=0 sang st=1
  st=1;
  
   
  if(st==1){
    float x;
    if( radio.available()){
        while (radio.available()) {                                 
        radio.read( &x, sizeof(float) );           
    }
    dem++;
    tb+=x;
    if( dem>=10 ){
    st=2;
    dem=0;
    tb=tb/10;
    }
    }
    if(st==2){
    //radio.stopListening();                                        
    //radio.write( &x, sizeof(float) );                 
    //radio.startListening();                                    
    Serial.print(F("Do am duoc nhan la : "));
    Serial.println(tb);
    Serial.println("--------------------\n");
    Serial.println("rat cao = ");Serial.print(ratcao(tb,a,b,c,d,e));
    Serial.println("cao = ");Serial.print(cao(tb,a,b,c,d,e));
    Serial.println("trung binh = ");Serial.print(trungbinh(tb,a,b,c,d,e));
    Serial.println("thap = ");Serial.print(thap(tb,a,b,c,d,e));
    Serial.println("rat thap = ");Serial.print(ratthap(tb,a,b,c,d,e));
    float ratit,it,vua,nhieu,ratnhieu;
    ratit=ratcao(tb,a,b,c,d,e);
    it=cao(tb,a,b,c,d,e);
    vua=trungbinh(tb,a,b,c,d,e);
    nhieu=thap(tb,a,b,c,d,e);
    ratnhieu=ratthap(tb,a,b,c,d,e);
    luongnuoc=(v*ratit+y*it+z*vua+t*nhieu+k*ratnhieu)/(ratit+it+vua+nhieu+ratnhieu);
    Serial.println("luongnuoc= ");Serial.print(luongnuoc);
    st=3;
    tb=0;
    }
    if(st==3){
     digitalWrite(2,HIGH); //relay
     int buttonState = digitalRead(pushButton);
    //Serial.print(buttonState);
    float f;
    f=luongnuoc*450;
    trangthaihientai = buttonState;
    if (trangthaihientai != trangthaitruoc )
    {
    solanthaydoitrangthai++;
    //Serial.println("So lan thay doi trang thai la: ");
    //Serial.println(solanthaydoitrangthai);
    }
    trangthaitruoc=trangthaihientai;
    if(solanthaydoitrangthai>=f){
      st=0;
      f=0;
      digitalWrite(2,LOW);
    }
    }
  }
}

