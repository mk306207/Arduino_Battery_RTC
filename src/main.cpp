#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <SPI.h>

#define BATTERY_PIN A0
#define R1 4700
#define R2 10000 

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {

  analogReference(EXTERNAL);
  Serial.begin(9600);

  Wire.begin();
  lcd.init();
  lcd.backlight();

  if(!(rtc.begin())){
    lcd.setCursor(0, 0);
    lcd.print("Brak RTC!");
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  DateTime now = rtc.now();

  int adcValue = analogRead(BATTERY_PIN);
  float voltage = adcValue * (3.3 / 1023.0);
  float batteryVoltage = voltage * ((R1 + R2) / (float)R2);

  lcd.setCursor(0,0);
  if (now.hour() < 10) lcd.print("0");
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute(), DEC);
  lcd.print(":");
  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second(), DEC);

  lcd.setCursor(0, 1);
  lcd.print("V: ");
  lcd.print(batteryVoltage, 2);
  lcd.print(" V     ");


  Serial.print("Napiecie baterii: ");
  Serial.print(batteryVoltage, 2);
  Serial.println(" V");
  Serial.print("adcValue: ");
  Serial.println(adcValue, 2);

  delay(1000); 
}

