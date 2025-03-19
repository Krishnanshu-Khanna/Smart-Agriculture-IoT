#define BLYNK_TEMPLATE_ID "TMPL3hTfQCFtJ"
#define BLYNK_TEMPLATE_NAME "Smart Agriculture"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// 🔹 Blynk Credentials
char auth[] = "ZDrUYjsJCyBG8ynC0seWgL99Webx-P84";
char ssid[] = "Lalala";
char pass[] = "123456789";

// 🔹 Sensor & Actuator Pins
#define SOIL_MOISTURE_PIN 34  
#define DHT_PIN 4             
#define LDR_PIN 35            
#define PIR_PIN 13            
#define BUZZER_PIN 27         
#define LED_PIN 26            
#define SERVO_PIN 25          

LiquidCrystal_I2C lcd(0x27, 16, 2);

// 🔹 DHT Sensor Setup
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// 🔹 Servo Motor
Servo waterGate;

// 🔹 Blynk Virtual Pins
#define V_SOIL V0
#define V_TEMP V1
#define V_HUMIDITY V2
#define V_LDR V3
#define V_PIR V4
#define V_BUZZER V5
#define V_LED V6
#define V_SERVO V7

// 🔹 Blynk Timer
BlynkTimer timer;

// 🔹 WiFi Reconnect Function
void checkWiFi() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.print("Reconnecting WiFi...");
        WiFi.begin(ssid, pass);
        int attempt = 0;
        while (WiFi.status() != WL_CONNECTED && attempt < 10) {
            delay(500);
            Serial.print(".");
            attempt++;
        }
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("\nWiFi Reconnected!");
            Blynk.connect();
        } else {
            Serial.println("\nWiFi Failed! Retrying in 10 sec...");
        }
    }
}

// 🔹 Setup Function
void setup() {
    Serial.begin(115200);

    // 🔹 Initialize Sensors
    dht.begin();
    pinMode(SOIL_MOISTURE_PIN, INPUT);
    pinMode(LDR_PIN, INPUT);
    pinMode(PIR_PIN, INPUT);

    // 🔹 Initialize Actuators
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    waterGate.attach(SERVO_PIN);
    waterGate.write(0);

    // 🔹 Connect to WiFi
    WiFi.begin(ssid, pass);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");

    // 🔹 Connect to Blynk
    Blynk.config(auth);
    Blynk.connect();

    // 🔹 LCD Setup
    lcd.begin();  // ✅ Fix: Use lcd.init() instead of lcd.begin()
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("ESP32 Smart Agri");
    lcd.setCursor(0, 1);
    lcd.print("LCD Connected!");

    // 🔹 Set Timer to Read Sensors Every 2 Seconds
    timer.setInterval(2000L, readSensors);
}

// 🔹 Main Loop (Non-Blocking)
void loop() {
    Blynk.run();
    timer.run();
    checkWiFi(); // ✅ Auto-reconnect WiFi
}

// 🔹 Read Sensor Data & Send to Blynk
void readSensors() {
    int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();
    int ldrValue = analogRead(LDR_PIN);
    int pirMotion = digitalRead(PIR_PIN);

    // ✅ Fix: NaN (Not a Number) Check for DHT Sensor
    if (isnan(temp) || isnan(humidity)) {
        Serial.println("⚠️ DHT Sensor Failed! Skipping Data...");
        return;
    }

    // 🔹 Convert Soil Moisture to %
    int soilMoisturePercent = map(soilMoisture, 0, 4095, 100, 0);
    soilMoisturePercent = constrain(soilMoisturePercent, 0, 100);

    // 🔹 Print Sensor Values
    Serial.print("🌱 Soil Moisture: "); Serial.print(soilMoisturePercent); Serial.println("%");
    Serial.print("🌡️ Temperature: "); Serial.print(temp); Serial.println("°C");
    Serial.print("💧 Humidity: "); Serial.print(humidity); Serial.println("%");
    Serial.print("☀️ LDR Value: "); Serial.println(ldrValue);
    Serial.print("🚶 PIR Motion: "); Serial.println(pirMotion);
    
    // 🔹 Send Data to Blynk
    Blynk.virtualWrite(V_SOIL, soilMoisturePercent);
    Blynk.virtualWrite(V_TEMP, temp);
    Blynk.virtualWrite(V_HUMIDITY, humidity);
    Blynk.virtualWrite(V_LDR, ldrValue);
    Blynk.virtualWrite(V_PIR, pirMotion);

    // 🔹 Update LCD Display
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Soil: ");
    lcd.print(soilMoisturePercent);
    lcd.print("% ");

    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.print("C");

    // 🔹 Smart Water Gate Control
    if (soilMoisturePercent < 30) {
        waterGate.write(90);
        Blynk.virtualWrite(V_SERVO, 90);
        Serial.println("🚰 Watering Plants!");
    } else {
        waterGate.write(0);
        Blynk.virtualWrite(V_SERVO, 0);
        Serial.println("✅ Soil Moisture OK!");
    }

    // 🔹 Bird Scare Feature (Using PIR)
    if (pirMotion == HIGH|| ldrValue>1024) {
        digitalWrite(BUZZER_PIN, HIGH);
        digitalWrite(LED_PIN, HIGH);
        Blynk.virtualWrite(V_BUZZER, 1);
        Blynk.virtualWrite(V_LED, 1);
        Serial.println("⚠️ Motion Detected! Bird Scare ON");
    } else {
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_PIN, LOW);
        Blynk.virtualWrite(V_BUZZER, 0);
        Blynk.virtualWrite(V_LED, 0);
    }
}

// 🔹 Blynk App Manual Control for Servo Motor
BLYNK_WRITE(V_SERVO) {
    int angle = param.asInt();
    waterGate.write(angle);
}
