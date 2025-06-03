# 🎬 IBCF with Cosine Similarity

> **CMP2003 – Data Structures and Algorithms with C++**  
> 2024–2025 Fall Term Project  
> Bahçeşehir University — Department of Computer Engineering

A high-performance movie rating prediction system implemented in C++, using **Item-Based Collaborative Filtering (IBCF)** and **Cosine Similarity**.

---

## 🧠 Project Description

Recommender systems are widely used in modern digital platforms to suggest content to users based on their preferences. This project implements an IBCF-based recommender engine that predicts movie ratings for users based on item similarities.

We focused on accuracy, efficiency, and scalability — incorporating smart data structures, normalization techniques, and similarity caching to reduce runtime.

---

## 🎯 Objectives

- Implement a rating prediction system using IBCF with Cosine Similarity.
- Optimize runtime performance with caching and normalization.
- Handle large datasets efficiently using proper data structures like `unordered_map`.
- Provide accurate predictions with a robust similarity metric.

---

## 🛠 Technologies Used

- **Language**: C++20
- **Standard Libraries**: `<unordered_map>`, `<vector>`, `<algorithm>`, `<cmath>`, `<sstream>`, `<iostream>`
- **Build Tool**: CMake
- **Development Environment**: CLion / g++

---

## 🧱 Data Structures

| Name           | Type                                               | Purpose |
|----------------|----------------------------------------------------|---------|
| `data_map`     | `unordered_map<unsigned short, unordered_map<unsigned short, float>>` | Stores user ratings per film |
| `filmAvgMap`   | `unordered_map<unsigned short, float>`            | Stores average rating per film |
| `similarityCache` | `unordered_map<uint64_t, float>`               | Caches previously computed cosine similarities |
| `makeCacheKey` | Combines two film IDs into a unique 64-bit key     | Enables fast symmetric similarity lookup |

---

## ⚙️ How It Works

1. **Input Reading**
    - Reads from either `cin` (for HackerRank) or local `.txt` files (`public_training_data.txt`, `public_test_data.txt`).
2. **Preprocessing**
    - Computes average ratings for each film.
    - Normalizes all film ratings by subtracting the average.
3. **Similarity Calculation**
    - Calculates cosine similarity between film pairs.
    - Caches results using a hash-based key.
4. **Rating Prediction**
    - For a given user and film, selects top-K similar films the user rated.
    - Computes a weighted average of normalized scores and re-centers.

---

## 📦 File Structure

```
IBCF-with-Cosine-Similarity/
├── CMakeLists.txt                # Build instructions
├── LICENSE                      # License information
├── README.md                    # Project description and usage
├── data/                        # Dataset folder
│   ├── public_training_data.txt  # Training input data
│   └── public_test_data.txt      # Test input data
├── src/                         # Source code folder
│   ├── main.cpp                  # Main application logic
│   ├── ibcf.cpp                  # Core algorithm: similarity + prediction
│   ├── ibcf.h
│   ├── utils.cpp                 # Helper functions: normalization, average, etc.
│   └── utils.h
└── cmake-build-debug/           # CLion auto-generated build files (ignored in VCS)
```

---

## 🧪 Example Usage

**Running from CLI (with local test files):**
```bash
Input file format (training):
train dataset
10 100 4.0
10 101 5.0
...
test dataset
10 200
10 201
...

Output file format:
3.92
4.18
...
```
---

## 👥 Contributors

- [@OmerINKAYA](https://github.com/OmerINKAYA)
- [@thecloudrazor](https://github.com/thecloudrazor)
