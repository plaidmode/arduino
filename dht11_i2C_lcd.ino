// LCD 16X2 i2C
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

// DHT11
#include "DHT.h" //DHT 11 sensor library
#define DHTPIN 7     //Which arduino pin do you use?
#define DHTTYPE DHT11   // DHT 11 (Sensor type)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  Serial.println( DHT11 Trial");
  dht.begin();
}

void loop() {
  delay(1000);

  //Reading humidity data
  int humidity = dht.readHumidity();
  //Reading in Celcius format (c)
  int celcius = dht.readTemperature();
  //Reading in Fahrenheit format
  int fahrenheit = dht.readTemperature(true);

  //If else for failed reading
  if (isnan(humidity) || isnan(celcius) || isnan(fahrenheit)) {
    Serial.println("Reading data from sensor is failed");
    return;
  }

  int htof = dht.computeHeatIndex(fahrenheit, humidity); 
  //Procedure reading for heat index data in Fahreheit
  int htoc = dht.computeHeatIndex(celcius, humidity, false);
  //Procedure reading for heat index data in Celcius

  //reading humidity value from value derived from sensor
  Serial.print("Kelembaban: ");
  Serial.print(humidity);
  Serial.print(" %\t");

  // Showing humidity at LCD
  lcd.setCursor(0, 0);
  lcd.print("Humidity:");
  lcd.setCursor(10, 0);
  lcd.print(humidity);
  lcd.setCursor(13, 0);
  lcd.print("%");
  
  //reading temperature value from value derived from sensor
  Serial.print("Suhu : ");
  Serial.print(celcius); //Celcius format
  Serial.print("°"); //degree symbol
  Serial.print("C / ");
  Serial.print(fahrenheit); //Fahrenheit format
  Serial.print("°");
  Serial.print("F\t");

  // Showing temperature at LCD
  lcd.setCursor(0, 1);
  lcd.print("Temperature:");
  lcd.setCursor(13, 1);
  lcd.print(celcius);
  lcd.setCursor(15, 1);
  lcd.print("C");

  Serial.print("Heat Index: ");
  Serial.print(htof); 
  Serial.print("°");
  Serial.print("F / ");
  Serial.print(htoc);
  Serial.print("°");
  Serial.println("C ");

}
