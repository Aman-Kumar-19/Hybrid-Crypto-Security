# Hybrid Cryptographic Approach for Strengthening 5G/B5G Network Security  

## 📌 Introduction  
This project presents a hybrid cryptographic model combining **AES (Advanced Encryption Standard), DES (Data Encryption Standard), and RSA (Rivest-Shamir-Adleman)** to enhance security in **5G and beyond 5G (B5G) networks**.  

The objective is to evaluate **encryption performance, throughput, and data handling efficiency** using benchmark comparisons and statistical analysis.  

---

## 🔹 Features & Objectives  

✅ **Hybrid AES-DES-RSA Encryption** → Strengthens security by leveraging symmetric and asymmetric cryptographic techniques.  
✅ **Performance Evaluation** → Analyzes encryption speed, computational efficiency, and throughput.  
✅ **Data Size Optimization** → Examines the impact of encryption on different data sizes.  
✅ **Benchmark Comparisons** → Evaluates encryption performance against standard cryptographic implementations.  
✅ **Graphical Analysis** → Compares results through detailed visualizations.  

---

## 📂 Repository Structure  

Hybrid-Crypto-5G/ │── data/ # Contains encryption-related JSON files │ ├── sbox_aes.json # AES S-Box modifications │ ├── sbox_des.json # DES S-Box modifications │ │── src/ # Source code implementation │ ├── main.py # Main encryption execution script │ ├── load_sbox.py # Code for loading S-Boxes from JSON files │ │── results/ # Stores performance evaluation results │ ├── encryption_speed.png │ ├── throughput_analysis.png │ │── notebooks/ # Jupyter Notebooks for analysis and visualization │ ├── Average_operation_time_and_Data_size.ipynb │ ├── Benchmark_Comparison.ipynb │ ├── Comparison_of_data_sizes.ipynb │ ├── Throughput_and_Encryption_Performance_Evaluation.ipynb │ │── docs/ # Documentation files │ ├── project_overview.md # This overview file │ │── README.md # General project documentation │── requirements.txt # Dependencies for running the code │── .gitignore # Files to ignore in the repository

---
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
##Proposed model
![proposed_model_diagram](https://github.com/user-attachments/assets/cf6a978d-a77a-48c2-95fe-20f1a4f69d2f)

----
## 📊 Results & Performance Analysis
📌 Key Findings:

AES-DES-RSA Hybrid Model: Provides a balance of speed, security, and encryption strength.
Performance Benchmarking: AES is faster, but hybrid encryption enhances security at a reasonable computational cost.
Throughput Analysis: Evaluates encryption efficiency under different data sizes.
Data Size Impact: Encryption methods vary in efficiency depending on data size, influencing real-world applications.
Graphical Representation: Jupyter Notebooks visualize trends across encryption techniques.
---
## 🤝 Contributors
Aman Kumar (Lead Developer & Researcher)
---
## 📖 References
Research Paper: Hybrid Cryptographic Approach for Strengthening 5G/B5G Security
Cryptographic Standards: AES, DES, RSA, and S-Box Theory
---
You're done! 🚀







