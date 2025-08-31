# Automated Smart Desk

**Authors:** Anshita Sharma & Abhinav Ghosh.  
**Short:** An ESP32-based IoT smart study desk that monitors ambient light (LDR) and temperature/humidity (DHT11), automatically switches an LED and a DC fan, and offers remote control via Blynk.  

## Features
- Auto LED control based on ambient light.
- Auto fan control when temperature > 28°C.
- Remote/manual override via Blynk app.
- Simple, low-cost components for student/home use.

## Components
- ESP32 microcontroller  
- LDR (digital output)  
- DHT11 temperature & humidity sensor  
- DC Fan (switched via transistor/relay)  
- LEDs, resistors, and supporting wiring


## How to use
1. Open `code/arduino/SmartDesk/SmartDesk.ino` in Arduino IDE.  
2. Select board: **ESP32** and correct COM port.  
3. Install required libraries (DHT library, Blynk) via Library Manager.  
4. Flash to the ESP32. Configure Blynk token in the sketch if using remote control.

## Wiring
See `hardware/circuit-diagram.png` and `hardware/schematics.pdf` for full connections.





