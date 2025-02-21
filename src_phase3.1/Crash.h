#ifndef CRASH_H
#define CRASH_H

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

class Crash {
    public:
        Crash() {}

        void add_record(string id, string cd, string b, string inj_p, string kld_p) {
            collision_id.emplace_back(trim_string(id));
            crash_date.emplace_back(trim_string(cd));
            borough.emplace_back(trim_string(b));
            person_injured.emplace_back(string_to_int(inj_p));
            person_killed.emplace_back(string_to_int(kld_p));
        }

        size_t get_size() {
            return borough.size();
        }

        string get_collision_id(int idx) {
            return collision_id[idx];
        }

        string get_crash_date(int idx) {
            return crash_date[idx];
        }
        
        string get_borough(int idx) {
            return borough[idx];
        }

        int get_person_injured(int idx) {
            return person_injured[idx];
        }

        int get_person_killed(int idx) {
            return person_killed[idx];
        }

        vector<string>& get_collision_id() {
            return collision_id;
        }

        vector<string>& get_crash_date() {
            return crash_date;
        }
        
        vector<string>& get_borough() {
            return borough;
        }

        vector<int>& get_person_injured() {
            return person_injured;
        }

        vector<int>& get_person_killed() {
            return person_killed;
        }
    
    private:
        vector<string> collision_id;
        vector<string> crash_date;
        vector<string> borough;
        vector<int> person_injured;
        vector<int> person_killed;

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
};

#endif