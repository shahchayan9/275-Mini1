#ifndef COLLISIONDATASET_H
#define COLLISIONDATASET_H

#include <vector>
#include "Collision.h"

using namespace std;

class CollisionDataset {
    private:
        vector<Collision> collisions;
    
    public:
        void load_CSV(string filename);
        vector<Collision> search_by_zip_code(int zc);
        vector<Collision> search_by_injury_ranges(int inj_low, int inj_high);
        vector<Collision> search_by_latitude(float lat);
        vector<Collision> search_by_date_range(string start_date, string end_date);
        vector<Collision> search_by_borough(string b);

        vector<Collision> get_collisions() {
            return collisions;
        }

        int format_date(string date) {
            if (collisions.size() == 0)
                return 0;
            
            return collisions[0].format_date(date);
        }

};

#endif