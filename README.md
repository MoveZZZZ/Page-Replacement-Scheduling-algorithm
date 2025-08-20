# 📊 Page Replacement & CPU Scheduling Algorithms

[![Language](https://img.shields.io/badge/C%2B%2B-17%2B-blue)]()
[![Category](https://img.shields.io/badge/Algorithms-Scheduling%20%7C%20Paging-brightgreen)]()

An educational **C++** project that implements and compares classic **CPU scheduling** and **page replacement** strategies.  
Run repeatable experiments using input files, and save results for later analysis.

---

## ✅ Implemented Algorithms

### 🔹 CPU Scheduling
- **FCFS** — First Come First Serve  
- **LCFS** — Last Come First Serve  
- **SJF** — Shortest Job First  

### 🔹 Page Replacement
- **LRU** — Least Recently Used  
- **LFU** — Least Frequently Used  
- **MFU** — Most Frequently Used  

---

## 📁 Project Structure

```
Page-Replacement-Scheduling-algorithm-alg/
├─ include/                        # Header files
│  ├─ cAlgorithm_FCFS_LCFS_SJF.h
│  ├─ cAlgorithm_LRU_LFU_MFU.h
│  ├─ cOperationFile_FCFS_LCFS_SJF.h
│  ├─ cOperationFile_LRU_LFU_MFU.h
│  └─ cController.h
├─ src/                            # Source files
│  ├─ cAlgorithm_FCFS_LCFS_SJF.cpp
│  ├─ cAlgorithm_LRU_LFU_MFU.cpp
│  ├─ cOperationFile_FCFS_LCFS_SJF.cpp
│  ├─ cOperationFile_LRU_LFU_MFU.cpp
│  ├─ cController.cpp
│  └─ main.cpp                     # Entry point
└─ txt/                            # Inputs and results
   ├─ DaneFCFS_LCFS_SJF.txt
   ├─ DaneLRU_LFU_MFU.txt
   ├─ DaneOstatnioTestowaneFCFS_LCFS_SJF.txt
   ├─ DaneOstatnioTestowaneLRU_LFU_MFU.txt
   ├─ WynikiFCFS_LCFS_SJF.txt
   └─ WynikiLRU_LFU_MFU.txt
```

---

## ⚙️ Requirements

- **C++17** (or newer) toolchain (GCC/Clang/MSVC)
- Works on **Linux**, **Windows**, and **macOS** (CLI application)

---

## 🔧 Build & Run

### Linux / macOS (GCC/Clang)
```bash
g++ src/*.cpp -Iinclude -O2 -std=c++17 -o algorithms
./algorithms
```

### Windows (MSVC, Developer Command Prompt)
```bat
cl /std:c++17 /O2 /I include src\*.cpp /Fe:algorithms.exe
algorithms.exe
```

---

## 🗂️ Input & Output

- Provide input data in the `txt/` directory:
  - `DaneFCFS_LCFS_SJF.txt` — job list for **FCFS/LCFS/SJF**
  - `DaneLRU_LFU_MFU.txt` — page-reference sequence for **LRU/LFU/MFU**
- The program writes results to:
  - `WynikiFCFS_LCFS_SJF.txt`
  - `WynikiLRU_LFU_MFU.txt`

> Tip: keep separate input files per experiment and commit both inputs and resulting outputs for reproducibility.

---

## 🧩 Design Notes

- **OOP architecture**: each algorithm is encapsulated in its own class.
- A central **Controller** coordinates loading inputs, running simulations, and saving outputs.
- File I/O helpers in `cOperationFile_*` manage reading/writing datasets.

---

## 🧪 What to Compare

For scheduling:
- Average **waiting time**, **turnaround time**, **response time**.

For paging:
- Number of **page faults**, **hit ratio**, and **fault rate** vs. reference string length.

*(Exact metrics depend on how you configure the inputs.)*

---
