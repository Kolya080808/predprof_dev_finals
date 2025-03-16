#include <StandardCplusplus.h>
#include <vector>
#include <string>
#include <iostream>

#define PHOTOTRANSISTOR_PIN A0  // Аналоговый вход для фототранзистора
#define PHOTORESISTOR_PIN   A1  // Аналоговый вход для фоторезистора (калибровка порога)
#define BIT_DURATION        50  // Длительность чтения одного бита (мс) - подстройте под вашу диаграмму
#define SYMBOL_DELAY        100 // Доп. задержка между символами (мс)


// Глобальные переменные
int thresholdValue = 0;          // Порог, выше которого считаем бит "1"
vector<char> receivedBits;       // Хранилище для 8 бит текущего символа
string receivedMessage;          // Итоговое расшифрованное сообщение

// Функция для расшифровки символа (сдвиг -2 по шифру Цезаря)
char decryptCaesar(char ch, int shift = -6) {

	if (isalpha(ch)) {

		char base = isupper(ch) ? 'A' : 'a';
		return (ch - base - shift + 26) % 26 + base;
    	}

	return ch;
}


void calibrateThreshold() {

	long sum = 0;
	const int samples = 10;

	// Несколько измерений, чтобы усреднить
	for (int i = 0; i < samples; i++) {
		sum += analogRead(PHOTORESISTOR_PIN);
		delay(10);
	}
	int ambientLight = sum / samples;
	// Устанавливаем порог выше среднего порога освещенности
	// Подбираем эксперементально
	thresholdValue = ambientLight +50;

	Serial.print("Ambient light (avg): ");
	Serial.println(ambientLight);
	Serial.print("Threshold set to: ");
	Serial.println(thresholdValue);
}

void readBits() {
	receivedBits.clear();
	for (int i = 0; i < 8; i++) {

		// считываем значение с фоторезистора
		int sensorValue = analogRead(PHOTOTRANSISTOR_PIN);


		// Сравниваем с порогом
		if (sensorValue > thresholdValue) {
			receivedBits.push_back('1');
		} else {
			receivedBits.push_back('0');
		}
		// ждем время, соответствующее одному биту
		delay(BIT_DURATION);
	}

	delay(SYMBOL_DELAY);
}

// Преобразование 8 бит из вектора в ASCII-символ
char decodeASCII() {
	// Если меньше или больше 8 бит — ошибка
	if (receivedBits.size() != 8) {
		return '?';
	}
	int asciiValue = 0;
	// Допустим, первый считанный бит — это старший бит (7), второй — 6 и т.д.
	for (int i = 0; i < 8; i++) {
		if (receivedBits[i] == '1') {
			asciiValue |= (1 << (7 - i));
		}
	}
	return (char)asciiValue;
}

void setup() {
	Serial.begin(9600);

	// Калибруем порог по уровню освещённости
	calibrateThreshold();

}

void loop() {

	readBits();

	char decodedChar = decodeASCII();
	char decryptedChar = decryptCaesar(decodedChar);

	receivedMessage += decryptedChar;

	// Для отладки выведем в монитор
	Serial.print("Bits: ");
	for (int i = 0; i < 8; i++) {
		Serial.print(receivedBits[i]);
	}
	Serial.print(" => Decoded: ");
	Serial.print(decodedChar);
	Serial.print(" | Decrypted: ");
	Serial.println(decryptedChar);
	Serial.print("Current message: ");
	Serial.println(receivedMessage);
	delay(500);
}






