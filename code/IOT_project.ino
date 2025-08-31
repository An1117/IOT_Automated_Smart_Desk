// // #include <DHT.h>
// // #include <DHT_U.h>

// // #include "DHT.h"
// // #define LDR_PIN 2  // Digital output from LDR module
// // #define LED_PIN 4   // LED connected to D2 (can be changed)

// // #define DHTPIN 5       // DHT11 data pin connected to GPIO4
// // #define DHTTYPE DHT11  // Sensor type
// // #define FAN_PIN 13     // Digital pin to control fan
// // DHT dht(DHTPIN, DHTTYPE);

// // void setup() {
// //   Serial.begin(115200);
// //   pinMode(LDR_PIN, INPUT);
// //   pinMode(LED_PIN, OUTPUT);
// //   dht.begin();
// //   pinMode(FAN_PIN, OUTPUT);
// //   digitalWrite(FAN_PIN, LOW);  // Start with fan off
// // }

// // void loop() {
// //   int lightStatus = digitalRead(LDR_PIN); // HIGH if light detected, LOW if dark
// //   Serial.println(lightStatus);            // Debug: Print light status

// //   if (lightStatus == HIGH) {
// //     digitalWrite(LED_PIN, HIGH); // Turn ON LED in darkness
// //   } else {
// //     digitalWrite(LED_PIN, LOW);  // Turn OFF LED in brightness
// //   }

// //   delay(500); // Delay to avoid bouncing
  
// //   float temp = dht.readTemperature();    // Read temperature in Celsius
// //   float hum = dht.readHumidity();        // Read humidity

// //   // Check if readings are valid
// //   if (isnan(temp) || isnan(hum)) {
// //     Serial.println("Failed to read from DHT sensor!");
// //     return;
// //   }

// //   Serial.print("Temp: ");
// //   Serial.print(temp);
// //   Serial.print("°C  |  Humidity: ");
// //   Serial.print(hum);
// //   Serial.println("%");

// //   // Fan control logic
// //   if (temp > 20.0) {
// //     digitalWrite(FAN_PIN, HIGH); // Turn fan ON
// //   } else {
// //     digitalWrite(FAN_PIN, LOW);  // Turn fan OFF
// //   }

// //   delay(2000); // Read every 2 seconds
// // }
// #define BLYNK_PRINT Serial
// #define BLYNK_TEMPLATE_ID "TMPL3U_9p_SxN"
// #define BLYNK_TEMPLATE_NAME "Quickstart Template"
// #define BLYNK_AUTH_TOKEN "dQAod3wNS7MBXDQOmsvZdMIjOf68sed4"

// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <BlynkSimpleEsp32.h>
// #include <DHT.h>

// // WiFi credentials
// char ssid[] = "EACCESS";
// char pass[] = "hostelnet";

// // Virtual pin for automation toggle
// #define VIRTUAL_PIN_SWITCH V7

// // // Sensor and hardware pins
// #define LDR_PIN 2        // Digital pin from LDR module
// #define LED_PIN 4        // LED pin
// #define DHTPIN 5         // DHT11 data pin
// #define DHTTYPE DHT11
// #define FAN_PIN 18       // Fan control pin

// DHT dht(DHTPIN, DHTTYPE);
// bool automationEnabled = false;  // Will be updated by Blynk app

// // Called when switch on Blynk app is toggled
// BLYNK_WRITE(VIRTUAL_PIN_SWITCH) {
//   int value = param.asInt(); // 1 = ON, 0 = OFF
//   automationEnabled = value;
// }

// void setup() {
//   Serial.begin(115200);
//   Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

//   dht.begin();
//   pinMode(LDR_PIN, INPUT);
//   pinMode(LED_PIN, OUTPUT);
//   pinMode(FAN_PIN, OUTPUT);

//   digitalWrite(LED_PIN, LOW);
//   digitalWrite(FAN_PIN, LOW);
// }

// void loop() {
//   Blynk.run();  // Run Blynk background

//   if (automationEnabled) {
//     // LDR Control
//     int lightStatus = digitalRead(LDR_PIN);
//     if (lightStatus == HIGH) {
//       digitalWrite(LED_PIN, HIGH);
//     } else {
//       digitalWrite(LED_PIN, LOW);
//     }

//     // DHT Control
//     float temp = dht.readTemperature();
//     float hum = dht.readHumidity();

//     if (!isnan(temp) && !isnan(hum)) {
//       Serial.print("Temp: ");
//       Serial.print(temp);
//       Serial.print(" °C, Humidity: ");
//       Serial.print(hum);
//       Serial.println(" %");

//       if (temp > 28.0) {
//         digitalWrite(FAN_PIN, HIGH);
//       } else {
//         digitalWrite(FAN_PIN, LOW);
//       }
//     } else {
//       Serial.println("Failed to read from DHT sensor!");
//     }

//   } else {
//     // Automation OFF: turn off all outputs
//     digitalWrite(LED_PIN, LOW);
//     digitalWrite(FAN_PIN, LOW);
//   }

//   delay(2000); // Delay between sensor checks
// }


#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL3U_9p_SxN"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "dQAod3wNS7MBXDQOmsvZdMIjOf68sed4"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// WiFi credentials
char ssid[] = "Anshita's iPhone";
char pass[] = "Meowwww17";

// Virtual pin for automation toggle
#define VIRTUAL_PIN_SWITCH V7

// Sensor and hardware pins
#define LDR_PIN 2
#define LED_PIN 4
#define DHTPIN 5
#define DHTTYPE DHT11

// L298N Motor Driver Pins for Fan
#define IN1 19    // Fan motor input 1
#define IN2 22    // Fan motor input 2
#define EN 23    // Enable pin (can be PWM if speed control needed)

DHT dht(DHTPIN, DHTTYPE);
bool automationEnabled = false;

// Called when switch on Blynk app is toggled
BLYNK_WRITE(VIRTUAL_PIN_SWITCH) {
  int value = param.asInt(); // 1 = ON, 0 = OFF
  automationEnabled = value;
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  dht.begin();
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // Motor control pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(EN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  stopFan(); // Ensure fan is off
}

void loop() {
  Blynk.run();

  if (automationEnabled) {
    // LDR Light Control
    int lightStatus = digitalRead(LDR_PIN);
    digitalWrite(LED_PIN, (lightStatus == HIGH) ? HIGH : LOW);

    // DHT11 Temperature + Fan Control
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (!isnan(temp) && !isnan(hum)) {
      Serial.print("Temp: ");
      Serial.print(temp);
      Serial.print(" °C, Humidity: ");
      Serial.print(hum);
      Serial.println(" %");

      if (temp >= 29.90) {
        startFan();
        Serial.println("Fan ON (Temp > 28°C)");
      } else {
        stopFan();
        Serial.println("Fan OFF (Temp <= 28°C)");
      }
    } else {
      Serial.println("Failed to read from DHT sensor!");
    }

  } else {
    digitalWrite(LED_PIN, LOW);
    stopFan(); // Ensure fan is off when automation is disabled
  }

  delay(2000); // Delay between sensor checks
}

void startFan() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(EN, HIGH); // Enable fan
}

void stopFan() {
  digitalWrite(EN, LOW); // Disable fan
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
