#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <omp.h>
#include <sys/stat.h>
#include "CrashData.h"

using namespace std;

void CrashData::loadCrashDataFromCSV(string filename) {
    struct stat stat_buf;
    if (stat(filename.c_str(), &stat_buf) != 0) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }
    long file_size = stat_buf.st_size;

    int num_threads = 5;
    long chunk_size = file_size / num_threads;
    vector<vector<Crash>> thread_data(num_threads);

    cout << "Using " << num_threads << " threads." << endl;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        long start = thread_id * chunk_size;
        long end = (thread_id == num_threads - 1) ? file_size : start + chunk_size;

        ifstream file(filename);
        file.seekg(start);

        // Ensure we start at the beginning of a new line
        if (thread_id > 0) {
            string dummy;
            getline(file, dummy);
        }

        string line, temp, collision_id, crash_date, borough, person_injured, person_killed;
        while (file.tellg() < end && getline(file, line)) {
            stringstream ss(line);

            getline(ss, crash_date, ',');
            getline(ss, temp, ',');  // Skip one column
            getline(ss, borough, ',');

            for (int i = 0; i < 7; i++) getline(ss, temp, ',');

            getline(ss, person_injured, ',');
            getline(ss, person_killed, ',');

            for (int i = 0; i < 11; i++) getline(ss, temp, ',');

            getline(ss, collision_id, ',');

            thread_data[thread_id].emplace_back(collision_id, crash_date, borough, person_injured, person_killed);
        }
    }

    // Merge all thread data into the final crashes vector
    for (const auto& local_data : thread_data) {
        crashes.insert(crashes.end(), local_data.begin(), local_data.end());
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