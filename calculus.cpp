#include <iostream>
#include <cmath>
#include <vector>
#include <string>

// Structure to handle 3D Vectors
struct Vector3 {
    double x, y, z;

    void print(std::string label) const {
        std::cout << label << ": <" << x << ", " << y << ", " << z << ">\n";
    }
};

// --- Vector Operations (3-Dimensional Space Section) ---

double dotProduct(Vector3 a, Vector3 b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vector3 crossProduct(Vector3 a, Vector3 b) {
    return {
        (a.y * b.z) - (a.z * b.y),
        (a.z * b.x) - (a.x * b.z),
        (a.x * b.y) - (a.y * b.x)
    };
}

double magnitude(Vector3 a) {
    return std::sqrt(std::pow(a.x, 2) + std::pow(a.y, 2) + std::pow(a.z, 2));
}

// --- Partial Derivatives (Partial Derivatives Section) ---
// Using numerical differentiation (Difference Quotient) 
// for a function f(x, y, z) = x^2 + y*z
double f(double x, double y, double z) {
    return std::pow(x, 2) + (y * z); 
}

double partialX(double x, double y, double z, double h = 1e-7) {
    return (f(x + h, y, z) - f(x, y, z)) / h;
}

double partialY(double x, double y, double z, double h = 1e-7) {
    return (f(x, y + h, z) - f(x, y, z)) / h;
}

// --- Gradient Vector ---
Vector3 gradient(double x, double y, double z) {
    return {partialX(x, y, z), partialY(x, y, z), (f(x, y, z + 1e-7) - f(x, y, z)) / 1e-7};
}

int main() {
    std::cout << "--- Calculus III Problem Solver ---\n\n";

    // Example 1: Vector Arithmetic (from 3D Space Chapter)
    Vector3 v1 = {1, 3, -2};
    Vector3 v2 = {4, -1, 0};

    std::cout << "1. Vector Operations:\n";
    v1.print("Vector A");
    v2.print("Vector B");
    std::cout << "Dot Product: " << dotProduct(v1, v2) << "\n";
    crossProduct(v1, v2).print("Cross Product (AxB)");
    std::cout << "Magnitude of A: " << magnitude(v1) << "\n\n";

    // Example 2: Partial Derivatives & Gradient (from Partial Derivatives Chapter)
    double px = 2.0, py = 1.0, pz = 3.0;
    std::cout << "2. Partial Derivatives for f(x,y,z) = x^2 + yz at (2, 1, 3):\n";
    std::cout << "df/dx: " << partialX(px, py, pz) << "\n";
    std::cout << "df/dy: " << partialY(px, py, pz) << "\n";
    gradient(px, py, pz).print("Gradient Vector");

    return 0;
}
