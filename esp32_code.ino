#include <WiFi.h>
#include <ThingSpeak.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal_I2C.h>

// WiFi credentials
const char* ssid = "Me";
const char* password = "mehedi113";

// ThingSpeak channel details
unsigned long channelID = 2970008;
const char* writeAPIKey = "R3ZHI4IJ45QISZYK";

// Pin definitions
#define DHT_PIN 4
#define DHT_TYPE DHT22
#define LED_PIN 2
#define BUZZER_PIN 5

// Sensor & Display Setup
DHT dht(DHT_PIN, DHT_TYPE);
BH1750 lightMeter;
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD address and size
WiFiClient client;

// Timing variables for continuous sensor reading
unsigned long lastReadTime = 0;
const unsigned long readInterval = 2000; // Read sensors every 2 seconds

// Timing variables for ThingSpeak updates
unsigned long lastThingSpeakTime = 0;
const unsigned long thingSpeakInterval = 15000; // Update ThingSpeak every 15 seconds

void setup() {
  Serial.begin(115200);

  // Setup pins
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Start sensors and display
  dht.begin();
  Wire.begin(21, 22);  // SDA = 21, SCL = 22
  lightMeter.begin();
  lcd.init();
  lcd.backlight();

  lcd.print("Connecting WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1000);
  lcd.clear();

  ThingSpeak.begin(client);
}

void loop() {
  unsigned long currentTime = millis();
  
  // Read sensors and update display continuously
  if (currentTime - lastReadTime >= readInterval) {
    lastReadTime = currentTime;
    
    // Read sensors
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    float light = lightMeter.readLightLevel();

    // Check if readings are valid
    if (isnan(temperature) || isnan(humidity)) {

      Serial.println("Sensor read error!");
      return;
    }

    // Display values on LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temperature, 1);
    lcd.print("C H:");
    lcd.print(humidity, 1);

    lcd.setCursor(0, 1);
    lcd.print("Light:");
    lcd.print(light, 0);
    lcd.print(" lx");

    // Print to Serial Monitor
    Serial.print("T: ");
    Serial.print(temperature);
    Serial.print(" C, H: ");
    Serial.print(humidity);
    Serial.print(" %, Light: ");
    Serial.print(light);
    Serial.println(" lx");
    
    // Update ThingSpeak at the specified interval
    if (currentTime - lastThingSpeakTime >= thingSpeakInterval) {
      lastThingSpeakTime = currentTime;
      
      // Send to ThingSpeak
      ThingSpeak.setField(1, temperature);
      ThingSpeak.setField(2, humidity);
      ThingSpeak.setField(3, light);
      int code = ThingSpeak.writeFields(channelID, writeAPIKey);

      if (code == 200) {
        Serial.println("ThingSpeak Update: Success");

        // Turn on LED and synchronize buzzer
        digitalWrite(LED_PIN, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);  // Buzzer ON with LED
        delay(1000);
        digitalWrite(BUZZER_PIN, LOW);   // Turn off buzzer
        delay(1500);
        digitalWrite(LED_PIN, LOW);      // Turn off LED
      } else {
        Serial.print("ThingSpeak Error: ");
        Serial.println(code);
      }
    }
  }
}
