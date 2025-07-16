# ESP32 Testing for Hybrid AES-DES-RSA Cryptographic Model

This folder contains the complete implementation and output results from testing the hybrid cryptographic model (AES-DES-RSA) on the ESP32 microcontroller. The evaluation aligns with the experimental validation discussed in Section III-G of the research paper.

## 📁 Contents

- `esp32_test_code.ino` – Arduino sketch implementing the hybrid AES-DES-RSA encryption, decryption, and ThingSpeak upload functionality.
- `esp32_output_logs.txt` – Output logs showing timing results (encryption/decryption), memory usage, and successful message validation.
- `thingspeak_result_screenshot.png` *(optional)* – Screenshot of data transmission confirmation from the ThingSpeak cloud dashboard.

## ⚙️ Platform & Tools

- **Microcontroller**: ESP32-WROOM-32
- **IDE**: Arduino IDE 2.3.2
- **Libraries**: 
  - `WiFi.h`
  - `ThingSpeak.h`
  - Custom AES & DES logic with modified S-box and P-box
- **Communication**: Wi-Fi (2.4 GHz) with ThingSpeak API
- **Bit-lengths tested**: 8, 16, 32, 64, 96, 128 bits

## 📊 Observations

- **Encryption Time**: 1.02 ms to 2.02 ms across all bit-lengths
- **Decryption Time**: 0.91 ms to 1.95 ms (all outputs valid)
- **Transmission Time to ThingSpeak**: Ranged from 949 ms to 1262 ms
- **Memory Usage**:
  - Flash: ~906,962 bytes (69% of available)
  - RAM: ~46,860 bytes (14% of 327,680 bytes)
  - Free Heap: ~280 KB available for runtime

## ✅ Summary

- The hybrid cryptographic model was successfully implemented and tested on ESP32.
- All test cases showed valid decryption and consistent timing.
- The system proved lightweight and responsive, confirming suitability for resource-constrained IoT environments and real-time 5G applications.

---


