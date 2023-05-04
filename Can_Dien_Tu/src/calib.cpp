// #include <HX711_ADC.h>

// // Khai báo các chân kết nối với module HX711
// #define LOADCELL_DOUT_PIN 23
// #define LOADCELL_SCK_PIN 22

// HX711_ADC loadCell(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

// void setup() {
//   Serial.begin(115200);
//   delay(1000);

//   // Khởi tạo module HX711 với các chân kết nối đã khai báo
//   loadCell.begin();
//   loadCell.start(2000); // Cấu hình độ nhạy của cảm biến tải

//   Serial.println("HX711 ADC calibration demo");
//   Serial.println("Please place an known weight on the loadcell...");
// }

// void loop() {
//   // Đợi người dùng đặt trọng lượng cần calib lên loadcell
//   while (!loadCell.update()) {}

//   // Lấy giá trị đọc được từ cảm biến tải
//   long reading = loadCell.getData();

//   // Hiển thị giá trị đọc được lên Serial Monitor
//   Serial.print("Reading: ");
//   Serial.println(reading);

//   // Nếu người dùng đã đặt trọng lượng đúng trên loadcell
//   if (Serial.available()) {
//     float weight = Serial.parseFloat();

//     // Tính toán giá trị calib
//     float calibration_factor = reading / weight;

//     // Hiển thị giá trị calib lên Serial Monitor
//     Serial.print("Calibration factor: ");
//     Serial.println(calibration_factor);

//     // Lưu giá trị calib vào EEPROM
//     loadCell.setCalFactor(calibration_factor);

//     Serial.println("Calibration complete!");
//     Serial.println("Please restart the board...");
//     while(1);
//   }

//   delay(500);
// }
