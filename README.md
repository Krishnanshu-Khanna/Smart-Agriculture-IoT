# 🌱 Smart Irrigation and Weather Monitoring System with Bird Scaring  

This system is designed to automate irrigation, monitor weather conditions, and deter birds from damaging crops. It integrates multiple sensors and actuators to enhance agricultural efficiency using an **ESP32 WiFi module** and the **Blynk App**.

---

## 🚀 Key Features & Components  

### 1️⃣ Smart Irrigation System  
 **Automated Watering:** Uses soil moisture sensors to monitor soil water levels.  
 **Automatic Control:** Turns the water pump **ON** when moisture is low and **OFF** when sufficient.  
 **Manual IoT Control:** Can be controlled via **Blynk, Firebase, or a mobile app**.  

### 2️⃣ Weather Monitoring System  
 **Temperature & Humidity Monitoring:** Uses **DHT11/DHT22 sensors**.  
 **Light Intensity Detection:** Uses an **LDR (Light Dependent Resistor)**.  
 **Rainfall Prediction:** Uses a **rain sensor** to measure precipitation.  
 **IoT Updates:** Sends real-time data to **Blynk, Firebase, or ThingSpeak** for remote monitoring.  

### 3️⃣ Bird Scaring Mechanism  
 **Motion Detection:** Uses a **PIR Motion Sensor** to detect bird movement near crops.  
 **Light-Based Activation:** LDR detects brightness (since birds are more active during daylight).  
 **Bird Deterrence:**  
   - Activates a **buzzer** to scare birds.  
   - Turns **ON an LED** as a visual deterrent.  
   - Sends **IoT notifications** to alert farmers.  

---

## ⚙️ Working Mechanism  

### 1️⃣ Sensor Data Collection  
- **Soil Moisture, Temperature, Humidity, Light Intensity, and Rainfall** are monitored in real-time.  

### 2️⃣ Automated Decision Making  
- **If soil is dry** → Water pump **turns ON**.  
- **If soil is moist** → Water pump **turns OFF**.  
- **If motion/light is detected** → Buzzer & LED **activate to scare birds**.  

### 3️⃣ IoT Integration  
- Sends real-time sensor data to a **mobile app** using **Blynk/Firebase**.  
- Users can **manually control irrigation and bird deterrent mechanisms**.  

---

## 🎯 Benefits  
 **Water Conservation** – Uses only the required amount of water.  
 **Increased Crop Yield** – Protects crops from birds and optimizes irrigation.  
 **Real-Time Monitoring** – Farmers can track weather conditions remotely.  
 **Low Maintenance** – Fully automated and energy-efficient system.  

---

## 🛠️ Tech Stack  
- **Hardware:** ESP32, Soil Moisture Sensor, DHT11/DHT22, PIR Sensor, LDR, Rain Sensor, Buzzer, LED.  
- **Software:** Arduino IDE, Blynk App, Firebase, ThingSpeak.  
- **Communication:** WiFi (ESP32), IoT Integration.  

---

## 📷 Project Images & Demonstration  
*(Include screenshots, circuit diagrams, and working videos here.)*  

---

## 📝 How to Use  
1. **Set up the ESP32 module** and connect the sensors.  
2. **Upload the code** using Arduino IDE.  
3. **Connect the system to Blynk/Firebase** for real-time monitoring.  
4. **Monitor and control irrigation** and **bird scaring** via the app.  

---

## 🔗 References  
- [ESP32 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)  
- [Blynk IoT Platform](https://blynk.io/)  

---

## 📌 Author  
👨‍💻 **Krishnanshu Khanna**  
📧 [krishnanshu.khanna@gmail.com](mailto:krishnanshu.khanna@gmail.com)  
🔗 [GitHub](https://github.com/Krishnanshu-Khanna) | [LinkedIn](https://www.linkedin.com/in/krishnanshu-khanna/)  

---

🚀 **This project brings smart farming to the next level! If you like it, give it a ⭐ on GitHub!**  
