#include <LiquidCrystal.h>

// Пины для подключения к сдвиговому регистру 74HC595
const int dataPin = 11;    // DS (14 нога 74HC595) -> Arduino D11
const int clockPin = 12;   // SHCP (11 нога 74HC595) -> Arduino D12
const int latchPin = 10;   // STCP (12 нога 74HC595) -> Arduino D10

// Пины управления дисплеем
const int rsPin = 4;       // RS (4 пин дисплея) -> 14 нога 74HC595
const int enablePin = 13;  // EN (6 пин дисплея) -> 3 нога 74HC595

// Инициализация дисплея через сдвиговый регистр
LiquidCrystal lcd(rsPin, enablePin, dataPin, clockPin, latchPin);

// Дополнительные настройки
const int contrastPin = 9; // PWM пин для контраста (V0 дисплея)

void setup() {
  // Настройка контраста
  pinMode(contrastPin, OUTPUT);
  analogWrite(contrastPin, 80); // Начальное значение контраста

  // Инициализация дисплея
  lcd.begin(16, 2);
  lcd.print("System Ready!");
  
  // Дайте дисплею время на инициализацию
  delay(500);
}

void loop() {
  // Обновление показаний каждые 2 секунды
  static unsigned long lastUpdate = 0;
  if(millis() - lastUpdate >= 2000) {
    lastUpdate = millis();
    
    // Очистка дисплея
    lcd.clear();
    
    // Вывод статических меток
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.setCursor(8, 0);
    lcd.print("H:");
    
    lcd.setCursor(0, 1);
    lcd.print("DHT:");
    
    // Здесь можно добавить код для чтения датчиков
    // и вывода реальных значений
  }
}
