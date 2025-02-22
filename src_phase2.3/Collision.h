#ifndef CRASH_H
#define CRASH_H

#include <string>
#include <algorithm>
#include <iostream>
#include <cctype>

using namespace std;

class Collision {
    private:
        string collision_id;
        
        int crash_date;
        int crash_time;
        
        string borough;
        int zip_code;
        float latitude;
        float longitude;
        // string location;  // skipped because redundant (latitude, longitude)
        string on_street_name;
        string cross_street_name;
        string off_street_name;

        int num_of_persons_injured;
        int num_of_persons_killed;
        int num_of_pedestrians_injured;
        int num_of_pedestrians_killed;
        int num_of_cyclists_injured;
        int num_of_cyclists_killed;
        int num_of_motorists_injured;
        int num_of_motorists_killed;
        
        string contributing_factor_vehicle1;
        string contributing_factor_vehicle2;
        string contributing_factor_vehicle3;
        string contributing_factor_vehicle4;
        string contributing_factor_vehicle5;

        string vehicle_type_code1;
        string vehicle_type_code2;
        string vehicle_type_code3;
        string vehicle_type_code4;
        string vehicle_type_code5;

    public:
        int format_date(string date) {
            if (date.empty() || date.length() != 10)
                return 0;
            
            return stoi(date.substr(6, 4) + date.substr(0, 2) + date.substr(3, 2));
        }
        
        int format_time(string time) {
            if (time.empty() || time.length() != 5)
                return 0;
            
            return stoi(time.substr(0, 2) + time.substr(3, 2));
        }

        int string_to_int(string str) {
            if (str.empty() || !all_of(str.begin(), str.end(), ::isdigit))
                return 0;

            return stoi(str);
        }

        string trim_string(string str) {
            size_t first = str.find_first_not_of(" \t\n\r");
            size_t last = str.find_last_not_of(" \t\n\r");

            if (first == string::npos)
                return "N/A";
            
            return str.substr(first, (last - first + 1));
        }
        
        Collision(string id, string cd, string ct, string b, string zc, string l1, string l2, string on_sn, string cr_sn, string off_sn,
                    string prsn_inj, string prsn_kld, string pdstr_inj, string pdstr_kld, string cyc_inj, string cyc_kld, string mtr_inj, string mtr_kld,
                    string cfv1, string cfv2, string cfv3, string cfv4, string cfv5, string vtc1, string vtc2, string vtc3, string vtc4, string vtc5) {
            
            crash_date = format_date(cd);
            crash_time = format_time(ct);

            collision_id = trim_string(id);
            borough = trim_string(b);
            on_street_name = trim_string(on_sn);
            cross_street_name = trim_string(cr_sn);
            off_street_name = trim_string(off_sn);
            contributing_factor_vehicle1 = trim_string(cfv1);
            contributing_factor_vehicle2 = trim_string(cfv2);
            contributing_factor_vehicle3 = trim_string(cfv3);
            contributing_factor_vehicle4 = trim_string(cfv4);
            contributing_factor_vehicle5 = trim_string(cfv5);
            vehicle_type_code1 = trim_string(vtc1);
            vehicle_type_code2 = trim_string(vtc2);
            vehicle_type_code3 = trim_string(vtc3);
            vehicle_type_code4 = trim_string(vtc4);
            vehicle_type_code5 = trim_string(vtc5);

            zip_code = string_to_int(zc);
            num_of_persons_injured = string_to_int(prsn_inj);
            num_of_persons_killed = string_to_int(prsn_kld);
            num_of_pedestrians_injured = string_to_int(pdstr_inj);
            num_of_pedestrians_killed = string_to_int(pdstr_kld);
            num_of_cyclists_injured = string_to_int(cyc_inj);
            num_of_cyclists_killed = string_to_int(cyc_kld);
            num_of_motorists_injured = string_to_int(mtr_inj);
            num_of_motorists_killed = string_to_int(mtr_kld);
            
            latitude = (!l1.empty() ? stof(l1) : 0.0f);
            longitude = (!l2.empty() ? stof(l2) : 0.0f);
        }

        // AI-generated section start
        friend ostream& operator<<(ostream& os, const Collision& collision) {
            os << "Collision ID: " << collision.collision_id << "\n"
               << "Crash Date: " << collision.crash_date << "\n"
               << "Crash Time: " << collision.crash_time << "\n"
               << "Borough: " << collision.borough << "\n"
               << "ZIP Code: " << collision.zip_code << "\n"
               << "Latitude: " << collision.latitude << "\n"
               << "Longitude: " << collision.longitude << "\n"
               << "On Street: " << collision.on_street_name << "\n"
               << "Cross Street: " << collision.cross_street_name << "\n"
               << "Off Street: " << collision.off_street_name << "\n"
               << "Persons Injured: " << collision.num_of_persons_injured << "\n"
               << "Persons Killed: " << collision.num_of_persons_killed << "\n"
               << "Pedestrians Injured: " << collision.num_of_pedestrians_injured << "\n"
               << "Pedestrians Killed: " << collision.num_of_pedestrians_killed << "\n"
               << "Cyclists Injured: " << collision.num_of_cyclists_injured << "\n"
               << "Cyclists Killed: " << collision.num_of_cyclists_killed << "\n"
               << "Motorists Injured: " << collision.num_of_motorists_injured << "\n"
               << "Motorists Killed: " << collision.num_of_motorists_killed << "\n"
               << "Contributing Factors: [" 
               << collision.contributing_factor_vehicle1 << ", "
               << collision.contributing_factor_vehicle2 << ", "
               << collision.contributing_factor_vehicle3 << ", "
               << collision.contributing_factor_vehicle4 << ", "
               << collision.contributing_factor_vehicle5 << "]\n"    
               << "Vehicle Types: [" 
               << collision.vehicle_type_code1 << ", "
               << collision.vehicle_type_code2 << ", "
               << collision.vehicle_type_code3 << ", "
               << collision.vehicle_type_code4 << ", "
               << collision.vehicle_type_code5 << "]\n";
    
            return os;
        }
        
        string get_collision_id() const { return collision_id; }

        int get_crash_date() const { return crash_date; }
        int get_crash_time() const { return crash_time; }

        string get_borough() const { return borough; }
        int get_zip_code() const { return zip_code; }
        float get_latitude() const { return latitude; }
        float get_longitude() const { return longitude; }

        string get_on_street_name() const { return on_street_name; }
        string get_cross_street_name() const { return cross_street_name; }
        string get_off_street_name() const { return off_street_name; }

        int get_num_of_persons_injured() const { return num_of_persons_injured; }
        int get_num_of_persons_killed() const { return num_of_persons_killed; }
        int get_num_of_pedestrians_injured() const { return num_of_pedestrians_injured; }
        int get_num_of_pedestrians_killed() const { return num_of_pedestrians_killed; }
        int get_num_of_cyclists_injured() const { return num_of_cyclists_injured; }
        int get_num_of_cyclists_killed() const { return num_of_cyclists_killed; }
        int get_num_of_motorists_injured() const { return num_of_motorists_injured; }
        int get_num_of_motorists_killed() const { return num_of_motorists_killed; }

        string get_contributing_factor_vehicle1() const { return contributing_factor_vehicle1; }
        string get_contributing_factor_vehicle2() const { return contributing_factor_vehicle2; }
        string get_contributing_factor_vehicle3() const { return contributing_factor_vehicle3; }
        string get_contributing_factor_vehicle4() const { return contributing_factor_vehicle4; }
        string get_contributing_factor_vehicle5() const { return contributing_factor_vehicle5; }

        string get_vehicle_type_code1() const { return vehicle_type_code1; }
        string get_vehicle_type_code2() const { return vehicle_type_code2; }
        string get_vehicle_type_code3() const { return vehicle_type_code3; }
        string get_vehicle_type_code4() const { return vehicle_type_code4; }
        string get_vehicle_type_code5() const { return vehicle_type_code5; }
        // AI-generated section end

};

#endif