//
// Created by sounteg on 12. 5. 2020.
//

#ifndef BP_GENERATED_DATA_H
#define BP_GENERATED_DATA_H
#include <utility>
#include <ctime>

using namespace std;

class generated_data {
public:
    generated_data();

    virtual ~generated_data();

    int getRandomSensorData();

    time_t getTimestamp();
};

#endif //BP_GENERATED_DATA_H
