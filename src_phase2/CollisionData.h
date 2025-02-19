#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#include <string>

class CollisionData {
public:
    std::string collision_id;
    std::string date;
    std::string borough;
    int persons_injured;
    int persons_killed;

    // Constructor
    CollisionData(std::string id, std::string dt, std::string b, int injured, int killed)
        : collision_id(id), date(dt), borough(b), persons_injured(injured), persons_killed(killed) {}
};

#endif
