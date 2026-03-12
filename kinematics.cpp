#include <iostream>
#include <cmath>
#include <string>

using namespace std;

// We use an exceptionally low number to represent an "Unknown" variable
const double UNKNOWN = -99999.99;

// Helper function to check if a variable is known
bool isKnown(double var) {
    return var != UNKNOWN;
}

// Function to safely get user input
double getVariableInput(string varName) {
    string input;
    cout << "Enter " << varName << " (or type '?' if unknown): ";
    cin >> input;
    if (input == "?") {
        return UNKNOWN;
    }
    return stod(input); // Convert string to double
}

void solveKinematics() {
    cout << "\n--- High School Kinematics Auto-Solver ---\n";
    cout << "You will be prompted for the 5 kinematic variables.\n";
    cout << "Enter your known values, and type '?' for the ones you don't know.\n\n";

    double d = getVariableInput("Displacement (d)");
    double vi = getVariableInput("Initial Velocity (vi)");
    double vf = getVariableInput("Final Velocity (vf)");
    double a = getVariableInput("Acceleration (a)");
    double t = getVariableInput("Time (t)");

    cout << "\nCalculating missing variables...\n";

    // Loop until all 5 variables are known
    // We use a simple counter to prevent infinite loops if the user didn't provide enough data
    int passes = 0;
    while ((!isKnown(d) || !isKnown(vi) || !isKnown(vf) || !isKnown(a) || !isKnown(t)) && passes < 3) {
        
        // Equation 1: vf = vi + a*t
        if (!isKnown(vf) && isKnown(vi) && isKnown(a) && isKnown(t)) vf = vi + a * t;
        if (!isKnown(vi) && isKnown(vf) && isKnown(a) && isKnown(t)) vi = vf - a * t;
        if (!isKnown(a) && isKnown(vf) && isKnown(vi) && isKnown(t)) a = (vf - vi) / t;
        if (!isKnown(t) && isKnown(vf) && isKnown(vi) && isKnown(a)) t = (vf - vi) / a;

        // Equation 2: d = vi*t + 0.5*a*t^2
        if (!isKnown(d) && isKnown(vi) && isKnown(t) && isKnown(a)) d = vi * t + 0.5 * a * pow(t, 2);
        if (!isKnown(vi) && isKnown(d) && isKnown(t) && isKnown(a)) vi = (d - 0.5 * a * pow(t, 2)) / t;
        if (!isKnown(a) && isKnown(d) && isKnown(vi) && isKnown(t)) a = (2 * (d - vi * t)) / pow(t, 2);
        // Solving for t here requires the quadratic formula, handled via Equation 3 instead for simplicity

        // Equation 3: vf^2 = vi^2 + 2*a*d
        if (!isKnown(vf) && isKnown(vi) && isKnown(a) && isKnown(d)) vf = sqrt(pow(vi, 2) + 2 * a * d);
        if (!isKnown(vi) && isKnown(vf) && isKnown(a) && isKnown(d)) vi = sqrt(pow(vf, 2) - 2 * a * d);
        if (!isKnown(a) && isKnown(vf) && isKnown(vi) && isKnown(d)) a = (pow(vf, 2) - pow(vi, 2)) / (2 * d);
        if (!isKnown(d) && isKnown(vf) && isKnown(vi) && isKnown(a)) d = (pow(vf, 2) - pow(vi, 2)) / (2 * a);

        // Equation 4: d = ((vi + vf) / 2) * t
        if (!isKnown(d) && isKnown(vi) && isKnown(vf) && isKnown(t)) d = ((vi + vf) / 2.0) * t;
        if (!isKnown(vi) && isKnown(d) && isKnown(vf) && isKnown(t)) vi = (2 * d / t) - vf;
        if (!isKnown(vf) && isKnown(d) && isKnown(vi) && isKnown(t)) vf = (2 * d / t) - vi;
        if (!isKnown(t) && isKnown(d) && isKnown(vi) && isKnown(vf)) t = (2 * d) / (vi + vf);

        passes++;
    }

    // Check if the program successfully found everything
    if (!isKnown(d) || !isKnown(vi) || !isKnown(vf) || !isKnown(a) || !isKnown(t)) {
        cout << "Error: Not enough information provided to solve the system. You must provide at least 3 knowns.\n";
    } else {
        cout << "--- Solved System ---\n";
        cout << "Displacement (d)       = " << d << " m\n";
        cout << "Initial Velocity (vi)  = " << vi << " m/s\n";
        cout << "Final Velocity (vf)    = " << vf << " m/s\n";
        cout << "Acceleration (a)       = " << a << " m/s^2\n";
        cout << "Time (t)               = " << t << " s\n";
    }
}

int main() {
    solveKinematics();
    return 0;
}
