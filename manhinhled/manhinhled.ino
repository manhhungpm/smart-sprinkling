#include <Wire.h>;
#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C lcd(0x3F,16,2);
//0x27 là địa chỉ màn hình trong bus I2C. Phần này chúng ta không cần phải quá bận tâm vì hầu hết màn hình (20x4,...) đều như thế này!
//16 là số cột của màn hình (nếu dùng loại màn hình 20x4) thì thay bằng 20
//2 là số dòng của màn hình (nếu dùng loại màn hình 20x4) thì thay bằng 4
byte traitim[8]={
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000,
  B00000
}; // Cái này là tạo hình trái tim...đoạn này tham khảo của Thạc Sĩ Huỳnh Minh Phú đó các bạn
void setup(){
lcd.init();       //Khởi động màn hình. Bắt đầu cho phép Arduino sử dụng màn hình
lcd.backlight();   //Bật đèn nền
}
void loop()
{
  lcd.setCursor(3,0);
  lcd.print("Anh Yeu Em");//Viết dòng chữ Anh Yêu Em...Các bạn có thể thay bằng dòng khác như Minh Thich Cau...
  int i;
  // Viết liên tục các ký tự trái tim ở dòng 2
  for (i=0;i<=10;i++){
  lcd.setCursor(i,1);
  delay(200);  
  }
  delay(2000);
  lcd.clear();//Xóa màn hình
  delay(300);
}
