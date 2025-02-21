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
    vector<Crash> thread_data(num_threads);

    cout << "Using " << num_threads << " threads." << endl;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        long start = thread_id * chunk_size;
        long end = (thread_id == num_threads - 1) ? file_size : start + chunk_size;

        ifstream file(filename);
        file.seekg(start);

        if (thread_id > 0) {
            string dummy;
            getline(file, dummy);
        }

        string line, temp, collision_id, crash_date, borough, person_injured, person_killed;
        while (file.tellg() < end && getline(file, line)) {
            stringstream ss(line);

            getline(ss, crash_date, ',');
            getline(ss, temp, ',');
            getline(ss, borough, ',');

            for (int i = 0; i < 7; i++) getline(ss, temp, ',');

            getline(ss, person_injured, ',');
            getline(ss, person_killed, ',');

            for (int i = 0; i < 11; i++) getline(ss, temp, ',');

            getline(ss, collision_id, ',');

            thread_data[thread_id].add_record(collision_id, crash_date, borough, person_injured, person_killed);
        }
    }

    for (auto& local_crash : thread_data) {
        crashes.get_collision_id().insert(crashes.get_collision_id().end(), local_crash.get_collision_id().begin(), local_crash.get_collision_id().end());
        crashes.get_crash_date().insert(crashes.get_crash_date().end(), local_crash.get_crash_date().begin(), local_crash.get_crash_date().end());
        crashes.get_borough().insert(crashes.get_borough().end(), local_crash.get_borough().begin(), local_crash.get_borough().end());
        crashes.get_person_injured().insert(crashes.get_person_injured().end(), local_crash.get_person_injured().begin(), local_crash.get_person_injured().end());
        crashes.get_person_killed().insert(crashes.get_person_killed().end(), local_crash.get_person_killed().begin(), local_crash.get_person_killed().end());
    }
}

vector<int> CrashData::searchByBorough(string borough) {
    vector<int> query_result;

    #pragma omp parallel
    {
        vector<string> boroughs = crashes.get_borough();
        vector<int> thread_result;

        #pragma omp for schedule(dynamic) nowait
        for (size_t i = 0; i < crashes.get_size(); i++) {
            if (boroughs[i] == borough) {
                thread_result.push_back(i);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_result.begin(), thread_result.end());
        }
    }

    return query_result;
}

vector<int> CrashData::searchByThreshold(int injury_threshold, int killed_threshold) {
    vector<int> query_result;

    #pragma omp parallel
    {
        vector<int> thread_result;
        vector<int> injuries = crashes.get_person_injured();
        vector<int> deaths = crashes.get_person_killed();

        #pragma omp for schedule(dynamic) nowait
        for (size_t i = 0; i < crashes.get_size(); i++) {
            if (injuries[i] >= injury_threshold || deaths[i] >= killed_threshold) {
                thread_result.push_back(i);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_result.begin(), thread_result.end());
        }
    }

    return query_result;
}