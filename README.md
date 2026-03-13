# Postgrad Math Scripts

A collection of professional, independent C++ utility scripts designed to solve common mathematical, chemical, and physical problems. This repository serves as a multi-tool for students and developers, now featuring an integrated LLM parser to solve word problems automatically.

## 📚 Table of Contents

* [Features](#-features)
* [Technologies Used](#-technologies-used)
* [Installation](#-installation)
* [Usage](#-usage)
* [Scripts Overview](#-scripts-overview)

## ✨ Features

* **Geometry Multi-Tool**: Calculate area, perimeter, volume, and surface area for 2D and 3D shapes, plus Pythagorean and trigonometric functions.
* **Matrix Solver**: Solve systems of linear equations using Gaussian Elimination with partial pivoting for numerical stability.
* **Polynomial Root Finder**: Find all complex roots of a polynomial using the Durand-Kerner algorithm and Horner's method for efficient evaluation.
* **Chemical Equation Balancer**: A brute-force algorithmic solver to find the lowest whole-number coefficients for complex chemical reactions.
* **Kinematics Auto-Solver**: Input known kinematic variables to automatically calculate missing displacement, initial/final velocity, acceleration, and time.
* **AI Word Problem Solver**: Integrates with external LLM APIs to parse plain-English word problems, extract known variables, and automatically route them to the correct mathematical solver.
* **Robust Error Handling**: Includes checks for singular matrices, zero leading coefficients, and unsolvable kinematic systems.

## 💻 Technologies Used

* **Language**: C++11 or higher
* **Standard Libraries**: `<iostream>`, `<vector>`, `<complex>`, `<cmath>`, `<iomanip>`, `<string>`
* **External Dependencies**: `libcurl` (required for LLM API integration)

## ⚙️ Installation

1. Clone the repository:
```bash
git clone [https://github.com/yourusername/postgrad-custom-independent-scripts.git](https://github.com/mtepenner/postgrad-custom-independent-scripts.git)
```
