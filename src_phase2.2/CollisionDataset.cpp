#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <omp.h>
#include "CollisionDataset.h"

using namespace std;

void CollisionDataset::load_CSV(string file_name) {
    ifstream file(file_name);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }

    string line;
    vector<string> lines;
    
    getline(file, line);

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    #pragma omp parallel
    {
        vector<Collision> thread_collisions;

        #pragma omp for
        for (size_t i = 0; i < lines.size(); i++) {
            stringstream ss(lines[i]);
            
            string collision_id, crash_date, crash_time, borough, zip_code, latitude, longitude, location, on_street_name, cross_street_name, off_street_name;
            string person_injured, person_killed, pedestrian_injured, pedestrian_killed, cyclist_injured, cyclist_killed, motorist_injured, motorist_killed;
            string contributing_factor_vehicle1, contributing_factor_vehicle2, contributing_factor_vehicle3, contributing_factor_vehicle4, contributing_factor_vehicle5;
            string vehicle_type_code1, vehicle_type_code2, vehicle_type_code3, vehicle_type_code4, vehicle_type_code5;
            
            // AI-generated section start
            getline(ss, crash_date, ',');
            getline(ss, crash_time, ',');

            getline(ss, borough, ',');
            getline(ss, zip_code, ',');
            getline(ss, latitude, ',');
            getline(ss, longitude, ',');

            getline(ss, location, ',');
            if (!location.empty())
                getline(ss, location, ','); // dummy double read to ignore location data when present

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

            getline(ss, contributing_factor_vehicle1, ',');
            getline(ss, contributing_factor_vehicle2, ',');
            getline(ss, contributing_factor_vehicle3, ',');
            getline(ss, contributing_factor_vehicle4, ',');
            getline(ss, contributing_factor_vehicle5, ',');

            getline(ss, collision_id, ',');

            getline(ss, vehicle_type_code1, ',');
            getline(ss, vehicle_type_code2, ',');
            getline(ss, vehicle_type_code3, ',');
            getline(ss, vehicle_type_code4, ',');
            getline(ss, vehicle_type_code5, ',');

            thread_collisions.emplace_back(
                collision_id, crash_date, crash_time, borough, zip_code, latitude, longitude, on_street_name, cross_street_name, off_street_name,
                person_injured, person_killed, pedestrian_injured, pedestrian_killed, cyclist_injured, cyclist_killed, motorist_injured, motorist_killed,
                contributing_factor_vehicle1, contributing_factor_vehicle2, contributing_factor_vehicle3, contributing_factor_vehicle4, contributing_factor_vehicle5,
                vehicle_type_code1, vehicle_type_code2, vehicle_type_code3, vehicle_type_code4, vehicle_type_code5
            );
            // AI-generated section end
        }

        #pragma omp critical
        {
            collisions.insert(collisions.end(), thread_collisions.begin(), thread_collisions.end());
        }
    }
}

vector<Collision> CollisionDataset::search_by_zip_code(int zc) {
    vector<Collision> query_result;

    #pragma omp parallel
    {
        vector<Collision> thread_results;

        #pragma omp for
        for (size_t i = 0; i < collisions.size(); i++) {
            if (collisions[i].get_zip_code() == zc) {
                thread_results.emplace_back(collisions[i]);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_results.begin(), thread_results.end());
        }
    }    

    return query_result;
}

vector<Collision> CollisionDataset::search_by_injury_ranges(int inj_low, int inj_high) {
    vector<Collision> query_result;

    #pragma omp parallel
    {
        vector<Collision> thread_results;

        #pragma omp for
        for (size_t i = 0; i < collisions.size(); i++) {
            if (collisions[i].get_num_of_persons_injured() >= inj_low && collisions[i].get_num_of_persons_injured() <= inj_high) {
                thread_results.emplace_back(collisions[i]);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_results.begin(), thread_results.end());
        }
    }

    return query_result;
}

vector<Collision> CollisionDataset::search_by_latitude(float lat) {
    vector<Collision> query_result;

    #pragma omp parallel
    {
        vector<Collision> thread_results;

        #pragma omp for
        for (size_t i = 0; i < collisions.size(); i++) {
            if (collisions[i].get_latitude() == lat) {
                thread_results.emplace_back(collisions[i]);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_results.begin(), thread_results.end());
        }
    }

    return query_result;
}

vector<Collision> CollisionDataset::search_by_date_range(string sd, string ed) {
    vector<Collision> query_result;
    
    int start_date = format_date(sd);
    int end_date = format_date(ed);

    #pragma omp parallel
    {
        vector<Collision> thread_results;

        #pragma omp for
        for (size_t i = 0; i < collisions.size(); i++) {
            if (collisions[i].get_crash_date() >= start_date && collisions[i].get_crash_date() <= end_date) {
                thread_results.emplace_back(collisions[i]);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_results.begin(), thread_results.end());
        }
    }

    return query_result;
}

vector<Collision> CollisionDataset::search_by_borough(string b) {
    vector<Collision> query_result;

    #pragma omp parallel
    {
        vector<Collision> thread_results;

        #pragma omp for
        for (size_t i = 0; i < collisions.size(); i++) {
            if (collisions[i].get_borough() == b) {
                thread_results.emplace_back(collisions[i]);
            }
        }

        #pragma omp critical
        {
            query_result.insert(query_result.end(), thread_results.begin(), thread_results.end());
        }
    }

    return query_result;
}