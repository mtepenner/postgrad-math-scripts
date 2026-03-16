#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

/**
 * @brief Comprehensive Statistics Engine for CSV/Google Sheets Data
 */
class StatsEngine {
public:
    // --- Descriptive Statistics ---
    
    static double Mean(const std::vector<double>& data) {
        if (data.empty()) return 0.0;
        return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    }

    static double Median(std::vector<double> data) {
        if (data.empty()) return 0.0;
        std::sort(data.begin(), data.end());
        size_t size = data.size();
        if (size % 2 == 0) return (data[size / 2 - 1] + data[size / 2]) / 2;
        return data[size / 2];
    }

    static double Variance(const std::vector<double>& data, bool isSample = true) {
        if (data.size() < 2) return 0.0;
        double avg = Mean(data);
        double sum = 0;
        for (double x : data) sum += std::pow(x - avg, 2);
        return sum / (data.size() - (isSample ? 1 : 0));
    }

    static double StdDev(const std::vector<double>& data) {
        return std::sqrt(Variance(data));
    }

    // --- CSV Calibration & Import ---

    static std::vector<double> ImportColumn(const std::string& filename, int colIndex, bool hasHeader = true) {
        std::vector<double> columnData;
        std::ifstream file(filename);
        std::string line;

        if (!file.is_open()) {
            std::cerr << "CRITICAL ERROR: Could not open " << filename << std::endl;
            return columnData;
        }

        if (hasHeader) std::getline(file, line); // Skip header

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string cell;
            int currentCtx = 0;

            while (std::getline(ss, cell, ',')) {
                if (currentCtx == colIndex) {
                    try {
                        // Remove potential whitespace or quotes from Google Sheet exports
                        cell.erase(std::remove(cell.begin(), cell.end(), '\"'), cell.end());
                        if (!cell.empty()) {
                            columnData.push_back(std::stod(cell));
                        }
                    } catch (...) {
                        // Skip non-numeric entries or empty cells gracefully
                    }
                }
                currentCtx++;
            }
        }
        return columnData;
    }
};

int main() {
    // --- CALIBRATION SETTINGS ---
    const std::string filename = "data_export.csv"; // Your exported Google Sheet name
    const int targetColumn = 0;                    // 0 = Col A, 1 = Col B, etc.
    
    std::cout << "========================================" << std::endl;
    std::cout << "   C++ UNIVERSAL STATISTICS ENGINE      " << std::endl;
    std::cout << "========================================" << std::endl;

    // Load Data
    std::vector<double> data = StatsEngine::ImportColumn(filename, targetColumn);

    if (data.empty()) {
        std::cout << "[!] No data found. Ensure " << filename << " is in the same folder." << std::endl;
        return 1;
    }

    // Output Results
    std::cout << "Records Processed: " << data.size() << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Mean:               " << StatsEngine::Mean(data) << std::endl;
    std::cout << "Median:             " << StatsEngine::Median(data) << std::endl;
    std::cout << "Sample Variance:    " << StatsEngine::Variance(data, true) << std::endl;
    std::cout << "Standard Deviation: " << StatsEngine::StdDev(data) << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
