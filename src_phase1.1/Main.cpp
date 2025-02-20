#include <iostream>
#include <chrono>
#include <vector>
#include "CrashData.h"

using namespace std;

int main() {

    string filename = "../data/Motor_Vehicle_Collisions_-_Crashes_20250123.csv";

    auto start_time = chrono::high_resolution_clock::now();
    CrashData crash_data;
    crash_data.loadCrashDataFromCSV(filename);
    auto end_time = chrono::high_resolution_clock::now();
}