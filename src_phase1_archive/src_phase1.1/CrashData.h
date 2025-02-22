#ifndef CRASHDATA_H
#define CRASHDATA_H

#include <string>
#include <vector>
#include "Crash.h"

using namespace std;

class CrashData {
    public:
        void loadCrashDataFromCSV(string filename);
        vector<Crash> searchByBorough(string borough);
        vector<Crash> searchByThreshold(int injury_threshold, int killed_threshold);
        
        vector<Crash> getCrashes() {
            return crashes;
        }

    private:
        vector<Crash> crashes;
};

#endif