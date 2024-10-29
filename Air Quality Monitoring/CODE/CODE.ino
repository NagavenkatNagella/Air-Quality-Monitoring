#include <DHT.h>                // Library for DHT11/DHT22 sensor
#include <Wire.h>               // Library for I2C communication
#include <LiquidCrystal_I2C.h>  // Library for LCD with I2C module

// Define LCD and DHT settings
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address for 16x2 LCD (address may vary)
#define DHTPIN 2                  // Digital pin for DHT sensor
#define DHTTYPE DHT11             // Define sensor type (DHT11 or DHT22)
DHT dht(DHTPIN, DHTTYPE);

// Define gas sensor pin
const int gasSensorPin = A0;       // Analog pin for gas sensor (e.g., MQ-135)

// Threshold for air quality (adjust based on your sensor's reading)
int airQualityThreshold = 300;

void setup() {
  // Initialize serial monitor, LCD, and DHT sensor
  Serial.begin(9600);
  lcd.begin(16, 2);  // Specify the dimensions of the LCD
  lcd.backlight();
  dht.begin();
  
  // Display startup message
  lcd.setCursor(0, 0);
  lcd.print("Air Quality");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring");
  delay(2000);
}

void loop() {
  // Read gas sensor value
  int gasValue = analogRead(gasSensorPin);

  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Display air quality
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("G: ");
  lcd.print(gasValue);

  // Check if gas levels exceed the threshold
  if (gasValue > airQualityThreshold) {
    lcd.print(" BAD");
  } else {
    lcd.print(" GOOD");
  }

  // Display humidity and temperature
  lcd.setCursor(0, 1);
  lcd.print("H:");
  lcd.print(humidity);
  lcd.print("% ");
  lcd.print("T:");
  lcd.print(temperature);
  lcd.print("C");

  // Print data to Serial Monitor for testing
  Serial.print("Gas Level: ");
  Serial.println(gasValue);
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%, ");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println("C");

  // Delay before next reading
  delay(2000);
}
