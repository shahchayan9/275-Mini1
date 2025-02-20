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
    
    if (crash_data.getCrashes().empty()) {
        cerr << "No data loaded. Exiting.\n";
        return 1;
    }

    cout << "Total records loaded: " << crash_data.getCrashes().size() << endl;
    cout << "Loading time: " << chrono::duration<double>(end_time - start_time).count() << " seconds.\n";

    start_time = chrono::high_resolution_clock::now();
    vector<Crash> brooklynCrashes = crash_data.searchByBorough("BROOKLYN");
    end_time = chrono::high_resolution_clock::now();

    cout << "Number of Brooklyn crashes: " << brooklynCrashes.size() << endl;
    cout << "Query time: " << chrono::duration<double>(end_time - start_time).count() << " seconds.\n";

}