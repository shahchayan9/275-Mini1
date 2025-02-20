#ifndef CRASH_H
#define CRASH_H

#include <string>
#include <vector>

using namespace std;

class Crash {
    public:
        Crash(const vector<string> &row) {
            if (row.size() < 27) {
                cout << "Error: Row has insufficient columns!" << endl;
                return;
            }

            collision_id = row[23];

            crash_date = row[0];
            crash_time = row[1];

            borough = row[2];
            zip_code = row[3].empty() ? 0 : stoi(row[3]);
            latitude = row[4].empty() ? 0.0f : stof(row[4]);
            longitude = row[5].empty() ? 0.0f : stof(row[5]);

            on_street_name = row[6];
            cross_street_name = row[7];
            off_street_name = row[8];

            person_injured = row[9].empty() ? 0 : stoi(row[9]);
            person_killed = row[10].empty() ? 0 : stoi(row[10]);
            pedestrian_injured = row[11].empty() ? 0 : stoi(row[11]);
            pedestrian_killed = row[12].empty() ? 0 : stoi(row[12]);
            cyclist_injured = row[13].empty() ? 0 : stoi(row[13]);
            cyclist_killed = row[14].empty() ? 0 : stoi(row[14]);
            motorist_injured = row[15].empty() ? 0 : stoi(row[15]);
            motorist_killed = row[16].empty() ? 0 : stoi(row[16]);

            for (int i = 0; i < 5; i++) {
                contributing_factor_vehicle[i] = row[17 + i];
                vehicle_type_code[i] = row[24 + i];
            }
        }
    
    private:
        string collision_id;
        
        string crash_date;
        string crash_time;
        
        string borough;
        int zip_code;
        float latitude;
        float longitude;
        string on_street_name;
        string cross_street_name;
        string off_street_name;

        int person_injured;
        int person_killed;
        int pedestrian_injured;
        int pedestrian_killed;
        int cyclist_injured;
        int cyclist_killed;
        int motorist_injured;
        int motorist_killed;

        string contributing_factor_vehicle[5];
        string vehicle_type_code[5];
};

#endif