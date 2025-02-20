#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "CrashData.h"

using namespace std;

void CrashData::loadCrashDataFromCSV(string filename) {
    ifstream file(filename);

    string collision_id, crash_date, crash_time, borough, zip_code, latitude, longitude, location, on_street_name, cross_street_name, off_street_name;
    string person_injured, person_killed, pedestrian_injured, pedestrian_killed, cyclist_injured, cyclist_killed, motorist_injured, motorist_killed;
    string contributing_factor_vehicle[5], vehicle_type_code[5];
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    string line;

    getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        getline(ss, crash_date, ',');
        getline(ss, crash_time, ',');

        getline(ss, borough, ',');
        getline(ss, zip_code, ',');
        getline(ss, latitude, ',');
        getline(ss, longitude, ',');
        getline(ss, location, ',');
        getline(ss, on_street_name, ',');
        getline(ss, cross_street_name, ',');
        getline(ss, off_street_name, ',');
        
        getline(ss, person_injured, ',');
        getline(ss, person_killed, ',');
        getline(ss, pedestrian_injured, ',');
        getline(ss, pedestrian_killed, ',');
        getline(ss, cyclist_injured, ',');
        getline(ss, cyclist_killed, ',');
        getline(ss, motorist_injured, ',');
        getline(ss, motorist_killed, ',');
        
        for (int i = 0; i < 5; i++) {
            getline(ss, contributing_factor_vehicle[i], ',');
        }

        getline(ss, collision_id, ',');

        for (int i = 0; i < 5; i++) {
            getline(ss, vehicle_type_code[i], ',');
        }

        crashes.emplace_back(collision_id, crash_date, crash_time, 
            borough, zip_code, latitude, longitude, on_street_name, cross_street_name, off_street_name,
            person_injured, person_killed, pedestrian_injured, pedestrian_killed, cyclist_injured, cyclist_killed, motorist_injured, motorist_killed,
            contributing_factor_vehicle, vehicle_type_code);
    }

    file.close();
}

vector<Crash> CrashData::searchByBorough(string borough) {
    vector<Crash> query_result;

    for (auto &crash: crashes) {
        if (crash.get_borough() == borough) {
            query_result.push_back(crash);
        }
    }

    return query_result;
}