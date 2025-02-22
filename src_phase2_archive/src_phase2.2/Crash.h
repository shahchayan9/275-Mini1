#ifndef CRASH_H
#define CRASH_H

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

class Crash {
    public:
        Crash(string id, string cd, string b, string inj_p, string kld_p) {
            collision_id = trim_string(id);
            crash_date = trim_string(cd);
            borough = trim_string(b);
            person_injured = string_to_int(inj_p);
            person_killed = string_to_int(kld_p);
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
        string borough;
        int person_injured;
        int person_killed;

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