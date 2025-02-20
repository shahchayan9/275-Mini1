#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <omp.h>
#include "CrashData.h"

using namespace std;

void CrashData::loadCrashDataFromCSV(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    vector<string> lines;
    string line;
    
    getline(file, line);

    while (getline(file, line)) {
        lines.push_back(line);
    }
    
    file.close();

    int thread_count = omp_get_max_threads();
    //cout << "Threads used: " << thread_count << endl;

    crashes.reserve(lines.size());

    #pragma omp parallel
    {
        vector<Crash> thread_data;
        thread_data.reserve(lines.size() / thread_count);

        #pragma omp for schedule(dynamic) nowait
        for (size_t i = 0; i < lines.size(); i++) {
            stringstream ss(lines[i]);
            string temp, collision_id, crash_date, borough, person_injured, person_killed;

            getline(ss, crash_date, ',');
            getline(ss, temp, ',');
            getline(ss, borough, ',');

            for (int j = 0; j < 7; j++) getline(ss, temp, ',');

            getline(ss, person_injured, ',');
            getline(ss, person_killed, ',');

            for (int j = 0; j < 11; j++) getline(ss, temp, ',');

            getline(ss, collision_id, ',');

            thread_data.emplace_back(collision_id, crash_date, borough, person_injured, person_killed);
        }

        #pragma omp critical
        {
            crashes.insert(crashes.end(), thread_data.begin(), thread_data.end());
        }
    }
}

vector<Crash> CrashData::searchByBorough(string borough) {
    vector<Crash> query_result;

    #pragma omp parallel
    {
        vector<Crash> thread_result;

        #pragma omp for schedule(dynamic) nowait
        for (size_t i = 0; i < crashes.size(); i++) {
            if (crashes[i].get_borough() == borough) {
                thread_result.push_back(crashes[i]);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_result.begin(), thread_result.end());
        }   
    }

    return query_result;
}

vector<Crash> CrashData::searchByThreshold(int injury_threshold, int killed_threshold) {
    vector<Crash> query_result;

    #pragma omp parallel
    {
        vector<Crash> thread_result;

        #pragma omp for schedule(dynamic) nowait
        for (size_t i = 0; i < crashes.size(); i++) {
            if (crashes[i].get_person_injured() >= injury_threshold || crashes[i].get_person_killed() >= killed_threshold) {
                thread_result.push_back(crashes[i]);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_result.begin(), thread_result.end());
        }   
    }

    return query_result;
}