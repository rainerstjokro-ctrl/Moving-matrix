// ==========================================================
// Program Tes OLED 0.96" I2C (SSD1306)
// Digunakan untuk testing posisi koordinat teks sebelum game
// ==========================================================

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Lebar layar OLED dalam pixel
#define SCREEN_HEIGHT 64 // Tinggi layar OLED dalam pixel

// Inisialisasi display dengan alamat I2C default (-1 berarti tanpa pin reset)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ==========================================================
// PENGATURAN TEKS & KOORDINAT (Ubah di sini)
// ==========================================================
const char* textToDisplay = "Dino Game!"; // Teks yang ingin ditampilkan
int startX = 5;                           // Titik mulai koordinat X (Horizontal: 0 s.d 127)
int startY = 25;                           // Titik mulai koordinat Y (Vertikal: 0 s.d 63)
int textSize = 2;                          // Ukuran font (1 untuk kecil, 2 untuk sedang, dst)

void setup() {
  Serial.begin(9600);

  // Menggunakan alamat I2C 0x3C sesuai dengan konfigurasi proyek game kamu
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Gagal mendeteksi OLED SSD1306!"));
    while(1); // Stop program jika OLED tidak terdeteksi
  }

  // Membersihkan buffer layar di awal
  display.clearDisplay();

  // Konfigurasi teks
  display.setTextSize(textSize);             // Atur ukuran font
  display.setTextColor(SSD1306_WHITE);       // Atur warna teks (Hanya ada putih/hitam di OLED ini)
  display.setCursor(startX, startY);         // Atur titik start (X, Y)
  
  // Menampilkan teks ke buffer
  display.print(textToDisplay);
  
  // Mengirim data buffer ke layar fisik OLED agar muncul
  display.display(); 
}

void loop() {
  // Loop dikosongkan karena ini hanya untuk tes statis
}