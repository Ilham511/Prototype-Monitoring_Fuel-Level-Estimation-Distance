#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define potPin A0
#define KM_PER_LITER 10  // Anda bisa ubah angka ini sesuai kebutuhan (misal 1:12 atau 1:15)

float fuelLevel = 80;        
float displayFuel = 80;      
float displayDistance = 800; 
float lastPotMapped = 80;    

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("BBM & Sisa KM");
  delay(1000);
  lcd.clear();
}

void loop() {
  // === Potensiometer untuk BBM ===
  int potValue = analogRead(potPin);
  float mappedFuel = map(potValue, 0, 1023, 0, 80); // Potensiometer jadi 0-80 Liter
  mappedFuel = constrain(mappedFuel, 0, 80);

  // Update BBM dengan smoothing
  fuelLevel = mappedFuel;
  displayFuel += (fuelLevel - displayFuel) * 0.1;

  // === LOGIKA SINKRONISASI ===
  // Jarak tempuh = Sisa BBM * Konsumsi per liter
  float currentDistance = fuelLevel * KM_PER_LITER;
  displayDistance += (currentDistance - displayDistance) * 0.1;

  // === Tampilkan ke LCD ===
  // Baris Atas: KM (Jarak Tempuh)
  lcd.setCursor(0, 0);
  lcd.print("KM: ");
  lcd.print((int)displayDistance);
  lcd.print(" km      "); 

  // Baris Bawah: BBM
  lcd.setCursor(0, 1);
  lcd.print("BBM: ");
  lcd.print(displayFuel, 1);
  lcd.print(" liter    "); 

  delay(50); // Delay singkat agar simulasi berjalan lancar
}
