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
            string cfv[], string vtc[])
            : collision_id(id), crash_date(cd), crash_time(ct), borough(b), on_street_name(osn), cross_street_name(csn), off_street_name(ofsn) {
            
            zip_code = stringToInt(zc);
            person_injured = stringToInt(inj_p);
            person_killed = stringToInt(kld_p);
            pedestrian_injured = stringToInt(inj_ped);
            pedestrian_killed = stringToInt(kld_ped);
            cyclist_injured = stringToInt(inj_cyc);
            cyclist_killed = stringToInt(kld_cyc);
            motorist_injured = stringToInt(inj_mtr);
            motorist_killed = stringToInt(kld_mtr);
        
            latitude = stringToFloat(lat);
            longitude = stringToFloat(lon);
        
            for (int i = 0; i < 5; i++) {
                contributing_factor_vehicle[i] = cfv[i];
                vehicle_type_code[i] = vtc[i];
            }
        }

        string get_borough() {
            return borough;
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

        int stringToInt(string &str) {
            if (!str.empty() && all_of(str.begin(), str.end(), ::isdigit)) {
                return stoi(str);
            }

            return 0;
        }

        float stringToFloat(string &str) {
            if (!str.empty()) {
                return stof(str);
            }

            return 0.0f;
        }
};

#endif