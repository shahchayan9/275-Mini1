#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "CrashData.h"

using namespace std;

void CrashData::loadCrashDataFromCSV(string filename) {
    ifstream file(filename);

    string collision_id, crash_date, borough, person_injured, person_killed;
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    string line, temp;

    getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        getline(ss, crash_date, ',');
        getline(ss, temp, ',');

        getline(ss, borough, ',');

        for (int i = 0; i < 7; i++) {
            getline(ss, temp, ',');
        }
        
        getline(ss, person_injured, ',');
        getline(ss, person_killed, ',');

        for (int i = 0; i < 11; i++) {
            getline(ss, temp, ',');
        }

        getline(ss, collision_id, ',');

        crashes.emplace_back(collision_id, crash_date, borough, person_injured, person_killed);
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

vector<Crash> CrashData::searchByThreshold(int injury_threshold, int killed_threshold) {
    vector<Crash> query_result;

    for (auto &crash: crashes) {
        if (crash.get_person_injured() >= injury_threshold || crash.get_person_killed() >= killed_threshold) {
            query_result.push_back(crash);
        }
    }

    return query_result;
}