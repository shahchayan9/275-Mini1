#ifndef DATALOADER_H
#define DATALOADER_H

#include <vector>
#include <string>
#include "CollisionData.h"

class DataLoader {
public:
    static std::vector<CollisionData> loadCSV(const std::string& filename);
};

#endif
