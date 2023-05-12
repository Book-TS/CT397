// #include "Arduino.h"
// #include "DFRobotDFPlayerMini.h"

// DFRobotDFPlayerMini myDFPlayer;
// void printDetail(uint8_t type, int value);

// void setup()
// {
//   Serial2.begin(9600);
//   Serial.begin(115200);
  
//   if (!myDFPlayer.begin(Serial2)) 
//   {  
//     Serial.println(F("Không thể khởi động:"));
//     Serial.println(F("1.Kiểm tra lại kết nối"));
//     Serial.println(F("2.Lắp lại thẻ nhớ"));
//       while(true)
//       {
//         delay(0);
//       }
//   }
//   Serial.println(F("DFPlayer Mini đang hoạt động"));
  
//   myDFPlayer.volume(30);  //cài đặt volume từ 0 đến 30

// }

// void loop() 
// {
//   myDFPlayer.play(1); 
//   delay(3000);
//   myDFPlayer.playMp3Folder(2);
//   delay(3000);
//   myDFPlayer.playMp3Folder(3);
//   delay(3000);

//   myDFPlayer.playMp3Folder(4);
//   delay(3000);

// myDFPlayer.playMp3Folder(5);
//   delay(3000);
// }
