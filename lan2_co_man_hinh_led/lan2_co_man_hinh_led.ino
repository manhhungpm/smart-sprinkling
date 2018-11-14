#include <Wire.h>
#include <SPI.h>
#include "RF24.h"

#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C lcd(0x3F,16,2);


/* Địa chỉ của DS1307 */
const byte DS1307 = 0x68;
/* Số byte dữ liệu sẽ đọc từ DS1307 */
const byte NumberOfFields = 3;

/* khai báo các biến thời gian */
int second, minute, hour;

//set lam radio thu
bool radioNumber = 0;
RF24 radio(7,8);
byte addresses[][6] = {"1Node","2Node"};

//dia chi cho radio thuu
bool role = 0;

//set chuong trinh cho cam bien Hall
int pushButton = 2;

//cac tham so cua do am
const float a=400;
const float b=524;
const float c=649,d=774,e=899;

//cac tham so cua luong nuoc
const float v=200,y=400,z=600,t=800,k=1000;
float luongnuoc;
int st;
int dem;
float tb;

// do so lan thay doi trang thai
volatile int solanthaydoitrangthai=0;
int trangthaihientai;
int trangthaitruoc;

// hàm tăng biến đếm
void tangbiendem(){
  solanthaydoitrangthai++;
      //  Serial.println("abc");

}

void setup() {
  Serial.begin(115200);
  st=0;
  
  //DS1307
  Wire.begin();
  /* cài đặt thời gian cho module */
  setTime(17,59,50); // 12:30:45 CN 08-02-2015
  
  
  Serial.println(F("CAM BIEN DO AM + RADIO THU"));
  pinMode(pushButton,INPUT);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
  
  radio.startListening();
  st=0; //trang thai doi
  dem=0;
  tb=0;
  
  //van
  pinMode (4,OUTPUT);
  
  //cambienHALL
  pinMode (2,INPUT);
  attachInterrupt(0, tangbiendem, RISING);
  digitalWrite(4,HIGH);//hàm đọc giờ
   
 //khoi dong man hinh led
 lcd.init();       //Khởi động màn hình. Bắt đầu cho phép Arduino sử dụng màn hình
 lcd.backlight();  //bat den nen
}
void readDS1307()
{
        Wire.beginTransmission(DS1307);
        Wire.write((byte)0x00);
        Wire.endTransmission();
        Wire.requestFrom(DS1307, NumberOfFields);
        
        second = bcd2dec(Wire.read() & 0x7f);
        minute = bcd2dec(Wire.read() );
        hour   = bcd2dec(Wire.read() & 0x3f); // chế độ 24h.

}


/* Chuyển từ format BCD (Binary-Coded Decimal) sang Decimal */
int bcd2dec(byte num)
{
        return ((num/16 * 10) + (num % 16));
}
/* Chuyển từ Decimal sang BCD */
int dec2bcd(byte num)
{
        return ((num/10 * 16) + (num % 10));
}

void printDigits(int digits){
    // các thành phần thời gian được ngăn chách bằng dấu :
    lcd.print(":");
        
    if(digits < 10)
        lcd.print('0');
    lcd.print(digits);
}

/* cài đặt thời gian cho DS1307 */
void setTime(byte hr, byte min, byte sec)
{
        Wire.beginTransmission(DS1307);
        Wire.write(byte(0x00)); // đặt lại pointer
        Wire.write(dec2bcd(sec));
        Wire.write(dec2bcd(min));
        Wire.write(dec2bcd(hr));
        Wire.endTransmission();
}

void digitalClockDisplay(){
    // digital clock display of the time
    lcd.print("Gio hien tai la :");
    lcd.setCursor(0,1);
    lcd.print(hour);
    printDigits(minute);
    printDigits(second);
}

// cac ham mo
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
 //Set dòng cho LCD
 lcd.setCursor(0,0);
 
 /* Đọc dữ liệu của DS1307 */
  readDS1307();
  /* Hiển thị thời gian ra Serial monitor */
  
  
  
  //lcd.print();
  //delay(1000);
  //Serial.println(hour);
  if(st==0){
    
    delay(1000);
    digitalClockDisplay();
    if(hour==18 && minute ==00 && second==00 )st=1;
    
  }
    
   
  if(st==1){
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    radio.startListening();
    lcd.print("Chuyen sang st=1");
    long x=0;
    lcd.setCursor(0,1);
    if( radio.available()){
        while (radio.available()) {                                 
          radio.read( &x, sizeof(long) ); 
          lcd.print(x);
        
        }
    }
    
    //lcd.clear();
    
    dem++;
    tb+=x;
    if( dem>=10 ){
      st=2;
      dem=0;
      tb=tb/10;
    }
    if(x==0)
    {
      st=0;
    }
  }
  if(st==2){
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
//lcd.print("Chuyen sang st=2");
    radio.stopListening();                                        
    //radio.write( &x, sizeof(float) );                 
    radio.startListening(); 

    lcd.setCursor(0,0);    
    lcd.print(F("Do am duoc nhan la : "));
    lcd.setCursor(0,1);
    lcd.print(tb);
    Serial.println("--------------------\n");
    Serial.print("rat cao = ");Serial.println(ratcao(tb,a,b,c,d,e));
    Serial.print("cao = ");Serial.println(cao(tb,a,b,c,d,e));
    Serial.print("trung binh = ");Serial.println(trungbinh(tb,a,b,c,d,e));
    Serial.print("thap = ");Serial.println(thap(tb,a,b,c,d,e));
    Serial.print("rat thap = ");Serial.println(ratthap(tb,a,b,c,d,e));
    float ratit,it,vua,nhieu,ratnhieu;
    ratit=ratcao(tb,a,b,c,d,e);
    it=cao(tb,a,b,c,d,e);
    vua=trungbinh(tb,a,b,c,d,e);
    nhieu=thap(tb,a,b,c,d,e);
    ratnhieu=ratthap(tb,a,b,c,d,e);
    luongnuoc=(v*ratit+y*it+z*vua+t*nhieu+k*ratnhieu)/(ratit+it+vua+nhieu+ratnhieu);
    
    delay(1000);
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("luongnuoc= ");
    lcd.setCursor(0,1);
    lcd.print(luongnuoc);
    delay(2000);
    Serial.println("--------------------\n");
    Serial.println(luongnuoc);
    st=3;
    tb=0;
    solanthaydoitrangthai=0;
    }
   if(st==3){
     
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Dang bom");
      Serial.println("chuyen sang st=3");
      
    
     digitalWrite(4,LOW); //relay
     //int buttonState = digitalRead(pushButton);
    // sei();
           //Serial.println("chuyen");

     delay(1000);
           // Serial.println("chuyennnnnnnnnnn");

    //  cli();
      Serial.print("hall:");
      Serial.println(solanthaydoitrangthai);
    //Serial.print(buttonState);
      float f;
    
      f=luongnuoc*30350/1000;
      Serial.print("can phai quay:");
      Serial.println(f);
      Serial.println(solanthaydoitrangthai);
      if(solanthaydoitrangthai>=f){
        st=0;
        f=0;
        digitalWrite(4,HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("bom xong");
        delay(2000);
      }
    }
}

