#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <map>

class StatsEngine {
public:
    // Descriptive Statistics
    static double Mean(const std::vector<double>& data) {
        return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    }

    static double Median(std::vector<double> data) {
        std::sort(data.begin(), data.end());
        size_t size = data.size();
        if (size % 2 == 0) return (data[size/2 - 1] + data[size/2]) / 2;
        return data[size/2];
    }

    static double Variance(const std::vector<double>& data, bool isSample = true) {
        double avg = Mean(data);
        double sum = 0;
        for (double x : data) sum += std::pow(x - avg, 2);
        return sum / (data.size() - (isSample ? 1 : 0));
    }

    static double StdDev(const std::vector<double>& data) {
        return std::sqrt(Variance(data));
    }

    // Correlation (Pearson)
    static double Correlation(const std::vector<double>& x, const std::vector<double>& y) {
        double meanX = Mean(x), meanY = Mean(y);
        double num = 0, denX = 0, denY = 0;
        for (size_t i = 0; i < x.size(); ++i) {
            num += (x[i] - meanX) * (y[i] - meanY);
            denX += std::pow(x[i] - meanX, 2);
            denY += std::pow(y[i] - meanY, 2);
        }
        return num / std::sqrt(denX * denY);
    }
};

int main() {
    std::vector<double> dataset = {12.5, 14.2, 10.8, 11.1, 15.4, 13.9};

    std::cout << "--- Statistics Report ---" << std::endl;
    std::cout << "Mean:   " << StatsEngine::Mean(dataset) << std::endl;
    std::cout << "Median: " << StatsEngine::Median(dataset) << std::endl;
    std::cout << "StdDev: " << StatsEngine::StdDev(dataset) << std::endl;

    return 0;
}
