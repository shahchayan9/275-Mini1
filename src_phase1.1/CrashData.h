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
        vector<Crash> searchByInjuryThreshold(int injury_threshold);

    private:
        vector<Crash> crashes;
};

#endif