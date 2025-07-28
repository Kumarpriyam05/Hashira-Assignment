#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

unsigned long long toDecimal(const string& value, int base) {
    unsigned long long result = 0;
    for (char c : value) {
        int digit = isdigit(c) ? c - '0' : tolower(c) - 'a' + 10;
        result = result * base + digit;
    }
    return result;
}

unsigned long long lagrangeInterpolation(const vector<pair<int, unsigned long long>>& points) {
    long double result = 0.0;
    for (size_t i = 0; i < points.size(); i++) {
        long double term = points[i].second;
        for (size_t j = 0; j < points.size(); j++) {
            if (i != j)
                term *= (0.0 - points[j].first) / (points[i].first - points[j].first);
        }
        result += term;
    }
    return round(result);
}

void solve(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Could not open file: " << filename << endl;
        return;
    }

    json data;
    file >> data;

    int k = data["keys"]["k"];
    vector<pair<int, unsigned long long>> points;

  for (auto it = data.begin(); it != data.end(); ++it) {
    string key = it.key();
    if (key == "keys") continue;

    json val = it.value();
    int x = stoi(key);
    int base = stoi(val["base"].get<string>());
    string value = val["value"];
    unsigned long long y = toDecimal(value, base);
    points.emplace_back(x, y);
}


    vector<pair<int, unsigned long long>> selected(points.begin(), points.begin() + k);
    unsigned long long secret = lagrangeInterpolation(selected);
    cout << "Secret (c) for file " << filename << " = " << secret << endl;
}

int main() {
    solve("testcase1.json");
    solve("testcase2.json");
    return 0;
}
