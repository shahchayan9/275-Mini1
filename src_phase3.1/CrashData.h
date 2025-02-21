#ifndef CRASHDATA_H
#define CRASHDATA_H

#include <string>
#include <vector>
#include "Crash.h"

using namespace std;

class CrashData {
    public:
        void loadCrashDataFromCSV(string filename);
        vector<int> searchByBorough(string borough);
        vector<int> searchByThreshold(int injury_threshold, int killed_threshold);
        
        Crash get_crashes() {
            return crashes;
        }

    private:
        Crash crashes;
};

#endif