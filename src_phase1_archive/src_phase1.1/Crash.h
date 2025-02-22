#ifndef CRASH_H
#define CRASH_H

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

class Crash {
    public:
        Crash(string id, string cd, string ct, string b, string zc, string lat, string lon, string osn, string csn, string ofsn,
                string inj_p, string kld_p, string inj_ped, string kld_ped, string inj_cyc, string kld_cyc, string inj_mtr, string kld_mtr,
                string cfv[], string vtc[]) {
            
            collision_id = trim_string(id);
            crash_date = trim_string(cd);
            crash_time = trim_string(ct);
            borough = trim_string(b);
            on_street_name = trim_string(osn);
            cross_street_name = trim_string(csn);
            off_street_name = trim_string(ofsn);
            
            zip_code = string_to_int(zc);
            person_injured = string_to_int(inj_p);
            person_killed = string_to_int(kld_p);
            pedestrian_injured = string_to_int(inj_ped);
            pedestrian_killed = string_to_int(kld_ped);
            cyclist_injured = string_to_int(inj_cyc);
            cyclist_killed = string_to_int(kld_cyc);
            motorist_injured = string_to_int(inj_mtr);
            motorist_killed = string_to_int(kld_mtr);
        
            latitude = string_to_float(lat);
            longitude = string_to_float(lon);
        
            for (int i = 0; i < 5; i++) {
                contributing_factor_vehicle[i] = cfv[i];
                vehicle_type_code[i] = vtc[i];
            }
        }

        string get_borough() {
            return borough;
        }

        int get_person_injured() {
            return person_injured;
        }

        int get_person_killed() {
            return person_killed;
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

        string trim_string(string &str) {
            size_t first = str.find_first_not_of(" \t\n\r");
            size_t last = str.find_last_not_of(" \t\n\r");

            if (first == string::npos)
                return "N/A";
            
            return str.substr(first, (last - first + 1));
        }

        int string_to_int(string &str) {
            if (!str.empty() && all_of(str.begin(), str.end(), ::isdigit)) {
                return stoi(str);
            }

            return 0;
        }

        float string_to_float(string &str) {
            if (!str.empty()) {
                return stof(str);
            }

            return 0.0f;
        }
};

#endif