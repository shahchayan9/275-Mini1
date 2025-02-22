#include <fstream>
#include <sstream>
#include <iostream>
#include "CollisionDataset.h"

using namespace std;

void CollisionDataset::load_CSV(string file_name) {
    ifstream file(file_name);

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << file_name << endl;
        return;
    }

    string line;
    getline(file, line);

    string collision_id, crash_date, crash_time, borough, zip_code, latitude, longitude, location, on_street_name, cross_street_name, off_street_name;
    string person_injured, person_killed, pedestrian_injured, pedestrian_killed, cyclist_injured, cyclist_killed, motorist_injured, motorist_killed;
    string contributing_factor_vehicle1, contributing_factor_vehicle2, contributing_factor_vehicle3, contributing_factor_vehicle4, contributing_factor_vehicle5;
    string vehicle_type_code1, vehicle_type_code2, vehicle_type_code3, vehicle_type_code4, vehicle_type_code5;

    while (getline(file, line)) {
        stringstream ss(line);
        
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

        collisions.emplace_back(
            collision_id, crash_date, crash_time, borough, zip_code, latitude, longitude, on_street_name, cross_street_name, off_street_name,
            person_injured, person_killed, pedestrian_injured, pedestrian_killed, cyclist_injured, cyclist_killed, motorist_injured, motorist_killed,
            contributing_factor_vehicle1, contributing_factor_vehicle2, contributing_factor_vehicle3, contributing_factor_vehicle4, contributing_factor_vehicle5,
            vehicle_type_code1, vehicle_type_code2, vehicle_type_code3, vehicle_type_code4, vehicle_type_code5
        );
        // AI-generated section end
    }

    file.close();
}

vector<Collision> CollisionDataset::search_by_zip_code(int zc) {
    vector<Collision> query_result;

    for (auto c: collisions) {
        if (c.get_zip_code() == zc) {
            query_result.emplace_back(c);
        }
    }

    return query_result;
}

vector<Collision> CollisionDataset::search_by_injury_ranges(int inj_low, int inj_high) {
    vector<Collision> query_result;

    for (auto c: collisions) {
        if (c.get_num_of_persons_injured() >= inj_low && c.get_num_of_persons_injured() <= inj_high) {
            query_result.emplace_back(c);
        }
    }

    return query_result;
}

vector<Collision> CollisionDataset::search_by_latitude(float lat) {
    vector<Collision> query_result;

    for (auto c: collisions) {
        if (c.get_latitude() == lat) {
            query_result.emplace_back(c);
        }
    }

    return query_result;
}

vector<Collision> CollisionDataset::search_by_date_range(string sd, string ed) {
    vector<Collision> query_result;
    
    int start_date = format_date(sd);
    int end_date = format_date(ed);
    
    for (auto c: collisions) {
        if (c.get_crash_date() >= start_date && c.get_crash_date() <= end_date) {
            query_result.emplace_back(c);
        }
    }

    return query_result;
}

vector<Collision> CollisionDataset::search_by_borough(string b) {
    vector<Collision> query_result;
    
    for (auto c: collisions) {
        if (c.get_borough() == b) {
            query_result.emplace_back(c);
        }
    }

    return query_result;
}