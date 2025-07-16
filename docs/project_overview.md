# Hybrid Cryptographic Approach for Strengthening 5G/B5G Network Security  

## 📌 Introduction  
This project presents a hybrid cryptographic model combining **AES (Advanced Encryption Standard), DES (Data Encryption Standard), and RSA (Rivest-Shamir-Adleman)** to enhance security in **5G and beyond 5G (B5G) networks**.

The objective is to evaluate **encryption performance, throughput, memory efficiency**, and **real-time hardware feasibility** using benchmark comparisons and microcontroller testing.

---
## 🎯 Why Hybrid Encryption?  
🔹 **Combining Symmetric & Asymmetric Encryption** – Ensures speed and security.  
🔹 **Resists Quantum Threats** – Strengthens against potential future attacks.  
🔹 **Improved Key Management** – Uses RSA for secure key exchange.  
🔹 **Balanced Speed & Complexity** – Enhances efficiency compared to standalone AES or DES.  

---

## 🔹 Features & Objectives  

✅ **Hybrid AES-DES-RSA Encryption** – Strengthens security by leveraging multi-layer cryptography.  
✅ **Performance Evaluation** – Analyzes encryption speed, decryption timing, and system throughput.  
✅ **Data Size Optimization** – Measures impact of payload size on encryption performance.  
✅ **Benchmark Comparisons** – Compared against traditional and post-quantum cryptographic schemes.  
✅ **ESP32 Hardware Testing** – Confirms model feasibility in real-time IoT environments.  
✅ **Memory & Latency Metrics** – Includes flash usage and cloud transmission timing.

---

---

## 📂 Repository Structure  

Hybrid-Crypto-Security/
│
├── data/ # S-Box and encryption config files
│ ├── aes_sbox.json
│ ├── des_sbox.json
│
├── utils/ # Code utilities for S-box loading
│ └── load_sboxes.py
│
├── Results/ # Performance plots and graphs
│ ├── avg_encryption_time.png
│ ├── throughput.png
│ └── ...
│
├── esp32testing/ # ESP32 hardware implementation and logs
│ ├── esp32_test_code.ino
│ ├── esp32_output_logs.txt
│ └── thingspeak_result_screenshot.png (optional)
│
├── docs/
│ └── project_overview.md # This documentation file
│
├── main_code.ipynb # Full encryption workflow (AES-DES-RSA)
├── Average_operation_time_and_Data_size.ipynb
├── Benchmark_Comparison.ipynb
├── Comparison_of_data_sizes.ipynb
├── Throughput_and_Encryption_Performance_Evaluation.ipynb
│
├── README.md
├── LICENSE
└── .gitignore

yaml
Copy
Edit
----
## 🚀 How to Use the Project?  

### **1️⃣ Clone the Repository**  
```bash
git clone https://github.com/yourusername/Hybrid-Crypto-5G.git
cd Hybrid-Crypto-5G
```

### **2️⃣ Install Dependencies**  
```bash
pip install -r requirements.txt
```

### **3️⃣ Run the Main Code**  
To execute the hybrid AES-DES-RSA encryption:  
```bash
python src/main.py
```

### **4️⃣ Run Jupyter Notebooks for Analysis**  
```bash
jupyter notebook
```
Then open one of the analysis notebooks:  
- **`Throughput_and_Encryption_Performance_Evaluation.ipynb`**  
- **`Benchmark_Comparison.ipynb`**  
- **`Comparison_of_data_sizes.ipynb`**  
- **`Average_operation_time_and_Data_size.ipynb`**  

---
## 📲 ESP32 Hardware Implementation

To validate performance in resource-constrained environments, the hybrid encryption model was implemented on an **ESP32-WROOM-32** module.

- **Input bit-lengths**: 8 to 128 bits  
- **Encryption time**: 1–2 ms  
- **Decryption time**: 0.91–1.95 ms  
- **Cloud transmission time (ThingSpeak)**: 949–1262 ms  
- **Flash used**: ~69%  
- **RAM used**: ~14%

📁 All ESP32 source code, logs, and test results are available in [`esp32testing/`](../esp32testing/).
----
## Proposed model
<img width="773" height="531" alt="flowchart_proposed_model drawio" src="https://github.com/user-attachments/assets/dca874b3-6b1d-4a74-ab42-19fcf3215dc2" />


----
## 📊 Results & Performance Analysis

### 🔍 Key Findings:

✅ **AES-DES-RSA hybrid encryption** achieves a practical trade-off between security and processing speed.  
✅ **Real-world throughput** shows scalability with large payloads and minimal CPU bottlenecks.  
✅ **Hardware tests on ESP32** confirm suitability for 5G/IoT edge devices.  
✅ **Data size influences performance**; the hybrid model performs better than RSA-alone and more securely than AES-alone.

📈 All visualizations and comparisons are available as PNG graphs and interactive Jupyter notebooks in the repository.

---
## 🤝 Contributors
Aman Kumar (Lead Developer & Researcher)
---
## 📖 References
Research Paper: Hybrid Cryptographic Approach for Strengthening 5G/B5G Security
Cryptographic Standards: AES, DES, RSA, and S-Box Theory
---
You're done! 🚀







