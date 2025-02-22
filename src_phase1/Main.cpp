#include <iostream>
#include <chrono>
#include <vector>
#include "CollisionDataset.h"

using namespace std;

int main() {
    //todo: change before copying to collaborative repo
    string file_name = "../data/Motor_Vehicle_Collisions_-_Crashes_20250123.csv";
    CollisionDataset dataset;

    auto start_time_load = chrono::high_resolution_clock::now();
    dataset.load_CSV(file_name);
    auto end_time_load = chrono::high_resolution_clock::now();

    cout << dataset.get_collisions().size() << " records loaded in ";
    cout << chrono::duration<double>(end_time_load - start_time_load).count() << " seconds." << endl;

    if (dataset.get_collisions().empty()) {
        cerr << "No data loaded, exiting.\n";
        return 1;
    }

    int zip_code = 11217;
    auto start_time_q1 = chrono::high_resolution_clock::now();
    vector<Collision> collisions_in_zipcode = dataset.search_by_zip_code(zip_code);
    auto end_time_q1 = chrono::high_resolution_clock::now();
    cout << collisions_in_zipcode.size() << " collision records matched for zipcode " << zip_code << " in ";
    cout << chrono::duration<double>(end_time_q1 - start_time_q1).count() << " seconds." << endl;

    int inj_low = 3, inj_high = 10;
    auto start_time_q2 = chrono::high_resolution_clock::now();
    vector<Collision> collisions_with_injuries = dataset.search_by_injury_ranges(inj_low, inj_high);
    auto end_time_q2 = chrono::high_resolution_clock::now();
    cout << collisions_with_injuries.size() << " collision records matched for [" << inj_low;
    cout << "," << inj_high << "] injuries " << " in ";
    cout << chrono::duration<double>(end_time_q2 - start_time_q2).count() << " seconds." << endl;

    float lat = 40.66684;
    auto start_time_q3 = chrono::high_resolution_clock::now();
    vector<Collision> collisions_on_latitude = dataset.search_by_latitude(lat);
    auto end_time_q3 = chrono::high_resolution_clock::now();
    cout << collisions_on_latitude.size() << " collision records matched for latitude " << lat << " in ";
    cout << chrono::duration<double>(end_time_q3 - start_time_q3).count() << " seconds." << endl;

    string start_date = "12/01/2021", end_date = "12/31/2021";
    auto start_time_q4 = chrono::high_resolution_clock::now();
    vector<Collision> collisions_in_date_range = dataset.search_by_date_range(start_date, end_date);
    auto end_time_q4 = chrono::high_resolution_clock::now();
    cout << collisions_in_date_range.size() << " collision records matched for date range [";
    cout << start_date << "," << end_date << "] in ";
    cout << chrono::duration<double>(end_time_q4 - start_time_q4).count() << " seconds." << endl;

    string borough = "MANHATTAN";
    auto start_time_q5 = chrono::high_resolution_clock::now();
    vector<Collision> collisions_in_borough = dataset.search_by_borough(borough);
    auto end_time_q5 = chrono::high_resolution_clock::now();
    cout << collisions_in_borough.size() << " collision records matched for borough " << borough << " in ";
    cout << chrono::duration<double>(end_time_q5 - start_time_q5).count() << " seconds." << endl;

    return 0;
}