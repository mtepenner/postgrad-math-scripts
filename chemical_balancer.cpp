#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int numElements;
    cout << "--- Chemical Equation Balancer (A + B -> C + D) ---\n";
    cout << "Enter the number of unique elements in the reaction: ";
    cin >> numElements;

    vector<string> elementNames(numElements);
    vector<int> R1(numElements), R2(numElements), P1(numElements), P2(numElements);

    // Collect the atomic breakdown of each molecule from the user
    for (int i = 0; i < numElements; ++i) {
        cout << "\nEnter symbol for element " << i + 1 << " (e.g., C, H, O): ";
        cin >> elementNames[i];
        
        cout << "How many " << elementNames[i] << " atoms in Reactant 1? (Enter 0 if none): ";
        cin >> R1[i];
        cout << "How many " << elementNames[i] << " atoms in Reactant 2? (Enter 0 if none): ";
        cin >> R2[i];
        cout << "How many " << elementNames[i] << " atoms in Product 1?  (Enter 0 if none): ";
        cin >> P1[i];
        cout << "How many " << elementNames[i] << " atoms in Product 2?  (Enter 0 if none): ";
        cin >> P2[i];
    }

    cout << "\nCalculating balanced coefficients...\n";

    // Brute force search for the lowest whole-number coefficients
    int limit = 20; // Maximum coefficient to check
    bool found = false;

    // Iterate through every possible combination of a, b, c, and d
    for (int a = 1; a <= limit && !found; ++a) {
        for (int b = 1; b <= limit && !found; ++b) {
            for (int c = 1; c <= limit && !found; ++c) {
                for (int d = 1; d <= limit && !found; ++d) {
                    
                    bool balanced = true;
                    
                    // Check if all elements are balanced with the current guess
                    for (int i = 0; i < numElements; ++i) {
                        if ((a * R1[i] + b * R2[i]) != (c * P1[i] + d * P2[i])) {
                            balanced = false;
                            break; // Move on to the next guess immediately
                        }
                    }

                    // If the loop finished and all elements matched, we found the answer
                    if (balanced) {
                        cout << "\n--- Balanced Equation Coefficients ---\n";
                        cout << "Reactant 1 coefficient (a): " << a << "\n";
                        cout << "Reactant 2 coefficient (b): " << b << "\n";
                        cout << "Product 1 coefficient  (c): " << c << "\n";
                        cout << "Product 2 coefficient  (d): " << d << "\n";
                        found = true;
                    }
                }
            }
        }
    }

    if (!found) {
        cout << "\nCould not find balancing coefficients under " << limit << ". The equation may be invalid or requires larger numbers.\n";
    }

    return 0;
}
